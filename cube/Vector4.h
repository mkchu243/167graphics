#pragma once

#include <iostream>
#include "vector3.h"

class Vector4
{
private:
    double w;
    Vector3 v3;

  public:
    Vector4(double x, double y, double z);
    Vector4(double x, double y, double z, double w);
    void set(double x, double y, double z, double w);
    double getX();
    double getY();
    double getZ();
    double getW();
    double operator[](int i);
    Vector4 add(const Vector4& a,const Vector4& b);
    Vector4 operator+(const Vector4& v);
    Vector4 sub(const Vector4& a, const Vector4& b);
    Vector4 operator-(const Vector4& v);
    Vector3 getVector3();
    void dehomogenize();
    std::string toString();
    void print();
    ~Vector4();
};