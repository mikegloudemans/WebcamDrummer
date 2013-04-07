#pragma once
class Vector
{
private: 
	double myX;
	double myY;
	double myZ;

public:
	Vector(double x, double y, double z)
	{
		myX = x;
		myY = y;
		myZ = z;
	}

	//default constructor
	Vector()
	{
		myX = 0;
		myY = 0;
		myZ = 0;
	}

	~Vector(){};

	//shallow copy of class is good enough so no copy constructor or assignement opperator overload is defined

	double dot(const Vector& v) const;

	Vector cross(const Vector& v) const;
	static Vector cross(const Vector& v, const Vector& u);

	void add(const Vector& v);
	static Vector add(const Vector& u, const Vector& v);
	friend Vector operator+(const Vector& u, const Vector& v);
	void operator+=(const Vector& v);

	void subtract(const Vector& v);
	static Vector subtract(const Vector& u, const Vector& v);
	friend Vector operator-(const Vector& u, const Vector& v);
	void operator-=(const Vector& v);

	void multiply(double f);
	static Vector multiply(const Vector& v, double f);
	friend Vector operator*(const Vector& v, double f);
	void operator*=(double f);

	void divide(double t);
	static Vector divide(const Vector& v, double f);
	friend Vector operator/(const Vector& v, double t);
	void operator/=(double t);

	double distance(const Vector& v);
	void normalize();
	static Vector normalize(const Vector& v);
	double getMagnitude() const;
	
	//getters and setters
	void setX(double x) {
		myX = x;
	}

	void setY(double y) {
		myY = y;
	}

	void setZ(double z) {
		myZ = z;
	}

	double getX() const{
		return myX;
	}

	double getY() const{
		return myY;
	}

	double getZ() const{
		return myZ;
	}

	
};