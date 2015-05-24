#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glut.h>

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "main.h"

#include "vector3.h"
#include "vector4.h"
#include "Camera.h"

using namespace std;

namespace Globals
{
  Cube cube;
  Camera camera;
};

void testVector4();
void testVector3();
void testMatrix4();

int main(int argc, char *argv[])
{
    Matrix4 matrix = Matrix4(
      5, 5, 5, 5,
      5, 6, 4, 8,
      3, 3, 5, 12,
      13, 14, 15, 16);

    std::cout << matrix.determinant();

  //Vector3 centerOfProj(-15,5,10);
  //Vector3 lookAtPoint(-5,0,0);
  //Vector3 up(0,1,0.5);

  Vector3 centerOfProj(0,10,10);
  Vector3 lookAtPoint(0,0,0);
  Vector3 up(0,1,0);
  Globals::camera = Camera(centerOfProj, lookAtPoint, up);

  float specular[]  = {1.0, 1.0, 1.0, 1.0};
  float shininess[] = {100.0};
  float position[]  = {0.0, 10.0, 1.0, 0.0};	// lightsource position
  
  glutInit(&argc, argv);      	      	      // initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitWindowSize(Window::width, Window::height);      // set initial window size
  glutCreateWindow("OpenGL Cube");    	      // open window and set window title

  glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
  glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
  glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
  glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
  glShadeModel(GL_SMOOTH);             	      // set shading to smooth
  glMatrixMode(GL_PROJECTION); 
  
  // Generate material properties:
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  
  // Generate light source:
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glDisable(GL_LIGHTING);
  // Install callback functions:
  glutDisplayFunc(Window::displayCallback);
  glutReshapeFunc(Window::reshapeCallback);
  glutIdleFunc(Window::idleCallback);
  glutKeyboardFunc(Window::glutKeyboardFunc);
  glutSpecialFunc(Window::glutSpecialFunc);
    
  // Initialize cube matrix:
  Globals::cube.getMatrix().identity();
    
  glutMainLoop();
  return 0;
}

void testMatrix4()
{
  Matrix4 m1;
  m1.identity();
  m1.print();

  Matrix4 m2(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
  m2.print();
}


void testVector4()
{
  Vector4 v1(1.1, 2.2, 3.3, 1);
  Vector4 v2(1.2, 2.4, 3.3, 0);
  v1.print();
  v2.print();
  Vector4 v3 = v1 + v2;
  v3.print();
  v3 = v1 - v2;
  v3.print();
  v3 = Vector4(5, 9, 1, 4);
  v3.dehomogenize();
  v3.print();
}

void testVector3()
{
  Vector3 v1(1.3, 2.3, 3.3);
  Vector3 v2(5.5, 5.3, 5.1);
  //v.print();
  Vector3 v3 = v2 - v1;
  v3.print();
  v3 = v2 + v1;
  v3.print();
  v3 = Vector3::crossProduct(v2, v1);
  v3.print();
  std::cout << Vector3::dotProduct(v1, v2) << std::endl;
  v3.normalize();
  v3.print();
  std::cout << v3.magnitude();
}