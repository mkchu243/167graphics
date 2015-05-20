#include <math.h>
#include <string>
#include <iostream>
#include "Matrix4.h"

Matrix4::Matrix4()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = 0;
    }
  }
} 

Matrix4::Matrix4(double x0, double x1, double x2, double x3,
                    double x4, double x5, double x6, double x7,
                    double x8, double x9, double x10, double x11,
                    double x12, double x13, double x14, double x15)
{
  m[0][0] = x0;
  m[0][1] = x4;
  m[0][2] = x8;
  m[0][3] = x12;

  m[1][0] = x1;
  m[1][1] = x5;
  m[1][2] = x9;
  m[1][3] = x13;
  
  m[2][0] = x2;
  m[2][1] = x6;
  m[2][2] = x10;
  m[2][3] = x14;
  
  m[3][0] = x3;
  m[3][1] = x7;
  m[3][2] = x11;
  m[3][3] = x15;
}

Matrix4& Matrix4::operator=(const Matrix4& m2)
{
  if (this != &m2)
  {
    for (int i=0; i<4; ++i)
    {
      for (int j=0; j<4; ++j)
      {
        m[i][j] = m2.m[i][j];
      }
    }
  }
  return *this;
}

double Matrix4::get(int x, int y)
{
  return m[x][y];
}


// return pointer to matrix elements
double* Matrix4::getPointer()
{
  return &m[0][0];
}

Matrix4 Matrix4::multiply(Matrix4& mat)
{
  Matrix4 result;
  for(int row = 0; row < 4; row++)
  {
    for(int col = 0; col < 4; col++)
    {
      result.m[row][col] = MulRowByCol(*this, mat, row, col);
    }
  }
  return result;
}

double Matrix4::MulRowByCol(Matrix4& m1, Matrix4&m2, int row, int col)
{
  double res = 0;
  for(int i = 0; i < 4; i++)
  {
    res += m1.get(row,i) * m2.get(i,col);
  }
  return res;
}

Vector4 Matrix4::multiply(Vector4& v)
{
  double vec[4];
  for(int row = 0; row < 4; row++)
  {
    double temp = 0;
    for(int col = 0; col < 4; col++)
    {
      temp += this->m[row][col] * v[col];
    }
    vec[row] = temp;
  }
  return Vector4(vec[0], vec[1], vec[2], vec[3]);
}

// set matrix to identity matrix
void Matrix4::identity()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      if (i==j) 
        m[i][j] = 1.0; 
      else 
        m[i][j] = 0.0;
    }
  }
}

// transpose the matrix (mirror at diagonal)
void Matrix4::transpose()
{
  Matrix4 temp;
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      temp.m[j][i] = m[i][j];
    }
  }
  *this = temp;  // copy temporary values to this matrix
}

// Creates a rotation matrix which rotates about the y axis.
// angle is expected in degrees
void Matrix4::makeRotateY(double angle)
{
  angle = angle / 180.0 * M_PI;  // convert from degrees to radians
  identity();
	m[0][0] = cos(angle);
	m[0][2] = sin(angle);
	m[2][0] = -sin(angle);
	m[2][2] = cos(angle);
}

void Matrix4::makeRotateX(double angle)
{
  angle = angle / 180.0 * M_PI;  // convert from degrees to radians
  identity();
	m[1][1] = cos(angle);
	m[2][1] = sin(angle);
	m[1][2] = -sin(angle);
	m[2][2] = cos(angle);
}
 
void Matrix4::makeRotateZ(double angle)
{
  angle = angle / 180.0 * M_PI;  // convert from degrees to radians
  identity();
	m[0][0] = cos(angle);
	m[0][1] = -sin(angle);
	m[1][0] = sin(angle);
	m[1][1] = cos(angle);
}

void Matrix4::makeRotateAxis(double angle, double ax, double ay, double az)
{
  angle = angle / 180.0 * M_PI;  // convert from degrees to radians
  identity();
  double magnitude = sqrt(ax*ax + ay*ay + az*az);
  ax = ax/magnitude;
  ay = ay/magnitude;
  az = az/magnitude;
	m[0][0] = 1 + (1-cos(angle))*(pow(ax,2)-1);
	m[0][1] = -1*az*sin(angle)+(1-cos(angle))*ax*ay;
	m[0][2] = ay*sin(angle)+(1-cos(angle))*ax*az;
	m[1][0] = az*sin(angle)+(1-cos(angle))*ay*ax;
	m[1][1] = 1 + (1-cos(angle))*(pow(ay,2)-1);
  m[1][2] = -1*ax*sin(angle)+(1-cos(angle))*ay*az;
  m[2][0] = -1*ay*sin(angle)+(1-cos(angle))*az*ax;
  m[2][1] = ax*sin(angle)+(1-cos(angle))*az*ay;
  m[2][2] = 1 + (1-cos(angle))*(pow(az,2)-1);
}

Matrix4 Matrix4::makeTranslation(double tx, double ty, double tz)
{
  Matrix4 result;
  result.identity();
  result.m[0][3] = tx;
  result.m[1][3] = ty;
  result.m[2][3] = tz;
  return result;
}

Matrix4 Matrix4::makeScaling(double sx, double sy, double sz)
{
  Matrix4 result;
  result.identity();
  result.m[0][0] = sx;
  result.m[1][1] = sy;
  result.m[2][2] = sz;
  return result;
}

std::string Matrix4::toString()
{
  char returnVal[200];
  std::string matFormat = 
    std::string("%4.3f, %4.3f, %4.3f, %4.3f\r\n ") +
    "%4.3f, %4.3f, %4.3f, %4.3f\r\n" +
    "%4.3f, %4.3f, %4.3f, %4.3f\r\n" +
    "%4.3f, %4.3f, %4.3f, %4.3f";
  sprintf_s(returnVal, matFormat.c_str(),
    m[0][0], m[0][1], m[0][2], m[0][3],
    m[1][0], m[1][1], m[1][2], m[1][3],
    m[2][0], m[2][1], m[2][2], m[2][3],
    m[3][0], m[3][1], m[3][2], m[3][3]
    );
  return returnVal;
}

void Matrix4::print()
{
  std::cout << toString() << std::endl;
}
