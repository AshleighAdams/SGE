#include "Camera.h"
#define private public
#include "Engine.h"
#undef private

CCamera::CCamera()
{
	m_Position.X = 0.0;
	m_Position.Y = 0.0;
	m_Position.Z = 0.0;
	
	m_Up.X = 0.0;
	m_Up.Y = 0.0;
	m_Up.Z = 1.0;

	m_Pitch = 0.0;
	m_Yaw = 0.0;

	m_VelocityAccumulator = 0.0;
	m_Velocity = CVector(0, 0, 0);
}

void CCamera::LookAt()
{
	CVector dir(m_Pitch, m_Yaw);
	dir += m_Position;

	gluLookAt(m_Position.X,		m_Position.Y,	m_Position.Z,
			  dir.X,			dir.Y,			dir.Z,
			  m_Up.X,			m_Up.Y,			m_Up.Z
	);
}

void CCamera::SetPosition(CVector& Vec)
{
	m_Position.X = Vec.X;
	m_Position.Y = Vec.Y;
	m_Position.Z = Vec.Z;
}

CVector CCamera::GetPosition()
{
	return m_Position;
}

double modulus(double a, double b)
{
	int result = static_cast<int>( a / b );
	return a - static_cast<double>( result ) * b;
}

void CCamera::Update(double FrameTime)
{
	if(!pEngineInstance->Focused())
		return;

	int CenterX = pEngineInstance->m_WindowWidth / 2;
	int CenterY = pEngineInstance->m_WindowHeight / 2;

	POINT mpos;
	GetCursorPos(&mpos);
	
	if(mpos.x != CenterX || mpos.y != CenterY)
	{
		double Y = CenterX - mpos.x;
		double P = CenterY - mpos.y;

		m_Pitch += P * 0.003;
		m_Yaw += Y * 0.003;

		if(m_Pitch > 1.5)
			m_Pitch = 1.5;
		else if(m_Pitch < -1.5)
			m_Pitch = -1.5;

		m_Yaw = modulus(m_Yaw, 3.14159265358979232 * 2.0);
		

		SetCursorPos(CenterX, CenterY);
	}
	
	double right = 0.0;
	double fwd = 0.0;
	double up = 0.0;

	if(GetKeyState('D') & 0x80)
		right += 1.0;
	if(GetKeyState('A') & 0x80)
		right -= 1.0;
	
	if(GetKeyState('W') & 0x80)
		fwd += 1.0;
	if(GetKeyState('S') & 0x80)
		fwd -= 1.0;

	if(GetKeyState(' ') & 0x80)
		up += 1.0;

	if(up == 0.0 && fwd == 0.0 && right == 0.0 && m_Velocity.LengthSqr() == 0.0)
		return;

	double speed = 25.0;

	if(GetKeyState(VK_SHIFT) & 0x80)
		speed = 75.0;

	if(GetKeyState(VK_CONTROL) & 0x80)
		speed = 1.0;

	speed *= FrameTime;

	CVector vFwd = CVector(m_Pitch, m_Yaw) * fwd;
	CVector vRight = CVector(0.0, m_Yaw).Cross(CVector(0.0, 0.0, 1.0)) * right;
	CVector vUp = CVector(0.0, 0.0, 1.0) * up;

	CVector vComb = vUp + vRight + vFwd;

	vComb.Normalize();
	CVector TargetVelocity = vComb * speed;

	if(TargetVelocity.LengthSqr() == 0.0)
		m_VelocityAccumulator = 1;
	else
		m_VelocityAccumulator = 2;

	m_Velocity.Approach(TargetVelocity, m_VelocityAccumulator * FrameTime);

	m_Position += m_Velocity;

	if(GetKeyState('L') & 0x80)
		m_Position = CVector(10, 0, 1);
}