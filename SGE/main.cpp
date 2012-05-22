#include "SGE/Engine.h"
CEngineInstance* pEngineInstance = 0;

#include <iostream>
#include <string>
#include <functional>
#include <sstream>
#include <fstream>

using namespace std;

#include "SGE/FileSystem.h"
#include "SGE/Model.h"


class CStaticProp : public CBaseEntity
{
	string 		m_ClassName;
	CModel		m_Model;
	CVector		m_Pos;
	CAngle		m_Ang;
	CShader		m_Shader;
	CTexture	m_Texture;
public:
	CStaticProp()
	{
		string s = CBaseEntity::GetClass();
		m_ClassName = "CStaticProp:" + s;
		m_Model.SetModel("bench.obj", true);
		m_Pos = CVector(0, 0, 0);
		m_Ang = CAngle(0, 0, 0);
		m_Shader = CShader();
		string null;
		m_Shader.Compile("wobble.shader", null);
		m_Shader.Call();
		m_Shader.SetUniform("time", pEngineInstance->GetTime());
		m_Texture.LoadFromFile("wood.tga");
	}
	~CStaticProp()
	{
	}
	const char* GetClass()
	{
		return m_ClassName.c_str();
	}
	void SetPosition(const CVector& Vec)
	{
		m_Pos = Vec;
	}
	void SetModel(const string& str, bool SwapYZ = false)
	{
		m_Model.SetModel(str, SwapYZ);
	}
	void Think() // Called every tick
	{
	}
	void Simulate(double Time) // Called every frame, with a frame time
	{
		m_Ang.Yaw += 10.0 * Time; // 10 Deg per second
	}
	void Draw()
	{
		glEnable(GL_TEXTURE_2D);
		m_Texture.Bind();
		m_Model.Draw(m_Pos, m_Ang);
		glDisable(GL_TEXTURE_2D);
	}
	void DrawDebug()
	{
		m_Model.DrawNormals(m_Pos, m_Ang);
	}
};

#include "SGE/Shader.h"

int main()
{
	pEngineInstance = new CEngineInstance();
	pEngineInstance->UpdateWindow("Testing", 0, 0, 32, false); // 0, 0 for loading from settings
		
	pEngineInstance->GetCamera()->SetPosition(CVector(-1, 0, 10));
	
	CStaticProp* Prop1 = new CStaticProp();
	Prop1->SetPosition(CVector(0, 0, 0));
	pEngineInstance->GetWorld()->AddEntity(Prop1);
	
	MSG msg;
	while(true)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))	// Is There A Message Waiting?
		{
			if(msg.message == WM_QUIT)
				break;

			WndProc(msg.hwnd, msg.message, msg.wParam, msg.lParam);

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		pEngineInstance->Update();
		pEngineInstance->Draw();
	}

	pEngineInstance->GetOptions()->SaveSettings();

	delete pEngineInstance;
}