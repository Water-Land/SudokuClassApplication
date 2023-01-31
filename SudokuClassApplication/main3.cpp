#include"SudokuPuzzle.h"
#include "framework.h"
#include "SudokuClassApplication.h"
#include"SudokuViewClass.h"
#include"SudokuEditerClass.h"
#include "SudokuGenerateClass.h"
#define _CRT_SECURE_NO_WARNINGS
#define _OPEN_SYS_ITOA_EXT
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <tchar.h>
#include<Commdlg.h>
#pragma comment(lib, "Comdlg32.lib")
SudokuPuzzle sudoku;
SudokuViewClass view;
SudokuEditerClass edit;
SudokuGenerateClass gen;
HINSTANCE hInst;
HWND hWnd;
extern INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
bool filereadis;
int HintCount = -1;

void testgithubcommand()
{
	int test_a = 0;
}
void testgithubcommand2()
{
	int a2 = 0;
	int a3 = 0;
	int a4 = 0;
}

void FileRead(char* filename)
{
	FILE* fp;
	fopen_s(&fp, filename, "r");
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int num = 0;
			fscanf_s(fp, "%c", &num);
			view.DataSet(j, i, num - '0');
		}
		int num2 = 0;
		fscanf_s(fp, "%c", &num2);
	}
	fclose(fp);
}
void FileReadMask(char* filename)
{
	FILE* fp;
	fopen_s(&fp, filename, "r");
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int num = 0;
			fscanf_s(fp, "%c", &num);
			view.DataMaskSet(j, i, num - '0');
		}
		int num2 = 0;
		fscanf_s(fp, "%c", &num2);
	}
	fclose(fp);
	testgithubcommand();
}
void CopyData()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			sudoku.setBoardValue(i, j, view.DataGet(j, i));
		}
	}

}
void FileReadCommand()
{
	OPENFILENAMEA ofn;       // common dialog box structure
	char szFile[260] = { 0 };       // if using TCHAR macros

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileNameA(&ofn) == TRUE)
	{
		FileRead((char*)ofn.lpstrFile);
		CopyData();
	}
}
void FileReadCommandMask()
{
	OPENFILENAMEA ofn;       // common dialog box structure
	char szFile[260] = { 0 };       // if using TCHAR macros

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileNameA(&ofn) == TRUE)
	{
		FileReadMask((char*)ofn.lpstrFile);
		CopyData();
	}
}
void Init()
{
	filereadis = false;
	view.DrawPosSet(30, 30);
}
void Init2()
{

}

void DrawWindow(HDC hdc)
{
	view.DataDraw(hdc);
}
void DrawWindowEdit(HDC hdc)
{
	edit.DrawData(hdc);
}
void OnClick(int x, int y)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			sudoku.setBoardValue(i, j, view.DataGet(j, i));
		}
	}
	SetWindowTextW(hWnd, L"解答を始めます。");
	bool flag = sudoku.solve();
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			view.DataSet(j, i, sudoku.getBoardValue(i, j));
		}
	}
	InvalidateRect(hWnd, NULL, true);
	if (flag == true)
	{
		MessageBoxA(NULL, "解けました。", "CHECKED", MB_OK);
	}
	if (flag == false)
	{
		MessageBoxA(NULL, "解けませんでした。", "CHECKED", MB_OK);
	}
	SetWindowTextW(hWnd, L"解答を終わりました。");

}

void EditWindowCreate(bool chk1)
{
	edit.WindowSizeSet(30 * 2 + 24 * 3 * 9 + 15, 30 * 2 + 24 * 3 * 9 + 90);
	edit.WindowPosSet(30, 30);
	edit.CellSizeSmallSet(24, 24);
	edit.CopyData(&view);
	edit.CheckMarkSet(chk1);
	edit.WindowCreate();
}
void WindowDestroy()
{
	//edit.WindowDelete();

}
void OnClick2(int x, int y)
{
	edit.SelectNumberSet(x, y);
}
void OnClose2()
{
	edit.CopyDataTo(&view);
	InvalidateRect(hWnd, NULL, true);
}
void OnCheck()//複数解チェック
{
	SudokuPuzzle sol1;
	SudokuPuzzle sol2;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			sol1.setBoardValue(i, j, view.DataGet(j, i));
			sol2.setBoardValue(i, j, view.DataGet(j, i));
		}
	}
	sol1.NormalModeSet(true);
	sol2.NormalModeSet(false);
	sol1.solve();
	sol2.solve();
	bool chk = true;
	bool tchk = true;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sol1.getBoardValue(i, j) == 0 || sol2.getBoardValue(i, j) == 0)
			{
				tchk = false;
			}
			if (sol1.getBoardValue(i, j) != sol2.getBoardValue(i, j))
			{
				chk = false;
			}
		}
	}
	if (chk == false)
	{
		MessageBoxA(NULL, "重複しています。", "CHECKED", MB_OK);
	}
	if (chk == true)
	{
		if (tchk == true)
		{
			MessageBoxA(NULL, "重複していません。", "CHECKED", MB_OK);
		}
		if (tchk == false)
		{
			MessageBoxA(NULL, "解けませんでした。", "CHECKED", MB_OK);
		}


	}

}
void MaskDataFlag(bool ch1)
{
	view.CheckMarkSet(ch1);
	InvalidateRect(hWnd, NULL, true);
}
void ExecuteMakeData()
{
	bool retflag = false;
	MessageBoxA(NULL, "EXECUTE", "", MB_OK);
	while (retflag == false)
	{
		gen.CopyData(&view);
		gen.HintCountSet(HintCount);
		retflag = gen.Execute();
	}
	MessageBoxA(NULL, "DONE", "", MB_OK);
}