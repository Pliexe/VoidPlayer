/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#include "Queue.h"
#include <iostream>

namespace Music {

	void Queue::Add(wchar_t _path[MAX_PATH])
	{
		std::wstring path(_path);
		int toStartAt = path.find_last_of(L"\\") + 1;
		std::wstring title = path.substr(toStartAt, path.length() - toStartAt - 4);

		std::wcout << "TESTING 3: " << title;
		std::cout << std::endl;

		tracks.emplace_back(title, path);
	}

	void Queue::Remove(int index)
	{
		tracks.erase(tracks.begin() + index);
	}

	Track Queue::Get(int index)
	{
		return tracks[index];
	}

	Track Queue::Pop(int i)
	{
		Track temp = tracks[i];
		tracks.erase(tracks.begin() + i);
		return temp;
	}
}