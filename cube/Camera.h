#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "vector3.h"
#include "Matrix4.h"

class Camera
{
protected:
  Matrix4 matrix;

public:
  Camera();
  Camera(Vector3& centerOfProj, Vector3& lookAtPoint, Vector3& up);
  double* getCameraMatrix();
};

#endif