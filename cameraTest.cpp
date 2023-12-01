#include "graphics_engine/buffers/buffers.h"
#include "graphics_engine/graphics_engine.h"
#include "graphics_engine/renderer/renderer.h"
#include "graphics_engine/shaders/shader.h"
#include "graphics_engine/texture/texture.h"
#include "math_engine/math.h"
#include <iostream>

int main()
{   

float colors[]=
{
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
};

float data[252]={
  -1.0f,-1.0f,-1.0f,1.0,0.0f,0.0f,1.0f,// triangle 1 : begin
    -1.0f,-1.0f, 1.0f,1.0,0.0f,0.0f,1.0f,
    -1.0f, 1.0f, 1.0f,1.0,0.0f,0.0f,1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f,1.0,0.0f,0.0f,1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,1.0,0.0f,0.0f,1.0f,
    -1.0f, 1.0f,-1.0f,1.0,0.0f,0.0f,1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,1.0,0.0f,0.0f,1.0f,
    -1.0f,-1.0f,-1.0f,1.0,0.0f,0.0f,1.0f,
    1.0f,-1.0f,-1.0f,1.0,0.0f,0.0f,1.0f,
    1.0f, 1.0f,-1.0f,1.0,0.0f,0.0f,1.0f,
    1.0f,-1.0f,-1.0f,1.0,0.0f,0.0f,1.0f,
    -1.0f,-1.0f,-1.0f,1.0,0.0f,0.0f,1.0f,
    -1.0f,-1.0f,-1.0f,1.0,0.0f,0.0f,1.0f,
    -1.0f, 1.0f, 1.0f,1.0,0.0f,0.0f,1.0f,
    -1.0f, 1.0f,-1.0f,1.0,0.0f,0.0f,1.0f,
    1.0f,-1.0f, 1.0f,1.0,0.0f,0.0f,1.0f,
    -1.0f,-1.0f, 1.0f,1.0,0.0f,0.0f,1.0f,
    -1.0f,-1.0f,-1.0f,1.0,0.0f,0.0f,1.0f,
    -1.0f, 1.0f, 1.0f,1.0,0.0f,0.0f,1.0f,
    -1.0f,-1.0f, 1.0f,1.0,0.0f,0.0f,1.0f,
    1.0f,-1.0f, 1.0f,1.0,0.0f,0.0f,1.0f,
    1.0f, 1.0f, 1.0f,1.0,0.0f,0.0f,1.0f,
    1.0f,-1.0f,-1.0f,1.0,0.0f,0.0f,1.0f,
    1.0f, 1.0f,-1.0f,1.0,0.0f,0.0f,1.0f,
    1.0f,-1.0f,-1.0f,1.0,0.0f,0.0f,1.0f,
    1.0f, 1.0f, 1.0f,1.0,0.0f,0.0f,1.0f,
    1.0f,-1.0f, 1.0f,1.0,0.0f,0.0f,1.0f,
    1.0f, 1.0f, 1.0f,1.0,0.0f,0.0f,1.0f,
    1.0f, 1.0f,-1.0f,1.0,0.0f,0.0f,1.0f,
    -1.0f, 1.0f,-1.0f,1.0,0.0f,0.0f,1.0f,
    1.0f, 1.0f, 1.0f,1.0,0.0f,0.0f,1.0f,
    -1.0f, 1.0f,-1.0f,1.0,0.0f,0.0f,1.0f,
    -1.0f, 1.0f, 1.0f,1.0,0.0f,0.0f,1.0f,
    1.0f, 1.0f, 1.0f,1.0,0.0f,0.0f,1.0f,
    -1.0f, 1.0f, 1.0f,1.0,0.0f,0.0f,1.0f,
    1.0f,-1.0f, 1.0f,1.0,0.0f,0.0f,1.0f
};

    Math::vec4f cubeData[36];

    unsigned int indCube[108];

    for(int i=0;i<108;i++)
    {
        indCube[i]=i;
    }

        for(int i=0;i<36;i++)
    {
        cubeData[i].x=data[i*7];
        cubeData[i].y=data[i*7+1];
        cubeData[i].z=data[i*7+2];
        cubeData[i].w=0.0f;
        data[i*7+3]=colors[i*3];
        data[i*7+4]=colors[i*3+1];
        data[i*7+5]=colors[i*3+2];
    }




    Program program;
    program.start();
    Window window("MyWindow",800,800);
    program.useWindow(window);
    Event event;
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    Math::vec3f axis[3]={
        {0.0f,0.0f,1.0f},
        {0.0f,1.0f,0.0f},
        {1.0f,0.0f,0.0f},
    };
   

    Camera3f cam({0.0f,0.0f,0.0f},axis,90.0f,5.0f,1000.0f);

 

  

    Math::vec3f origin(0.0f,0.0f,0.0f);
    for(int i=0;i<36;i++)
    {
        cubeData[i]=utils::model3F({cubeData[i].x,cubeData[i].y,cubeData[i].z},{0.0f,0.0f,40.0f},{10.0f,10.0f,10.0f});
        origin+={cubeData[i].x,cubeData[i].y,cubeData[i].z};
    }

    origin/=36.0f;





    if(program.CheckForError())return 1;

    window.setColor(0,100,100,255);


    Renderer renderer;

    graphicalAtribute *colAtributes=ColAtrib();
    Shader *colShader=ColShader();

    VertexArray arr(7*sizeof(float));
    arr.bind();
    VertexBuffer buff(data,252*sizeof(float));
    arr.addData(buff, colAtributes,2);
    IndexBuffer ind(indCube,108);
    ind.bind();
    colShader->bind();
    Texture t("wall.jpg",0,0);
    t.bind();


    while(!window.isClosed())
    {
       renderer.clear();
       window.clear();



        for(int i=0;i<36;i++)
    {

        Math::vec3f temp={cubeData[i].x,cubeData[i].y,cubeData[i].z};
        temp-=origin;
        Math::rotate3F(temp,{1.0f,0.0f,0.0f},1.0f);
        temp+=origin;
        cubeData[i].x=temp.x;
        cubeData[i].y=temp.y;
        cubeData[i].z=temp.z;
    }

    float ar=float(window.getHeight())/float(window.getWidth());

            for(int i=0;i<36;i++)
    {
        Math::vec4f view=utils::view3F({cubeData[i].x,cubeData[i].y,cubeData[i].z},cam);
        Math::vec4f projed=utils::perspProjection3F({view.x,view.y,view.z},cam,ar);
        projed=utils::normalize4F(projed);
        data[i*7]=projed.x;
        data[i*7+1]=projed.y;
        data[i*7+2]=projed.z;
    }

    buff.update(data,252*sizeof(float));



        window.pollEvents(event);
        if(event.type==KEYBOARD_EVENT)
        {
            if(event.key.action==KEY_REPEAT){
            if(event.key.keysym.key==KEY_A)
            {
                cam.moveRight(-1.0f);
            }
                if(event.key.keysym.key==KEY_S)
            {
                cam.moveFront(-1.0f);
            }
                if(event.key.keysym.key==KEY_W)
            {
                cam.moveFront(1.0f);
            }
                if(event.key.keysym.key==KEY_D)
            {
                cam.moveRight(1.0f);
            }
                if(event.key.keysym.key==KEY_SPACE)
            {
                cam.moveUp(1.0f);
            }
                if(event.key.keysym.key==KEY_BACKSPACE)
            {
                 cam.moveUp(-1.0f);
            }

                if(event.key.keysym.key==KEY_UP)
            {
                 cam.rotate({1.0f,0.0f,0.0f},1.0f);
            }
                if(event.key.keysym.key==KEY_DOWN)
            {
                  cam.rotate({1.0f,0.0f,0.0f},-1.0f);
            }

                if(event.key.keysym.key==KEY_LEFT)
            {
                 cam.rotate({0.0f,1.0f,0.0f},-1.0f);
            }

                if(event.key.keysym.key==KEY_RIGHT)
            {
                  cam.rotate({0.0f,1.0f,0.0f},1.0f);
            }

                if(event.key.keysym.key==KEY_K)
            {
                 cam.rotate({0.0f,0.0f,1.0f},-1.0f);
            }
            
                if(event.key.keysym.key==KEY_L)
            {
                  cam.rotate({0.0f,0.0f,1.0f},1.0f);
            }

            }


        }
       renderer.drawType1(arr,ind,*colShader);
        window.swap();
    }
    


    program.terminate();
}

