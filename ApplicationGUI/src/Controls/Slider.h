/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#pragma once

#include "Control.h"

using namespace Gdiplus;

namespace Controls {

	class GUI_API Slider : public Control
	{
	private:
		Color m_backgroundColor;
		Color m_fillerColor;
		Color m_handleColor;

		void DrawHandle(int fillerLength);

		int m_value = 0;

		int m_maxvalue = 200;
		int m_minvalue = 0;

		int m_diameter;

		bool heldDown = false;

		void HandleValueDetection()
		{
			heldDown = false;

			POINT mousePos;
			GetCursorPos(&mousePos);

			if (!ScreenToClient(hWnd, &mousePos))
			{
				std::cout << "Error: Failed to convert mouse position from screen to client area at Slider!" << std::endl;
				MessageBox(this->hWnd, L"VoidPlayer: Error", L"Faile to update slider bar!", MB_ICONERROR);
				return;
			}

			RECT cRect;
			GetClientRect(hWnd, &cRect);

			m_value = ((float)mousePos.x / (float)cRect.right) * (m_maxvalue - m_minvalue);

			//RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

			InvalidateRect(hWnd, &cRect, false);
		}

	public:

		void OnPaint(HDC& hdc, PAINTSTRUCT& ps);
		LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam);

		void Create();

		void SetValue(int value) { m_value = value; }
		void SetRadius(int radius) { m_diameter = radius * 2; }

		void SetColors(Color backgroundColor, Color fillerColor, Color handleColor)
		{
			m_backgroundColor = backgroundColor;
			m_fillerColor = fillerColor;
			m_handleColor = handleColor;
		}

		PCWSTR ClassName() const { return L"Slider"; }
	};

}

