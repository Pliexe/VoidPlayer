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
		Graphics graphics(hdc);

		graphics.SetSmoothingMode(SmoothingMode::SmoothingModeHighQuality);

		int oldPageUnit = graphics.SetPageUnit(UnitPixel);

		//Rect rect((int)ps.rcPaint.left, (int)ps.rcPaint.top, (int)ps.rcPaint.right - ps.rcPaint.left, (int)ps.rcPaint.bottom - ps.rcPaint.top);

		RECT cRect;

		GetClientRect(hWnd, &cRect);

		Rect rect = WinRectToGdiRect(cRect);

		int fillerLength = ((float)m_value / (float)m_maxvalue) * rect.Width;

		SolidBrush brushBackground(m_backgroundColor);

		GraphicsPath pathBackground;

		pathBackground.Reset();

		Rect cornerBackground(fillerLength, 0, m_diameter, m_diameter);


		Rect cornerBkg(0, 0, m_diameter, m_diameter);
		GraphicsPath pathBkg;

		if (fillerLength > m_diameter)
			pathBkg.AddLine(fillerLength - m_diameter, rect.Height - 1, fillerLength - m_diameter, 0);
		else {
			pathBkg.AddArc(cornerBkg, 180, 90);
		}

		cornerBkg.X = rect.Width - m_diameter;
		pathBkg.AddArc(cornerBkg, 270, 90);

		cornerBkg.Y = rect.Height - m_diameter - 1;
		pathBkg.AddArc(cornerBkg, 0, 90);

		if (fillerLength <= m_diameter)
		{
			cornerBkg.X = fillerLength;
			pathBackground.AddArc(cornerBackground, 90, 90);
		}

		pathBkg.CloseFigure();
		graphics.FillPath(&brushBackground, &pathBkg);

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

		graphics.SetPageUnit((Unit)oldPageUnit);

		DrawHandle(fillerLength);

		//graphics.FillEllipse(&handleBrush, rect);
	}

	LRESULT Slider::HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
			default:
				return DefWindowProc(hWnd, msg, wParam, lParam);
		}

		return TRUE;
	}

}