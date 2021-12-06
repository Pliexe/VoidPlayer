/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#ifndef UNICODE
#define UNICODE
#endif

#include "Void Player.h"

using namespace Gdiplus;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	ApplicationGUI::MainWindow win;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR			gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	if (!win.Create(TEXT("Void Player"), WS_OVERLAPPEDWINDOW | CS_HREDRAW | CS_VREDRAW, WS_EX_ACCEPTFILES))
	{
		MessageBox(NULL, L"Failed to open program! Error: 1", L"Fatal Error! (Void Player)", MB_ICONERROR);
		return 0;
	}

	ShowWindow(win.Window(), nCmdShow);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	GdiplusShutdown(gdiplusToken);

	return 0;
}
