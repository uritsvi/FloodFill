#pragma once

#include <Windows.h>

class Config
{
public:
	static Config& GetInstance() {
		static Config instance = Config();
		return instance;
	}

	void Init(
		HINSTANCE hInstance, 
		int cmdShow);

	HINSTANCE GetHINSTANCE();
	int GetCMDShow();

private:
	HINSTANCE m_hInstance;
	int m_cmdShow;
};

