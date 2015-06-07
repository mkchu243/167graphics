#include <iostream>
#include <GL/glut.h>

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "main.h"
#include "house.h"
#include "Camera.h"
#include "map.h"

using namespace std;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
Window::renderMode Window::currentMode = cube;

void Window::glutKeyboardFunc(unsigned char key,
                                   int x, int y)
{
  switch(currentMode)
  {
    case cube:
      Globals::cube.glutKeyboardFunc(key, x, y);
      break;
    case map:
      Globals::map.glutKeyboardFunc(key, x, y);
      break;
  }
}

void Window::glutSpecialFunc(int key, int x, int y)
{
  Globals::cube.glutSpecialFunc(key, x, y);
  switch(key)
  {
    case GLUT_KEY_F1:
    case GLUT_KEY_F2:
    case GLUT_KEY_F3:
    case GLUT_KEY_F4:
    case GLUT_KEY_F5:
    case GLUT_KEY_F6:
      currentMode = cube;
      break;
    case GLUT_KEY_F7:
      currentMode = map;
      break;
    case GLUT_KEY_F8:
      currentMode = house;
      break;
  }
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
  switch(currentMode)
  {
    case cube:
      Globals::cube.idle();   // rotate cube; if it spins too fast try smaller values and vice versa
      break;
    case map:
      Globals::map.idle();
      break;
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
 switch(currentMode)
 {
   case cube:
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); // set perspective projection viewing frustum
    glTranslatef(0, 0, -20);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)
    break;
   case house:
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 1000.0);
    glTranslatef(0, 0, -20);
    break;
   case map:
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 1000.0);
      //glTranslatef(0, 0, -20);
     break;
  }
  glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
 switch(currentMode)
 {
   case cube:
     Window::drawCube();
     break;
   case house:
     Window::drawHouse();
     break;
   case map:
     Window::drawMap();
     break;
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

void Window::drawMap()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
  glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode

  glLoadMatrixd(Globals::map.getCamera().getCameraMatrix());
  //gluLookAt(0.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  glEnableClientState( GL_COLOR_ARRAY );
  glEnableClientState( GL_VERTEX_ARRAY );
  glColorPointer( 3, GL_FLOAT, 0, Globals::map.s_colors);
  glVertexPointer( 3, GL_FLOAT, 0, Globals::map.s_vertices);
  glDrawElements( GL_TRIANGLES, Globals::map.s_nIndices, GL_UNSIGNED_INT, Globals::map.s_indices );
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

  if(Globals::cube.renderCube)
  {
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
  } else {
    glEnableClientState( GL_COLOR_ARRAY );
    glEnableClientState( GL_VERTEX_ARRAY );
    glColorPointer( 3, GL_FLOAT, 0, Globals::cube.s_colors);
    glVertexPointer( 3, GL_FLOAT, 0, Globals::cube.s_vertices);
    glDrawElements( GL_TRIANGLES, Globals::cube.s_nIndices, GL_UNSIGNED_INT, Globals::cube.s_indices );
  }
  
  glFlush();  
  glutSwapBuffers();
}
