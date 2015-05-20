#pragma once

#include "vector4.h"
#define _USE_MATH_DEFINES
#include <math.h>

class Matrix4_2
{
private:
  double mat[4][4]; //first index is rows
  double MulRowByCol(Matrix4_2& m1, Matrix4_2&m2, int row, int col);

public:
  Matrix4_2();
  Matrix4_2(double x0, double x1, double x2, double x3,
            double x4, double x5, double x6, double x7,
            double x8, double x9, double x10, double x11,
            double x12, double x13, double x14, double x15);
  double get(int x, int y);
  Matrix4_2* multiply(Matrix4_2& mat);
  Vector4* multiply(Vector4& v);
  Matrix4_2 makeRotX(double angle);
  Matrix4_2 makeRotY(double angle);
  Matrix4_2 makeRotZ(double angle);
  Matrix4_2 makeRotAxis(double angle, double ax, double ay, double az);
  Matrix4_2 makeScaling(double sx, double sy, double sz);
  Matrix4_2 makeTranslation(double tx, double ty, double tz);
  void transpose();
  std::string toString();
  void print();

};