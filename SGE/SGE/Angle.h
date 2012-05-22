#ifndef ANGLE_H
#define ANGLE_H

#include "Vector.h"
class CVector;

class CAngle
{
public:
	double Pitch;
	double Yaw;
	double Roll;
	CAngle(double Pitch, double Yaw, double Roll);
	CAngle();
	CVector Forward();
	CVector Right();
	CVector Up();
	CVector ToVector();
};

// TODO: Operators

#endif