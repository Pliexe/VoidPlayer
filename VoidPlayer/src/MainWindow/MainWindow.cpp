/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#include "MainWindow.h"

using namespace Controls;

inline void MainWindow::AddControls()
{
#ifdef _DEBUG
	std::cout << "Hi" << std::endl;
#endif

	musicPanel = Panel();

	musicPanel.EnableDynamicResizing();
	musicPanel.SetAnchorY(ANCHOR_BOTTOM);
	musicPanel.SetPosPivot(PIVOT_LEFT_BOTTOM);
	musicPanel.SetWidthPercent(100);
	musicPanel.SetSize(0, 100);
	musicPanel.SetBackgroundBrush(CreateSolidBrush(RGB(200, 200, 200)));

	RegisterControl(&musicPanel);

	playBtn = CustomDrawnIconButton();

	playBtn.EnableDynamicResizing();
	playBtn.SetAnchorX(ANCHOR_MIDDLE);
	playBtn.SetPosAndSize(0, 10, 50, 50);
	playBtn.SetPosPivot(PIVOT_LEFT_MIDDLE_TOP_RIGHT);
	playBtn.SetBkgColor(Color(50, 50, 50));
	playBtn.SetIconCallback([](Graphics& graphics) {

		SolidBrush iconBrush(Color(255, 255, 255, 255));

		Point verticesT[] = { { 17, 15}, {17, 35}, {35,  25} }; // Why does trigRect.top + move it up??

		graphics.FillPolygon(&iconBrush, verticesT, 3);

	});

	playBtn.onMouseDown = [](HWND hwnd, MouseButton btn) {
		MessageBox(hwnd, L"Button clicked!", L"Eyyy it works!!! EVENTS BABY!", MB_OKCANCEL);
	};

	musicPanel.RegisterControl(&playBtn);

	prevBtn = CustomDrawnIconButton();

	prevBtn.EnableDynamicResizing();
	prevBtn.SetAnchorX(ANCHOR_MIDDLE);
	prevBtn.SetPosAndSize(-70, 10, 50, 50);
	prevBtn.SetPosPivot(PIVOT_LEFT_MIDDLE_TOP_RIGHT);
	prevBtn.SetBkgColor(Color(50, 50, 50));
	prevBtn.SetIconCallback([](Graphics& graphics) {

		SolidBrush iconBrush(Color(255, 255, 255, 255));
		Pen iconPen(Color(255, 255, 255, 255));

		Point vertices1P[] = { {25, 15}, {25, 35}, {15, 25} };
		Point vertices2P[] = { {35, 15}, {35, 35}, {25, 25} };

		graphics.FillPolygon(&iconBrush, vertices1P, 3);
		graphics.FillPolygon(&iconBrush, vertices2P, 3);
		graphics.DrawLine(&iconPen, 15, 15, 15, 35);

	});

	prevBtn.onMouseDown = [](HWND hwnd, MouseButton btn) {
		MessageBox(hwnd, L"Button clicked!", L"Eyyy it works!!! EVENTS BABY!", MB_OKCANCEL);
	};

	musicPanel.RegisterControl(&prevBtn);

	nextBtn = CustomDrawnIconButton();

	nextBtn.EnableDynamicResizing();
	nextBtn.SetAnchorX(ANCHOR_MIDDLE);
	nextBtn.SetPosAndSize(70, 10, 50, 50);
	nextBtn.SetPosPivot(PIVOT_LEFT_MIDDLE_TOP_RIGHT);
	nextBtn.SetBkgColor(Color(50, 50, 50));
	nextBtn.SetIconCallback([](Graphics& graphics) {

		SolidBrush iconBrush(Color(255, 255, 255, 255));
		Pen iconPen(Color(255, 255, 255, 255));

		Point vertices1P[] = { {15, 15}, {15, 35}, {25, 25} };
		Point vertices2P[] = { {25, 15}, {25, 35}, {35, 25} };

		graphics.FillPolygon(&iconBrush, vertices1P, 3);
		graphics.FillPolygon(&iconBrush, vertices2P, 3);
		graphics.DrawLine(&iconPen, 35, 15, 35, 35);

	});

	nextBtn.onMouseDown = [](HWND hwnd, MouseButton btn) {
		MessageBox(hwnd, L"Button clicked!", L"Eyyy it works!!! EVENTS BABY!", MB_OKCANCEL);
	};

	musicPanel.RegisterControl(&nextBtn);


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

		case WM_LBUTTONDOWN:
		{
			MessageBox(hWnd, L"HEYYY", L"Clicked inside window", 0);

			return TRUE;
		}

		case WM_SIZE:
		{
			RECT rect;

			GetClientRect(hWnd, &rect);

			musicPanel.OnParentResize(rect);

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
