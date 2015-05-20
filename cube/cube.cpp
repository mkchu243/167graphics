#include "Cube.h"
#include "Matrix4.h"

using namespace std;

Cube::Cube() : translations(0,0,0), color(0,1,0), scale(1,1,1)
{
  reset();
}

Matrix4& Cube::getMatrix()
{
  Matrix4 currentRotationZ;
  currentRotationZ.makeRotateAxis(angleZ, 0, 0, 1);
  Matrix4 scaleMat = Matrix4::makeScaling(scale.getX(), scale.getY(), scale.getZ());
  Matrix4 translationMatrix = Matrix4::makeTranslation(translations.getX(), translations.getY(), translations.getZ());
  return currentRotationZ.multiply(translationMatrix.multiply(scaleMat.multiply(currentRotationY)));
}

void Cube::reset()
{
  angleZ = 0.0;
  angleY = 0.0;
  translations.set(0,0,0);
  scale.set(1,1,1);
  color.set(0,1,0);
  reverseAngle = false;
}

void Cube::idle()
{
  spin(1.0);
}

void Cube::spin(double deg)   // deg is in degrees
{
  if(reverseAngle){
    angleY -= deg;
  }
  else {
    angleY += deg;
  }
  if (angleY > 360.0 || angleY < -360.0) angleY = 0.0;
  currentRotationY.makeRotateY(angleY);   // This creates the matrix to rotate the cube
}

void Cube::glutKeyboardFunc(unsigned char key, int x, int y)
{
  switch(key)
  {
  case 'w':
    translations = translations + Vector3(0, 1, 0);
    translations.print();
    break;
  case 'a':
    translations = translations + Vector3(-1, 0, 0);
    translations.print();
    break;
  case 's':
    translations = translations + Vector3(0, -1, 0);
    translations.print();
    break;
  case 'd':
    translations = translations + Vector3(1, 0, 0);
    translations.print();
    break;
  case 'z':
    translations = translations + Vector3(0, 0, 1);
    translations.print();
    break;
  case 'Z':
    translations = translations + Vector3(0, 0, -1);
    translations.print();
    break;
  case 'q':
    scale.scale(1.25);
    break;
  case 'e':
    scale.scale(.75);
    break;
  case 'x':
    angleZ += 10;
    break;
  case 'X':
    angleZ -= 10;
    break;
  case 'c':
    reverseAngle = !reverseAngle;
    break;
  case '1':
    color.set(1,0,0);
    break;
  case '2':
    color.set(0,1,0);
    break;
  case '3':
    color.set(0,0,1);
    break;
  case '4':
    color.set(1,1,0);
    break;
  case 'r':
    reset();
    break;
  }
}
