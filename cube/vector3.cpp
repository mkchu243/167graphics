#include "vector3.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>

Vector3::Vector3(double x, double y, double z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

void Vector3::set(double x, double y, double z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

double Vector3::getX()
{
  return x;
}

double Vector3::getY()
{
  return y;
}

double Vector3::getZ()
{
  return z;
}

double Vector3::operator[](int i)
{
  switch(i)
  {
  case 0:
    return x;
  case 1:
    return y;
  case 2:
    return z;
  default:
    return -1;
  }
}

Vector3 Vector3::add(const Vector3& a, const Vector3& b)
{
  return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector3 Vector3::operator+(const Vector3& v)
{
  return add(*this, v);
}

void Vector3::operator=(const Vector3& v)
{
  x = v.x;
  y = v.y;
  z = v.z;
}

Vector3 Vector3::sub(const Vector3& a, const Vector3& b)
{
  return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vector3 Vector3::operator-(const Vector3& v)
{
  return sub(*this, v);
}

void Vector3::scale(double s)
{
  x = x * s;
  y = y * s;
  z = z * s;
}

void Vector3::negate()
{
  scale(-1.0);
}

double Vector3::dotProduct(const Vector3& a, const Vector3& b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 Vector3::crossProduct(const Vector3& a, const Vector3& b)
{
  return Vector3( a.y * b.z - a.z * b.y,
                  a.z * b.x - a.x * b.z,
                  a.x * b.y - a.y * b.x);
}

double Vector3::magnitude()
{
  return sqrt( x*x + y*y + z*z);
}

void Vector3::normalize()
{
  scale(1.0/magnitude());
}

std::string Vector3::toString()
{
  char returnVal[100];
  sprintf_s(returnVal, "%4.3f, %4.3f, %4.3f", x, y, z);
  return returnVal;
}

void Vector3::print()
{
  std::cout << toString() << std::endl;
}