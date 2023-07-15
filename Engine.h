#pragma once

#include <Windows.h>
#include <memory>
#include <vector>

#include "Constants.h"
#include "Window.h"

class Engine
{
public:
	Engine();

	void Run();

	void MouseCallback(
		POINT& point,
		void* p);

private:
	
	void Fill(
		POINT& point, 
		DWORD color);

private:
	std::shared_ptr<Window> m_Window;

	const int m_Width = 600;
	const int m_Height = 500;

	const std::wstring m_WindowClassName = L"FlattFillwindow";

	const int m_FullBufferSize = 
		m_Width *
		m_Height *
		Constants::BytesPerPixel;

	std::vector<char> m_ScreenBuffer;
};

