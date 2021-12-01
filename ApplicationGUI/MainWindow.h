/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#pragma once

#include <Windows.h>
#include <WinUser.h>
#include <tchar.h>
#include <GdiPlus.h>
#include <windowsx.h>
#include "BaseWindow.h"
#pragma comment(lib,"gdiplus.lib")

#define PLAY_BUTTON 1


#define PANEL_MUSIC_CONTROL 420

typedef void (*VoidFunc)();


namespace ApplicationGUI
{

	class MainWindow : public BaseWindow<MainWindow>
	{
	private:
		void AddControls();

		HWND playButton;

		HWND musicControlPanel;

	public:
		PCWSTR ClassName() const { return L"Void Player Main Window Class"; }
		LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam);
	};
}