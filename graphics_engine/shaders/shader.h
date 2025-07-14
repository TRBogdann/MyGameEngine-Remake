#pragma once
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <ostream>
#include <string>
#include "glm/glm.hpp"

unsigned int ShaderCompiler(const std::string &source , unsigned int type );

class Shader
{

public:
unsigned int rendererId;

Shader(const std::string &vertexShader ,const std::string &fragmentShader);
~Shader();


void bind();
void unbind();

void setUniformMat4(std::string name, const glm::mat4& matrix);
void setUniform4f(std::string name, float r , float g , float b, float a);
void setUniform1i(std::string name, int slot);
void setUniform1f(std::string name, float slot);


private:

unsigned int findUniform(std::string name);
std::string _fragmentShader;
std::string _vertexShader;

};

std::string FileToString(const std::ifstream &file);

Shader* ColMVPShader();
Shader* ColShader();
Shader* TexShader();
Shader* TexPersShader();
Shader* ClippingObjectSpaceShader();


