/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#pragma once

#include "Core.h"
#include <vector>
#include <string>
#include <bass.h>

namespace Music {

	struct Track {
		std::wstring title;
		std::wstring path;

		Track() { }
		Track(std::wstring _title, std::wstring _path): title(_title), path(_path) { }
	};

	class MUSIC_API Queue
	{
	private:
		std::vector<Track> tracks;

	public:
		const std::vector<Track>  GetTracks() { return tracks; }

		void Add(wchar_t path[MAX_PATH]);
		void Remove(int index);
		Track Pop(int i);
		unsigned int Size() { return tracks.size(); }

		bool isEmpty() { return tracks.size() <= 0; }
	};


}