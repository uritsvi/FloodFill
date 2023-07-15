#include "Config.h"

void Config::Init(
	HINSTANCE hInstance,
	int cmdShow) {

	m_hInstance = hInstance;
	m_cmdShow = cmdShow;
}

HINSTANCE Config::GetHINSTANCE() {
	return m_hInstance;
}
int Config::GetCMDShow() {
	return m_cmdShow;
}