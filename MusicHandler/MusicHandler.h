/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#ifndef UNICODE
#define UNICODE
#endif

#pragma once

#pragma comment(lib, "winmm.lib")
#include <Windows.h>
#include <iostream>

namespace Music
{
	class MusicHandler
	{

#pragma region Singleton implementation

	public:
		static MusicHandler& getInstance()
		{
			static MusicHandler instance;

			return instance;
		}

	private:

		MusicHandler() {}

	public:
		MusicHandler(MusicHandler const&)	= delete;
		void operator=(MusicHandler const&) = delete;

#pragma endregion

	public:
		void PlayTest(std::wstring path);
	};
}