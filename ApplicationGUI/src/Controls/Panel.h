/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#pragma once

#include "Core.h"
#include "Control.h"

using namespace Gdiplus;

namespace Controls {

	class GUI_API Panel : public Control
	{
	private:
		HBRUSH m_backgroundBrush;

	protected:


	public:
		void OnPaint(HDC& hdc, PAINTSTRUCT& ps);
		LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam);

		void SetBackgroundBrush(HBRUSH brush) { m_backgroundBrush = brush; }
		
		PCWSTR ClassName() const { return L"Panel"; }
	};

}

