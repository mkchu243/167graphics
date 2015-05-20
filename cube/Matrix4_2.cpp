#include "Matrix4_2.h"

Matrix4_2::Matrix4_2()
{
  mat[0][0] =
  mat[0][1] = 
  mat[0][2] = 
  mat[0][3] =

  mat[1][0] =
  mat[1][1] =
  mat[1][2] =
  mat[1][3] =
  
  mat[2][0] = 
  mat[2][1] =
  mat[2][2] =
  mat[2][3] = 
  
  mat[3][0] =
  mat[3][1] =
  mat[3][2] =
  mat[3][3] = 0;
}

Matrix4_2::Matrix4_2(double x0, double x1, double x2, double x3,
                    double x4, double x5, double x6, double x7,
                    double x8, double x9, double x10, double x11,
                    double x12, double x13, double x14, double x15)
{
  mat[0][0] = x0;
  mat[0][1] = x4;
  mat[0][2] = x8;
  mat[0][3] = x12;

  mat[1][0] = x1;
  mat[1][1] = x5;
  mat[1][2] = x9;
  mat[1][3] = x13;
  
  mat[2][0] = x2;
  mat[2][1] = x6;
  mat[2][2] = x10;
  mat[2][3] = x14;
  
  mat[3][0] = x3;
  mat[3][1] = x7;
  mat[3][2] = x11;
  mat[3][3] = x15;
}

double Matrix4_2::get(int x, int y)
{
  return mat[x][y];
}

Matrix4_2* Matrix4_2::multiply(Matrix4_2& mat)
{
  Matrix4_2* result= new Matrix4_2();
  for(int row = 0; row < 4; row++)
  {
    for(int col = 0; col < 4; col++)
    {
      result->mat[row][col] = MulRowByCol(*this, mat, row, col);
    }
  }
  return result;
}

double Matrix4_2::MulRowByCol(Matrix4_2& m1, Matrix4_2&m2, int row, int col)
{
  double res = 0;
  for(int i = 0; i < 4; i++)
  {
    res += m1.get(row,i) * m2.get(i,col);
  }
  return res;
}

Vector4* Matrix4_2::multiply(Vector4& v)
{
  double vec[4];
  for(int row = 0; row < 4; row++)
  {
    double temp = 0;
    for(int col = 0; col < 4; col++)
    {
      temp += this->mat[row][col] * v[col];
    }
    vec[row] = temp;
  }
  return new Vector4(vec[0], vec[1], vec[2], vec[3]);
}