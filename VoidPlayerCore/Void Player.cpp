#ifndef UNICODE
#define UNICODE
#endif

#include "Void Player.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	ApplicationGUI::MainWindow& wnd = ApplicationGUI::MainWindow::getInstance(hInstance);

	return wnd.Init();
}
