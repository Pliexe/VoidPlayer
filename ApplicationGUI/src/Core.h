/* Copyright (C) 2021 Sabadi L�szl�-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#pragma once


#ifdef APPGUI_BUILD_DLL
#define GUI_API __declspec(dllexport)
#else
#define GUI_API __declspec(dllimport)
#endif