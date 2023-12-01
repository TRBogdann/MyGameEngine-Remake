#include "texture.h"
#include <SDL2/SDL_surface.h>
#include <cstddef>
#include <iostream>


#define STB_IMAGE_IMPLEMENTATION
#include "../thirdParties/stb_image.h"

Texture::Texture(const std::string filename,bool keepLocalData,bool useOpacity)
:rendererId(0),filePath(filename),pixelBuffer(nullptr),width(0),height(0),density(0),opacity(useOpacity)
{  
    
    void* pixels=stbi_load(filePath.c_str(), &width, &height,
&density, 0);

    if(keepLocalData)pixelBuffer=pixels;
   

    glGenTextures(1,&rendererId);
    glBindTexture(GL_TEXTURE_2D,rendererId);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    

    if(!opacity){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB ,width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
    }

    else {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
    }


    if(pixels)
    {
        stbi_image_free(pixels);
    }

}

Texture::~Texture()
{
    glDeleteTextures(1,&rendererId);
}

void Texture::bind(unsigned int slot)
{   
    glActiveTexture(GL_TEXTURE0+slot);
    glBindTexture(GL_TEXTURE_2D,rendererId);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::getDensity()
{
    return density;
}

int Texture::getWidth()
{
    return width;
}

int Texture::getHeight()
{
    return height;
}

void Texture::enableOpacity()
{
    opacity=1;
}

void Texture::disableOpacity()
{
    opacity=0;
}