#pragma once
#include"SudokuViewClass.h"
class SudokuGenerateClass
{
private:
	struct DATACELL
	{
		int num;
		int mask;
		int rest[9];
		int restcnt;
	};
	DATACELL Board[9][9];
	int HintCount;
public:
	SudokuGenerateClass();
	void CopyData(SudokuViewClass* view);
	void CopyDataTo(SudokuViewClass* view);
	bool Execute();
	void HintCountSet(int cnt);
private:
	void PrepareFunction();
	bool FirstFinction(int lx,int ly);
	void FileOut();
	bool MaskProcess();
	bool MaskProcess2();
};

