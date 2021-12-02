/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#pragma once

#include <Windows.h>
#include <gdiplus.h>

using namespace Gdiplus;

namespace ApplicationGUI
{
	namespace Utils {

		void GetRoundRectPath(GraphicsPath* pPath, Rect r, int dia)
		{
			if (dia > r.Width) dia = r.Width;
			if (dia > r.Height) dia = r.Height;

			// define a corner
			Rect Corner(r.X, r.Y, dia, dia);

			pPath->Reset();

			// top left
			pPath->AddArc(Corner, 180, 90);

			// tweak needed for radius of 10 (dia of 20)
			if (dia == 20)
			{
				Corner.Width += 1;
				Corner.Height += 1;
				r.Width -= 1; r.Height -= 1;
			}

			// top right
			Corner.X += (r.Width - dia - 1);
			pPath->AddArc(Corner, 270, 90);

			// bottom right
			Corner.Y += (r.Height - dia - 1);
			pPath->AddArc(Corner, 0, 90);

			// bottom left
			Corner.X -= (r.Width - dia - 1);
			pPath->AddArc(Corner, 90, 90);

			// end path
			pPath->CloseFigure();
		}

        void DrawRoundRect(Graphics* pGraphics, Rect r, Color color, int radius, int width)
        {
            int dia = 2 * radius;

            // set to pixel mode
            int oldPageUnit = pGraphics->SetPageUnit(UnitPixel);

            // define the pen
            Pen pen(color, 1);
            pen.SetAlignment(PenAlignmentCenter);

            // get the corner path
            GraphicsPath path;

            // get path
            GetRoundRectPath(&path, r, dia);

            // draw the round rect
            pGraphics->DrawPath(&pen, &path);

            // if width > 1
            for (int i = 1; i < width; i++)
            {
                // left stroke
                r.Inflate(-1, 0);
                // get the path
                GetRoundRectPath(&path, r, dia);

                // draw the round rect
                pGraphics->DrawPath(&pen, &path);

                // up stroke
                r.Inflate(0, -1);

                // get the path
                GetRoundRectPath(&path, r, dia);

                // draw the round rect
                pGraphics->DrawPath(&pen, &path);
            }

            // restore page unit
            pGraphics->SetPageUnit((Unit)oldPageUnit);
        }

        void FillRoundRect(Graphics* pGraphics, Brush* pBrush, Rect r, Color border, int radius)
        {
            int dia = 2 * radius;

            // set to pixel mode
            int oldPageUnit = pGraphics->SetPageUnit(UnitPixel);

            // define the pen
            Pen pen(border, 1);
            pen.SetAlignment(PenAlignmentCenter);

            // get the corner path
            GraphicsPath path;

            // get path
            GetRoundRectPath(&path, r, dia);

            // fill
            pGraphics->FillPath(pBrush, &path);

            // draw the border last so it will be on top
            pGraphics->DrawPath(&pen, &path);

            // restore page unit
            pGraphics->SetPageUnit((Unit)oldPageUnit);
        }
	}
}