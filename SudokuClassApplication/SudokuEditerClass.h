#pragma once
#include<Windows.h>
#include"SudokuViewClass.h"
#include "framework.h"
#include "SudokuClassApplication.h"
class SudokuEditerClass
{
private:
	HWND hWnd;
	SIZE smallCellSize;
	SIZE largeCellSize;
	POINT pos;
	SIZE windowSize;
	int SelectNumber;
	int Board[9][9];
	int Mask[9][9];
	bool chk1;
public:
	void WindowCreate();
	void WindowDelete();
	void DrawData(HDC hDC);
	void CellSizeSmallSet(int cx, int cy);
	void WindowPosSet(int x, int y);
	void WindowSizeSet(int cx, int cy);
	void DrawCellData(HDC hDC,int lx, int ly);
	void SelectNumberSet(int click_x, int click_y);
	void CopyData(SudokuViewClass* view);
	void CopyDataTo(SudokuViewClass* view);
	void CheckMarkSet(bool ch1);
};