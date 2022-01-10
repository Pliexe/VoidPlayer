/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#include "pch.h"
#include "Slider.h"

#define TIMER_MOUSE_EVENT 100

namespace Controls {

	void Slider::DrawHandle(int fillerLength, Graphics* graphics)
	{
		SolidBrush handleBrush(m_handleColor);

		auto dia = m_handle_radius * 2;

		graphics->FillEllipse(&handleBrush, fillerLength - m_handle_radius, m_height / 2 - m_handle_radius - 1, dia, dia);
	}

	void Slider::OnPaint(HDC& hdc, RECT& toRepaint)
	{
		RECT cRect;

		GetClientRect(hWnd, &cRect);

		Rect rect = WinRectToGdiRect(cRect);

		int fillerLength = (((float)m_value / (float)(m_maxvalue - m_minvalue)) * (rect.Width - m_handle_radius * 2)) + m_handle_radius;

		HDC hdcBuffer = CreateCompatibleDC(hdc);

		HBITMAP hBmp = CreateCompatibleBitmap(hdc, rect.Width, rect.Height);
		SelectObject(hdcBuffer, hBmp);
		
		Control* parentThis = (Control*)GetWindowLongPtr(m_parent, GWLP_USERDATA);

		parentThis->OnPaint(hdcBuffer, toRepaint);

		Graphics graphics(hdcBuffer);

		graphics.SetSmoothingMode(SmoothingMode::SmoothingModeHighQuality);

		int oldPageUnit = graphics.SetPageUnit(UnitPixel);

		//Rect rect((int)ps.rcPaint.left, (int)ps.rcPaint.top, (int)ps.rcPaint.right - ps.rcPaint.left, (int)ps.rcPaint.bottom - ps.rcPaint.top);

		SolidBrush brushBackground(m_backgroundColor);

		GraphicsPath pathBkg;

		pathBkg.Reset();

		Rect cornerBkg(m_handle_radius, m_yOffset, m_diameter, m_diameter);

		if (fillerLength > m_handle_radius)
			pathBkg.AddLine(fillerLength - m_diameter, rect.Height - 1 - m_yOffset, fillerLength - m_diameter, m_yOffset);
		else {
			pathBkg.AddArc(cornerBkg, 180, 90);
		}

		cornerBkg.X = rect.Width - m_diameter - 1 - m_handle_radius;
		pathBkg.AddArc(cornerBkg, 270, 90);

		cornerBkg.Y = rect.Height - m_diameter - 1 - m_yOffset;
		pathBkg.AddArc(cornerBkg, 0, 90);

		if (fillerLength <= m_handle_radius)
		{
			cornerBkg.X = m_handle_radius;

			pathBkg.AddArc(cornerBkg, 90, 90);
		}

		pathBkg.CloseFigure();
		graphics.FillPath(&brushBackground, &pathBkg);

		if (fillerLength > 0)
		{
			SolidBrush brushFiller(m_mouseInside ? m_fillerHoverColor : m_fillerColor);

			Rect cornerFiller(m_handle_radius, m_yOffset, m_diameter, m_diameter);

			GraphicsPath pathFiller;

			pathFiller.Reset();

			pathFiller.AddArc(cornerFiller, 180, 90);

			cornerFiller.X = fillerLength - m_diameter;
			pathFiller.AddArc(cornerFiller, 270, 90);

			cornerFiller.Y = rect.Height - m_diameter - 1 - m_yOffset;
			pathFiller.AddArc(cornerFiller, 0, 90);

			cornerFiller.X = m_handle_radius;
			pathFiller.AddArc(cornerFiller, 90, 90);

			pathFiller.CloseAllFigures();

			graphics.FillPath(&brushFiller, &pathFiller);
		}

		if(m_mouseInside) DrawHandle(fillerLength, &graphics);

		BitBlt(hdc, 0, 0, rect.Width, rect.Height, hdcBuffer, 0, 0, SRCCOPY);

		DeleteDC(hdcBuffer);
		DeleteObject(hBmp);
	}

	LRESULT Slider::HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam)
	{
		static bool mouseTrackingOn = false;

		switch (msg)
		{
			case WM_NCLBUTTONUP:
				if (heldDown) HandleValueDetection();
				heldDown = false;
				return TRUE;
			case WM_LBUTTONUP:
				if (heldDown) HandleValueDetection();
				heldDown = false;
				return TRUE;
			case WM_NCRBUTTONUP:
				if (heldDown) HandleValueDetection();
				heldDown = false;
				return TRUE;
			case WM_RBUTTONUP:
				if (heldDown) HandleValueDetection();
				heldDown = false;
				return TRUE;
			case WM_LBUTTONDOWN:
				heldDown = true;
				return TRUE;
			case WM_RBUTTONDOWN:
				heldDown = true;
				return TRUE;

			case WM_MOUSEMOVE:
				RECT screenControlRect;
				POINT mousePos;

				GetWindowRect(hWnd, &screenControlRect);
				mousePos.x = GET_X_LPARAM(lParam);
				mousePos.y = GET_Y_LPARAM(lParam);
				ClientToScreen(hWnd, &mousePos);

				if (PtInRect(&screenControlRect, mousePos))
				{
					if (hWnd != GetCapture()) {
						m_mouseInside = true;
						SetCapture(hWnd);
						RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
					} else if ((MK_RBUTTON | MK_LBUTTON) & wParam) {
						UpdateProgressPosition();
					}
				} else if (hWnd == GetCapture()) {
					if ((MK_RBUTTON | MK_LBUTTON) & wParam)
						UpdateProgressPosition();
					else
					{
						m_mouseInside = false;
						ReleaseCapture();
						RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

						/*RECT cRect;
						GetClientRect(hWnd, &cRect);

						MapWindowPoints(hWnd, m_parent, (LPPOINT)&cRect, 2);

						InvalidateRect(m_parent, &cRect, true);*/
					}
				}
				break;
			/*case WM_MOUSEMOVE:
				RECT screenControlRect;
				POINT mousePos;

				GetWindowRect(hWnd, &screenControlRect);
				mousePos.x = GET_X_LPARAM(lParam);
				mousePos.y = GET_Y_LPARAM(lParam);

				if (PtInRect(&screenControlRect, mousePos))
				{
					SetTimer(hWnd, TIMER_MOUSE_EVENT, 500, NULL);
					if (hWnd != GetCapture())
					{
						SetCapture(hWnd);
						PostMessage(hWnd, WM_MOUSEENTER, 0, 0L);
					}
					break;
				}
				ReleaseCapture();
				KillTimer(hWnd, TIMER_MOUSE_EVENT);
				PostMessage(hWnd, WM_MOUSELEAVE, 0, 0L);
				break;

			case WM_TIMER:
				GetWindowRect(hWnd, &screenControlRect);
				GetCursorPos(&mousePos);
				if (PtInRect(&screenControlRect, mousePos))
				{
					PostMessageW(hWnd, WM_MOUSEHOVER, 0, 0L);
					break;
				}
				ReleaseCapture();
				KillTimer(hWnd, TIMER_MOUSE_EVENT);
				PostMessage(hWnd, WM_MOUSELEAVE, 0, 0L);
				break;*/

			case WM_MOUSEENTER:

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
			WS_EX_LAYERED, ClassName(), 0, WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS,
			size.left, size.top, size.right, size.bottom,
			m_parent, 0, (HINSTANCE)GetWindowLongPtr(m_parent, GWLP_HINSTANCE),
			this
		);
	}
}