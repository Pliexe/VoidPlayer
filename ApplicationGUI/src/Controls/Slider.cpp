/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#include "pch.h"
#include "Slider.h"

namespace Controls {

	void Slider::DrawHandle(int fillerLength)
	{
		auto hdc = GetDC(hWnd);
		auto dc = SaveDC(hdc);

		Graphics graphics(hdc);

		SolidBrush handleBrush(m_handleColor);

		graphics.FillEllipse(&handleBrush, fillerLength - 25, 0, 50, 50);
	}

	void Slider::OnPaint(HDC& hdc, PAINTSTRUCT& ps)
	{
		RECT cRect;

		GetClientRect(hWnd, &cRect);

		Rect rect = WinRectToGdiRect(cRect);

		int fillerLength = ((float)m_value / (float)(m_maxvalue - m_minvalue)) * rect.Width;

		HDC hdcBuffer = CreateCompatibleDC(hdc);

		HBITMAP hBmp = CreateCompatibleBitmap(hdc, rect.Width, rect.Height);
		SelectObject(hdcBuffer, hBmp);

		BitBlt(hdcBuffer, 0, 0, rect.Width, rect.Height, hdc, 0, 0, SRCCOPY);

		Graphics graphics(hdcBuffer);

		graphics.SetSmoothingMode(SmoothingMode::SmoothingModeHighQuality);

		int oldPageUnit = graphics.SetPageUnit(UnitPixel);

		//Rect rect((int)ps.rcPaint.left, (int)ps.rcPaint.top, (int)ps.rcPaint.right - ps.rcPaint.left, (int)ps.rcPaint.bottom - ps.rcPaint.top);

#ifdef _DEBUG

		std::cout << "Value of slider is: " << m_value << std::endl;

#endif // _DEBUG



		SolidBrush brushBackground(m_backgroundColor);

		GraphicsPath pathBkg;

		pathBkg.Reset();

		Rect cornerBkg(fillerLength, 0, m_diameter, m_diameter);

		if (fillerLength > m_diameter)
			pathBkg.AddLine(fillerLength - m_diameter, rect.Height - 1, fillerLength - m_diameter, 0);
		else {
			pathBkg.AddArc(cornerBkg, 180, 90);
		}

		cornerBkg.X = rect.Width - m_diameter - 1;
		pathBkg.AddArc(cornerBkg, 270, 90);

		cornerBkg.Y = rect.Height - m_diameter - 1;
		pathBkg.AddArc(cornerBkg, 0, 90);

		if (fillerLength <= m_diameter)
		{
			cornerBkg.X = fillerLength;

			pathBkg.AddArc(cornerBkg, 90, 90);
		}

		pathBkg.CloseFigure();
		graphics.FillPath(&brushBackground, &pathBkg);
		Pen pen(Color(255, 0, 0));
		graphics.DrawPath(&pen, &pathBkg);

		if (fillerLength > 0)
		{
			SolidBrush brushFiller(m_fillerColor);

			Rect cornerFiller(0, 0, m_diameter, m_diameter);

			GraphicsPath pathFiller;

			pathFiller.Reset();

			pathFiller.AddArc(cornerFiller, 180, 90);

			cornerFiller.X = fillerLength - m_diameter;
			pathFiller.AddArc(cornerFiller, 270, 90);

			cornerFiller.Y = rect.Height - m_diameter - 1;
			pathFiller.AddArc(cornerFiller, 0, 90);

			cornerFiller.X = 0;
			pathFiller.AddArc(cornerFiller, 90, 90);

			pathFiller.CloseAllFigures();

			graphics.FillPath(&brushFiller, &pathFiller);
		}

		

#ifdef _DEBUG
		if (!BitBlt(hdc, 0, 0, rect.Width, rect.Height, hdcBuffer, 0, 0, SRCCOPY))
			std::cout << "Slider -> Failed to copy BitBtl()" << std::endl;
#else
		BitBlt(hdc, 0, 0, rect.Width, rect.Height, hdcBuffer, 0, 0, SRCCOPY);
#endif // _DEBUG

		//DrawHandle(fillerLength);

		//graphics.FillEllipse(&handleBrush, rect);
	}

	LRESULT Slider::HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
			case WM_NCLBUTTONUP:
				if (heldDown) HandleValueDetection();
				return TRUE;
			case WM_LBUTTONUP:
				if (heldDown) HandleValueDetection();
				return TRUE;
			case WM_NCRBUTTONUP:
				if (heldDown) HandleValueDetection();
				return TRUE;
			case WM_RBUTTONUP:
				if (heldDown) HandleValueDetection();
				return TRUE;
			case WM_LBUTTONDOWN:
				heldDown = true;
				return TRUE;
			case WM_RBUTTONDOWN:
				heldDown = true;
				return TRUE;
			case WM_ERASEBKGND:
				return TRUE;
			default:
				return DefWindowProc(hWnd, msg, wParam, lParam);
		}

		return TRUE;
	}

	void Slider::Create()
	{
		RegisterClassIfUnregistered([](WNDCLASS& wc, HINSTANCE hInstance, Control* pThis) {
			wc.hInstance = hInstance;
			wc.lpszClassName = pThis->ClassName();
			wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
			wc.lpfnWndProc = Slider::WindowProcMinimal;
			//wc.style = 

			RegisterClass(&wc);
		});

		RECT size;
		RECT parentSize;

		GetClientRect(m_parent, &parentSize);

		GetNewSize(parentSize, size);

		hWnd = CreateWindowEx(
			0, ClassName(), m_text, WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS,
			size.left, size.top, size.right, size.bottom,
			m_parent, 0, (HINSTANCE)GetWindowLongPtr(m_parent, GWLP_HINSTANCE),
			this
		);
	}
}