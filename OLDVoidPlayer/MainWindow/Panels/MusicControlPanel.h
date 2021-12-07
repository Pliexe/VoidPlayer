/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#pragma once

#include ""

#define PLAY_BUTTON 1
#define PREV_BUTTON 1
#define NEXT_BUTTON 1
#define TRACK_PROGRESS 10

using namespace ApplicationGUI;
using namespace ApplicationGUI::Controls;

namespace ApplicationGUI
{
	class MusicControlPanel : public Panel<MusicControlPanel>
	{
	public:

		CustomDrawnCircleButton playButton;
		CustomDrawnCircleButton nextButton;
		CustomDrawnCircleButton prevButton;
		Slider trackTimeSlider;

		void Init();

	protected:
		PCWSTR ClassName() const { return L"MusicPanel"; }

		LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam);
	};
}

