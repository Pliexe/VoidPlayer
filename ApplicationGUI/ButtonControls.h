/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#pragma once

#include <Windows.h>
#include <gdiplus.h>
#include "Controls.h"

using namespace Gdiplus;

namespace Controls {
	
	class CustomDrawnCircleButton : public Control
	{
	public:
		Color m_backgroundColor;
		Color m_backgroundColor2;
		int m_height;
		int m_width;

		bool gradient = false;

		void Create(
			HWND parent,
			int x, int y,
			int width, int height,
			HMENU hmenu = NULL,
			Color _backgroundColor = Color(50, 50, 50)
		)
		{
			m_width = width;
			m_height = height;

			m_backgroundColor = _backgroundColor;

			hWnd = CreateWindow(
				TEXT("STATIC"),
				NULL,
				WS_VISIBLE | WS_CHILD | SS_OWNERDRAW | SS_NOTIFY,
				x, y, width, height,
				parent,
				hmenu,
				(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
				NULL
			);
		}

		void CreateWithGradient(
			HWND parent,
			int x, int y,
			int width, int height,
			HMENU hmenu = NULL,
			Color _backgroundColor = Color(50, 50, 50),
			Color _backgroundColor2 = Color(70, 70, 70)
		) {
			m_backgroundColor2 = _backgroundColor2;
			gradient = true;
			this->Create(parent, x, y, width, height, hmenu, _backgroundColor);
		}
			

		void DrawControl(DRAWITEMSTRUCT* lpDrawItem, void (*iconCallback)(Graphics&))
		{
			Graphics graphics(lpDrawItem->hDC); // Create graphics class?

			graphics.SetSmoothingMode(SmoothingModeHighQuality); // Set smoothing to high quality for crispy look ;)

			RECT cRect;

			GetClientRect(lpDrawItem->hwndItem, &cRect);

			if (gradient)
			{
				Point point1(0, 0);
				Point point2(50, 50);

				LinearGradientBrush circleBrush(point1, point2, m_backgroundColor, m_backgroundColor2);
				graphics.FillEllipse(&circleBrush, 0, 0, m_width, m_height);
			}
			else
			{
				SolidBrush circleBrush(m_backgroundColor);
				graphics.FillEllipse(&circleBrush, 0, 0, m_width, m_height);
			}

			SolidBrush iconBrush(Color(255, 255, 255));

			iconCallback(graphics);
		}
	};
}