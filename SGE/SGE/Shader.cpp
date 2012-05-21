#include "Shader.h"
#define WIN32_LEAN_AND_MEAN

#include "Engine.h"

#include <functional>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <Shellapi.h>

using namespace std;

CPreProcessor::CPreProcessor()
{
}
CPreProcessor::~CPreProcessor()
{
}

bool CPreProcessor::BuildShader(const std::string& file, std::string& out)
{
	string app = pEngineInstance->GetFileSystem()->GetBaseDIR() + "lupo.exe";
	LPCTSTR lpApplicationName = (LPCTSTR)app.c_str();

	STARTUPINFO lpStartupInfo;
	PROCESS_INFORMATION  lpProcessInfo;

	memset(&lpStartupInfo, 0, sizeof(lpStartupInfo));
	memset(&lpProcessInfo, 0, sizeof(lpProcessInfo));

	lpStartupInfo.cb = sizeof(lpStartupInfo);
	
	string commandline = "";

	if(m_Defines.size() > 0)
	{
		// set the defines
		for(auto it = m_Defines.begin(); it != m_Defines.end(); it++)
		{
			commandline += "-d" + (*it).first;
			commandline += "=";
			commandline += "\"" + (*it).second + "\" ";
		}
	}

	commandline += " \"" + pEngineInstance->GetFileSystem()->GetShader(file) + "\"";

	string env = pEngineInstance->GetFileSystem()->GetShader("");

	SetEnvironmentVariable((LPCSTR)"LUPO_INCLUDEPATH", (LPCSTR)env.c_str());
	SetCurrentDirectory((LPCSTR)env.c_str());

	DeleteFile("lupo.out");

	ShellExecute(0, 0, lpApplicationName, (LPSTR)commandline.c_str(), 0, SW_SHOWNORMAL);
	/*
	if (!CreateProcess(lpApplicationName, (LPSTR)commandline.c_str(), 0, 0, true, 0, 0, 0, &lpStartupInfo, &lpProcessInfo))
	{
		DWORD err = GetLastError();
		return false;
	}*/

	WaitForSingleObject(lpProcessInfo.hProcess, INFINITE);
	CloseHandle(lpProcessInfo.hProcess);
	CloseHandle(lpProcessInfo.hThread);
	
	double t = pEngineInstance->GetTime();
	while(pEngineInstance->GetTime() - t < 0.2);

	ifstream ifs("lupo.out");

	if(!ifs.is_open())
		return false;

	ifs.seekg(0, ios::end);
	size_t len = ifs.tellg();
	ifs.seekg(0, ios::beg);

	char* in = new char[len];

	ifs.read(in, len);
	out = string(in, len);

	delete [] in;
	return true;
}

void CPreProcessor::Define(const std::string& Def, const std::string& What)
{
	m_Defines[Def] = What;
}

void CPreProcessor::Define(const std::string& Def)
{
	Define(Def, "1");
}

void CPreProcessor::Undefine(const std::string& Def)
{
	m_Defines.erase(Def);
}

CShader::CShader()
{
	m_FSOID = m_VSOID = m_Program = 0;
}

CShader::~CShader()
{

}

bool CShader::Compile(const std::string& File, std::string& Error)
{
	m_Shader = File;

	m_PreProcessor.Define("VERTEX");
	if(!m_PreProcessor.BuildShader(m_Shader, m_VertexShader))
		return false;
	m_PreProcessor.Undefine("VERTEX");
	
	m_PreProcessor.Define("FRAGMENT");
	if(!m_PreProcessor.BuildShader(m_Shader, m_FragmentShader))
		return false;
	m_PreProcessor.Undefine("FRAGMENT");

	m_VSOID = glCreateShader(GL_VERTEX_SHADER);
	m_FSOID = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vs = m_VertexShader.c_str();
	const char* fs = m_VertexShader.c_str();

	glShaderSource(m_VSOID, 1, &vs, 0);
	glShaderSource(m_FSOID, 1, &fs, 0);

	glCompileShader(m_VSOID);
	glCompileShader(m_FSOID);

	m_Program = glCreateProgram();
	glAttachShader(m_Program, m_VSOID);
	glAttachShader(m_Program, m_FSOID);

	glLinkProgram(m_Program);

	return true;
}

void CShader::SetUniform(const std::string& Name, CVector& Value)
{
	int v = glGetUniformLocation(m_Program, Name.c_str());
	glUniform3d(v, Value.X, Value.Y, Value.Z);
}

void CShader::SetUniform(const std::string& Name, float Value)
{
	int v = glGetUniformLocation(m_Program, Name.c_str());
	glUniform1f(v, Value);
}

void CShader::SetUniform(const std::string& Name, double Value)
{
	int v = glGetUniformLocation(m_Program, Name.c_str());
	glUniform1d(v, Value);
}

void CShader::SetUniform(const std::string& Name, int Value)
{
	int v = glGetUniformLocation(m_Program, Name.c_str());
	glUniform1i(v, Value);
}

void CShader::Call()
{
	glUseProgram(m_Program);
}

void CShader::DrawQuad()
{
	glBegin(GL_QUADS);
		glVertex2d(-1, -1);
		glVertex2d(+1, -1);
		glVertex2d(+1, +1);
		glVertex2d(-1, +1);
	glEnd();
}