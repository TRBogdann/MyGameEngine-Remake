#include "graphics_engine/buffers/buffers.h"
#include "graphics_engine/graphics_engine.h"
#include "graphics_engine/renderer/renderer.h"
#include "graphics_engine/shaders/shader.h"
#include "graphics_engine/texture/texture.h"
#include "math_engine/math.h"
#include <iostream>


void rotateCube(Math:: vec4f cube[36],Math::vec3f origin)
{
            for(int i=0;i<36;i++)
    {

        Math::vec3f temp={cube[i].x,cube[i].y,cube[i].z};
        temp-=origin;
        Math::rotate3F(temp,{1.0f,0.0f,0.0f},1.0f);
        temp+=origin;
        cube[i].x=temp.x;
        cube[i].y=temp.y;
        cube[i].z=temp.z;
    }
}

void projectCube(float *data,Math::vec4f cube[36],Camera3f &cam,float ar)
{
           for(int i=0;i<36;i++)
    {
        Math::vec4f view=utils::view3F({cube[i].x,cube[i].y,cube[i].z},cam);
        Math::vec4f projed=utils::perspProjection3F({view.x,view.y,view.z},cam,ar);
        
        data[i*6]=projed.x;
        data[i*6+1]=projed.y;
        data[i*6+2]=projed.z;
        data[i*6+3]=projed.w;
    }
}


void projectTerrain(float *data,Math::vec4f terrain[6],Camera3f &cam,float ar)
{
           for(int i=0;i<6;i++)
    {
        Math::vec4f view=utils::view3F({terrain[i].x,terrain[i].y,terrain[i].z},cam);
        Math::vec4f projed=utils::perspProjection3F({view.x,view.y,view.z},cam,ar);
        
        data[i*8]=projed.x;
        data[i*8+1]=projed.y;
        data[i*8+2]=projed.z;
        data[i*8+3]=projed.w;
    }
}


int main()
{   


float terrainData[48]=
{
-0.5f, -0.5f, -0.5f,1.0f,  0.3636f, 0.4135f,0.2229f,1.0f,
0.5f, -0.5f, -0.5f,1.0f,  0.3636f, 0.4135f,0.2229f,1.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.3636f, 0.4135f,0.2229f,1.0f,
0.5f, -0.5f, 0.5f,1.0f,  0.3636f, 0.4135f,0.2229f,1.0f,
-0.5f, -0.5f, 0.5f,1.0f,  0.3636f, 0.4135f,0.2229f,1.0f,
-0.5f, -0.5f, -0.5f,1.0f,  0.3636f, 0.4135f,0.2229f,1.0f
};



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

    Math::vec4f cube1[36];
    Math::vec4f cube2[36];
    Math::vec4f cube3[36];
    Math::vec4f cube4[36];
    Math::vec4f terrain[6];

    unsigned int indCube[108];
    unsigned int indTerrain[6]={0,1,2,3,4,5};

    for(int i=0;i<108;i++)
    {
        indCube[i]=i;
    }

        for(int i=0;i<36;i++)
    {
        cube1[i].x=data[i*6];
        cube1[i].y=data[i*6+1];
        cube1[i].z=data[i*6+2];
        cube1[i].w=1.0f;

        cube2[i].x=data[i*6];
        cube2[i].y=data[i*6+1];
        cube2[i].z=data[i*6+2];
        cube2[i].w=1.0f;

        cube3[i].x=data[i*6];
        cube3[i].y=data[i*6+1];
        cube3[i].z=data[i*6+2];
        cube3[i].w=1.0f;

        cube4[i].x=data[i*6];
        cube4[i].y=data[i*6+1];
        cube4[i].z=data[i*6+2];
        cube4[i].w=1.0f;
    }


    for(int i=0;i<6;i++)
    {
        terrain[i].x=terrainData[8*i];
        terrain[i].y=terrainData[8*i+1];
        terrain[i].z=terrainData[8*i+2];
        terrain[i].w=1.0f;
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

 

  

   // Math::vec3f origin1(0.0f,0.0f,0.0f);
    for(int i=0;i<36;i++)
    {
        cube1[i]=utils::model3F({cube1[i].x,cube1[i].y,cube1[i].z},{0.0f,0.0f,40.0f},{10.0f,10.0f,10.0f});
        cube2[i]=utils::model3F({cube2[i].x,cube2[i].y,cube2[i].z},{15.0f,0.0f,40.0f},{10.0f,10.0f,10.0f});
        cube3[i]=utils::model3F({cube3[i].x,cube3[i].y,cube3[i].z},{-15.0f,0.0f,40.0f},{10.0f,10.0f,10.0f});
        cube4[i]=utils::model3F({cube4[i].x,cube4[i].y,cube4[i].z},{30.0f,0.0f,40.0f},{10.0f,10.0f,10.0f});
        //TextureCorrection[i]=utils::model3F({TextureCorrection[i].x,TextureCorrection[i].y,0.0f},{0.0f,0.0f,0.0f},{10.0f,10.0f,10.0f});
        //origin1+={cube1[i].x,cube1[i].y,cube1[i].z};
    }

    for(int i=0;i<6;i++)
    {
         terrain[i]=utils::model3F({terrain[i].x,terrain[i].y,terrain[i].z},{0.0f,-5.1f,0.0f},{100.f,1.0f,100.0f});
    }

    //origin1/=36.0f;





    if(program.CheckForError())return 1;

     window.setColor(53,81,92,255);


    Renderer renderer;

    graphicalAtribute *texAtributes=TexPersAtrib();
    Shader *texShader=TexShader();
    graphicalAtribute *colAtributes=ColPersAtrib();
    Shader *colShader=ColShader();

    VertexArray terrainArr(8*sizeof(float));
    terrainArr.bind();
    VertexBuffer terrainBuff(terrainData,48*sizeof(float));
    terrainArr.addData(terrainBuff, colAtributes,2);
    IndexBuffer terraInd(indTerrain,6);
    terraInd.bind();

    VertexArray arr(6*sizeof(float));
    arr.bind();
    VertexBuffer buff(data,216*sizeof(float));
    arr.addData(buff, texAtributes,2);
    IndexBuffer ind(indCube,108);
    ind.bind();
    texShader->bind();
    Texture t4("crate.png",0,0);
    t4.bind();


    while(!window.isClosed())
    {
       renderer.clear();
       window.clear();



   //rotateCube(cube1,{0.0f,0.0f,40.0f});
   //rotateCube(cube2,{15.0f,0.0f,40.0f});
   //rotateCube(cube3,{-15.0f,0.0f,40.0f});
   //rotateCube(cube4,{30.0f,0.0f,40.0f});

    float ar=float(window.getHeight())/float(window.getWidth());

    projectTerrain(terrainData,terrain, cam,ar);
    terrainBuff.update(terrainData,46*sizeof(float));
    renderer.drawType1(terrainArr,terraInd,*colShader);

    projectCube(data,cube1,cam,ar);
    buff.update(data,216*sizeof(float));
    renderer.drawType1(arr,ind,*texShader);


    projectCube(data,cube2,cam,ar);
    buff.update(data,216*sizeof(float));
    renderer.drawType1(arr,ind,*texShader);


    projectCube(data,cube3,cam,ar);

    buff.update(data,216*sizeof(float));
    renderer.drawType1(arr,ind,*texShader);

    projectCube(data,cube4,cam,ar);
    t4.bind();
    buff.update(data,216*sizeof(float));
    renderer.drawType1(arr,ind,*texShader);

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
        window.swap();
    }
    


    program.terminate();
}
