#include "transformations.h"
#include <math.h>

namespace utils {

Math::vec3f convertToGlCoords(Math::vec3f point,float width,float height)
{
float ar=width/height;
point.x=point.x/width;
point.y=point.y/height;
point.x=(2*point.x-1);
point.y=(1-2*point.y);
return {point.x,point.y,point.z};
}

Math::vec3d convertToGlCoords(Math::vec3d point,float width,float height)
{
float ar=width/height;
point.x=point.x/width;
point.y=point.y/height;
point.x=(2*point.x-1);
point.y=(1-2*point.y);
return {point.x,point.y,point.z};
}

Math::vec3f model2F(Math::vec2f vec,Math::vec2f finalPos,Math::vec2f scale)
{
    Math::vec2f temp=vec;
    Math::scaleVec2F(temp,scale.x,scale.y);
    Math::translate2F(temp,finalPos.x,finalPos.y);
    return Math::vec3f(temp.x,temp.y,1.0f);
}

Math::vec3d model2D(Math::vec2d vec,Math::vec2d finalPos,Math::vec2d scale)
{
    Math::vec2d temp=vec;
    Math::scaleVec2D(temp,scale.x,scale.y);
    Math::translate2D(temp,finalPos.x,finalPos.y);
    return Math::vec3d(temp.x,temp.y,1.0f);
}

Math::vec4f model3F(Math::vec3f vec,Math::vec3f finalPos,Math::vec3f scale)
{
    Math::vec3f temp=vec;
    Math::scaleVec3F(temp,scale.x,scale.y,scale.z);
    Math::translate3F(temp,finalPos.x,finalPos.y,finalPos.z);
    return Math::vec4f(temp.x,temp.y,temp.z,1);
}
Math::vec4d model3D(Math::vec3d vec,Math::vec3d finalPos,Math::vec3d scale)
{
    Math::vec3d temp=vec;
    Math::scaleVec3D(temp,scale.x,scale.y,scale.z);
    Math::translate3D(temp,finalPos.x,finalPos.y,finalPos.z);
    return Math::vec4d(temp.x,temp.y,temp.z,1);
}

Math::vec4f orthoProjection3F(Math::vec3f vec,Camera3f &camera,float aspectRatio)
{
    float angle=Math::degreesToRad(camera.fov)/2.0f;
    float top=tanf(angle)*camera.near;
    float bottom=-top;
    float right=top*aspectRatio;
    float left=-right;

    Math::mat4f p;
    p[0][0]=2.0f/(right-left);
    p[1][1]=2.0f/(top-bottom);
    p[2][2]=-2.0f/(camera.far-camera.near);
    p[0][3]=-(right+left)/(right-left);
    p[1][3]=-(top+bottom)/(top-bottom);
    p[2][3]=-(camera.far+camera.near)/(camera.far-camera.near);
    p[3][3]=1.0f;

    return p*Math::vec4f(vec.x,vec.y,vec.z,1.0f);
}

Math::vec4d orthoProjection3D(Math::vec3d vec,Camera3d &camera,double aspectRatio)
{
    double angle=Math::degreesToRad(camera.fov)/2.0f;
    double top=tanf(angle)*camera.near;
    double bottom=-top;
    double right=+top*aspectRatio;
    double left=-right;
    Math::mat4d p;
    p[0][0]=2.0f/(right-left);
    p[1][1]=2.0f/(top-bottom);
    p[2][2]=-2.0f/(camera.far-camera.near);
    p[0][3]=-(right+left)/(right-left);
    p[1][3]=-(top+bottom)/(top-bottom);
    p[2][3]=-(camera.far+camera.near)/(camera.far-camera.near);
    p[3][3]=1.0f;

    return p*Math::vec4d(vec.x,vec.y,vec.z,1.0f);
}

Math::vec4f perspProjection3F(Math::vec3f vec,Camera3f &camera,float aspectRatio)
{
    float angle=Math::degreesToRad(camera.fov)/2.0f;
    float top=tanf(angle)*camera.near;
    float bottom=-top;
    float right=top*aspectRatio;
    float left=-right;
    
    Math::mat4f p;
    p[0][0]=2.0f*camera.near/(right-left);
    p[1][1]=2.0f*camera.near/(top-bottom);
    p[2][2]=-(camera.far+camera.near)/(camera.far-camera.near);
    p[2][3]=-(2.0f*camera.far*camera.near)/(camera.far-camera.near);
    p[0][2]=(right+left)/(right-left);
    p[1][2]=(top+bottom)/(top-bottom);
    p[3][2]=-1.0f;

    return p*Math::vec4f(vec.x,vec.y,vec.z,1.0f);
}

Math::vec4d perspProjection3D(Math::vec3d vec,Camera3d &camera,double aspectRatio)
{
    double angle=Math::degreesToRad(camera.fov)/2.0f;
    double top=tan(angle)*camera.near;
    double bottom=-top;
    double right=top*aspectRatio;
    double left=-right;
    Math::mat4d p;
    p[0][0]=2.0f*camera.near/(right-left);
    p[1][1]=2.0f*camera.near/(top-bottom);
    p[2][2]=-(camera.far+camera.near)/(camera.far-camera.near);
    p[2][3]=-(2.0f*camera.far*camera.near)/(camera.far-camera.near);
    p[0][2]=(right+left)/(right-left);
    p[1][2]=(top+bottom)/(top-bottom);
    p[3][2]=-1.0f;
   

    return p*Math::vec4d(vec.x,vec.y,vec.z,1);
}

Math::vec4f normalize4F(Math::vec4f v)
{
    return v/v.w;
}

Math::vec4d normalize4D(Math::vec4d v)
{
    return v/v.w;
}

Math::vec4f view3F(Math::vec3f vec,Camera3f &camera)
{   

    Math::mat4f v;
    v[0][0]=camera.axisRight.x;
    v[0][1]=camera.axisUp.x;
    v[0][2]=-camera.axisFront.x;

    v[1][0]=camera.axisRight.y;
    v[1][1]=camera.axisUp.y;
    v[1][2]=-camera.axisFront.y;

    v[2][0]=camera.axisRight.z;
    v[2][1]=camera.axisUp.z;
    v[2][2]=-camera.axisFront.z;

    v[0][3]=-1*camera.position*camera.axisRight;
    v[1][3]=-1*camera.position*camera.axisUp;
    v[2][3]=camera.position*camera.axisFront;

    v[3][3]=1.0f;

    return v*Math::vec4f{vec.x,vec.y,vec.z,1.0f};
    
}
Math::vec4d view3D(Math::vec3d vec,Camera3d &camera)
{   
    
    Math::mat4d v;
    v[0][0]=camera.axisRight.x;
    v[0][1]=camera.axisUp.x;
    v[0][2]=-camera.axisFront.x;

    v[1][0]=camera.axisRight.y;
    v[1][1]=camera.axisUp.y;
    v[1][2]=-camera.axisFront.y;

    v[2][0]=camera.axisRight.z;
    v[2][1]=camera.axisUp.z;
    v[2][2]=-camera.axisFront.z;

    v[0][3]=-1*camera.position*camera.axisRight;
    v[1][3]=-1*camera.position*camera.axisUp;
    v[2][3]=camera.position*camera.axisFront;

    v[3][3]=1.0f;

    return v*Math::vec4d{vec.x,vec.y,vec.z,1.0f};
}
}