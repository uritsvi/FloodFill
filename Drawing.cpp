#define _USE_MATH_DEFINES
#include <math.h>

#include "Drawing.h"

#define TO_RAD(x) x / 180.0f * M_PI

void Drawing::ConvertNormalizedToCartision(
	RECT& const windowRect,
	FPOINT& const p,
	POINT& out) {

	float x = (p.x + 1) / 2.0f;
	float y = (-p.y + 1) / 2.0f;
	
	out.x = x * (windowRect.right - windowRect.left);
	out.y = y * (windowRect.bottom - windowRect.top);
}

void Drawing::DrawLine(
	Window& window,
	std::vector<char>& buffer,
	FPOINT& const p1,
	FPOINT& const p2) {

	POINT cP1;
	POINT cP2;

	RECT windowRect;
	window.GetRect(windowRect);

	Drawing::ConvertNormalizedToCartision(
		windowRect,
		p1,
		cP1);

	Drawing::ConvertNormalizedToCartision(
		windowRect,
		p2,
		cP2);


	int windowWidth =
		windowRect.right -
		windowRect.left;

	auto start = cP1.x < cP2.x ? cP1 : cP2;

	float m = ((float)cP1.y - cP2.y) / ((float)cP1.x - cP2.x);
	if (((float)cP1.y - cP2.y) == 0 && ((float)cP1.x - cP2.x) == 0) {
		m = 0;
	}
	

	float b = start.y;

	int startX = start.x * Constants::BytesPerPixel;

	for (int i = 0;
		i <= abs(cP1.x - cP2.x) * Constants::BytesPerPixel;
		i += Constants::BytesPerPixel)
	{

		if (i / Constants::BytesPerPixel == 600) {
			int a = 0;
		}

		int y = (i / Constants::BytesPerPixel  * m) + b;

		if (!PtInRect(
			&windowRect,
			POINT{ (startX + i) / 4, y }))
		{

			continue;
		}

		PaintFullPixel(buffer, (startX + i) + (y * windowWidth * Constants::BytesPerPixel), 255);

	}
}

void Drawing::DrawCircule(
	Window& window,
	std::vector<char>& buffer, 
	float radius) {
		
	for (float i = 0; i < 360.0f; i += 0.01f) {
			float x = cosf(TO_RAD(i)) * radius;
			float y = sinf(TO_RAD(i)) * radius;

			auto point = FPOINT{ x, y };

			Drawing::DrawLine(
				window,
				buffer,
				point,
				point);
		}
	}

void Drawing::PaintFullPixel(
	std::vector<char>& buffer,
	int baseAddress,
	char color) {

	buffer[baseAddress] = color;
	buffer[baseAddress + 1] = color;
	buffer[baseAddress + 2] = color;
	buffer[baseAddress + 3] = color;
}

