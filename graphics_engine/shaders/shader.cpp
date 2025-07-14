#include "GL/glew.h"
#include "shader.h"
#include <iostream>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


 std::string FileToString(const std::ifstream &file)
{ 
  std::stringstream buffer;

  buffer << file.rdbuf();

  std::string str = buffer.str();

  return str;
  
}


 unsigned int ShaderCompiler(const std::string &source , unsigned int type )
{
   unsigned int id =glCreateShader(type);
   const char* src=source.c_str();
   glShaderSource(id,1,&src,nullptr);
   glCompileShader(id);


    //Verificare erori
  int status;
  glGetShaderiv(id,GL_COMPILE_STATUS,&status);
    if(status == GL_FALSE)
    {
    
        int message_lenght;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH, &message_lenght);
        char* message = (char*)alloca(message_lenght * sizeof(char)); 
        std::cout<<"Failed to compile shader"<<'\n'; 
        std::cout<<message<<'\n';
        std::cout<<source;
        glDeleteShader(id);
        
        return 0;
    }


   return id;
}


 Shader::Shader(const std::string &vertexShader ,const std::string &fragmentShader)
{

 rendererId=glCreateProgram();

_vertexShader=vertexShader;
_fragmentShader=fragmentShader;

 unsigned int vshader= ShaderCompiler(vertexShader, GL_VERTEX_SHADER);
 unsigned int fshader= ShaderCompiler(fragmentShader, GL_FRAGMENT_SHADER);

 glAttachShader(rendererId,vshader);
 glAttachShader(rendererId,fshader);

 glLinkProgram(rendererId);
 glValidateProgram(rendererId);

 glDeleteShader(vshader);
 glDeleteShader(fshader);

};

Shader::~Shader()
{
 
}

void Shader::bind()
{
  glUseProgram(rendererId);
}

void Shader::unbind()
{
  glUseProgram(0);
}

void Shader::setUniform4f(std::string name,float r , float g, float b, float a)
{
    glUniform4f((findUniform(name)),r,g,b,a);
}

void Shader::setUniform1f(std::string name,float slot)
{
    glUniform1f((findUniform(name)),slot);
}

void Shader::setUniform1i(std::string name,int slot)
{
    glUniform1i((findUniform(name)),slot);
}

void Shader::setUniformMat4(std::string name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(findUniform(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

unsigned int Shader::findUniform(std::string name)
{
   int location = glGetUniformLocation(rendererId,name.c_str());
   if(location==-1)
   {
    std::cerr<<"\n[ERROR]: Invalid uniform location";
   }

   return location;

}

Shader* ColShader()
{

std::string vertexShader=" #version 450 core \n layout(location = 0) in vec4 aPos; \n layout (location = 1) in vec4 aColor; \n out vec4 ourColor; \n void main() \n { \n  gl_Position = aPos; \n ourColor = aColor; \n } ";
std::string fragmentShader=" #version 450 core \n out vec4 FragColor; \n in vec4 ourColor; \n void main() \n { \n FragColor = ourColor; \n } ";

Shader *sh = new Shader(vertexShader,fragmentShader);

return sh;

}

Shader* TexShader()
{
  

std::string vertexShader=" #version 450 core \n layout(location = 0)  in vec4 aPos; \n  layout (location = 1) in vec2 texCoord; \n out vec2 fragTexCoord;\n void main()\n { \n gl_Position = aPos; \n fragTexCoord = texCoord; \n } ";
std::string fragmentShader=" #version 450 core \n uniform sampler2D textureSampler;\n in vec2 fragTexCoord; \n out vec4 FragColor; \n void main() \n { \n FragColor = texture(textureSampler, fragTexCoord); \n } ";

Shader *sh = new Shader(vertexShader,fragmentShader);

return sh;

}

Shader* TexPersShader()
{
  

std::string vertexShader=" #version 450 core \n layout(location = 0)  in vec4 aPos; \n  layout (location = 1) in vec2 texCoord; \n out vec2 fragTexCoord;\n void main()\n { \n gl_Position = aPos; \n gl_Position.w=1; \n fragTexCoord = texCoord/aPos.w; \n } ";
std::string fragmentShader=" #version 450 core \n uniform sampler2D textureSampler;\n in vec2 fragTexCoord; \n out vec4 FragColor; \n void main() \n { \n FragColor = texture(textureSampler, fragTexCoord); \n } ";

Shader *sh = new Shader(vertexShader,fragmentShader);

return sh;

}

Shader* ColMVPShader()
{
    std::string vertexShader = R"( 
        #version 450 core

        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec4 aColor;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        out vec4 ourColor;

        void main()
        {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
            ourColor = aColor;
        }
    )";

    std::string fragmentShader = R"( 
        #version 450 core

        in vec4 ourColor;
        out vec4 FragColor;

        void main()
        {
            FragColor = ourColor;
        }
    )";

    return new Shader(vertexShader, fragmentShader);
}

Shader* ClippingObjectSpaceShader()
{
    std::string vertexShader = R"( 
        #version 450 core

        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec4 aColor;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        uniform vec4 mxPoz;
        uniform vec4 mnPoz;

        out vec4 ourColor;
        out float clipMe;

        void main()
        {

            clipMe = 0.0;
            if (aPos.x < mnPoz.x || aPos.x > mxPoz.x ||
                aPos.y < mnPoz.y || aPos.y > mxPoz.y ||
                aPos.z < mnPoz.z || aPos.z > mxPoz.z)
            {
                clipMe = 1.0;
            }

            gl_Position = projection * view * model * vec4(aPos, 1.0);
            ourColor = aColor;
        }
    )";

    std::string fragmentShader = R"( 
        #version 450 core

        in vec4 ourColor;
        in float clipMe;

        out vec4 FragColor;

        void main()
        {
            if (clipMe > 0.5)
                discard;

            FragColor = ourColor;
        }
    )";

    return new Shader(vertexShader, fragmentShader);
}
