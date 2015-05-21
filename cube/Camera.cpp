#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(Vector3& centerOfProj, Vector3& lookAtPoint, Vector3& up)
{
  Vector3 zAxis = centerOfProj - lookAtPoint;
  zAxis.normalize();
  Vector3 xAxis = Vector3::crossProduct(up, zAxis);
  Vector3 yAxis = Vector3::crossProduct(zAxis, xAxis);

  matrix = Matrix4(xAxis[0], xAxis[1], xAxis[2], 0,
    yAxis[0], yAxis[1], yAxis[2], 0,
    zAxis[0], zAxis[1], zAxis[2], 0,
    lookAtPoint[0], lookAtPoint[1], lookAtPoint[2], 1);
}

double* Camera::getCameraMatrix()
{
  return matrix.getPointer();
}