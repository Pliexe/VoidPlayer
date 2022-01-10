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
	static RectF lastStringSize(0, 0, m_width, m_height);
	static PointF lastPosition(0, 0);

	static FontFamily fontFamily(L"Arial");
	Font font(&fontFamily, m_fontSize, FontStyleRegular, UnitPixel);
	SolidBrush solidBrush(m_textColor);

	RECT cRect;

	GetClientRect(hWnd, &cRect);

	HDC hdcBuffer = CreateCompatibleDC(hdc);
	HBITMAP hBmp = CreateCompatibleBitmap(hdc, cRect.right, cRect.bottom);
	SelectObject(hdcBuffer, hBmp);

	Control* parentThis = (Control*)GetWindowLongPtr(m_parent, GWLP_USERDATA);

	Graphics graphics(hdcBuffer);

	graphics.SetSmoothingMode(SmoothingModeHighQuality);

	RectF newStringSize;
	RectF layoutRect(cRect.left, cRect.top, cRect.right - 1, cRect.bottom - 1);
	graphics.MeasureString(m_text.c_str(), m_text.length(), &font, layoutRect, &newStringSize);

	//if (newStringSize.Width > lastStringSize.Width) lastStringSize.Width = newStringSize.Width;
	//if (newStringSize.Height > lastStringSize.Height) lastStringSize.Height = newStringSize.Height;

	PointF textPosition;
	GetTextPosition(newStringSize, textPosition);

	/*RECT toUpdate;
	toUpdate.left = textPosition.X;
	toUpdate.right = lastStringSize.Width;
	toUpdate.top = textPosition.Y;
	toUpdate.bottom = lastStringSize.Height;
	parentThis->OnPaint(hdcBuffer, toUpdate);*/

	parentThis->OnPaint(hdcBuffer, cRect);
	 
	/*Pen pen(Color(255, 0, 0));
	Pen pen2(Color(0, 255, 0));

	Rect toUpdateR;

	toUpdateR.X = textPosition.X;
	toUpdateR.Width= lastStringSize.Width;
	toUpdateR.Y = textPosition.Y;
	toUpdateR.Height= lastStringSize.Height;*/

	/*graphics.DrawRectangle(&pen, toUpdateR);
	graphics.DrawRectangle(&pen2, layoutRect);*/

	graphics.DrawString(m_text.c_str(), -1, &font, textPosition, &solidBrush);

	//BitBlt(hdc, lastPosition.X, lastPosition.Y, lastStringSize.Width, lastStringSize.Height, hdcBuffer, textPosition.X, textPosition.Y, SRCCOPY);
	BitBlt(hdc, 0, 0, cRect.right, cRect.bottom, hdcBuffer, 0, 0, SRCCOPY);
	lastStringSize = newStringSize;

	DeleteDC(hdcBuffer);
	DeleteObject(hBmp);
}
