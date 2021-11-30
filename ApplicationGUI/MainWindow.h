#pragma once

#include <Windows.h>
/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#include <tchar.h>

const int test = 66;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

namespace ApplicationGUI
{
	class MainWindow
	{

	private:

		HWND hWnd;			 // Window Handle
		HINSTANCE hInstance; // prg instance
		LPCTSTR CLASS_NAME = TEXT("Void Player Window Class");

		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	public:

#pragma region Singleton Class

		// Get instance

		static MainWindow& getInstance(HINSTANCE hInstance);

		MainWindow() { }

		MainWindow(MainWindow const&) = delete;
		void operator=(MainWindow const&) = delete;

#pragma endregion

		int Init(); // Initialize Window

	};
}