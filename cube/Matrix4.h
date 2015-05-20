#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#define M_PI 3.14159265358979323846
#include "vector4.h"

class Matrix4
{
  protected:
    double m[4][4];   // matrix elements; first index is for rows, second for columns (row-major)
    double MulRowByCol(Matrix4& m1, Matrix4&m2, int row, int col);
    
  public:
    Matrix4();
    Matrix4(double x0, double x1, double x2, double x3,
          double x4, double x5, double x6, double x7,
          double x8, double x9, double x10, double x11,
          double x12, double x13, double x14, double x15);
    Matrix4& operator=(const Matrix4&);
    double get(int x, int y);
    double* getPointer(); 
    Matrix4 multiply(Matrix4& mat);
    Vector4 multiply(Vector4& v);
    void identity(); 
    void transpose();
    void makeRotateX(double angle); 
    void makeRotateY(double angle); 
    void makeRotateZ(double angle); 
    void makeRotateAxis(double angle, double ax, double ay, double az); 
    static Matrix4 makeScaling(double sx, double sy, double sz);
    static Matrix4 makeTranslation(double tx, double ty, double tz);
    std::string toString();
    void print();
};

#endif