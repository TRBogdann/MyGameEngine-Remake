#include "brain_triangles.h"
#include "glm/glm.hpp"
#include "graphics_engine/buffers/buffers.h"
#include "graphics_engine/graphics_engine.h"
#include "graphics_engine/renderer/renderer.h"
#include "graphics_engine/shaders/shader.h"
#include "graphics_engine/texture/texture.h"
#include "math_engine/math.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

glm::mat4 GetViewMatrix(const Camera3f &cam) {
  glm::vec3 eye = glm::vec3(cam.position.x, cam.position.y, cam.position.z);
  glm::vec3 front =
      glm::vec3(cam.axisFront.x, cam.axisFront.y, cam.axisFront.z);
  glm::vec3 up = glm::vec3(cam.axisUp.x, cam.axisUp.y, cam.axisUp.z);

  return glm::lookAt(eye, eye + front, up);
}

glm::mat4 GetProjectionMatrix(const Camera3f &cam, float aspectRatio) {
  return glm::perspective(glm::radians(cam.fov), aspectRatio, cam.near,
                          cam.far);
}

// --- Camera movement and rotation free functions ---

void rotateCamera(Camera3f &cam, const Math::vec3f &axis, float angleDeg) {
  float angleRad = glm::radians(angleDeg);

  glm::vec3 front(cam.axisFront.x, cam.axisFront.y, cam.axisFront.z);
  glm::vec3 up(cam.axisUp.x, cam.axisUp.y, cam.axisUp.z);
  glm::vec3 rotationAxis(axis.x, axis.y, axis.z);

  glm::mat4 rot = glm::rotate(glm::mat4(1.0f), angleRad, rotationAxis);

  glm::vec3 newFront = glm::normalize(glm::vec3(rot * glm::vec4(front, 0.0f)));
  glm::vec3 newUp = glm::normalize(glm::vec3(rot * glm::vec4(up, 0.0f)));
  glm::vec3 newRight = glm::normalize(glm::cross(newFront, newUp));
  newUp = glm::normalize(glm::cross(newRight, newFront));

  cam.axisFront = {newFront.x, newFront.y, newFront.z};
  cam.axisUp = {newUp.x, newUp.y, newUp.z};
}

void moveCameraFront(Camera3f &cam, float delta) {
  cam.position += cam.axisFront * delta;
}

void moveCameraRight(Camera3f &cam, float delta) {
  glm::vec3 front(cam.axisFront.x, cam.axisFront.y, cam.axisFront.z);
  glm::vec3 up(cam.axisUp.x, cam.axisUp.y, cam.axisUp.z);
  glm::vec3 right = glm::normalize(glm::cross(front, up));

  cam.position += Math::vec3f{right.x, right.y, right.z} * delta;
}

void moveCameraUp(Camera3f &cam, float delta) {
  cam.position += cam.axisUp * delta;
}

int main() {
  // brainData
// Total vertices: 662136
// Total triangles: 220712

  unsigned int *indCube = new unsigned int[662136];

  for (int i = 0; i < 662136; i++) {
    indCube[i] = i;
  }

  Program program;
  program.start();
  Window window("MyWindow", 800, 800);
  program.useWindow(window);
  Event event;
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  Math::vec3f axis[3] = {
      {0.0f, 0.0f, 1.0f},
      {0.0f, 1.0f, 0.0f},
      {1.0f, 0.0f, 0.0f},
  };

  Camera3f cam({0.0f, 0.0f, 0.0f}, axis, 90.0f, 5.0f, 1000.0f);
  if (program.CheckForError())
    return 1;

  window.setColor(0, 100, 100, 255);
  Renderer renderer;

  graphicalAtribute *colAtributes = new graphicalAtribute[2];
  colAtributes[0].name = "Vertecies";
  colAtributes[0].size = 3;
  colAtributes[1].name = "Color";
  colAtributes[1].size = 4;

  Shader *colShader = ClippingObjectSpaceShader();

  glm::vec3 modelPosition = glm::vec3(0.0f, 0.0f, 40.0f);
  glm::vec3 modelScale = glm::vec3(10.0f, 10.0f, 10.0f);

  glm::mat4 model = glm::translate(glm::mat4(1.0f), modelPosition);
  model = glm::scale(model, modelScale);

  glm::mat4 view = GetViewMatrix(cam);
  glm::mat4 projection = GetProjectionMatrix(cam, 16.0f / 9.0f);

  colShader->bind();
  colShader->setUniformMat4("model", model);
  colShader->setUniformMat4("view", view);
  colShader->setUniformMat4("projection", projection);
  colShader->setUniform4f("mnPoz", -1.0, -1.0, -1.0, 0);
  colShader->setUniform4f("mxPoz", 1.0, 1.0, 1.0, 0);
  VertexArray arr(7 * sizeof(float));
  arr.bind();
  VertexBuffer buff(brainData, 662136 * 7 * sizeof(float));
  arr.addData(buff, colAtributes, 2);
  IndexBuffer ind(indCube, 662136);
  ind.bind();
  colShader->bind();
  Texture t("wall.jpg", 0, 0);
  t.bind();

  while (!window.isClosed()) {
    renderer.clear();
    window.clear();

    float ar = float(window.getHeight()) / float(window.getWidth());

    window.pollEvents(event);
    if (event.type == KEYBOARD_EVENT) {
      if (event.key.action == KEY_REPEAT) {
        switch (event.key.keysym.key) {
        case KEY_A:
          moveCameraRight(cam, -1.0f);
          break;
        case KEY_D:
          moveCameraRight(cam, 1.0f);
          break;
        case KEY_W:
          moveCameraFront(cam, 1.0f);
          break;
        case KEY_S:
          moveCameraFront(cam, -1.0f);
          break;
        case KEY_SPACE:
          moveCameraUp(cam, 1.0f);
          break;
        case KEY_BACKSPACE:
          moveCameraUp(cam, -1.0f);
          break;

        case KEY_UP:
          rotateCamera(cam, {1.0f, 0.0f, 0.0f}, 1.0f);
          break;
        case KEY_DOWN:
          rotateCamera(cam, {1.0f, 0.0f, 0.0f}, -1.0f);
          break;
        case KEY_LEFT:
          rotateCamera(cam, {0.0f, 1.0f, 0.0f}, -1.0f);
          break;
        case KEY_RIGHT:
          rotateCamera(cam, {0.0f, 1.0f, 0.0f}, 1.0f);
          break;
        case KEY_K:
          rotateCamera(cam, {0.0f, 0.0f, 1.0f}, -1.0f);
          break;
        case KEY_L:
          rotateCamera(cam, {0.0f, 0.0f, 1.0f}, 1.0f);
          break;
        }
      }
    }

    model = glm::translate(glm::mat4(1.0f), modelPosition);
    model = glm::scale(model, modelScale);
    view = GetViewMatrix(cam);
    projection = GetProjectionMatrix(cam, ar);

    colShader->bind();
    colShader->setUniformMat4("model", model);
    colShader->setUniformMat4("view", view);
    colShader->setUniformMat4("projection", projection);
    // colShader->setUniform4f("mnPoz", -0.2, -1.0, -1.0, 0);
    // colShader->setUniform4f("mxPoz", 0.2, 1.0, 1.0, 0);

    renderer.drawType1(arr, ind, *colShader);
    window.swap();
  }

  program.terminate();
  return 0;
}
