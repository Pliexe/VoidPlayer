/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#include "MainWindow.h"
#include "MusicHandler.h"
#include "Queue.h"

extern Music::MusicHandler musicHandler;

using namespace Controls;

inline void MainWindow::AddControls()
{
	musicHandler.onPlay = [&]() {
		Music::Track current = musicHandler.queue.Get(musicHandler.currentIndex);
		std::cout << "Title: ";
		std::wcout << current.title;
		std::cout << std::endl;
		songTitle.SetText(current.title.c_str());

		double duration = musicHandler.CurrentLength();

		std::cout << "Length is: " << duration << std::endl;

		wchar_t text[64];

		swprintf(text, sizeof(text), L"%02u:%02u", (int)duration / 60, (int)duration % 60);

		std::wcout << L"string is: " << text;
		std::cout << std::endl;


		totalTrackLength.SetText(text);
		playBtn.Redraw();
	};

	musicPanel = Panel();

	musicPanel.EnableDynamicResizing();
	musicPanel.SetAnchorY(ANCHOR_BOTTOM);
	musicPanel.SetPosPivot(PIVOT_LEFT_BOTTOM);
	musicPanel.SetWidthPercent(100);
	musicPanel.SetSize(0, 120);
	musicPanel.SetBackgroundBrush(CreateSolidBrush(RGB(20, 24, 66)));

	RegisterControl(&musicPanel);

	playBtn = CustomDrawnIconButton();

	playBtn.EnableDynamicResizing();
	playBtn.SetAnchorX(ANCHOR_MIDDLE);
	playBtn.SetPosAndSize(0, 10, 50, 50);
	playBtn.SetPosPivot(PIVOT_LEFT_MIDDLE_TOP_RIGHT);
	playBtn.SetBkgColor(Color(255, 255, 255));
	playBtn.SetIconCallback([&](Graphics& graphics) {

		if (musicHandler.IsPaused())
		{
			SolidBrush iconBrush(Color(0, 10, 115));

			Point verticesT[] = { { 17, 15}, {17, 35}, {35,  25} }; // Why does trigRect.top + move it up??

			graphics.FillPolygon(&iconBrush, verticesT, 3);
		} else {
			SolidBrush iconBrush(Color(0, 10, 115));

			graphics.FillRectangle(&iconBrush, 15, 15, 7, 20);
			graphics.FillRectangle(&iconBrush, 28, 15, 7, 20);

		}
	});

	playBtn.onMouseDown = [&](HWND hwnd, MouseButton btn) { PlayPause(); };

	musicPanel.RegisterControl(&playBtn);

	prevBtn = CustomDrawnIconButton();

	prevBtn.EnableDynamicResizing();
	prevBtn.SetAnchorX(ANCHOR_MIDDLE);
	prevBtn.SetPosAndSize(-70, 10, 50, 50);
	prevBtn.SetPosPivot(PIVOT_LEFT_MIDDLE_TOP_RIGHT);
	prevBtn.SetBkgColor(Color(0, 10, 115));
	prevBtn.SetIconCallback([](Graphics& graphics) {

		SolidBrush iconBrush(Color(255, 255, 255, 255));
		Pen iconPen(Color(255, 255, 255, 255));

		Point vertices1P[] = { {25, 15}, {25, 35}, {15, 25} };
		Point vertices2P[] = { {35, 15}, {35, 35}, {25, 25} };

		graphics.FillPolygon(&iconBrush, vertices1P, 3);
		graphics.FillPolygon(&iconBrush, vertices2P, 3);
		graphics.DrawLine(&iconPen, 15, 15, 15, 35);

	});

	prevBtn.onMouseUp = [&](HWND hwnd, MouseButton btn) {
		musicHandler.StartPlayback(musicHandler.GetPrevious(), [&]() {
			trackTimeSlider.SetMaxValue(musicHandler.CurrentLength());
		});
	};

	musicPanel.RegisterControl(&prevBtn);

	nextBtn = CustomDrawnIconButton();

	nextBtn.EnableDynamicResizing();
	nextBtn.SetAnchorX(ANCHOR_MIDDLE);
	nextBtn.SetPosAndSize(70, 10, 50, 50);
	nextBtn.SetPosPivot(PIVOT_LEFT_MIDDLE_TOP_RIGHT);
	nextBtn.SetBkgColor(Color(0, 10, 115));
	nextBtn.SetIconCallback([](Graphics& graphics) {
		SolidBrush iconBrush(Color(255, 255, 255, 255));
		Pen iconPen(Color(255, 255, 255, 255));

		Point vertices1P[] = { {15, 15}, {15, 35}, {25, 25} };
		Point vertices2P[] = { {25, 15}, {25, 35}, {35, 25} };

		graphics.FillPolygon(&iconBrush, vertices1P, 3);
		graphics.FillPolygon(&iconBrush, vertices2P, 3);
		graphics.DrawLine(&iconPen, 35, 15, 35, 35);
	});

	nextBtn.onMouseUp = [&](HWND hwnd, MouseButton btn) { Next(); };

	musicPanel.RegisterControl(&nextBtn);

	trackTimeSlider = Slider();

	trackTimeSlider.EnableDynamicResizing();
	trackTimeSlider.SetAnchorX(ANCHOR_MIDDLE);
	trackTimeSlider.SetPosPivot(PIVOT_LEFT_MIDDLE_TOP_RIGHT);
	trackTimeSlider.SetRadius(5);
	trackTimeSlider.SetPosAndSize(0, 70, 600, 10);
	trackTimeSlider.SetValue(20);
	
	trackTimeSlider.SetColors(Color(150, 150, 150), Color(0, 135, 29), Color(20, 97, 0), Color(255, 255, 255));
	trackTimeSlider.SetHandleSize(9);
	trackTimeSlider.onChange = [&](int newvalue) {
		musicHandler.SetPosition(newvalue);

		if (musicHandler.IsPaused())
		{
			double elapsed = musicHandler.Elapsed();

			wchar_t text[64];

			swprintf(text, sizeof(text), L"%d:%d", (int)elapsed / 60, (int)elapsed % 60);

			currentTrackLength.SetText(text);
		}
	};

	musicPanel.RegisterControl(&trackTimeSlider);

	currentTrackLength.SetText(L"00:00");
	currentTrackLength.SetPosAndSize(-305, 70, 200, 50);
	currentTrackLength.EnableDynamicResizing();
	currentTrackLength.SetAnchorX(Controls::ANCHOR_MIDDLE);
	currentTrackLength.SetColor(Color(255, 255, 255));
	currentTrackLength.SetTextAlign(TextAlign::TextAlign_Right);
	currentTrackLength.SetPosPivot(PIVOT_RIGHT_TOP);

	musicPanel.RegisterControl(&currentTrackLength);

	totalTrackLength.SetText(L"00:00");
	totalTrackLength.SetPosAndSize(305, 70, 200, 50);
	totalTrackLength.EnableDynamicResizing();
	totalTrackLength.SetAnchorX(Controls::ANCHOR_MIDDLE);
	totalTrackLength.SetColor(Color(255, 255, 255));

	musicPanel.RegisterControl(&totalTrackLength);

	songTitle.SetPosAndSize(10, 20, 800, 50);
	songTitle.SetWidthPercent(40);
	songTitle.EnableDynamicResizing();
	songTitle.SetFontSize(18);
	songTitle.SetText(L"IDK");
	//songTitle.SetAnchorX();
	songTitle.SetColor(Color(255, 255, 255));

	musicPanel.RegisterControl(&songTitle);

	

	LPWSTR* szArglist;
	int nArgs;
	szArglist = CommandLineToArgvW(GetCommandLine(), &nArgs);


	if (nArgs > 1)
	{
		DWORD dwAttrib = GetFileAttributes(szArglist[1]);

		if ((dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY)))
		{
			musicHandler.queue.Add(szArglist[1]);

			musicHandler.StartPlayback(0, [&]() {
				trackTimeSlider.SetMaxValue(musicHandler.CurrentLength());
			});
		}
	}
}

