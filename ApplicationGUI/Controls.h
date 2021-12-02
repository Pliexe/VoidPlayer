/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#pragma once

#include <gdiplus.h>
#include <Windows.h>

using namespace Gdiplus;

namespace Controls {

	class Control
	{
	public:

		HWND hWnd = NULL;
		void Create();


	};

	class DrawnControl : public Control
	{
	public:
		void DrawControl(DRAWITEMSTRUCT* lpDrawItem); 
	};


	class Slider : public Control {

	};


	template <class DERIVED_PANEL>
	class Panel : public Control
	{
	public:

#pragma region Linking HandleMessage to WindowProc
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			DERIVED_PANEL* pThis = NULL;

			if (uMsg == WM_NCCREATE)
			{
				CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
				pThis = (DERIVED_PANEL*)pCreate->lpCreateParams;
				SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);

				pThis->hWnd = hWnd;
			}
			else
				pThis = (DERIVED_PANEL*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

			if (pThis)
				return pThis->HandleMessage(uMsg, wParam, lParam);
			else
				return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
#pragma endregion


		void Create(
			HWND parent,
			int x, int y,
			int width, int height,
			Color _backgroundColor = Color(255, 255, 255),
			HMENU hmenu = NULL
		) {
			m_width = width;
			m_height = height;
			backgroundColor = _backgroundColor;
			m_parent = parent;

			WNDCLASS wc = { 0 };

			wc.lpfnWndProc = DERIVED_PANEL::WindowProc;
			wc.hInstance = (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE);
			wc.lpszClassName = _T("Test");

			RegisterClass(&wc);

			hWnd = CreateWindow(
				_T("Test"),
				NULL,
				WS_VISIBLE | WS_CHILD | SS_OWNERDRAW,
				x, y,
				width, height,
				parent,
				hmenu,
				(HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE),
				this
			);
		}

		virtual void Init() = 0;

	protected:
		int m_width;
		int m_height;

		HWND m_parent;

		Color backgroundColor;


		virtual PCWSTR ClassName() const = 0;
		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	};


}