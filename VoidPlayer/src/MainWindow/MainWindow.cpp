/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#include "MainWindow.h"

#define PLAY_BUTTON 1

using namespace Controls;

inline void MainWindow::AddControls()
{
	playBtn = CustomDrawnIconButton();

	auto cbIcon = [](Graphics& graphics) {
		SolidBrush iconBrush(Color(255, 255, 255, 255));

		Point verticesT[] = { { 17, 15}, {17, 35}, {35,  25} }; // Why does trigRect.top + move it up??

		graphics.FillPolygon(&iconBrush, verticesT, 3);
	};

	if (playBtn.Create(hWnd, 50, 50, 50, 50, cbIcon, (HMENU)PLAY_BUTTON))
		MessageBox(hWnd, L"adawd", L"IS NOT NULL", NULL);
	else
		MessageBox(hWnd, L"adawd", L"IS NULL", NULL);
}

LRESULT MainWindow::HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CREATE:
			AddControls();
			return TRUE;

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
