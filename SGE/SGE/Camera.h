#ifndef CAMERA_H
#define CAMERA_H

#include "Vector.h"

class CCamera
{
public:
	CCamera();
	void SetPosition(CVector& Vec);
	CVector GetPosition();
	void Update(double FrameTime);
	void LookAt();
private:
	CVector m_Position;
	double m_Pitch;
	double m_Yaw;
	CVector m_Up;
	enum MoveMode { FirstPerson, FreeLook } m_MoveMode;
};

#endif