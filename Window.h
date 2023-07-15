#pragma once

#include <Windows.h>

#include <string>

typedef void(*MouseCallback)(
	POINT& point, 
	void* p);

class Window
{
public:
	Window(
		std::wstring windowName,
		int width,
		int height);

	~Window();

	void Show();

	void Draw(char* ptr);
	void SetTitle(std::string s);

	HWND GetHWND();

	void SetClose(bool b);
	bool IsClosed();

	void GetRect(RECT& out);

	void RegisterMouseCallback(
		MouseCallback callback, 
		void* p);

	void WndProcCallback(
		HWND hWnd, 
		UINT msg, 
		WPARAM wParam, 
		LPARAM lParam);

private:
	HWND m_HWND;

	int m_Width;
	int m_Height;

	bool m_Closed;

	MouseCallback m_MouseCallback;
	void* m_MouseCallback_P;
};

