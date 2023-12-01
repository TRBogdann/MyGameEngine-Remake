#include "../../math_engine/math.h"
#include "../camera/camera.h"

namespace utils {

Math::vec3f convertToGlCoords(Math::vec3f point,float width,float height);
Math::vec3d convertToGlCoords(Math::vec3d point,float width,float height);

Math::vec3f model2F(Math::vec2f vec,Math::vec2f finalPos,Math::vec2f scale);
Math::vec3d model2D(Math::vec2d vec,Math::vec2d finalPos,Math::vec2d scale);

Math::vec4f model3F(Math::vec3f vec,Math::vec3f finalPos,Math::vec3f scale);
Math::vec4d model3D(Math::vec3d vec,Math::vec3d finalPos,Math::vec3d scale);

Math::vec4f view3F(Math::vec3f vec,Camera3f &camera);
Math::vec4d view3D(Math::vec3d vec,Camera3d &camera);

Math::vec4f orthoProjection3F(Math::vec3f vec,Camera3f &camera,float aspectRatio);
Math::vec4d orthoProjection3D(Math::vec3d vec,Camera3d &camera,double aspectRatio);

Math::vec4f perspProjection3F(Math::vec3f vec,Camera3f &camera,float aspectRatio);
Math::vec4d perspProjection3D(Math::vec3d vec,Camera3d &camera,double aspectRatio);

Math::vec4f normalize4F(Math::vec4f v);
Math::vec4d normalize4D(Math::vec4d v);

Math::vec4f clip3F();
Math::vec4d clip3D();

Math::vec4f ModelViewProj3f();
Math::vec4d ModelViewProj3d();
}