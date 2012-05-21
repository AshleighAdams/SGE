#include "Angle.h"

CAngle::CAngle(double P, double Y, double R)
{
	Pitch = P;
	Yaw = Y;
	Roll = R;
}

CAngle::CAngle()
{
	Pitch = Yaw = Roll = 0;
}

CVector CAngle::ToVector()
{
	return CVector(Pitch, Yaw);
}