/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */


#include "pch.h"
#include "Label.h"

void Controls::Label::OnPaint(HDC& hdc, RECT& toRepaint)
{
	static bool first = true;
	static RectF lastStringSize;

	static FontFamily fontFamily(L"Arial");
	Font font(&fontFamily, m_fontSize, FontStyleRegular, UnitPixel);
	SolidBrush solidBrush(m_textColor);

	RECT cRect;

	GetClientRect(hWnd, &cRect);

	if (first)
	{
		first = false;
		Graphics graphics(hdc);

		graphics.SetSmoothingMode(SmoothingModeHighQuality);

		graphics.DrawString(m_text, -1, &font, PointF(m_tX, m_tY), &solidBrush);

		RectF layoutRect(cRect.left, cRect.top, cRect.right, cRect.bottom);
		graphics.MeasureString(m_text, lstrlen(m_text), &font, layoutRect, &lastStringSize);

	} else {

		HDC hdcBuffer = CreateCompatibleDC(hdc);
		HBITMAP hBmp = CreateCompatibleBitmap(hdc, cRect.right, cRect.bottom);
		SelectObject(hdcBuffer, hBmp);

		Control* parentThis = (Control*)GetWindowLongPtr(m_parent, GWLP_USERDATA);

		Graphics graphics(hdcBuffer);

		graphics.SetSmoothingMode(SmoothingModeHighQuality);

		RectF newStringSize;
		RectF layoutRect(cRect.left, cRect.top, cRect.right, cRect.bottom);
		graphics.MeasureString(m_text, lstrlen(m_text), &font, layoutRect, &newStringSize);

		if (newStringSize.Width > lastStringSize.Width) lastStringSize.Width = newStringSize.Width;
		if (newStringSize.Height > lastStringSize.Height) lastStringSize.Height = newStringSize.Height;

		RECT toUpdate;
		toUpdate.left = lastStringSize.X;
		toUpdate.right = lastStringSize.Width;
		toUpdate.top = lastStringSize.Y;
		toUpdate.bottom = lastStringSize.Height;
		parentThis->OnPaint(hdcBuffer, toUpdate);

		graphics.DrawString(m_text, -1, &font, PointF(m_tX, m_tY), &solidBrush);
		BitBlt(hdc, lastStringSize.X, lastStringSize.Y, lastStringSize.Width, lastStringSize.Height, hdcBuffer, lastStringSize.X, lastStringSize.Y, SRCCOPY);
		lastStringSize = newStringSize;
	}
}
