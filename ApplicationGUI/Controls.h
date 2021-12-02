/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#pragma once

#include <gdiplus.h>
#include <Windows.h>
#include "GraphicsUtils.h"

using namespace Gdiplus;

namespace Controls {

	class Control
	{
	public:

		HWND hWnd = NULL;
		void Create();

	};

	class DrawnControl : public Control
	{
	public:
		void DrawControl(DRAWITEMSTRUCT* lpDrawItem); 

	protected:
		Rect WinRectToGdiRect(RECT rect)
		{
			return Rect(rect.left, rect.top, rect.right, rect.bottom);
		}
	};




	class Slider : public DrawnControl {
	private:
		Color m_backgroundColor;
		Color m_fillerColor;
		Color m_handleColor;
		int m_value = 50;

		int m_maxvalue = 214;
		int m_minvalue = 0;

		int m_diameter;

	public:

		void Create(HWND parent, int x, int y, int width, int height, int radius, HMENU hmenu, Color backgroundColor, Color fillerColor, Color handleColor)
		{
			m_diameter = radius * 2;

			m_backgroundColor = backgroundColor;
			m_fillerColor = fillerColor;
			m_handleColor = handleColor;

			hWnd = CreateWindow(
				TEXT("STATIC"),
				NULL,
				WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_OWNERDRAW,
				x, y, width, height,
				parent,
				hmenu,
				(HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE),
				NULL
			);
		}

		void DrawnControl(DRAWITEMSTRUCT* lpDrawnItem)
		{

			Graphics graphics(lpDrawnItem->hDC);

			graphics.SetSmoothingMode(SmoothingModeHighQuality);

			RECT cRect;

			GetClientRect(lpDrawnItem->hwndItem, &cRect);

			Rect rect = WinRectToGdiRect(cRect);

			int fillerLength = ((float)m_value / (float)m_maxvalue) * rect.Width;

			SolidBrush brushBackground(m_backgroundColor);

			GraphicsPath pathBackground;

			pathBackground.Reset();

			Rect cornerBackground(fillerLength, 0, m_diameter, m_diameter);

			if (fillerLength > 0)
			{
				SolidBrush brushFiller(m_fillerColor);

				Rect cornerFiller(0, 0, m_diameter, m_diameter);

				GraphicsPath pathFiller;

				pathFiller.Reset();

				pathFiller.AddArc(cornerFiller, 180, 90);

				if (fillerLength == rect.Width)
				{
					cornerBackground.X = rect.Width - m_diameter;
					pathFiller.AddArc(cornerBackground, 270, 90);

					cornerFiller.Y = rect.Height - m_diameter - 1;
					pathFiller.AddArc(cornerFiller, 0, 90);
				}
				else 
				{
					pathFiller.AddLine(fillerLength, 0, fillerLength, rect.Height - 1);
					pathBackground.AddLine(fillerLength, rect.Height - 1, fillerLength, 0);
				}

				cornerFiller.Y = rect.Height - m_diameter - 1;

				pathFiller.AddArc(cornerFiller, 90, 90);

				pathFiller.CloseFigure();

				graphics.FillPath(&brushFiller, &pathFiller);

				graphics.DrawPath(&Pen(Color(255, 0, 0)), &pathFiller);

				
				
			}
			else {
				pathBackground.AddArc(cornerBackground, 180, 90);
			}	

			cornerBackground.X += rect.Width - fillerLength - m_diameter;
			pathBackground.AddArc(cornerBackground, 270, 90);

			cornerBackground.Y += rect.Height - m_diameter;
			pathBackground.AddArc(cornerBackground, 0, 90);

			if (fillerLength <= 0)
			{
				cornerBackground.X = 0;
				pathBackground.AddArc(cornerBackground, 90, 90);
			}

			pathBackground.CloseFigure();

			graphics.FillPath(&brushBackground, &pathBackground);
		}

		float GetXOffset(POINT mouseOffset, RECT cRect)
		{
			return ((float)mouseOffset.x / (float)cRect.right) * m_maxvalue;
		}

		void SelectSection()
		{
			POINT mouseOffset;

			GetCursorPos(&mouseOffset);

			ScreenToClient(hWnd, &mouseOffset);

			RECT cRect;

			GetClientRect(hWnd, &cRect);

			m_value = GetXOffset(mouseOffset, cRect);

			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		}
	};


	template <class DERIVED_PANEL>
	class Panel : public Control
	{
	public:

#pragma region Linking HandleMessage to WindowProc
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			DERIVED_PANEL* pThis = NULL;

			if (uMsg == WM_NCCREATE)
			{
				CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
				pThis = (DERIVED_PANEL*)pCreate->lpCreateParams;
				SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);

				pThis->hWnd = hWnd;
			}
			else
				pThis = (DERIVED_PANEL*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

			if (pThis)
				return pThis->HandleMessage(uMsg, wParam, lParam);
			else
				return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
#pragma endregion


		void Create(
			HWND parent,
			int x, int y,
			int width, int height,
			Color _backgroundColor = Color(255, 255, 255),
			HMENU hmenu = NULL
		) {
			m_width = width;
			m_height = height;
			backgroundColor = _backgroundColor;
			m_parent = parent;

			WNDCLASS wc = { 0 };

			wc.lpfnWndProc = DERIVED_PANEL::WindowProc;
			wc.hInstance = (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE);
			wc.lpszClassName = _T("Test");

			RegisterClass(&wc);

			hWnd = CreateWindow(
				_T("Test"),
				NULL,
				WS_VISIBLE | WS_CHILD | SS_OWNERDRAW,
				x, y,
				width, height,
				parent,
				hmenu,
				(HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE),
				this
			);
		}

		virtual void Init() = 0;

	protected:
		int m_width;
		int m_height;

		HWND m_parent;

		Color backgroundColor;


		virtual PCWSTR ClassName() const = 0;
		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	};


}