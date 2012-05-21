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
	stringstream ss;

	IConfigorNode* node = m_Config.GetRootNode()->GetChild("sensitivity");
	
	if(!node)
		m_Sensitivity = 1.0;
	else
	{
		ss << node->GetString();
		ss >> m_Sensitivity;
	}

	stringstream a;
	a << (*m_Config.GetRootNode())["debug"]["normals"].GetString();
	a >> m_DebugNormals;
}

void COptions::SaveSettings()
{
	stringstream ss;

	ss << m_Sensitivity;
	(*m_Config.GetRootNode())["sensitivity"] = (char*)ss.str().c_str();

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