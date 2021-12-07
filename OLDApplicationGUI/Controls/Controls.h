/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#pragma once

#include "Utils/GraphicsUtils.h"

using namespace Gdiplus;

namespace ApplicationGUI { namespace Controls {

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

	template <class DERIVED_CONTROL>
	class WndProcControl : public Control
	{
	public:
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			DERIVED_CONTROL* pThis = NULL;

			if (uMsg == WM_NCCREATE)
			{
				CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
				pThis = (DERIVED_CONTROL*)pCreate->lpCreateParams;
				SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);

				pThis->hWnd = hWnd;
			}
			else
				pThis = (DERIVED_CONTROL*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

			if (pThis)
				return pThis->HandleMessage(uMsg, wParam, lParam);
			else
				return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}

	protected:
		virtual LRESULT HandleMessage(UINT umsg, WPARAM wParam, LPARAM lParam) = 0;
		virtual PCWSTR ClassName() const = 0;
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

	class DrawnControl
	{
	public:
		void DrawControl(DRAWITEMSTRUCT* lpDrawItem);

	protected:
		Rect WinRectToGdiRect(RECT rect)
		{
			return Rect(rect.left, rect.top, rect.right, rect.bottom);
		}
	};

	class DllExport Slider : public WndProcControl<Slider>, public DrawnControl {
	private:
		Color m_backgroundColor;
		Color m_fillerColor;
		Color m_handleColor;

		int m_value = 50;

		int m_maxvalue = 214;
		int m_minvalue = 0;

		int m_diameter;

		PCWSTR ClassName() const { return L"Slider"; }

	public:

		LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam)
		{
			switch (msg)
			{
			case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);

				DrawControl(ps, hdc);

				EndPaint(hWnd, &ps);




				/*PAINTSTRUCT ps;
				HDC hdc;
				RECT rect;

				GetClientRect(hWnd, &rect);

				hdc = BeginPaint(hWnd, &ps);
				SetTextColor(hdc, RGB(0, 0, 0));
				SetBkMode(hdc, TRANSPARENT);
				DrawText(hdc, L"Hello World!", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				EndPaint(hWnd, &ps);*/

				return TRUE;
			}
			case WM_LBUTTONDOWN:
			{

				SelectSection();


				//HRGN hrng = CreateRectRgn(-50, -50, 1000, 1000);

				//if (SetWindowRgn(hWnd, hrng, TRUE) == 0) MessageBox(hWnd, L"Setrng failed", L"FUCK", MB_ICONERROR);
				return TRUE;
			}
			case WM_MOUSEHOVER:
			{
				SelectSection();
				return TRUE;
			}
			default:
				return DefWindowProc(hWnd, msg, wParam, lParam);
			}

			return TRUE;
		}

		void Create(HWND parent, int x, int y, int width, int height, int radius, HMENU hmenu, Color backgroundColor, Color fillerColor, Color handleColor)
		{
			InitPos(x, y, width, height);

			m_diameter = radius * 2;

			m_backgroundColor = backgroundColor;
			m_fillerColor = fillerColor;
			m_handleColor = handleColor;

			if (dynamicResizing)
				HandleDynamicInit(parent, x, y, width, height);

			HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE);

			WNDCLASS wc = { 0 };

			if (!GetClassInfo(hInstance, ClassName(), &wc))
			{

				wc.lpfnWndProc = Slider::WindowProc;
				wc.hInstance = (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE);
				wc.lpszClassName = ClassName();
				wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
				wc.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
				//wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);

				if (RegisterClass(&wc) == 0)
				{
					DWORD errorMessageId = GetLastError();

					wchar_t buf[256];

					FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
						NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
						buf, (sizeof(buf) / sizeof(wchar_t)), NULL);

					MessageBox(hWnd, buf, L"VoidPlayer Error; Slider", MB_ICONERROR);
				}


			}

			hWnd = CreateWindowEx(
				0,
				ClassName(),
				NULL,
				WS_CHILD | WS_VISIBLE,
				x, y, width, height,
				parent,
				hmenu,
				hInstance,
				this
			);
		}

		void DrawControl(PAINTSTRUCT& ps, HDC& hdc)
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

		void DrawHandle(int fillerLength)
		{
			auto hdc = GetDC(hWnd);
			auto dc = SaveDC(hdc);

			Graphics graphics(hdc);

			SolidBrush handleBrush(m_handleColor);

			graphics.FillEllipse(&handleBrush, fillerLength - 25, 0, 50, 50);

			//ReleaseDC(hdc, )

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
	class DllExport Panel : public Control
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

			HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE);

			wc.lpfnWndProc = DERIVED_PANEL::WindowProc;
			wc.hInstance = hInstance;
			wc.lpszClassName = ClassName();
			wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
			wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);

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
				hInstance,
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
} }