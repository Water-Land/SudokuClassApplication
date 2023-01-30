#include"SudokuViewClass.h"
#define _CRT_SECURE_NO_WARNINGS
#define _OPEN_SYS_ITOA_EXT
#include <stdio.h>
#include <stdlib.h>

SudokuViewClass::SudokuViewClass()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			Board[i][j] = 0;
			Mask[i][j] = 0;
		}
	}
	cellsize.cx = cellsize.cy = 64;
	cellpaddingsize.cx = 22;
	cellpaddingsize.cy = 14;
	pos.x = 0;
	pos.y = 0;
}
SudokuViewClass::~SudokuViewClass()
{

}
void SudokuViewClass::DataSet(int x, int y, int num)
{
	Board[x][y] = num;
}
int SudokuViewClass::DataGet(int x, int y)
{
	return Board[x][y];
}
void SudokuViewClass::DataDraw(HDC hDC)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			RECT cellRect;
			cellRect.left = pos.x + i * cellsize.cx;
			cellRect.top = pos.y + j * cellsize.cy;
			cellRect.right = pos.x + (i+1) * cellsize.cx;
			cellRect.bottom = pos.y + (j+1) * cellsize.cy;
			if (Mask[i][j] == 1 && chk1==true)
			{
				HBRUSH bru = CreateSolidBrush(RGB(240, 195, 195));
				HBRUSH obru = (HBRUSH)SelectObject(hDC, bru);
				HPEN pen = (HPEN)GetStockObject(NULL_PEN);
				HPEN open = (HPEN)SelectObject(hDC, pen);
				Rectangle(hDC, cellRect.left, cellRect.top, cellRect.right, cellRect.bottom);
				SelectObject(hDC, open);
				SelectObject(hDC, obru);
				DeleteObject(bru);
			}
			HFONT hFont1 = CreateFont(36, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_ROMAN, NULL);
			HFONT hFont2 = (HFONT)SelectObject(hDC, hFont1);
			char buffer[256] = { 0 };
			_itoa_s(Board[i][j], buffer, 10);
			if (Board[i][j] != 0)
			{
				SetBkMode(hDC, TRANSPARENT);
				TextOutA(hDC, cellpaddingsize.cx + pos.x + i * cellsize.cx, cellpaddingsize.cy + pos.y + j * cellsize.cy, buffer, 1);
			}
			SelectObject(hDC, hFont2);
			DeleteObject(hFont1);
		}
	}
	for (int i = 0; i < 10; i++)
	{
		MoveToEx(hDC, pos.x + i * cellsize.cx, pos.y, NULL);
		LineTo(hDC, pos.x + i * cellsize.cx, pos.y + cellsize.cy * 9);
		if (i % 3 == 0)
		{
			MoveToEx(hDC, pos.x + i * cellsize.cx + 2, pos.y, NULL);
			LineTo(hDC, pos.x + i * cellsize.cx + 2, pos.y + cellsize.cy * 9);
		}
	}
	for (int i = 0; i < 10; i++)
	{
		MoveToEx(hDC, pos.x, pos.y + i * cellsize.cy, NULL);
		LineTo(hDC, pos.x + cellsize.cx * 9, pos.y + i * cellsize.cy);
		if (i % 3 == 0)
		{
			MoveToEx(hDC, pos.x, pos.y + i * cellsize.cy + 2, NULL);
			LineTo(hDC, pos.x + cellsize.cx * 9, pos.y + i * cellsize.cy + 2);
		}
	}
}
void SudokuViewClass::DrawPosSet(int x, int y)
{
	pos.x = x;
	pos.y = y;
}

void SudokuViewClass::CheckMarkSet(bool ch1)
{
	chk1 = ch1;
}
void SudokuViewClass::DataMaskSet(int x, int y, int num)
{
	Mask[x][y] = num;
}
int SudokuViewClass::DataMaskGet(int x, int y)
{
	return Mask[x][y];
}