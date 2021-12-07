/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>
#include <gdiplus.h>
#include <iostream>
#include <functional>

#include "../Core.h"

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

#pragma endregion


	class GUI_API Control
	{
	protected:

		#pragma region Position and Size

		int m_x;
		int m_y;

		int m_width;
		int m_height;

#pragma endregion

		#pragma region Position and Size Percent scaling

		float m_xPercent = false;
		float m_yPercent = false;

		float m_hPercent = false;
		float m_wPercent = false;

#pragma endregion

		#pragma region AnchorRegions

		ControlPivot m_pivotPoint = ControlPivot::LEFT_TOP;

		AnchorPoint m_xAnchor = ANCHOR_LEFT;
		AnchorPoint m_yAnchor = ANCHOR_TOP;

#pragma endregion

		HMENU m_hmenu = NULL;	// ID to control
		HWND m_parent = NULL;	// Handle to parent window
		HWND hWnd = NULL;		// Handle to this control (window)

		virtual void OnPaint(HDC& hdc, PAINTSTRUCT& ps) = 0;

		void GetNewSize(RECT parentNewSize, RECT& newSize); // Get a new position and size in current parent cordinates (This was pain to make)

		

		std::function<void(WNDCLASS&, HINSTANCE, Controls::Control*)> DefaultClass();
		void RegisterClassIfUnregistered(HWND parent, std::function<void(WNDCLASS&, HINSTANCE, Controls::Control*)> registerClass)
		{
			HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE);
			WNDCLASS wc = { 0 };

			if (!GetClassInfo(hInstance, this->ClassName(), &wc))
				registerClass(wc, hInstance, this);
		}
		bool RegisterDefaultWindow(int x, int y, int w, int h, HWND parent, HMENU hmenu = 0, PCWSTR title = NULL);
	public:

		virtual LRESULT HandleMessage(UINT umsg, WPARAM wParam, LPARAM lParam) = 0;
		virtual PCWSTR ClassName() const = 0;
		//HWND Window() const { return hWnd; }

		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


		#pragma region Helper functions for changing / getting members

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

		void SetAnchorX(AnchorPoint ap) { m_xAnchor = ap; }
		void SetAnchorY(AnchorPoint ap) { m_yAnchor = ap; }

		void SetPosPivot(ControlPivot piv) { m_pivotPoint = piv; }

		HWND GetHandle() { return hWnd; }

#pragma endregion

		void Create(HWND parent, int x, int y, int width, int height, HMENU hmenu = 0);
	};

	//using onWcRegister = std::function<void(WNDCLASS&, HINSTANCE, Controls::Control*)>;
}

