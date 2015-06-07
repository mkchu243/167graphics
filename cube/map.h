#ifndef _MAP_H_
#define _MAP_H_

#include "Camera.h"
#include "vector4.h"

class Map	  // OpenGL output window related routines
{
  private:
    Vector4 x;
    Vector4 y;
    Vector4 z;
    Vector4 location;
    bool goForward;

    void loadMap();
    Vector3 getColor(int height);
    void rotate(Vector4 rotateAbout, bool positive);

  public:
    int s_nVerts;
    float *s_vertices;
    float *s_normals;
    float *s_texcoords;
    int s_nIndices;
    int *s_indices;
    float *s_colors;
    
    Map();
    void reset();
    void glutKeyboardFunc(unsigned char key,
                              int x, int y);
    Camera getCamera();
    void idle();
};

#endif

