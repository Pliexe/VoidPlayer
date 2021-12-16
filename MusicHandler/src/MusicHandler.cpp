/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#include "MusicHandler.h"

namespace Music {
	void MusicHandler::Init()
	{
	#ifdef _DEBUG
		freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

		std::cout << "HEY AM HERE" << std::endl;
	#endif // _DEBUG

		BASS_Init(-1, 44100, 0, 0, NULL);
		BASS_SetVolume(.5);
	}

	bool MusicHandler::SetPosition(double seconds)
	{
		return BASS_ChannelSetPosition(channel, BASS_ChannelSeconds2Bytes(channel, seconds), BASS_POS_BYTE);
	}

	QWORD MusicHandler::Elapsed()
	{
		return BASS_ChannelBytes2Seconds(channel, BASS_ChannelGetPosition(channel, BASS_POS_BYTE));
	}

	QWORD MusicHandler::CurrentLength()
	{
		return BASS_ChannelBytes2Seconds(channel, BASS_ChannelGetLength(channel, BASS_POS_BYTE));
	}

	bool MusicHandler::Pause()
	{
		return BASS_ChannelPause(channel);
	}

	bool MusicHandler::Play(bool restart)
	{
		return BASS_ChannelPlay(channel, restart);
	}

	int MusicHandler::StartPlayback(unsigned int i, std::function<void()> handleBeforePlaying)
	{

	#ifdef _DEBUG
		freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

		std::cout << "Init clicked" << std::endl;
	#endif // _DEBUG

		unsigned int test = queue.Size();

		if (queue.isEmpty()) return 0;
		if (i >= queue.Size()) return -1;
		if (channel != NULL) BASS_StreamFree(channel);

		current = queue.Pop(i);

	#ifdef _DEBUG
		std::wcout << L"Path: " << current.path;
		std::cout << std::endl;
		std::wcout << "Title: " << current.title;
		std::cout << std::endl;

	#endif // _DEBUG


		if (!(channel = BASS_StreamCreateFile(FALSE, current.path.c_str(), 0, 0, NULL)))
		{
			return -2;
		}

		if (handleBeforePlaying != nullptr)
			handleBeforePlaying();

		BASS_ChannelPlay(channel, FALSE);

		if (onPlay != nullptr)
			onPlay();

		return 1;
	}
}
