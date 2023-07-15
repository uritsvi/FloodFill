#pragma once

#include <vector>
#include <Windows.h>

#include "Window.h"
#include "Constants.h"

struct FPOINT {
	float x;
	float y;
};

class Drawing
{
public:
	static void ConvertNormalizedToCartision(
		RECT& const windowRect,
		FPOINT& const p,
		POINT& out);

	static void DrawLine(
		Window& window,
		std::vector<char>& buffer,
		FPOINT& const p1,
		FPOINT& const p2);

	 static void DrawCircule(
		Window& window,
		std::vector<char>& buffer,
		float radius);

	 static void PaintFullPixel(
		 std::vector<char>& buffer, 
		 int baseAddress, 
		 char color);
};

