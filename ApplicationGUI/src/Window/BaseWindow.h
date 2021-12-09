/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#pragma once

#include <Windows.h>

#include "Controls/Control.h"
#include "Core.h"

namespace ApplicationGUI {

	class GUI_API BaseWindow
	{
	public:
		bool resizeChildren = true;

		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		BaseWindow() : hWnd(NULL) { };

		bool Create(
			PCWSTR lpWindowName,
			DWORD dwStyle,
			DWORD dwExStyle = 0,
			int x = CW_USEDEFAULT, int y = CW_USEDEFAULT,
			int nWidth = CW_USEDEFAULT, int nHeight = CW_USEDEFAULT,
			HWND hWndParent = 0, HMENU hMenu = 0
		);

		HWND Window() const { return hWnd; }

		void ResizeChildren(RECT& newParentSize);

	protected:

		std::vector<Controls::Control*> m_Controls;

		void RegisterControl(Controls::Control* control);

		virtual PCWSTR ClassName() const = 0;
		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

		HWND hWnd;
	};

}