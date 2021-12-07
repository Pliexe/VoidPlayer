#pragma once

#include <Windows.h>
/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#include <gdiplus.h>

#include "Control.h"
#include "../Core.h"

using namespace Gdiplus;

namespace Controls {
	class GUI_API CustomDrawnIconButton : public Control
	{
	private:

		Color m_backgroundColor;
		Color m_backgroundColor2;

		void (*m_iconCallback)(Graphics&);

		bool useGradient = false;

	protected:

		void OnPaint(HDC& hdc, PAINTSTRUCT& ps);

	public:
		LRESULT HandleMessage(UINT umsg, WPARAM wParam, LPARAM lParam);

		bool Create(
			HWND parent, int x, int y, int width, int heigth, void (*iconCallback)(Graphics&), HMENU hmenu = 0,
			Color brushbackgroundColor = Color(50, 50, 50)
		);

		bool Create(
			HWND parent, int x, int y, int width, int heigth, void (*iconCallback)(Graphics&),
			Color brushbackgroundColor1 = Color(50, 50, 50),
			Color brushbackgroundColor2 = Color(70, 70, 70), HMENU hmenu = 0
		);
		

		PCWSTR ClassName() const { return L"CustomDrawnIconButton"; };
	};
}

