#pragma once

#include <Windows.h>
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