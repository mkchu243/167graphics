#ifndef _CUBE_H_
#define _CUBE_H_

#include "Matrix4.h"

class Cube
{
  protected:
    Matrix4 model2world;            // model matrix (transforms model coordinates to world coordinates)
    Matrix4 currentRotationY;      
    Vector3 translations;
    Vector3 scale;
    double angleY;                   // rotation angle [degrees]
    double angleZ;                   // rotation angle [degrees]
    bool reverseAngle;
    void spin(double);      // spin cube [degrees]
    void reset();      // spin cube [degrees]


  public:
    Vector3 color;
    Cube();   // Constructor
    Matrix4& getMatrix();
    void idle();
    void glutKeyboardFunc(unsigned char key,
                                 int x, int y);
};

#endif

