/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#pragma once

#include "Control.h"

#define WM_MOUSEENTER WM_USER

using namespace Gdiplus;

namespace Controls {

	class GUI_API Slider : public Control
	{
	private:
		Color m_backgroundColor;
		Color m_fillerColor;
		Color m_handleColor;
		Color m_fillerHoverColor;

		void DrawHandle(int fillerLength, Graphics* graphics);

		int m_value = 0;

		int m_maxvalue = 200;
		int m_minvalue = 0;

		int m_diameter;

		int m_handle_radius;
		int m_yOffset = 0;

		bool heldDown = false;

		void UpdateProgressPosition()
		{
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

			if (mousePos.x < m_handle_radius) mousePos.x = 0;
			else if (mousePos.x > cRect.right - m_handle_radius) mousePos.x = cRect.right;

			int lastDrawnPlace = m_value / m_maxvalue * cRect.right;

			m_value = ((float)mousePos.x / (float)cRect.right) * (m_maxvalue - m_minvalue);

			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);

			RECT upperInv;
			upperInv.top = 0;
			upperInv.left = lastDrawnPlace - m_handle_radius * 2 - 10;
			upperInv.bottom = m_height;
			upperInv.right = lastDrawnPlace + m_handle_radius * 2 + 10;

			//MapWindowPoints(hWnd, m_parent, (LPPOINT)&upperInv, 2);

			//InvalidateRect(m_parent, &upperInv, true);
		}

		void HandleValueDetection()
		{
			UpdateProgressPosition();

			std::cout << "Done" << std::endl;
		}

		bool m_mouseInside = false;

	public:

		void OnPaint(HDC& hdc, RECT& toRepaint);
		LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam);

		void Create();

		void SetValue(int value) { m_value = value; }
		void SetRadius(int radius) { m_diameter = radius * 2; }
		void SetHandleSize(int radius) 
		{ 
			m_handle_radius = radius; 

			if (radius * 2 > m_height)
			{
				m_yOffset = radius * 2 - m_height;
				m_height += m_yOffset;
				m_yOffset /= 2;
			}

			m_width += radius * 2;
		}

		void SetColors(Color backgroundColor, Color fillerHoverColor, Color fillerColor, Color handleColor)
		{
			m_backgroundColor = backgroundColor;
			m_fillerHoverColor = fillerHoverColor;
			m_fillerColor = fillerColor;
			m_handleColor = handleColor;
		}

		PCWSTR ClassName() const { return L"Slider"; }
	};

}

