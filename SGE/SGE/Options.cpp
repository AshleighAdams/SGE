#include "Options.h"
#include "Configor.h"
#include "Engine.h"
#include <sstream>

using namespace std;

COptions::COptions()
{
}



void COptions::LoadSettings()
{
	m_Config.LoadFromFile(pEngineInstance->GetFileSystem()->GetConfig("options.cfg"));
	
	m_FOV = m_Config["fov"].GetValue<double>(90.0);
	m_Sensitivity = m_Config["sensitivity"].GetValue<double>(1.0);
	m_DebugNormals = m_Config["debug"]["normals"].GetValue<bool>(false);
}

CConfigor& COptions::GetConfigor()
{
	return m_Config;
}

void COptions::SetFOV(double Val)
{
	m_FOV = Val;
}

double COptions::FOV()
{
	return m_FOV;
}

void COptions::SaveSettings()
{
	m_Config["fov"].SetValue(m_FOV);
	m_Config["sensitivity"].SetValue(m_Sensitivity);

	m_Config.SaveToFile(pEngineInstance->GetFileSystem()->GetConfig("options.cfg"));
}

res_t COptions::GetResolution()
{
	stringstream a;
	a << (*m_Config.GetRootNode())["resolution"]["x"].GetString();

	stringstream b;
	b << (*m_Config.GetRootNode())["resolution"]["y"].GetString();

	res_t ret;
	a >> ret.x;
	b >> ret.y;
	return ret;
}

double COptions::MouseSensitivity()
{
	return m_Sensitivity;
}

bool COptions::DebugNormals()
{
	return m_DebugNormals;
}