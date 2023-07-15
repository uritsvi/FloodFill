#include <Windows.h>

#include "Utils.h"

void Utils::ExitWithError(std::string errorMsg) {
	MessageBoxA(
		NULL, 
		errorMsg.c_str(), 
		NULL, 
		MB_OK);
}