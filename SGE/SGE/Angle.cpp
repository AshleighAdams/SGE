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

CVector CAngle::Forward()
{
	return CVector(Pitch, Yaw);
}

CVector CAngle::Right()
{
	const CVector crossright(0, 0, 1);
	return CVector(0.0, Yaw).Cross(crossright);
}

CVector CAngle::Up()
{
	return CVector(0.0, 0.0);
}

