#include "graphics_engine/buffers/buffers.h"
#include "graphics_engine/graphics_engine.h"
#include "graphics_engine/renderer/renderer.h"
#include "graphics_engine/shaders/shader.h"
#include "graphics_engine/texture/texture.h"
#include "math_engine/math.h"
#include <iostream>

int main()
{   


float data[216]={
 -0.5f, -0.5f, -0.5f,1.0f, 0.0f, 0.0f,
0.5f, -0.5f, -0.5f,1.0f,1.0f, 0.0f,
0.5f, 0.5f, -0.5f,1.0f, 1.0f, 1.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f,1.0f,  0.0f, 0.0f,

-0.5f, -0.5f, 0.5f,1.0f,  0.0f, 0.0f,
0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f,1.0f,  1.0f, 0.0f,

0.5f, 0.5f, 0.5f,1.0f,  1.0f, 0.0f,
0.5f, 0.5f, -0.5f,1.0f,  1.0f, 1.0f,
0.5f, -0.5f, -0.5f,1.0f,  0.0f, 1.0f,
0.5f, -0.5f, -0.5f,1.0f,  0.0f, 1.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,

-0.5f, -0.5f, -0.5f,1.0f,  0.0f, 1.0f,
0.5f, -0.5f, -0.5f,1.0f,  1.0f, 1.0f,
0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
0.5f, -0.5f, 0.5f,1.0f,  1.0f, 0.0f,
-0.5f, -0.5f, 0.5f,1.0f,  0.0f, 0.0f,
-0.5f, -0.5f, -0.5f,1.0f,  0.0f, 1.0f,

-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
-0.5f, 0.5f, 0.5f,1.0f,  0.0f, 0.0f,
-0.5f, 0.5f, -0.5f,1.0f,  0.0f, 1.0f
};

    Math::vec4f cubeData[36];
    Math::vec4f TextureCorrection[36];

    unsigned int indCube[108];

    for(int i=0;i<108;i++)
    {
        indCube[i]=i;
    }

        for(int i=0;i<36;i++)
    {
        cubeData[i].x=data[i*6];
        cubeData[i].y=data[i*6+1];
        cubeData[i].z=data[i*6+2];
        cubeData[i].w=1.0f;
        TextureCorrection[i].x=data[i*6+4];
        TextureCorrection[i].y=data[i*6+5];
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
    glHint (GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

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
        //TextureCorrection[i]=utils::model3F({TextureCorrection[i].x,TextureCorrection[i].y,0.0f},{0.0f,0.0f,0.0f},{10.0f,10.0f,10.0f});
        origin+={cubeData[i].x,cubeData[i].y,cubeData[i].z};
    }

    origin/=36.0f;





    if(program.CheckForError())return 1;

     window.setColor(0,100,100,255);


    Renderer renderer;

    graphicalAtribute *texAtributes=TexPersAtrib();
    Shader *texShader=TexShader();

    VertexArray arr(6*sizeof(float));
    arr.bind();
    VertexBuffer buff(data,216*sizeof(float));
    arr.addData(buff, texAtributes,2);
    IndexBuffer ind(indCube,108);
    ind.bind();
    texShader->bind();
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
        float u=TextureCorrection[i].x;
        float v=TextureCorrection[i].y;
        float w=1.0f;

        //Math::vec4f viewdTexture=utils::view3F({TextureCorrection[i].x,TextureCorrection[i].y,0.0f},cam);
        Math::vec4f view=utils::view3F({cubeData[i].x,cubeData[i].y,cubeData[i].z},cam);
        Math::vec4f projed=utils::perspProjection3F({view.x,view.y,view.z},cam,ar);
        
        //projed=utils::normalize4F(projed);
        data[i*6]=projed.x;
        data[i*6+1]=projed.y;
        data[i*6+2]=projed.z;
        data[i*6+3]=projed.w;
        data[i*6+4]=u;
        data[i*6+5]=v;
     
    }

    buff.update(data,216*sizeof(float));



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
       renderer.drawType1(arr,ind,*texShader);
        window.swap();
    }
    

    program.terminate();
}
