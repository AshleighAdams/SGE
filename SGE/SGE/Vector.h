#ifndef CVECTOR_H
#define CVECTOR_H

#include <iostream>

#include "Angle.h"
class CAngle;

class CVector
{
public:
	// Members
	double X; // Must be first so you can pass to something like struct Vec{ int x, int y, int z};
	double Y;
	double Z;

	// Funcs
	CVector(double X, double Y, double Z);
	CVector(double Pitch, double Yaw);
	CVector();
	~CVector();
	double Length();
	double LengthSqr(); // These operations are good for comparison, they offer a 'round compare distance' without the slowdowns of sqrt()
	double Length2D();
	double Length2DSqr();

	CAngle ToAngle();
	
	CVector Normal();
	double Distance(CVector& A);
	CVector Cross(CVector& A);
	double Dot(CVector& A);

	// These modify the vector!
	CVector& Normalize();
	CVector& Approach(CVector& What, const double& Ammount);

	// Math funcs, changes itself
	CVector& Add(CVector& A);
	CVector& Sub(CVector& A);
	CVector& Mul(CVector& A);
	CVector& Mul(double Scalar);
	CVector& Div(CVector& A);
	CVector& Div(double Scalar);
};


// Operators

// Stream helpers
std::istream& operator>>(std::istream&, CVector&);
std::ostream& operator<<(std::ostream&, CVector&);

// Math operators, but not with own type (Vec * 5.0)
CVector operator*(CVector&, double); // Scale
CVector operator/(CVector&, double);

// Math operators
CVector operator+(CVector&, CVector&);
CVector operator-(CVector&, CVector&);
CVector operator*(CVector&, CVector&);
CVector operator/(CVector&, CVector&);

// These return a reference to the first argument
CVector& operator+=(CVector&, CVector&);
CVector& operator-=(CVector&, CVector&);
CVector& operator*=(CVector&, CVector&);
CVector& operator/=(CVector&, CVector&);

// Unary operators
CVector operator+(CVector&);
CVector operator-(CVector&);

// Comparison operators
bool operator==(CVector&, CVector&);
bool operator!=(CVector&, CVector&);
bool operator>(CVector&, CVector&);
bool operator>=(CVector&, CVector&);
bool operator<(CVector&, CVector&);
bool operator<=(CVector&, CVector&);

#endif