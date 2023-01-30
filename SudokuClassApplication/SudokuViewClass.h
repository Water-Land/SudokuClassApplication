#pragma once
#include<Windows.h>
class SudokuViewClass
{
private:
	int Board[9][9];
	int Mask[9][9];
	SIZE cellsize;
	SIZE cellpaddingsize;
	POINT pos;
	bool chk1;
public:
	SudokuViewClass();
	~SudokuViewClass();
	void DataSet(int x, int y, int num);
	int DataGet(int x, int y);
	void DataMaskSet(int x, int y, int num);
	int DataMaskGet(int x, int y);
	void DataDraw(HDC hDC);
	void DrawPosSet(int x, int y);
	void CheckMarkSet(bool ch1);
};