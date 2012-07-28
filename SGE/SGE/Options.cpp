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
	
	IConfigorNode* node;
	
	node = m_Config.GetRootNode()->GetChild("sensitivity");
	if(!node)
		m_Sensitivity = 1.0;
	else
	{
		stringstream ss;
		ss << node->GetString();
		ss >> m_Sensitivity;
	}
	
	node = m_Config.GetRootNode()->GetChild("debug");
	if(node && node->GetChild("normals"))
	{
		stringstream ss;
		ss << node->GetChild("normals")->GetString();
		ss >> m_DebugNormals;
	}
	else
		m_DebugNormals = false;

	node = m_Config.GetRootNode()->GetChild("fov");
	if(node)
	{
		stringstream ss;
		ss << node->GetString();
		ss >> m_FOV;
	}
	else
		m_FOV = 90.0;
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
	stringstream ss;

	ss << m_Sensitivity;
	(*m_Config.GetRootNode())["sensitivity"] = (char*)ss.str().c_str();

	ss.str("");

	ss << m_FOV;
	(*m_Config.GetRootNode())["fov"] = (char*)ss.str().c_str();

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