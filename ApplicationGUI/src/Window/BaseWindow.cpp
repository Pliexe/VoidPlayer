/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#include "pch.h"

#include "BaseWindow.h"

namespace ApplicationGUI {

	inline bool GUI_API BaseWindow::Create(PCWSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu)
	{
		WNDCLASS wc = { 0 };

		wc.lpfnWndProc = BaseWindow::WindowProc;
		wc.hInstance = GetModuleHandle(NULL);
		wc.lpszClassName = ClassName();
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);

		RegisterClass(&wc);

		hWnd = CreateWindowEx(
			dwExStyle, ClassName(), lpWindowName, dwStyle, x, y,
			nWidth, nHeight, hWndParent, hMenu, GetModuleHandle(NULL), this
		);

		return hWnd ? true : false;
	}

	void BaseWindow::ResizeChildren(RECT& newParentSize)
	{
		for (auto control : m_Controls)
			control->OnParentResize(newParentSize);
	}

	void BaseWindow::RegisterControl(Controls::Control* control)
	{
		control->SetParent(hWnd);
		control->Create();
		m_Controls.push_back(control);
	}

	inline LRESULT GUI_API BaseWindow::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		BaseWindow* pThis = NULL;

		if (uMsg == WM_NCCREATE)
		{
			CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
			pThis = (BaseWindow*)pCreate->lpCreateParams;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);

			pThis->hWnd = hWnd;
		}
		else
			pThis = (BaseWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

		if (pThis)
		{
			switch (uMsg)
			{
				case WM_SIZE:
					if (pThis->resizeChildren)
					{
						RECT rect;
						GetClientRect(hWnd, &rect);

						pThis->ResizeChildren(rect);
					}
					else
					return pThis->HandleMessage(uMsg, wParam, lParam);
				default:
					return pThis->HandleMessage(uMsg, wParam, lParam);
			}
			
		}
		else
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}