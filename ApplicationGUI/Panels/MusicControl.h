/* Copyright (C) 2021 Sabadi L�szl�-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#pragma once

#include "Controls.h"
#include <CommCtrl.h>

#define PLAY_BUTTON 1
#define PREV_BUTTON 2
#define NEXT_BUTTON 3
#define SLIDER_PROGRESS 10

using namespace Controls;

namespace ApplicationGUI
{

	class MusicControlPanel : public Panel<MusicControlPanel>
	{
	public:

		CustomDrawnCircleButton playButton;
		CustomDrawnCircleButton nextButton;
		CustomDrawnCircleButton prevButton;
		Slider trackTimeSlider;
		
	public:
		void Init()
		{
			playButton = Controls::CustomDrawnCircleButton();
			playButton.EnableDynamicResizing();
			playButton.SetAnchorX(AnchorPoint::ANCHOR_MIDDLE);
			playButton.SetPosPivot(ControlPivot::LEFT_MIDDLE_TOP_RIGHT);

			playButton.CreateWithGradient(
				hWnd,
				0, 10,
				50, 50,
				(HMENU)PLAY_BUTTON,
				Color(255, 0, 0, 255), Color(255, 0, 100, 100)
			);

			prevButton = Controls::CustomDrawnCircleButton();
			prevButton.EnableDynamicResizing();
			prevButton.SetAnchorX(AnchorPoint::ANCHOR_MIDDLE);
			prevButton.SetPosPivot(ControlPivot::LEFT_MIDDLE_TOP_RIGHT);

			prevButton.CreateWithGradient(
				hWnd,
				-70, 10,
				50, 50,
				(HMENU)PLAY_BUTTON,
				Color(255, 0, 0, 255), Color(255, 0, 100, 100)
			);

			nextButton = Controls::CustomDrawnCircleButton();
			nextButton.EnableDynamicResizing();
			nextButton.SetAnchorX(AnchorPoint::ANCHOR_MIDDLE);
			nextButton.SetPosPivot(ControlPivot::LEFT_MIDDLE_TOP_RIGHT);

			nextButton.CreateWithGradient(
				hWnd,
				70, 10,
				50, 50,
				(HMENU)PLAY_BUTTON,
				Color(255, 0, 0, 255), Color(255, 0, 100, 100)
			);

			trackTimeSlider = Slider();

			trackTimeSlider.EnableDynamicResizing();
			trackTimeSlider.SetAnchorX(AnchorPoint::ANCHOR_MIDDLE);
			trackTimeSlider.SetPosPivot(ControlPivot::LEFT_MIDDLE_TOP_RIGHT);

			trackTimeSlider.Create(
				hWnd, 
				0, 80, 800, 12,
				6,
				(HMENU)SLIDER_PROGRESS, Color(255, 255, 255), Color(10, 10, 10), Color(0, 0, 0));

			//HWND hwndTrack =CreateWindow(
			//	TRACKBAR_CLASS,
			//	TEXT("Trackbar Control"),
			//	WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS | TBS_ENABLESELRANGE,
			//	100, 70, m_width - 200, 20,
			//	hWnd,
			//	0,
			//	(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			//	NULL
			//);

			//SendMessage(hwndTrack, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(0, 100));

			//SendMessage(hwndTrack, TBM_SETPAGESIZE,
			//	0, (LPARAM)4);                  // new page size 

			//SendMessage(hwndTrack, TBM_SETSEL,
			//	(WPARAM)FALSE,                  // redraw flag 
			//	(LPARAM)MAKELONG(1, 1000));

			//SendMessage(hwndTrack, TBM_SETPOS,
			//	(WPARAM)TRUE,                   // redraw flag 
			//	(LPARAM)50);
		}

		PCWSTR ClassName() const { return L"MusicPanel"; }

		LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam)
		{
			switch (msg)
			{

			case WM_SIZE:
			{
				RECT rect;
				GetClientRect(hWnd, &rect);

				prevButton.OnParentResize(rect);
				playButton.OnParentResize(rect);
				nextButton.OnParentResize(rect);
				trackTimeSlider.OnParentResize(rect);

				return TRUE;
			}

			case WM_CREATE:
			{
				Init();

				return TRUE;
			}

			case WM_DRAWITEM:
			{
				DRAWITEMSTRUCT* lpDrawItem = (DRAWITEMSTRUCT*)lParam;

				if (lpDrawItem->hwndItem == playButton.hWnd)
				{
					auto cbIcon = [](Graphics& graphics) {
						SolidBrush iconBrush(Color(255, 255, 255, 255));

						Point verticesT[] = { { 17, 15}, {17, 35}, {35,  25} }; // Why does trigRect.top + move it up??

						graphics.FillPolygon(&iconBrush, verticesT, 3);
					};

					playButton.DrawControl(lpDrawItem, cbIcon);
				}
				else if (lpDrawItem->hwndItem == nextButton.hWnd)
				{
					auto cbIcon = [](Graphics& graphics) {
						SolidBrush iconBrush(Color(255, 255, 255, 255));
						Pen iconPen(Color(255, 255, 255, 255));

						Point vertices1P[] = { {15, 15}, {15, 35}, {25, 25} };
						Point vertices2P[] = { {25, 15}, {25, 35}, {35, 25} };

						graphics.FillPolygon(&iconBrush, vertices1P, 3);
						graphics.FillPolygon(&iconBrush, vertices2P, 3);
						graphics.DrawLine(&iconPen, 35, 15, 35, 35);
					};

					playButton.DrawControl(lpDrawItem, cbIcon);
				}
				else if (lpDrawItem->hwndItem == prevButton.hWnd)
				{
					auto cbIcon = [](Graphics& graphics) {
						SolidBrush iconBrush(Color(255, 255, 255, 255));
						Pen iconPen(Color(255, 255, 255, 255));

						Point vertices1P[] = { {25, 15}, {25, 35}, {15, 25} };
						Point vertices2P[] = { {35, 15}, {35, 35}, {25, 25} };

						graphics.FillPolygon(&iconBrush, vertices1P, 3);
						graphics.FillPolygon(&iconBrush, vertices2P, 3);
						graphics.DrawLine(&iconPen, 15, 15, 15, 35);
					};

					playButton.DrawControl(lpDrawItem, cbIcon);
				}
				else if (lpDrawItem->hwndItem == trackTimeSlider.hWnd)
				{
					trackTimeSlider.DrawnControl(lpDrawItem);
				}
				

				return TRUE;

			}

			case WM_MOUSEACTIVATE:
			{
				switch (wParam)
				{
				default:
					break;
				}
			}

			case WM_COMMAND:

				switch (wParam)
				{
				case PLAY_BUTTON:
					MessageBox(hWnd, TEXT("Clicked"), TEXT("EYY"), MB_OK);
					break;
				case SLIDER_PROGRESS:
					trackTimeSlider.SelectSection();
					break;
				}

				return TRUE;

			case WM_PAINT:

			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);

				// Paint

				HBRUSH brush = CreateSolidBrush(RGB(backgroundColor.GetRed(), backgroundColor.GetGreen(), backgroundColor.GetBlue(), backgroundColor.GetAlpha()));

				FillRect(hdc, &ps.rcPaint, brush);
				EndPaint(hWnd, &ps);

				return TRUE;
			}
			default:
				return DefWindowProc(hWnd, msg, wParam, lParam);
			}


			return TRUE;
		}
	};

}