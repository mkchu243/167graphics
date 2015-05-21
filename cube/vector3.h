#pragma once

#include <iostream>

class Vector3
{
private:
    double x;
    double y;
    double z;

  public:
    Vector3(double x, double y, double z);
    void set(double x, double y, double z);
    double getX();
    double getY();
    double getZ();
    void operator=(const Vector3& v);
    double operator[](int i);
    Vector3 add(const Vector3& a,const Vector3& b) const;
    Vector3 operator+(const Vector3& v) const;
    Vector3 sub(const Vector3& a, const Vector3& b) const;
    Vector3 operator-(const Vector3& v) const;
    void negate();
    void scale(double s);
    static double dotProduct(const Vector3& a, const Vector3& b);
    static Vector3 crossProduct(const Vector3& a, const Vector3& b);
    double magnitude();
    void normalize();
    std::string toString();
    void print();
};