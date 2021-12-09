/* Copyright (C) 2021 Sabadi L�szl�-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>
#include <gdiplus.h>
#include "ApplicationGUI.h"

#include "MainWindow/MainWindow.h"

#ifdef _DEBUG

#include <fcntl.h>
#include <io.h>

class outbuf : public std::streambuf {
public:
	outbuf() {
		setp(0, 0);
	}

	virtual int_type overflow(int_type c = traits_type::eof()) {
		return fputc(c, stdout) == EOF ? traits_type::eof() : c;
	}
};

#endif // _DEBUG





int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
#ifdef _DEBUG :: Attach Debug Console
	AllocConsole();

	SetConsoleTitle(L"Debug Console");

	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
#endif

	MainWindow win;

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR					 gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	if (!win.Create(L"Void Player", WS_OVERLAPPEDWINDOW, WS_EX_ACCEPTFILES))
	{
		MessageBox(NULL, L"Failed to open program! Error: 1", L"Fatal Error! (Void Player)", MB_ICONERROR);
		return -1;
	}

	std::cout << "Test" << std::endl;

	ShowWindow(win.Window(), nCmdShow);

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Gdiplus::GdiplusShutdown(gdiplusToken);

	return 0;
}