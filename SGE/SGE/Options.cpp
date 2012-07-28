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

void COptions::SaveSettings()
{
	m_Config["fov"].SetValue(m_FOV);
	m_Config["sensitivity"].SetValue(m_Sensitivity);

	m_Config.SaveToFile(pEngineInstance->GetFileSystem()->GetConfig("options.cfg"));
}

IConfigorNode& COptions::GetSetting(const string Name)
{
	string CurrentName = "";
	IConfigorNode* CurrentNode = m_Config.GetRootNode();
	char x;

	for(size_t i = 0; i < Name.length(); i++)
	{
		x = Name[i];
		if(x == '.')
		{
			CurrentNode = &(*CurrentNode)[CurrentName];
			CurrentName = "";
		}
		else if(x >= 'A' && x <= 'Z')
			CurrentName += x + 32;
		else
			CurrentName += x;
	}

	return (*CurrentNode)[CurrentName];
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