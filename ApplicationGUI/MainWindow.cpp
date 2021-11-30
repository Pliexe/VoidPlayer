/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#include "MainWindow.h"

using namespace ApplicationGUI;

#pragma region Singletoon instance getter

MainWindow& MainWindow::getInstance(HINSTANCE hInstance)
{
	static MainWindow instance;

	instance.hInstance = hInstance;

	return instance;
}

#pragma endregion

LRESULT ApplicationGUI::MainWindow::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
	{
		// Fill in data

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		// Paint

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(hWnd, &ps);

		return 0;
	}

	case WM_CLOSE:
	{
		if (MessageBox(hWnd, TEXT("Really quit?"), TEXT("My app"), MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(hWnd);
		}

		return 0;
	}

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int ApplicationGUI::MainWindow::Init()
{
	WNDCLASS wc = {};

	wc.lpfnWndProc = MainWindow::WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	hWnd = CreateWindowEx(
		0, // Optional Window Styles
		CLASS_NAME,
		TEXT("Void Player"),
		WS_OVERLAPPEDWINDOW, // Window style

		// Size and Position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,		// Parent window
		NULL,		// Menu
		hInstance,	// Instance Handle
		NULL		// Additional application data
	);

	if (hWnd == NULL)
	{
		MessageBox(NULL, TEXT("Failed to open window!"), TEXT("Void Player Error!"), MB_ICONERROR);
		return -1;
	}

	ShowWindow(hWnd, SW_SHOW);

	MSG msg;
	
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}