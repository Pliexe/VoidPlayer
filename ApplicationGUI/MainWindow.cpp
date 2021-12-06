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

#include "MainWindow.h"
#include "MusicHandler.h"

using namespace ApplicationGUI;
using namespace Gdiplus;
using namespace Music;

void MainWindow::AddControls()
{
	RECT rect;

	if (GetClientRect(hWnd, &rect))
	{
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;

		musicControlPanel = MusicControlPanel();

		musicControlPanel.EnableDynamicResizing();
		musicControlPanel.SetAnchorY(Controls::ANCHOR_BOTTOM);
		musicControlPanel.SetWidthPercent(100);
		musicControlPanel.SetPosPivot(ControlPivot::LEFT_BOTTOM);

		musicControlPanel.Create(
			hWnd,
			0, 0,
			width, 150,
			Color(33, 26, 54)
		);

		Button btn;

		btn.SetPos(10, 10);

		btn.SetPosAndSize(10, 10, 50, 50);

		//btn.Create(hWnd);
	}
	else {
		MessageBox(hWnd, L"Failed to get window width, height!", L"Error!", MB_ICONERROR);
		DestroyWindow(hWnd);
	}
}

LRESULT MainWindow::HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{

	case WM_SIZE:
	{
		RECT rect;
		GetClientRect(hWnd, &rect);
	
		//SetWindowPos(musicControlPanel.hWnd, NULL, 0, rect.bottom - rect.top - 150, rect.right - rect.left, 150, SWP_NOZORDER);

		musicControlPanel.OnParentResize(rect);

		return TRUE;
	}

	case WM_DROPFILES:
	{
		HDROP hDropInfo = (HDROP)wParam;
		wchar_t sItem[MAX_PATH];

		DragQueryFile(hDropInfo, 0, (LPWSTR)sItem, sizeof(sItem));

		if (GetFileAttributes(sItem) &FILE_ATTRIBUTE_DIRECTORY)
			MessageBox(hWnd, L"Got folder, i cant play this man!", L"VoidPlayer", 0);
		else
		{
			MessageBox(hWnd, L"Got sound file", sItem, 0);
			MusicHandler::getInstance().PlayTest(std::wstring(sItem));
		} 

		DragFinish(hDropInfo);

		return TRUE;
	}

	case WM_DRAWITEM:
	{
		/*DRAWITEMSTRUCT* lpDrawItem = (DRAWITEMSTRUCT*)lParam;

		if (lpDrawItem->hwndItem == musicControlPanel.hWnd)
		{
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));

			RECT rcClient; GetClientRect(lpDrawItem->hwndItem, &rcClient);

			FillRect(lpDrawItem->hDC, &lpDrawItem->rcItem, hBrush);
		}*/


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

		HBRUSH brush = CreateSolidBrush(RGB(6, 32, 74));

		FillRect(hdc, &ps.rcPaint, brush);
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
