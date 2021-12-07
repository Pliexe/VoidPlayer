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

#include "CustomDrawnIconButton.h"

namespace Controls {

	bool CustomDrawnIconButton::Create(HWND parent, int x, int y, int width, int height, void(*iconCallback)(Graphics&), HMENU hmenu, Color backgroundColor)
	{
		m_backgroundColor = backgroundColor;
		m_iconCallback = iconCallback;
		Control::Create(parent, x, y, width, height, hmenu);

		RegisterClassIfUnregistered(parent, this->DefaultClass());

		return RegisterDefaultWindow(x, y, width, height, parent, hmenu);
	}

	bool CustomDrawnIconButton::Create(HWND parent, int x, int y, int width, int heigth, void (*iconCallback)(Graphics&), Color brushbackgroundColor1, Color brushbackgroundColor2, HMENU hmenu)
	{
		m_backgroundColor2 = brushbackgroundColor2;
		useGradient = true;
		return this->Create(parent, x, y, width, heigth, iconCallback, hmenu, brushbackgroundColor1);
	}

	void CustomDrawnIconButton::OnPaint(HDC& hdc, PAINTSTRUCT& ps)
	{
		Graphics graphics(hdc); // Create graphics class?

		graphics.SetSmoothingMode(SmoothingModeHighQuality); // Set smoothing to high quality for crispy look ;)

		RECT cRect;

		GetClientRect(hWnd, &cRect);

		if (useGradient)
		{
			Point point1(0, 0);
			Point point2(50, 50);

			LinearGradientBrush circleBrush(point1, point2, m_backgroundColor, m_backgroundColor2);
			graphics.FillEllipse(&circleBrush, 0, 0, m_width, m_height);
		} else
		{
			SolidBrush circleBrush(m_backgroundColor);
			graphics.FillEllipse(&circleBrush, 0, 0, m_width, m_height);
		}

		SolidBrush iconBrush(Color(255, 255, 255));

		m_iconCallback(graphics);
	}

	LRESULT CustomDrawnIconButton::HandleMessage(UINT umsg, WPARAM wParam, LPARAM lParam)
	{
		switch (umsg)
		{
			default:
				return DefWindowProc(hWnd, umsg, wParam, lParam);
		}

		return TRUE;
	}

}


