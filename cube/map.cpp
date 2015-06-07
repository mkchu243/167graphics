#include "Map.h"
#include "pgmLoader.h"
#include "Matrix4.h"
#include "Camera.h"

Map::Map() : x(1,0,0,0), y(0,1,0,0), z(0,0,1,0), location(0,0,0,1)
{
  reset();
  loadMap();
  rotate(Vector4(1,0,0,0), true);
}

void Map::reset()
{
  goForward = false;
  x = Vector4(1,0,0,0);
  y = Vector4(0,1,0,0);
  z = Vector4(0,0,1,0);
  location = Vector4(0,0,0,1);
}

void Map::loadMap()
{
  int h, w;
  unsigned char* pgm = pgmLoader::loadPGM("Heightmap.pgm", w, h);
  s_nVerts = w*h;
  s_colors = new float[3*s_nVerts];
  s_vertices = new float[3*s_nVerts];
  //w-1*h-1 = how many squares; *2  how many triangles;
  s_nIndices = (w-1)*(h-1)*2*3;
  s_indices = new int[s_nIndices]; 

  int currIndex = 0;
  int vertIndex = 0;
  int indicesIndex = 0;
  for (int i = 0; i < w; i++)
  {
    for (int j = 0; j < h; j++, currIndex++, vertIndex += 3)
    {
      int z = pgm[currIndex];
      
      s_vertices[vertIndex] = i;
      s_vertices[vertIndex+1] = j;
      s_vertices[vertIndex+2] = z;

      Vector3 color = getColor(z);
      s_colors[vertIndex] = color[0];
      s_colors[vertIndex+1] = color[1];
      s_colors[vertIndex+2] = color[2];

      if( i < w-1 && j < h-1)
      {
        s_indices[indicesIndex] = currIndex;
        s_indices[indicesIndex+1] = currIndex+w;
        s_indices[indicesIndex+2] = currIndex+w+1;

        s_indices[indicesIndex+3] = currIndex;
        s_indices[indicesIndex+4] = currIndex+1;
        s_indices[indicesIndex+5] = currIndex+w+1;
        indicesIndex += 6;
      }
    }
  }
}

Vector3 Map::getColor(int height)
{
  float increment = 255/5.0;

  if( height < increment ){
    //blue
    return Vector3(27/255.0, 136/255.0, 204/255.0);
  } else if (height < increment*2){
    //yellow
    //return Vector3(91/255.0, 88/255.0, 24/255.0);
    return Vector3(199/255.0, 184/255.0, 24/255.0);
  } else if (height < increment*3){
    //green
    return Vector3(35/255.0, 156/255.0, 19/255.0);
  } else if (height < increment*4){
    //grey
    return Vector3(84/255.0, 87/255.0, 80/255.0);
  } else { //if (height < increment*5){
    //white
    return Vector3(255/255.0, 255/255.0, 255/255.0);
  }
}

void Map::glutKeyboardFunc(unsigned char key, int x, int y)
{
  switch(key)
  {
  case 'w':
    location = location + this->x;
    break;
  case 's':
    location = location - this->x;
    break;
  case 'a':
    rotate(z, true);
    break;
  case 'd':
    rotate(z, false);
    break;
  case 'i':
    rotate(this->y, true);
    break;
  case 'k':
    rotate(this->y, false);
    break;
  case 'j':
    rotate(this->x, false);
    break;
  case 'l':
    rotate(this->x, true);
    break;
  case 'r':
    reset();
    break;
  case ' ':
    goForward = !goForward;
    break;
  }
}

void Map::rotate(Vector4 rotateAbout, bool positive)
{
  double angle = positive ? 1.0 : -1.0;

  Matrix4 m;
  m.makeRotateAxis(angle, rotateAbout[0], rotateAbout[1], rotateAbout[2]);
  x = m.multiply(x);
  y = m.multiply(y);
  z = m.multiply(z);
}

Camera Map::getCamera()
{
  Vector4 lookAtPoint = location + x;
  return Camera(location.getVector3(),lookAtPoint.getVector3(), z.getVector3()); 
}

void Map::idle()
{
  if(goForward)
  {
    location = location + this->x;
  }
}