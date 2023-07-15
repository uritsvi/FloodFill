#include <windowsx.h>

#include "Window.h"
#include "Config.h"
#include "Utils.h"

LRESULT WndProc(
	HWND hWnd, 
	UINT msg, 
	WPARAM wParam, 
	LPARAM lParam) {

	LONG_PTR instancePtr =
		GetWindowLongPtr(hWnd, GWLP_USERDATA);
	Window* instance = reinterpret_cast<Window*>(instancePtr);

	switch (msg) {
		case WM_CLOSE: {
			PostQuitMessage(0);
			instance->SetClose(true);

			return 0;
		}
	}

	instance->WndProcCallback(
		hWnd, 
		msg, 
		wParam, 
		lParam);

	return DefWindowProc(
		hWnd, 
		msg, 
		wParam, 
		lParam);
}

Window::Window(
	std::wstring windowName,
	int width, 
	int height) {

	m_Closed = false;

	m_Width = width;
	m_Height = height;

	RECT client = {0, 0, m_Width, m_Height};
	AdjustWindowRect(
		&client, 
		WS_OVERLAPPEDWINDOW, 
		FALSE);

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = Config::GetInstance().GetHINSTANCE();
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = windowName.c_str();
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(
		nullptr, 
		IDC_ARROW);

	RegisterClassExW(&wc);

	m_HWND =
		CreateWindowExW(
			0,
			windowName.c_str(),
			L"",
			WS_OVERLAPPEDWINDOW,
			0,
			0,
			client.right - client.left,
			client.bottom - client.top,
			NULL,
			NULL,
			Config::GetInstance().GetHINSTANCE(),
			NULL);

	if (m_HWND == nullptr) {
		Utils::ExitWithError("Failed to create window");
	}

	SetWindowLongPtrA(
		m_HWND, 
		GWLP_USERDATA, 
		(LONG_PTR)this);
}
Window::~Window() {

}

void Window::Show() {
	ShowWindow(
		m_HWND, 
		Config::GetInstance().GetCMDShow());
}

void Window::SetTitle(std::string string) {
	SetWindowTextA(m_HWND, string.c_str());
}

HWND Window::GetHWND() {
	return m_HWND;
}

bool Window::IsClosed() {
	return m_Closed;
}
void Window::SetClose(bool b) {
	m_Closed = b;
}

void Window::GetRect(RECT& out) {
	out.left = 0;
	out.top = 0;
	out.right = m_Width;
	out.bottom = m_Height;
}

void Window::Draw(char* ptr) {
	HDC DC = GetDC(m_HWND);
	
	BITMAPINFO info;
	ZeroMemory(&info, sizeof(info));

	info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	info.bmiHeader.biHeight = -m_Height;
	info.bmiHeader.biWidth = m_Width;
	info.bmiHeader.biBitCount = 32;
	info.bmiHeader.biCompression = BI_RGB;
	info.bmiHeader.biPlanes = 1;

	int i = SetDIBitsToDevice(
		DC,
		0,
		0,
		m_Width,
		m_Height,
		0,
		0,
		0,
		m_Height,
		ptr,
		&info,
		DIB_RGB_COLORS);

	ReleaseDC(
		m_HWND, 
		DC);
}

void Window::RegisterMouseCallback(
	MouseCallback callback, 
	void* p) {
	
	m_MouseCallback_P = p;
	m_MouseCallback = callback;
}

void Window::WndProcCallback(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam) {

	switch (msg) {
		case WM_LBUTTONDOWN: {
			POINT p;

			p.x = GET_X_LPARAM(lParam);
			p.y = GET_Y_LPARAM(lParam);

			m_MouseCallback(
				p, 
				m_MouseCallback_P);
		}
	}
}
