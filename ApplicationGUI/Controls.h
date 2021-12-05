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
#include <tchar.h>
#include <iostream>
#include "GraphicsUtils.h"

using namespace Gdiplus;

namespace Controls {

	enum AnchorPoint {
		ANCHOR_LEFT,
		ANCHOR_RIGHT,
		ANCHOR_TOP,
		ANCHOR_BOTTOM,
		ANCHOR_MIDDLE
	};

	enum ControlPivot {
		LEFT_TOP,
		LEFT_BOTTOM,
		LEFT_MIDDLE_TOP_RIGHT,
		LEFT_MIDDLE_BOTTOM,
		MIDDLE,
		RIGHT_TOP,
		RIGHT_BOTTOM,
		RIGHT_MIDDLE_BOTTOM,
		RIGHT_MIDDLE_BOTTOM_LEFT
	};

	class Control
	{
	protected:

		int m_height = 50;
		int m_width = 50;

		float m_hPercent = false;
		float m_wPercent = false;

		int m_x = 0;
		int m_y = 0;

		float m_xPercent = false;
		float m_yPercent = false;

		ControlPivot m_pivotPoint = ControlPivot::LEFT_TOP;

		AnchorPoint m_xAnchor = ANCHOR_LEFT;
		AnchorPoint m_yAnchor = ANCHOR_TOP;

		bool dynamicResizing = false;

		LPCSTR m_text = NULL;


		HMENU m_hmenu = NULL;

		HWND m_parent = NULL;

		void (*cb_onMouseDown)() = NULL;
		void (*cb_onMouseUp)() = NULL;
		void (*cb_onMouseActive)() = NULL;
		void (*cb_onMouseHover)() = NULL;

		void InitPos(int x, int y, int w, int h) { m_x = x; m_y = y; m_width = w; m_height = h; }

		void GetNewSize(RECT parentNewSize, RECT& newSize)
		{		
			if (m_wPercent > 0)
				newSize.right = m_wPercent * parentNewSize.right;
			else newSize.right = m_width;

			if (m_hPercent > 0)
				newSize.bottom = m_hPercent * parentNewSize.bottom;
			else newSize.bottom = m_height;

			switch (m_xAnchor)
			{
			case ANCHOR_LEFT:
				if (m_xPercent > 0)
					newSize.left = m_xPercent * parentNewSize.right + m_x;
				else newSize.left = m_x;
				break;

			case ANCHOR_MIDDLE:
				if (m_xPercent > 0)
					newSize.left = m_xPercent * (parentNewSize.right / 2) + (m_x + parentNewSize.right / 2);
				else newSize.left = m_x + parentNewSize.right / 2;
				break;

			case ANCHOR_RIGHT:
				if (m_xPercent > 0)
					newSize.left = parentNewSize.right - m_width - m_x - m_xPercent * parentNewSize.right;
				else newSize.left = parentNewSize.right - m_width - m_x;
				break;
			}

			switch (m_yAnchor)
			{
			case ANCHOR_TOP:
				if (m_yPercent > 0)
					newSize.top = m_yPercent * parentNewSize.bottom + m_y;
				else newSize.top = m_y;
				break;
			case ANCHOR_MIDDLE:
				if (m_yPercent > 0)
					newSize.top = m_yPercent * (parentNewSize.bottom / 2) + (m_y + parentNewSize.bottom / 2);
				else newSize.top = m_y + parentNewSize.bottom / 2;
				break;
			case ANCHOR_BOTTOM:
				if (m_yPercent > 0)
					newSize.top = parentNewSize.bottom + m_y + m_yPercent * parentNewSize.bottom;
				else newSize.top = parentNewSize.bottom + m_y;
				break;
			}

			switch (m_pivotPoint)
			{
			case ControlPivot::LEFT_BOTTOM:
				newSize.top -= newSize.bottom;
				break;
			case ControlPivot::LEFT_MIDDLE_BOTTOM:
				newSize.top -= newSize.bottom / 2;
				break;
			case ControlPivot::LEFT_MIDDLE_TOP_RIGHT:
				newSize.left -= newSize.right / 2;
				break;
			case ControlPivot::RIGHT_BOTTOM:
				newSize.left -= newSize.right;
				newSize.top -= newSize.bottom;
				break;
			case ControlPivot::RIGHT_TOP:
				newSize.left -= newSize.right;
				break;
			case ControlPivot::RIGHT_MIDDLE_BOTTOM:
				newSize.left -= newSize.right;
				newSize.top -= newSize.bottom / 2;
				break;
			case ControlPivot::RIGHT_MIDDLE_BOTTOM_LEFT:
				newSize.left -= newSize.right / 2;
				newSize.top -= newSize.bottom;
				break;
			case ControlPivot::MIDDLE:
				newSize.left -= newSize.right / 2;
				newSize.top -= newSize.bottom / 2;
				break;
			}
		}
	public:
		HWND hWnd = NULL;
		void SetX(int x) { m_x = x; }
		void SetY(int y) { m_y = y; }

