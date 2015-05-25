#ifndef _CUBE_H_
#define _CUBE_H_

#include "Matrix4.h"
#include <random>

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
    void setShape(std::string objPath);

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> dis;

  public:
    Vector3 color;
    
    int s_nVerts;
    float *s_vertices;
    float *s_normals;
    float *s_texcoords;
    int s_nIndices;
    int *s_indices;
    float *s_colors;
    bool renderCube;

    Cube();   // Constructor
    Matrix4& getMatrix();
    void idle();
    void glutKeyboardFunc(unsigned char key,
                                 int x, int y);
    void glutSpecialFunc(int key, int x, int y);
};

#endif

