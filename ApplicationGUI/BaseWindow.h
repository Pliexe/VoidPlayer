/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#pragma once

#include <Windows.h>

namespace ApplicationGUI
{
	template <class DERIVED_WINDOW>
	class BaseWindow
	{
	public:
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			DERIVED_WINDOW*pThis = NULL;

			if (uMsg == WM_NCCREATE)
			{
				CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
				pThis = (DERIVED_WINDOW*)pCreate->lpCreateParams;
				SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);

				pThis->hWnd = hWnd;
			}
			else
				pThis = (DERIVED_WINDOW*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

			if (pThis)
				return pThis->HandleMessage(uMsg, wParam, lParam);
			else
				return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}

		BaseWindow() : hWnd(NULL) { }

		BOOL Create(
			PCWSTR lpWindowName,
			DWORD dwStyle,
			DWORD dwExStyle = 0,
			int x = CW_USEDEFAULT,
			int y = CW_USEDEFAULT,
			int nWidth = CW_USEDEFAULT,
			int nHeight = CW_USEDEFAULT,
			HWND hWndParent = 0,
			HMENU hMenu = 0
		)
		{
			wWidth = nWidth;
			wHeight = nHeight;

			WNDCLASS wc = { 0 };

			wc.lpfnWndProc = DERIVED_WINDOW::WindowProc;
			wc.hInstance = GetModuleHandle(NULL);
			wc.lpszClassName = ClassName();
			wc.hCursor = LoadCursor(NULL, IDC_ARROW);

			RegisterClass(&wc);

			hWnd = CreateWindowEx(
				dwExStyle, ClassName(), lpWindowName, dwStyle, x, y,
				nWidth, nHeight, hWndParent, hMenu, GetModuleHandle(NULL), this
			);

			return (hWnd ? TRUE : FALSE);
		}

		HWND Window() const { return hWnd; }

	protected:

		virtual PCWSTR ClassName() const = 0;
		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

		int wWidth;
		int wHeight;

		HWND hWnd;
	};
}