void MainWindow::PlayPause()
{
	switch (musicHandler.GetActiveState())
	{
		case Music::MusicHandler::ActiveType::Active_Stopped:
			musicHandler.StartPlayback(musicHandler.currentIndex, [&]() {
				trackTimeSlider.SetMaxValue(musicHandler.CurrentLength());
			});
			break;
		case Music::MusicHandler::Active_Paused:
			musicHandler.Play();
			playBtn.Redraw();
			break;
		case Music::MusicHandler::Active_Playing:
			musicHandler.Pause();
			playBtn.Redraw();
			break;
		case Music::MusicHandler::Active_Paused_Device:
			MessageBox(hWnd, L"Device paused!", L"Failure", MB_ICONINFORMATION);
			break;
		case Music::MusicHandler::Active_Paused_Stalled:
			MessageBox(hWnd, L"Insufficient data. Playback will automatically resume once there is sufficent data!", L"Failure", MB_ICONERROR);
			break;
	}
}

void MainWindow::Next()
{
	musicHandler.StartPlayback(musicHandler.GetNext(), [&]() {
		trackTimeSlider.SetMaxValue(musicHandler.CurrentLength());
	});
}

LRESULT MainWindow::HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CREATE:
			AddControls();

			SetTimer(hWnd, 0, 100, 0);

			break;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			HBRUSH brush = CreateSolidBrush(RGB(6, 32, 74));

			FillRect(hdc, &ps.rcPaint, brush);
			EndPaint(hWnd, &ps);

			DeleteObject(brush);

			break;
		}

		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_SPACE:
					PlayPause();
					break;
				case VK_F1:
				{
					//currentTrackLength.Redraw();

					double elapsed = musicHandler.Elapsed();

					//if (elapsed == musicHandler.CurrentLength()) MessageBox(hWnd, L"HAHAHA", L"END", MB_ICONINFORMATION);

					trackTimeSlider.SetValue(elapsed);

					wchar_t text[64];

					swprintf(text, sizeof(text), L"Track: %u - %02u:%02u", musicHandler.currentIndex, (int)elapsed / 60, (int)elapsed % 60);

					std::wcout << "RESULT IS: " << text;
					std::cout << std::endl;

					currentTrackLength.SetText(text);

					std::cout << "STATE: " << musicHandler.GetActiveState() << std::endl;

					break;
				}
			}

			return TRUE;
		}

		case WM_DROPFILES:
		{

			HDROP hDropInfo = (HDROP)wParam;

			wchar_t sItem[MAX_PATH];

			DragQueryFile(hDropInfo, 0, (LPWSTR)sItem, sizeof(sItem));

			if (GetFileAttributes(sItem) & FILE_ATTRIBUTE_DIRECTORY)
				MessageBox(hWnd, L"Got folder, i cant play this man!", L"VoidPlayer", 0);
			else
			{
				//MessageBox(hWnd, L"Added to queue!", sItem, 0);

				musicHandler.queue.Add(sItem);

				/*HSAMPLE sample = BASS_SampleLoad(false, sItem, 0, 0, 1, BASS_SAMPLE_MONO);
				HCHANNEL channel = BASS_SampleGetChannel(sample, FALSE);
				BASS_ChannelPlay(channel, FALSE);*/
			}

			DragFinish(hDropInfo);

			break;
		}

		case WM_COPYDATA:
		{
			COPYDATASTRUCT* cds;
			cds = (COPYDATASTRUCT*)lParam;

			if (cds->dwData == CD_COMMAND_LINE)
			{
				
				LPWSTR* arglist = (LPWSTR*)cds->lpData;



				/*DWORD dwAttrib = GetFileAttributes(arglist[1]);

				if ((dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY)))
				{
					musicHandler.queue.Add(arglist[1]);

					musicHandler.StartPlayback(0, [&]() {
						trackTimeSlider.SetMaxValue(musicHandler.CurrentLength());
					});
				}*/
			}
			break;
		}

		case WM_TIMER:
		{
			switch (musicHandler.GetActiveState())
			{
				case Music::MusicHandler::Active_Stopped:
					if (musicHandler.playNext && musicHandler.Elapsed() == musicHandler.CurrentLength())
					{
						musicHandler.playNext = false;
						if(musicHandler.queue.Size() - 1 != musicHandler.currentIndex)
							Next();
					}
					break;
				case Music::MusicHandler::Active_Playing:
				{
					double elapsed = musicHandler.Elapsed();

					////if (elapsed == musicHandler.CurrentLength()) MessageBox(hWnd, L"HAHAHA", L"END", MB_ICONINFORMATION);

					trackTimeSlider.SetValue(elapsed);

					wchar_t text[64];

					swprintf(text, sizeof(text), L"Track: %u - %02u:%02u", musicHandler.currentIndex, (int)elapsed / 60, (int)elapsed % 60);

					//std::wcout << "RESULT IS: " << text;
					//std::cout << std::endl;

					currentTrackLength.SetText(text);

					//std::cout << "STATE: " << musicHandler.GetActiveState() << std::endl;

					break;
				}
			}

			break;
		}

		case WM_SIZE:
		{
			RECT rect;

			GetClientRect(hWnd, &rect);

			musicPanel.OnParentResize(rect);

			break;
		}

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);

	}

	return TRUE;
}
