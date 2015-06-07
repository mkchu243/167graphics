#include "Cube.h"
#include "Matrix4.h"
#include "objreader.h"

using namespace std;

Cube::Cube() : translations(0,0,0), color(0,1,0), scale(1,1,1), rd(), gen(rd), dis(0,1)
{
  renderCube = true;
  s_nIndices = s_nVerts = 0;
  s_vertices = nullptr;
  s_normals = nullptr;
  s_texcoords = nullptr;
  s_indices = nullptr;
  s_colors = nullptr;
  reset();
}

Matrix4& Cube::getMatrix()
{
  Matrix4 currentRotationZ;
  currentRotationZ.makeRotateAxis(angleZ, 0, 0, 1);
  Matrix4 scaleMat = Matrix4::makeScaling(scale.getX(), scale.getY(), scale.getZ());
  Matrix4 translationMatrix = Matrix4::makeTranslation(translations.getX(), translations.getY(), translations.getZ());
  model2world = currentRotationZ.multiply(translationMatrix.multiply(scaleMat.multiply(currentRotationY)));
  return model2world;
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

void Cube::glutSpecialFunc(int key, int x, int y)
{
  switch(key)
  {
    case 1: //F1
      setShape("teapot.obj");
      break;
    case 2:
      setShape("sphere.obj");
      break;
   case 3:
      setShape("teddy.obj");
      break;
   case 4:
      setShape("cow.obj");
      break;
   case 5:
      setShape("bunny.obj");
      break;
   case 6:
      renderCube = true;
      break;
  }
}

void Cube::setShape(std::string objPath)
{
    delete s_colors;
    delete s_vertices;
    delete s_normals;
    delete s_texcoords;
    delete s_indices;

    renderCube = false;
    ObjReader::readObj((char *)objPath.c_str(), s_nVerts, &s_vertices, &s_normals, &s_texcoords, s_nIndices, &s_indices);
    s_colors = new float[s_nVerts*3];
    //std::cout << "size " <<  s_nVerts * 3 << std::endl;
    for(int i = 0, index = 0; i < s_nVerts; i+=3, index+=9)
    {
      s_colors[index] = s_colors[index+3] = s_colors[index+6] = (float)dis(gen);
      s_colors[index+1] = s_colors[index+4] = s_colors[index+7] = (float)dis(gen);
      s_colors[index+2] = s_colors[index+5] = s_colors[index+8] = (float)dis(gen);
    }
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
