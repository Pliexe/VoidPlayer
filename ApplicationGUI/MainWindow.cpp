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

		musicControlPanel = CreateWindow(
			_T("Static"),
			NULL,
			WS_VISIBLE | WS_CHILD | WS_BORDER | BS_OWNERDRAW,
			0,
			0,
			width,
			height,
			hWnd,
			NULL,
			(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			NULL
		);

		playButton = CreateWindow(
			_T("BUTTON"),	// Predifined class
			_T("PLAY"),	// Button Text
			WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, // SS_OWNERDRAWN
			width / 2,			// x position
			height - 150,			// y position
			50,		// Button width
			50,		// Button height
			hWnd,		// Parent window
			(HMENU)PLAY_BUTTON,		// No menu
			(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			NULL		// ptr not needed
		);

		CreateWindow(
			_T("BUTTON"),	// Predifined class
			_T("BACK"),	// Button Text
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			width / 2 - 100,			// x position
			height - 150,			// y position
			50,		// Button width
			50,		// Button height
			hWnd,		// Parent window
			NULL,		// No menu
			(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			NULL		// ptr not needed
		);

		CreateWindow(
			_T("BUTTON"),	// Predifined class
			_T("FORWARD"),	// Button Text
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			width / 2 + 100,			// x position
			height - 150,			// y position
			50,		// Button width
			50,		// Button height
			hWnd,		// Parent window
			NULL,		// No menu
			(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			NULL		// ptr not needed
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

	case WM_DRAWITEM:
	{
		DRAWITEMSTRUCT* lpDrawItem = (DRAWITEMSTRUCT*)lParam;

		PAINTSTRUCT		 ps;
		HDC				 hdc;

		if (lpDrawItem->hwndItem == playButton)
		{
			HRGN hrgnBtn1 = CreateRectRgn(0, 0, 0, 0);
			GetWindowRgn(lpDrawItem->hwndItem, hrgnBtn1);
			RECT rcClient; GetClientRect(lpDrawItem->hwndItem, &rcClient);

			FillRect(lpDrawItem->hDC, &lpDrawItem->rcItem, GetSysColorBrush(COLOR_WINDOW));

			
			
			rcClient.top += 1, rcClient.left += 1;
			HRGN hrgnBtn2 = CreateEllipticRgnIndirect(&rcClient);
			//FillRgn(lpDrawItem->hDC, hrgnBtn2, GetSysColorBrush(COLOR_BTNSHADOW));
			FillRgn(lpDrawItem->hDC, hrgnBtn2, GetSysColorBrush(COLOR_BTNFACE));
			
			HBRUSH hbrush1 = CreateSolidBrush(RGB(255, 255, 0));

			Graphics graphics(lpDrawItem->hDC);

			graphics.SetSmoothingMode(SmoothingModeHighQuality);
			

			RECT trigRect;
			GetClientRect(lpDrawItem->hwndItem, &trigRect);

			Rect rRectT(trigRect.left, trigRect.top, trigRect.right, trigRect.bottom);

			

			trigRect.left += 20;
			trigRect.right -= 15;

			trigRect.top += 15;
			trigRect.bottom -= 15;

			Point point1(rRectT.X, rRectT.Y);
			Point point2(rRectT.Width, rRectT.Height);

			LinearGradientBrush circleBrush(point1, point2, Color(255, 0, 0, 255), Color(255, 0, 100, 100));
			SolidBrush iconBrush(Color(255, 255, 255, 255));


			Point verticesT[] = { {trigRect.left, trigRect.top}, {trigRect.left, trigRect.bottom}, {trigRect.right,  (trigRect.top - (trigRect.top - trigRect.bottom) / 2)} }; // Why does trigRect.top + move it up??

			graphics.FillEllipse(&circleBrush, rRectT);
			graphics.FillPolygon(&iconBrush, verticesT, 3);

			DeleteObject(hrgnBtn2);

			DeleteObject(hrgnBtn1);
		}
		else if (lpDrawItem->hwndItem == musicControlPanel)
		{
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));

			RECT rcClient; GetClientRect(lpDrawItem->hwndItem, &rcClient);

			FillRect(lpDrawItem->hDC, &lpDrawItem->rcItem, hBrush);
		}


		return 0;
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

		Graphics graphics(hdc);

		SolidBrush solidBrush(Color(255, 255, 0, 0));

		graphics.FillRectangle(&solidBrush, 0, 0, 100, 100);

		graphics.FillEllipse(&solidBrush, 0, 0, 100, 60);

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
