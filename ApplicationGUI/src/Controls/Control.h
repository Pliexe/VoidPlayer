/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#pragma once

#include "pch.h"

#include "Core.h"

using namespace Gdiplus;

namespace Controls {

#pragma region Snapping enums

	enum AnchorPoint {
		ANCHOR_LEFT,
		ANCHOR_RIGHT,
		ANCHOR_TOP,
		ANCHOR_BOTTOM,
		ANCHOR_MIDDLE
	};

	enum ControlPivot {
		PIVOT_LEFT_TOP,
		PIVOT_LEFT_BOTTOM,
		PIVOT_LEFT_MIDDLE_TOP_RIGHT,
		PIVOT_LEFT_MIDDLE_BOTTOM,
		PIVOT_MIDDLE,
		PIVOT_RIGHT_TOP,
		PIVOT_RIGHT_BOTTOM,
		PIVOT_RIGHT_MIDDLE_BOTTOM,
		PIVOT_RIGHT_MIDDLE_BOTTOM_LEFT
	};

	enum TextAlign {

	};

#pragma endregion

#pragma region Buttons

	enum MouseButton {
		RIGHT_BUTTON,
		LEFT_BUTTON,
		MIDDLE_BUTTON
	};

#pragma endregion

	class GUI_API Control
	{
	public:

	protected:
		bool dynamicResizing = false;

		#pragma region Position and Size

		int m_x = 0;
		int m_y = 0;

		int m_width = 50;
		int m_height = 50;

		#pragma endregion

		#pragma region Position and Size Percent scaling

		float m_xPercent = false;
		float m_yPercent = false;

		float m_hPercent = false;
		float m_wPercent = false;

		#pragma endregion

		#pragma region AnchorRegions

		ControlPivot m_pivotPoint = ControlPivot::PIVOT_LEFT_TOP;

		AnchorPoint m_xAnchor = AnchorPoint::ANCHOR_LEFT;
		AnchorPoint m_yAnchor = AnchorPoint::ANCHOR_TOP;

		#pragma endregion

		LPCWSTR m_text = NULL;

		HWND m_parent = NULL;	// Handle to parent window
		HWND hWnd = NULL;		// Handle to this control (window)

		Rect WinRectToGdiRect(RECT rect);


		void GetNewSize(RECT& parentNewSize, RECT& newSize); // Get a new position and size in current parent cordinates (This was pain to make)

		std::function<void(WNDCLASS&, HINSTANCE, Control*)> DefaultClass();
		void RegisterClassIfUnregistered(std::function<void(WNDCLASS&, HINSTANCE, Control*)> registerClass)
		{ 
			HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(m_parent, GWLP_HINSTANCE);
			WNDCLASS wc = { 0 };

			if (!GetClassInfo(hInstance, this->ClassName(), &wc))
				registerClass(wc, hInstance, this);
		}
		bool RegisterDefaultWindow(RECT size);


		std::vector<Control*> m_Controls;
	public:
		void SetParent(HWND parent) { m_parent = parent; }
		void OnParentResize(RECT& parentNewSize);

		void RegisterControl(Control *control);

		void Create();

		HWND Window() const { return hWnd;  } // Return handle to window

		void EnableDynamicResizing() { dynamicResizing = true; }
		void DisableDynamicResizing() { dynamicResizing = false; }

		virtual void OnPaint(HDC& hdc, RECT& toRepaint) = 0;


		#pragma region Events
		
		std::function<void(HWND)> onHover = NULL;
		std::function<void(HWND, MouseButton)> onClick = NULL;
		std::function<void(HWND, MouseButton)> onMouseDown = NULL;
		std::function<void(HWND, MouseButton)> onMouseUp = NULL;

		std::function<void(HWND)> onResize = NULL;

		#pragma endregion

		virtual LRESULT HandleMessage(UINT umsg, WPARAM wParam, LPARAM lParam) = 0;
		virtual PCWSTR ClassName() const = 0;
		//HWND Window() const { return hWnd; }

		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK WindowProcMinimal(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		#pragma region Helper functions for changing / getting members

		void SetX(int x) { m_x = x; }
		void SetY(int y) { m_y = y; }

		void SetWidth(int width) { m_width = width; }
		void SetHeight(int height) { m_height = height; }

		void SetPos(int x, int y) { m_x = x; m_y = y; }
		void SetSize(int width, int height) { m_width = width; m_height = height; }
		void SetPosAndSize(int x, int y, int width, int height) { m_x = x; m_y = y; m_width = width; m_height = height; }

		void SetXpercent(float x) { m_xPercent = x / 100.0; }
		void SetYpercent(float y) { m_yPercent = y / 100.0; }

		void SetWidthPercent(float width) { m_wPercent = width / 100.0; }
		void SetHeightPercent(float heigth) { m_hPercent = heigth / 100.0; }

		void SetAnchorX(AnchorPoint ap) { m_xAnchor = ap; }
		void SetAnchorY(AnchorPoint ap) { m_yAnchor = ap; }

		void SetPosPivot(ControlPivot piv) { m_pivotPoint = piv; }

		void Redraw() { RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW); }

		HWND GetHandle() { return hWnd; }

#pragma endregion
	};

	//using onWcRegister = std::function<void(WNDCLASS&, HINSTANCE, Controls::Control*)>;
}

