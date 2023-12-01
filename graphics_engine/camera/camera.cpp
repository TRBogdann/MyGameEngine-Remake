#include "camera.h"

Camera3f::Camera3f(Math::vec3f _position,Math::vec3f axis[3],float _fov,float _near,float _far):
position(_position),fov(_fov),near(_near),far(_far)
{
    axisFront=axis[0];
    axisUp=axis[1];
    axisRight=axis[2];
}

Camera3f::~Camera3f()
{

}

void Camera3f::move(Math::vec3f dir)
{
    Math::translate3F(this->position,dir.x,dir.y,dir.z);
}

void Camera3f::moveRight(float units)
{
    this->position+=units*this->axisRight;
}
void Camera3f::moveUp(float units)
{
    this->position+=units*this->axisUp;
}
void Camera3f::moveFront(float units)
{
    this->position+=units*this->axisFront;
}

void Camera3f::rotate(Math::vec3f axis, float angle)
{
    axis.x=-axis.x;
    Math::rotate3F(this->axisFront,axis,angle);
    Math::rotate3F(this->axisUp,axis,angle);
    Math::rotate3F(this->axisRight,axis,angle);

}


Camera3d::Camera3d(Math::vec3d _position,Math::vec3d axis[3],double _fov,double _near ,double _far):
position(_position),fov(_fov),near(_near),far(_far)
{
    axisFront=axis[0];
    axisUp=axis[1];
    axisRight=axis[2];
}

Camera3d::~Camera3d()
{
    
}

void Camera3d::move(Math::vec3d dir)
{
    Math::translate3D(this->position,dir.x,dir.y,dir.z);
}

void Camera3d::rotate(Math::vec3d axis, double angle)
{
    axis.x=-axis.x;
    Math::rotate3D(this->axisFront,axis,angle);
    Math::rotate3D(this->axisUp,axis,angle);
    Math::rotate3D(this->axisRight,axis,angle);
}
void Camera3d::moveRight(float units)
{
    this->position+=units*this->axisRight;
}
void Camera3d::moveUp(float units)
{
    this->position+=units*this->axisUp;
}
void Camera3d::moveFront(float units)
{
    this->position+=units*this->axisFront;
}
