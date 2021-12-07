/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#include "MainWindow.h"

using namespace ApplicationGUI;

LRESULT MainWindow::HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		HBRUSH brush = CreateSolidBrush(RGB(6, 32, 74));

		FillRect(hdc, &ps.rcPaint, brush);
		EndPaint(hWnd, &ps);

		return TRUE;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return TRUE;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);

	}

	return TRUE;
}
