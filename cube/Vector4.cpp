#include "vector4.h"
#include <string>
#include <stdio.h>

Vector4::Vector4(double x, double y, double z) : v3(x,y,z)
{
  this->w = 1;
}

Vector4::Vector4(double x, double y, double z, double w) : v3(x,y,z)
{
  this->w = w;
}

void Vector4::set(double x, double y, double z, double w)
{
  this->v3.set(x,y,z);
  this->w = w;
}

double Vector4::getX()
{
  return this->v3.getX();
}

double Vector4::getY()
{
  return this->v3.getY();
}

double Vector4::getZ()
{
  return this->v3.getZ();
}

double Vector4::getW()
{
  return w;
}

double Vector4::operator[](int i)
{
  switch(i)
  {
  case 0:
  case 1:
  case 2:
    return v3[i];
  case 3:
    return w;
  default:
    return -1;
  }
}

Vector4 Vector4::add(const Vector4& a, const Vector4& b)
{
  if(a.w == 1 && b.w == 0)
  {
    Vector3 temp = a.v3 + b.v3;
    return Vector4(temp.getX(), temp.getY(), temp.getZ(), 1);
  }
  throw new std::exception("Vector4.sub: a.w must be a 1 and b.w must be 0");
}

Vector4 Vector4::operator+(const Vector4& v)
{
  return add(*this, v);
}

Vector4 Vector4::sub(const Vector4& a, const Vector4& b)
{
  if(a.w == 1 && b.w == 0 )
  {
    Vector3 temp = a.v3 - b.v3;
    return Vector4(temp.getX(), temp.getY(), temp.getZ(), a.w - b.w);
  }
  throw new std::exception("Vector4.sub: a.w must be a 1 and b.w must be 0");
}

Vector4 Vector4::operator-(const Vector4& v)
{
  return sub(*this, v);
}

Vector3 Vector4::getVector3()
{
  return Vector3(v3[0], v3[1], v3[2]);
}

void Vector4::dehomogenize()
{
  if(w != 0)
  {
    v3.scale(1.0/w);
    w = 1;
  }
}

std::string Vector4::toString()
{
  char wString[100];
  sprintf_s(wString, " %4.3f", w);
  return v3.toString() + wString;
}

void Vector4::print()
{
  std::cout << toString() << std::endl;
}

Vector4::~Vector4()
{
}