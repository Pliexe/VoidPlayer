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

#include "MusicHandler.h"

using namespace Music;
using namespace std;

MusicHandler::MusicHandler()
{
	BASS_Init(-1, 44000, BASS_DEVICE_STEREO, 0, NULL);
}

void MusicHandler::PlayTest(wstring path)
{
	//PlaySound(path, GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);

	LPCWSTR pPath = path.c_str();
	
	MessageBox(NULL, pPath, L"Playing from lib", 0);

	wstring pmsg = wstring(L"open \"") + path;
	wstring smsg = pmsg + L"\" type mpegvideo alias mp3";
	LPCWSTR msg = smsg.c_str();

	MessageBox(NULL, pmsg.c_str(), L"Message", 0);
	MessageBox(NULL, smsg.c_str(), L"Message", 0);

	mciSendString(msg, NULL, 0, NULL);
	mciSendString(L"play mp3 wait", NULL, 0, NULL);
}
