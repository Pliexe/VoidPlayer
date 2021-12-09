/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#include "pch.h"
#include "Panel.h"

namespace Controls {
	void Panel::OnPaint(HDC& hdc, PAINTSTRUCT& ps)
	{
		FillRect(hdc, &ps.rcPaint, m_backgroundBrush);
	}

	LRESULT Panel::HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

}
