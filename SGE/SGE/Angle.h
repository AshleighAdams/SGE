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
	CVector ToVector();
};

// TODO: Operators

#endif