/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#pragma once

#include <ApplicationGUI.h>
#include <bass.h>
#include <Windows.h>

class MainWindow : public ApplicationGUI::BaseWindow
{
private:
	Controls::CustomDrawnIconButton playBtn;
	Controls::CustomDrawnIconButton nextBtn;
	Controls::CustomDrawnIconButton prevBtn;
	Controls::Slider trackTimeSlider;

	Controls::Panel musicPanel;

	void AddControls();

public:
	PCWSTR ClassName() const { return L"VoidPlayer MainWin Class"; }
	LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam);
};

