#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(Vector3& centerOfProj, Vector3& lookAtPoint, Vector3& up)
{
  Vector3 zAxis = centerOfProj - lookAtPoint;
  zAxis.normalize();
  Vector3 xAxis = Vector3::crossProduct(up, zAxis);
  xAxis.normalize();
  Vector3 yAxis = Vector3::crossProduct(zAxis, xAxis);

  matrix = Matrix4(xAxis[0], yAxis[0], zAxis[0], centerOfProj[0],
    xAxis[1], yAxis[1], zAxis[1], centerOfProj[1],
    xAxis[2], yAxis[2], zAxis[2], centerOfProj[2],
    0, 0, 0, 1);
  
}


double* Camera::getCameraMatrix()
{
  return matrix.getPointer();
}