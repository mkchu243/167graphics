#include <iostream>

#include <GL/glut.h>

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "main.h"
#include "house.h"
#include "Camera.h"

using namespace std;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
bool Window::cubeMode = false;

void Window::glutKeyboardFunc(unsigned char key,
                                   int x, int y)
{
  if(cubeMode){
    Globals::cube.glutKeyboardFunc(key, x, y);
  }
}

void Window::glutSpecialFunc(int key, int x, int y)
{
  switch(key)
  {
    case GLUT_KEY_F8:
      cubeMode = false;
      break;
    case GLUT_KEY_F9:
      cubeMode = true;
      break;
  }
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
  if(cubeMode){
    Globals::cube.idle();   // rotate cube; if it spins too fast try smaller values and vice versa
  }
  displayCallback();         // call display routine to show the cube
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
  cerr << "Window::reshapeCallback called" << endl;
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
  if(cubeMode)
  {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); // set perspective projection viewing frustum
    glTranslatef(0, 0, -20);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)
  }  else  {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 1000.0);
    glTranslatef(0, 0, -20);
  }
  glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
 if(cubeMode){
   Window::drawCube();
 } else {
   Window::drawHouse();
 }
}

void Window::drawHouse()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
  glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode


  double mat[16] = { 1, 0, 0, 0,
    0, 0.707, 0.707, 0, 
    0, -0.707, 0.707, 0,
    0, 0, -14.443, 1};
    // Tell OpenGL what ModelView matrix to use:
  glLoadMatrixd(Globals::camera.getCameraMatrix());
  //gluLookAt(0.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  glEnableClientState( GL_COLOR_ARRAY );
  glEnableClientState( GL_VERTEX_ARRAY );
  glColorPointer( 3, GL_FLOAT, 0, House::colors );
  glVertexPointer( 3, GL_FLOAT, 0, House::vertices );
  glDrawElements( GL_TRIANGLES, 60, GL_UNSIGNED_INT, House::indices );
  glFlush();  
  glutSwapBuffers();
}

void Window::drawCube()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
  glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode

  // Tell OpenGL what ModelView matrix to use:
  Matrix4 glmatrix;
  glmatrix = Globals::cube.getMatrix();
  glmatrix.transpose();
  glLoadMatrixd(glmatrix.getPointer());

  // Draw all six faces of the cube:
  glBegin(GL_QUADS);
    glColor3f(Globals::cube.color.getX(), Globals::cube.color.getY(), Globals::cube.color.getZ());		// This makes the cube green; the parameters are for red, green and blue. 
                                // To change the color of the other faces you will need to repeat this call before each face is drawn.
    // Draw front face:
    glNormal3f(0.0, 0.0, 1.0);   
    glVertex3f(-5.0,  5.0,  5.0);
    glVertex3f( 5.0,  5.0,  5.0);
    glVertex3f( 5.0, -5.0,  5.0);
    glVertex3f(-5.0, -5.0,  5.0);
    
    // Draw left side:
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-5.0,  5.0,  5.0);
    glVertex3f(-5.0,  5.0, -5.0);
    glVertex3f(-5.0, -5.0, -5.0);
    glVertex3f(-5.0, -5.0,  5.0);
    
    // Draw right side:
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f( 5.0,  5.0,  5.0);
    glVertex3f( 5.0,  5.0, -5.0);
    glVertex3f( 5.0, -5.0, -5.0);
    glVertex3f( 5.0, -5.0,  5.0);
  
    // Draw back face:
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-5.0,  5.0, -5.0);
    glVertex3f( 5.0,  5.0, -5.0);
    glVertex3f( 5.0, -5.0, -5.0);
    glVertex3f(-5.0, -5.0, -5.0);
  
    // Draw top side:
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-5.0,  5.0,  5.0);
    glVertex3f( 5.0,  5.0,  5.0);
    glVertex3f( 5.0,  5.0, -5.0);
    glVertex3f(-5.0,  5.0, -5.0);
  
    // Draw bottom side:
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-5.0, -5.0, -5.0);
    glVertex3f( 5.0, -5.0, -5.0);
    glVertex3f( 5.0, -5.0,  5.0);
    glVertex3f(-5.0, -5.0,  5.0);
  glEnd();
  
  glFlush();  
  glutSwapBuffers();
}
