#include <Windows.h>
#include <memory>

#include "Window.h"
#include "Config.h"
#include "Engine.h"

int WinMain(
	HINSTANCE hInstance, 
	HINSTANCE pInstance, 
	LPSTR cmd, 
	int cmdShow){

	Config::GetInstance().Init(
		hInstance, 
		cmdShow);

	auto engine = std::make_shared<Engine>();
	engine->Run();

	return 0;
}