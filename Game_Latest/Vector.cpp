#include "stdafx.h"
#include "Vector.h"
#include <math.h>

double Vector::dot(const Vector& v) const
{
	return myX * v.myX + myY * v.myY + myZ * v.myZ;
}

Vector Vector::cross(const Vector& v) const
{
	double outX = myY * v.myZ - myZ * v.myY;
	double outY = -(myX * v.myZ - myZ * v.myX);
	double outZ = myX * v.myY - myY * v.myX;

	return Vector(outX, outY, outZ);
}

Vector Vector::cross(const Vector& v, const Vector& u)
{
	double outX = v.myY * u.myZ - v.myZ * u.myY;
	double outY = -(v.myX * u.myZ - v.myZ * u.myX);
	double outZ = v.myX * u.myY - v.myY * u.myX;

	return Vector(outX, outY, outZ);
}

void Vector::add(const Vector& v)
{
	myX += v.myX;
	myY += v.myY;
	myZ += v.myZ;
}

Vector Vector::add(const Vector& v, const Vector& u)
{
	double outX = v.myX + u.myX;
	double outY = v.myY + u.myY;
	double outZ = v.myZ + u.myZ;

	return Vector(outX, outY, outZ);
}

Vector operator+(const Vector& v, const Vector& u)
{
	return Vector::add(v, u);
}

void Vector::operator+=(const Vector& v)
{
	add(v);
}


void Vector::subtract(const Vector& v)
{
	myX -= v.myX;
	myY -= v.myY;
	myZ -= v.myZ;
}

Vector Vector::subtract(const Vector& v, const Vector& u)
{
	double outX = v.myX - u.myX;
	double outY = v.myY - u.myY;
	double outZ = v.myZ - u.myZ;

	return Vector(outX, outY, outZ);
}

Vector operator-(const Vector& v, const Vector& u)
{
	return Vector::subtract(v, u);
}

void Vector::operator-=(const Vector& v)
{
	subtract(v);
}

void Vector::multiply(double f)
{
	myX *= f;
	myY *= f;
	myZ *= f;
}

Vector Vector::multiply(const Vector& v, double f)
{
	double outX = v.myX * f;
	double outY = v.myY * f;
	double outZ = v.myZ * f;

	return Vector(outX, outY, outZ);
}

Vector operator*(const Vector& v, double f)
{
	return Vector::multiply(v, f);
}

void Vector::operator*=(double f)
{
	multiply(f);
}

void Vector::divide(double f)
{
	myX /= f;
	myY /= f;
	myZ /= f;
}

Vector Vector::divide(const Vector& v, double f)
{
	double outX = v.myX / f;
	double outY = v.myY / f;
	double outZ = v.myZ / f;

	return Vector(outX, outY, outZ);
}

Vector operator/(const Vector& v, double f)
{
	return Vector::divide(v, f);
}

void Vector::operator/=(double f)
{
	divide(f);
}

double Vector::distance(const Vector& v)
{
	return sqrt(pow((myX - v.myX), 2) + pow((myY - v.myY), 2) + pow((myZ - v.myZ), 2));
}

void Vector::normalize()
{
	double mag = sqrt(pow(myX, 2) + pow(myY, 2) + pow(myZ, 2)); 
	myX /= mag;
	myY /= mag;
	myZ /= mag;
}

Vector Vector::normalize(const Vector& v)
{
	Vector u(v.getX(), v.getY(), v.getZ());
	u.normalize();
	return u;
}

double Vector::getMagnitude() const
{
	return sqrt(pow(myX, 2) + pow(myY, 2) + pow(myZ, 2));
}