#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <unordered_map>

#include "Vector.h"

class CPreProcessor
{
public:
	CPreProcessor();
	~CPreProcessor();
	void Define(const std::string& Def, const std::string& What);
	void Define(const std::string& Def);

	void Undefine(const std::string& Def);

	bool BuildShader(const std::string& file_in, std::string& out);
private:
	std::unordered_map<std::string, std::string> m_Defines;
};

class CShader
{
public:
	CShader();
	~CShader();
	CPreProcessor* GetPreProcessor();
	bool Compile(const std::string& File, std::string& Error);
	bool CreateProgram();
	bool Enable();
	bool Disable();
	void Call();
	void DrawQuad();

	void SetUniform(const std::string& Name, CVector& Value);
	void SetUniform(const std::string& Name, float Value);
	void SetUniform(const std::string& Name, double Value);
	void SetUniform(const std::string& Name, int Value);

private:
	
	
	CPreProcessor m_PreProcessor;
	std::string m_Shader;

	int m_Program;

	int m_VSOID;
	int m_FSOID;

	std::string m_VertexShader;
	std::string m_FragmentShader;
	std::string m_GeometryShader;
};

#endif