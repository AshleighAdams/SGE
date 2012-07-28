#ifndef OPTIONS_H
#define OPTIONS_H

#include "Configor.h"

struct res_t { unsigned int x; unsigned int y; };

class COptions
{
public:
	COptions();
	void SaveSettings();
	void LoadSettings();
	CConfigor& GetConfigor();
	double MouseSensitivity();
	double SetMouseSensitivity();
	double FOV();
	void SetFOV(double What);
	res_t GetResolution();
	void SetResolution();
	bool DebugNormals();
private:
	CConfigor m_Config;
	double m_Sensitivity;
	double m_FOV;
	bool m_DebugNormals;
};

#endif