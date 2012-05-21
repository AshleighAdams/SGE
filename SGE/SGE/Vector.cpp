#include <cmath>
#include "Vector.h"

CVector::CVector()
{
}

CVector::CVector(double x, double y, double z)
{
	X = x;
	Y = y;
	Z = z;
}

CVector::CVector(double Pitch, double Yaw)
{
	double cos_pitch = cos(Pitch);
	X = cos(Yaw) * cos_pitch;
	Y = sin(Yaw) * cos_pitch;
	Z = sin(Pitch);
}

CVector::~CVector()
{
	X = 0;
	Y = 0;
	Z = 0;
}

// Functions

double CVector::Length()
{
	return sqrt(X * X + Y * Y + Z * Z);
}

double CVector::LengthSqr()
{
	return X * X + Y * Y + Z * Z;
}

double CVector::Length2D()
{
	return sqrt(X * X + Y * Y);
}

double CVector::Length2DSqr()
{
	return X * X + Y * Y;
}

CVector CVector::Normal()
{
	double Len = Length();
	return CVector(X / Len, Y / Len, Z / Len);
}

double CVector::Distance(CVector& A)
{
	CVector ret(X, Y, Z);
	return (ret += A).Length();
}

CVector CVector::Cross(CVector& A)
{
	return CVector
	(
		Y * A.Z - Z * A.Y,
		Z * A.X - X * A.Z,
		X * A.Y - Y * A.X
	);
}

double CVector::Dot(CVector& A)
{
	return X * A.X + Y * A.Y + Z * A.Z;
}

// These modify the actual vector!

CVector& CVector::Normalize()
{
	double Len = Length();
	if(Len == 0.0)
		Len = 1.0;
	X /= Len;
	Y /= Len;
	Z /= Len;
	return *this;
}

// Operators


// Math functions, will be used by += but you can still use the method, flexibility.

CVector& CVector::Add(CVector& A)
{
	X += A.X;
	Y += A.Y;
	Z += A.Z;
	return *this;
}
CVector& CVector::Sub(CVector& A)
{
	X -= A.X;
	Y -= A.Y;
	Z -= A.Z;
	return *this;
}
CVector& CVector::Mul(CVector& A)
{
	X *= A.X;
	Y *= A.Y;
	Z *= A.Z;
	return *this;
}

CVector& CVector::Mul(double Scalar)
{
	X *= Scalar;
	Y *= Scalar;
	Z *= Scalar;
	return *this;
}
CVector& CVector::Div(CVector& A)
{
	X /= A.X;
	Y /= A.Y;
	Z /= A.Z;
	return *this;
}
CVector& CVector::Div(double Scalar)
{
	X /= Scalar;
	Y /= Scalar;
	Z /= Scalar;
	return *this;
}

// Operators

std::istream& operator>>(std::istream& s, CVector& Vec)
{
	s >> Vec.X;
	s >> Vec.Y;
	s >> Vec.Z;
	return s;
}

std::ostream& operator<<(std::ostream& s, CVector& Vec)
{
	s << Vec.X << ", " << Vec.Y << ", " << Vec.Z;
	return s;
}

// Math operators using other than own type

CVector operator*(CVector& A, double Scalar)
{
	return CVector(A.X * Scalar, A.Y * Scalar, A.Z * Scalar);
}
CVector operator/(CVector& A, double Scalar)
{
	return CVector(A.X / Scalar, A.Y / Scalar, A.Z / Scalar);
}

CVector operator*=(CVector& A, double Scalar)
{
	return A.Mul(Scalar);
}
CVector operator/=(CVector& A, double Scalar)
{
	return A.Div(Scalar);
}

// Math operators

CVector operator+(CVector& A, CVector& B)
{
	return CVector(A.X + B.X, A.Y + B.Y, A.Z + B.Z);
}
CVector operator-(CVector& A, CVector& B)
{
	return CVector(A.X - B.X, A.Y - B.Y, A.Z - B.Z);
}
CVector operator*(CVector& A, CVector& B)
{
	return CVector(A.X * B.X, A.Y * B.Y, A.Z * B.Z);
}
CVector operator/(CVector& A, CVector& B)
{
	return CVector(A.X / B.X, A.Y / B.Y, A.Z / B.Z);
}

// X= operators

CVector& operator+=(CVector& A, CVector& B)
{
	return A.Add(B);
}
CVector& operator-=(CVector& A, CVector& B)
{
	return A.Sub(B);
}
CVector& operator*=(CVector& A, CVector& B)
{
	return A.Mul(B);
}
CVector& operator/=(CVector& A, CVector& B)
{
	return A.Div(B);
}


// Unary operators
CVector operator+(CVector& A)
{
	return CVector(+A.X, +A.Y, +A.Z);
}
CVector operator-(CVector& A)
{
	return CVector(-A.X, -A.Y, -A.Z);
}

// Comparison operators

bool operator==(CVector& A, CVector& B)
{
	return A.X == B.X && A.Y == B.Y && A.Z == B.Z;
}
bool operator!=(CVector& A, CVector& B)
{
	return !operator==(A, B);
}
bool operator>(CVector& A, CVector& B)
{
	return A.LengthSqr() > B.LengthSqr(); // To use no sqrt function (only squaring) is much, much quicker!
}
bool operator>=(CVector& A, CVector& B)
{
	return operator==(A, B) || operator>(A,B);
}
bool operator<(CVector& A, CVector& B)
{
	return A.LengthSqr() < B.LengthSqr();
}
bool operator<=(CVector& A, CVector& B)
{
	return operator==(A, B) || operator<(A,B);
}

