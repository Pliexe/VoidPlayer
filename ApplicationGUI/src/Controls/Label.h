/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */


#pragma once

#include "Control.h"
#include "Core.h"

namespace Controls {
	class GUI_API Label : public Control
	{

	private:
		Color m_textColor;

		int m_fontSize = 15;

		int m_tX = 0;
		int m_tY = 0;
	public:
		LRESULT HandleMessage(UINT umsg, WPARAM wParam, LPARAM lParam) { return DefWindowProc(hWnd, umsg, wParam, lParam); }
		void OnPaint(HDC& hdc, RECT& toRepaint);

		void SetTextPos(int x, int y) { m_tX = x; m_tY = y; }
		void SetFontSize(int fSize) { m_fontSize = fSize; }

		void SetColor(Color color) { m_textColor = color; }

		PCWSTR ClassName() const { return L"CLabel"; };

		/*void Create()
		{
			RECT rect;
			RECT parentSize;
			GetClientRect(m_parent, &parentSize);
			GetNewSize(parentSize, rect);

			

			RegisterDefaultWindow(rect);
		}*/

		void SetText(LPCWSTR text)
		{
			if(hWnd == NULL)
				m_text = text;
			else {
				/*if (lstrcmp(m_text, text) != 0)
				{
					m_text = text;
					Redraw();
				}*/

				m_text = text;
				Redraw();
			}
		}
	};
}