		void SetWidth(int width) { m_width = width; }
		void SetHeight(int height) { m_height = height; }

		void SetPos(int x, int y) { m_x = x; m_y = y; }
		void SetSize(int width, int height) { m_width = width; m_height = height; }
		void SetPosAndSize(int x, int y, int width, int height) { m_x = x; m_y = y; m_width = width; m_height = height; }

		void SetXpercent(float x) { m_xPercent = x / 100; }
		void SetYpercent(float y) { m_yPercent = y / 100; }

		void SetWidthPercent(float width) { this->m_wPercent = width / 100; }
		void SetHeightPercent(float heigth) { m_hPercent = heigth / 100; }

		void SetHMENU(HMENU hmenu) { m_hmenu = hmenu; }

		void EnableDynamicResizing() { dynamicResizing = true; }
		void DisableDynamicResizing() { dynamicResizing = false; }

		void SetAnchorX(AnchorPoint ap) { m_xAnchor = ap; }
		void SetAnchorY(AnchorPoint ap) { m_yAnchor = ap; }

		void SetPosPivot(ControlPivot piv) { m_pivotPoint = piv; }

		

		void OnParentResize(RECT parentNewSize)
		{
			if (!dynamicResizing) return;

			RECT newSize;

			GetNewSize(parentNewSize, newSize);

			SetWindowPos(hWnd, NULL, newSize.left, newSize.top, newSize.right, newSize.bottom, SWP_NOZORDER);
			//ValidateRect(hWnd, NULL);
		}

		void HandleDynamicInit(HWND parent, int& x, int& y, int& w, int& h)
		{
			RECT parentRect;
			GetClientRect(parent, &parentRect);
			RECT newSize;

			GetNewSize(parentRect, newSize);

			x = newSize.left;
			w = newSize.right;

			y = newSize.top;
			w = newSize.bottom;
		}
	};

	class Button : public Control
	{
	protected:

		static std::string ClassName() { return "CustomButton"; };
	public:

		LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam)
		{
			switch (msg)
			{
			default:
				return DefWindowProc(hWnd, msg, wParam, lParam);
			}

			return TRUE;
		}
	};

	class Control1
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
			InitPos(x, y, width, height);

			m_diameter = radius * 2;

			m_backgroundColor = backgroundColor;
			m_fillerColor = fillerColor;
			m_handleColor = handleColor;

			if (dynamicResizing)
				HandleDynamicInit(parent, x, y, width, height);

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
			InitPos(x, y, width, height);

			backgroundColor = _backgroundColor;
			m_parent = parent;

			WNDCLASS wc = { 0 };

			wc.lpfnWndProc = DERIVED_PANEL::WindowProc;
			wc.hInstance = (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE);
			wc.lpszClassName = ClassName();

			RegisterClass(&wc);

			if (dynamicResizing)
				HandleDynamicInit(parent, x, y, width, height);

			hWnd = CreateWindowEx(
				0,
				ClassName(),
				NULL,
				WS_VISIBLE | WS_CHILD,
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
		HWND m_parent;

		Color backgroundColor;


		virtual PCWSTR ClassName() const = 0;
		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	};


}