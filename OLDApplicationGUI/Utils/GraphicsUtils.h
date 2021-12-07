/* Copyright (C) 2021 Sabadi László-Zsolt - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VoidPlayer/blob/master/LICENSE
 */

#pragma once

#include "agpch.h"

using namespace Gdiplus;

namespace ApplicationGUI
{
    namespace Utils {

        void GetRoundRectPath(GraphicsPath* path, Rect rect, int diameter)
        {
            Rect corner(rect.X, rect.Y, diameter, diameter);

            path->Reset();

            path->AddArc(corner, 180, 90);

            corner.X += rect.Width - diameter - 1;
            path->AddArc(corner, 270, 90);

            corner.Y += rect.Height - diameter - 1;
            path->AddArc(corner, 0, 90);

            corner.X -= rect.Width - diameter - 1;
            path->AddArc(corner, 90, 90);

            path->CloseFigure();
        }

        void FillRoundRect(Graphics* graphics, Rect rect, Brush* brush, Pen* pen, int radius)
        {
            int diameter = 2 * radius;

            GraphicsPath path;

            GetRoundRectPath(&path, rect, diameter);

            graphics->FillPath(brush, &path);
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
