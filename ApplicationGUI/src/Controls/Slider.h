/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#pragma once

#include "Control.h"

using namespace Gdiplus;

namespace Controls {

	class Slider : public Control
	{
	private:
		Color m_backgroundColor;
		Color m_fillerColor;
		Color m_handleColor;

		void DrawHandle(int fillerLength);

		int m_value = 0;

		int m_maxvalue = 200;
		int m_minvalue = 0;

		int m_diameter;

	public:

		void OnPaint(HDC& hdc, PAINTSTRUCT& ps);
		LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam);

		void SetColors(Color backgroundColor, Color fillerColor, Color handleColor)
		{
			m_backgroundColor = backgroundColor;
			m_fillerColor = fillerColor;
			m_handleColor = handleColor;
		}

		PCWSTR ClassName() const { return L"Slider"; }
	};

}

