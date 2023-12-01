#include "../../math_engine/math.h"

class Camera3f
{
public:
Camera3f(Math::vec3f _position,Math::vec3f axis[3],float _fov,float _near,float _far);
~Camera3f();

void move(Math::vec3f dir);
void moveRight(float units);
void moveUp(float units);
void moveFront(float units);
void rotate(Math::vec3f axis, float angle);

Math::vec3f position;
Math::vec3f axisUp;
Math::vec3f axisRight;
Math::vec3f axisFront;
float fov;
float near;
float far;

private:
};

class Camera3d
{
public:
Camera3d(Math::vec3d _position,Math::vec3d axis[3],double _fov,double _near ,double _far);
~Camera3d();

void move(Math::vec3d dir);
void moveRight(float units);
void moveUp(float units);
void moveFront(float units);
void rotate(Math::vec3d axis, double angle);

Math::vec3d position;
Math::vec3d axisUp;
Math::vec3d axisRight;
Math::vec3d axisFront;
double fov;
double near;
double far;
private:

};