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


	public:
		void OnPaint(HDC& hdc, PAINTSTRUCT& ps);
		LRESULT HandleMessage(UINT umsg, WPARAM wParam, LPARAM lParam);

		void SetBkgColor(Color bkgC) { m_backgroundColor = bkgC; }
		void SetGradientBkgColor(Color bkgC1, Color bkgC2) {
			m_backgroundColor = bkgC1;
			m_backgroundColor2 = bkgC2;
			useGradient = true;
		}

		void SetIconCallback(void (*iconCallback)(Graphics&))
		{
			m_iconCallback = iconCallback;
		}
		
		PCWSTR ClassName() const { return L"CustomDrawnIconButton"; };
	};
}

