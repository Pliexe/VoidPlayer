/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#pragma once

#include <functional>
#include <bass.h>
#include <iostream>

#include "Core.h"
#include "Queue.h"

namespace Music {

	

	class MUSIC_API MusicHandler
	{
	public:
		enum ActiveType {
			Active_Stopped = BASS_ACTIVE_STOPPED,
			Active_Playing = BASS_ACTIVE_PLAYING,
			Active_Paused = BASS_ACTIVE_PAUSED,
			Active_Paused_Device = BASS_ACTIVE_PAUSED_DEVICE,
			Active_Paused_Stalled = BASS_ACTIVE_STALLED
		};

	#pragma region Singleton Implementation

	public:
		MusicHandler(MusicHandler const&)	= delete;
		void operator=(MusicHandler const&) = delete;

		MusicHandler() { };
	private:

	#pragma endregion

	private:
		
		DWORD channel = NULL;

	public:

		bool playNext = false;

		Queue queue;
		unsigned int currentIndex = 0;

		DWORD GetActiveState() { return BASS_ChannelIsActive(channel); }
		bool IsPaused() { 
			return channel == NULL ? true : BASS_ChannelIsActive(channel) == ActiveType::Active_Paused;
		}

		void Init();

		int StartPlayback(unsigned int i, std::function<void()> handleBeforePlaying = nullptr);
		bool SetPosition(double seconds);

		int GetNext()
		{
			if (currentIndex >= queue.Size() - 1)
				return currentIndex;
			else currentIndex = currentIndex + 1;
		}

		int GetPrevious()
		{
			if (currentIndex <= 0) return 0;
			else currentIndex = currentIndex - 1;
		}

		bool Pause();
		bool Play(bool restart = false);

		QWORD Elapsed();
		QWORD CurrentLength();

	#pragma region Events

		std::function<void()> onPlay = nullptr;

		/*std::function<void()> onPlay = NULL;
		std::function<void()> onEnd = NULL;
		std::function<void()> onTime = NULL;*/

	#pragma endregion

	};

}
