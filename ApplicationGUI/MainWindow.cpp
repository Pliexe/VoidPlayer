/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#include "MainWindow.h"

using namespace ApplicationGUI;
using namespace Gdiplus;

void MainWindow::AddControls()
{
	RECT rect;

	if (GetWindowRect(hWnd, &rect))
	{
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;

		musicControlPanel = MusicControlPanel();

		musicControlPanel.Create(
			hWnd,
			0, height - 150,
			width, 150,
			Color(255, 0, 0)
		);
	}
	else {
		MessageBox(hWnd, _T("Failed to get window width, height!"), _T("Error!"), MB_ICONERROR);
		DestroyWindow(hWnd);
	}
}

LRESULT MainWindow::HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{

	case WM_SIZE:
	{


		return TRUE;
	}

	case WM_DRAWITEM:
	{
		DRAWITEMSTRUCT* lpDrawItem = (DRAWITEMSTRUCT*)lParam;

		if (lpDrawItem->hwndItem == musicControlPanel.hWnd)
		{
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));

			RECT rcClient; GetClientRect(lpDrawItem->hwndItem, &rcClient);

			FillRect(lpDrawItem->hDC, &lpDrawItem->rcItem, hBrush);
		}


		return TRUE;
	}
	case WM_CREATE:

		AddControls();

		return 0;

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


	case WM_COMMAND:

		switch (wParam)
		{
		case PLAY_BUTTON:
			MessageBox(hWnd, TEXT("Clicked"), TEXT("EYY"), MB_OK);
			break;
		}

		return 0;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return TRUE;
}
