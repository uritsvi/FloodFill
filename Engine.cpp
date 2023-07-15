#include <list>

#include "Engine.h"
#include "Drawing.h"

Engine::Engine() {
	m_ScreenBuffer = std::vector<char>(m_FullBufferSize);

	m_Window = std::make_shared<Window>(
		m_WindowClassName.c_str(),
		m_Width,
		m_Height);
}

void Engine::Run() {
	m_Window->Show();

	Drawing::DrawCircule(*m_Window.get(), m_ScreenBuffer, 0.3f);
	Drawing::DrawCircule(*m_Window.get(), m_ScreenBuffer, 0.7f);


	m_Window->RegisterMouseCallback([](POINT& point, void* p) {
		auto instance = reinterpret_cast<Engine*>(p);
		instance->MouseCallback(point, p);
	},
	this);

	while (!m_Window->IsClosed())
	{
		MSG msg;
		msg.message = 0;

		if (PeekMessageA(
			&msg,
			nullptr,
			0,
			0,
			TRUE)) {

			TranslateMessage(&msg);
			DispatchMessageA(&msg);

		}

		m_Window->Draw((char*)m_ScreenBuffer.data());

	}

}

void Engine::Fill(
	POINT& point,
	DWORD color) {
	
	auto currentPoints = std::make_shared<std::list<POINT>>();
	currentPoints->push_back(point);
	
	auto nextPoints = std::make_shared<std::list<POINT>>();

	do {

		for (auto currentPoint : *currentPoints) {

			auto pointAddr = 
				(currentPoint.y * m_Width * Constants::BytesPerPixel) + 
				(currentPoint.x * Constants::BytesPerPixel);

			if (m_ScreenBuffer[pointAddr] != color) {
				continue;
			}

			Drawing::PaintFullPixel(
				m_ScreenBuffer, 
				pointAddr, 
				255);

			// left
			if (pointAddr - Constants::BytesPerPixel >= 0 && 
				m_ScreenBuffer[pointAddr-Constants::BytesPerPixel] == color) {
				
				nextPoints->push_back(POINT{ currentPoint.x-1, currentPoint.y });
			}
			// right
			if (pointAddr - Constants::BytesPerPixel < m_FullBufferSize &&
				m_ScreenBuffer[pointAddr + Constants::BytesPerPixel] == color) {
				
				nextPoints->push_back(POINT{ currentPoint.x+1, currentPoint.y });
			}
			// top
			if (pointAddr-(Constants::BytesPerPixel * m_Width) >= 0 &&
				m_ScreenBuffer[pointAddr-(Constants::BytesPerPixel * m_Width)] == color) {
				
				nextPoints->push_back(POINT{ currentPoint.x, currentPoint.y-1 });
			}
			// bottom
			if (pointAddr+(Constants::BytesPerPixel * m_Width) < m_FullBufferSize &&
				m_ScreenBuffer[pointAddr + (Constants::BytesPerPixel * m_Width)] == color) {
				
				nextPoints->push_back(POINT{ currentPoint.x, currentPoint.y+1 });
			}

		}

		currentPoints->clear();
		auto temp = currentPoints;

		currentPoints = nextPoints;
		nextPoints = temp;




	} while (currentPoints->size() > 0);
}

void Engine::MouseCallback(
	POINT& point,
	void* p) {

	DWORD color = 
		m_ScreenBuffer[
			(point.y * Constants::BytesPerPixel * m_Width) + 
			point.x * Constants::BytesPerPixel];

	Fill(point, color);
}
