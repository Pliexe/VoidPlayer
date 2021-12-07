/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#include "Control.h"

namespace Controls {


	void Control::GetNewSize(RECT parentNewSize, RECT& newSize)
	{
		if (m_wPercent > 0)
			newSize.right = (long)m_wPercent * parentNewSize.right;
		else newSize.right = m_width;

		if (m_hPercent > 0)
			newSize.bottom = (long)m_hPercent * parentNewSize.bottom;
		else newSize.bottom = m_height;

		switch (m_xAnchor)
		{
			case ANCHOR_LEFT:
				if (m_xPercent > 0)
					newSize.left = (long)m_xPercent * parentNewSize.right + m_x;
				else newSize.left = m_x;
				break;

			case ANCHOR_MIDDLE:
				if (m_xPercent > 0)
					newSize.left = (long)m_xPercent * (parentNewSize.right / 2) + (m_x + parentNewSize.right / 2);
				else newSize.left = m_x + parentNewSize.right / 2;
				break;

			case ANCHOR_RIGHT:
				if (m_xPercent > 0)
					newSize.left = parentNewSize.right - m_width - m_x - (long)m_xPercent * parentNewSize.right;
				else newSize.left = parentNewSize.right - m_width - m_x;
				break;
		}

		switch (m_yAnchor)
		{
			case ANCHOR_TOP:
				if (m_yPercent > 0)
					newSize.top = (long)m_yPercent * parentNewSize.bottom + m_y;
				else newSize.top = m_y;
				break;
			case ANCHOR_MIDDLE:
				if (m_yPercent > 0)
					newSize.top = (long)m_yPercent * (parentNewSize.bottom / 2) + (m_y + parentNewSize.bottom / 2);
				else newSize.top = m_y + parentNewSize.bottom / 2;
				break;
			case ANCHOR_BOTTOM:
				if (m_yPercent > 0)
					newSize.top = parentNewSize.bottom + m_y + (long)m_yPercent * parentNewSize.bottom;
				else newSize.top = parentNewSize.bottom + m_y;
				break;
		}

		switch (m_pivotPoint)
		{
			case ControlPivot::LEFT_BOTTOM:
				newSize.top -= newSize.bottom;
				break;
			case ControlPivot::LEFT_MIDDLE_BOTTOM:
				newSize.top -= newSize.bottom / 2;
				break;
			case ControlPivot::LEFT_MIDDLE_TOP_RIGHT:
				newSize.left -= newSize.right / 2;
				break;
			case ControlPivot::RIGHT_BOTTOM:
				newSize.left -= newSize.right;
				newSize.top -= newSize.bottom;
				break;
			case ControlPivot::RIGHT_TOP:
				newSize.left -= newSize.right;
				break;
			case ControlPivot::RIGHT_MIDDLE_BOTTOM:
				newSize.left -= newSize.right;
				newSize.top -= newSize.bottom / 2;
				break;
			case ControlPivot::RIGHT_MIDDLE_BOTTOM_LEFT:
				newSize.left -= newSize.right / 2;
				newSize.top -= newSize.bottom;
				break;
			case ControlPivot::MIDDLE:
				newSize.left -= newSize.right / 2;
				newSize.top -= newSize.bottom / 2;
				break;
		}
	}	

	std::function<void(WNDCLASS&, HINSTANCE, Controls::Control*)> Control::DefaultClass()
	{
		return [](WNDCLASS& wc, HINSTANCE hInstance, Control* pThis) {
			wc.lpfnWndProc = Control::WindowProc;
			wc.hInstance = hInstance;
			wc.lpszClassName = pThis->ClassName();
			wc.hCursor = LoadCursor(hInstance, IDC_ARROW);

			RegisterClass(&wc);
		};
	}

	bool Control::RegisterDefaultWindow(int x, int y, int w, int h, HWND parent, HMENU hmenu, PCWSTR title)
	{
		hWnd = CreateWindowEx(
			0, ClassName(), title, WS_VISIBLE | WS_CHILD,
			x, y, w, h,
			parent, hmenu, (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE),
			this
		);

		return hWnd != NULL;
	}

	LRESULT Control::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		Control* pThis = NULL;

		if (uMsg == WM_NCCREATE)
		{
			CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
			pThis = (Control*)pCreate->lpCreateParams;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);

			pThis->hWnd = hWnd;
		} else
			pThis = (Control*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

		if (pThis)
		{
			switch (uMsg)
			{
				case WM_PAINT:
				{
					PAINTSTRUCT ps;
					HDC hdc = BeginPaint(hWnd, &ps);

					pThis->OnPaint(hdc, ps);

					EndPaint(hWnd, &ps);

					return TRUE;
				}
				default:
					return pThis->HandleMessage(uMsg, wParam, lParam);
			}
		} else
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	void Control::Create(HWND parent, int x, int y, int width, int height, HMENU hmenu)
	{
		m_x = x;
		m_y = y;
		m_width = width;
		m_height = height;

		m_hmenu = hmenu;
	}

}