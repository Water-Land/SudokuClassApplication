#include "SudokuGenerateClass.h"
#include"SudokuPuzzle.h"
#include<time.h>
#define  _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
SudokuGenerateClass::SudokuGenerateClass()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            ////////////////////////////////////////////////////////////////////////////////////////////    init()        ////////////////////**********************************************************
        }
    }
}
void SudokuGenerateClass::CopyData(SudokuViewClass* view)
{
    bool allsiro = true;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (view->DataMaskGet(i, j) != 0)
            {
                allsiro = false;
            }
        }
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            Board[i][j].num = view->DataGet(i, j);
            if (allsiro == false)
            {
                Board[i][j].mask = view->DataMaskGet(i, j);
            }
            else
            {
                Board[i][j].mask = 1;
            }
        }
    }
}
void SudokuGenerateClass::CopyDataTo(SudokuViewClass* view)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            view->DataSet(i, j, Board[i][j].num);
            view->DataMaskSet(i, j, Board[i][j].mask);
        }
    }
}

bool SudokuGenerateClass::Execute()
{
    bool flag2 = true;
    PrepareFunction();
    flag2 = FirstFinction(0, 0);
    if (flag2 == false) { return false; }
    PrepareFunction();
    flag2 = FirstFinction(1, 0);
    if (flag2 == false) { return false; }
    PrepareFunction();
    flag2 = FirstFinction(0, 1);
    if (flag2 == false) { return false; }
    PrepareFunction();
    flag2 = FirstFinction(2, 0);
    if (flag2 == false) { return false; }
    PrepareFunction();
    flag2 = FirstFinction(0, 2);
    if (flag2 == false) { return false; }
    PrepareFunction();
    flag2 = FirstFinction(1, 1);
    if (flag2 == false) { return false; }
    PrepareFunction();
    flag2 = FirstFinction(2, 1);
    if (flag2 == false) { return false; }
    SudokuPuzzle solver;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            solver.setBoardValue(i, j, Board[i][j].num);
        }
    }
    solver.solve();
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            Board[i][j].num = solver.getBoardValue(i, j);
        }
    }
    bool flag = true;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (Board[i][j].num == 0)
            {
                flag = false;
            }
        }
    }
    if (flag == false)
    {
        return false;
    }
    if (HintCount == -1 && MaskProcess() == false)
    {
        return false;
    }
    if (HintCount != -1 && MaskProcess2() == false)
    {
        return false;
    }
    FileOut();
    return true;
}
void SudokuGenerateClass::HintCountSet(int cnt)
{
    HintCount = cnt;
}
void SudokuGenerateClass::FileOut()
{
    FILE* fp;
    fopen_s(&fp, "testdat.txt", "w");
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            fprintf(fp, "%d", Board[j][i].num);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}
void SudokuGenerateClass::PrepareFunction()// HINT AND HINT_COUNT@SET
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            for (int k = 0; k < 9; k++)
            {
                Board[i][j].rest[k] = 1;
            }
            Board[i][j].restcnt = 0;
        }
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            int m = i / 3;
            int n = j / 3;
            for (int a = 0; a < 3; a++)
            {
                for (int b = 0; b < 3; b++)
                {
                    if (Board[m * 3 + a][n * 3 + b].num != 0)
                    {
                        Board[i][j].rest[Board[m * 3 + a][n * 3 + b].num - 1] = 0;
                    }
                }
            }
        }
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            for (int a = 0; a < 9; a++)
            {
                if (Board[i][a].num != 0)
                {
                    Board[i][j].rest[Board[i][a].num - 1] = 0;
                }
            }
        }
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            for (int a = 0; a < 9; a++)
            {
                if (Board[a][j].num != 0)
                {
                    Board[i][j].rest[Board[a][j].num - 1] = 0;
                }
            }
        }
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            for (int k = 0; k < 9; k++)
            {
                if (Board[i][j].rest[k] != 0)
                {
                    Board[i][j].restcnt++;
                }
            }
        }
    }
}
bool SudokuGenerateClass::FirstFinction(int lx,int ly)
{
    DATACELL* dat[9];
    dat[0] = &Board[0 + lx * 3][0 + ly * 3];
    dat[1] = &Board[1 + lx * 3][0 + ly * 3];
    dat[2] = &Board[2 + lx * 3][0 + ly * 3];
    dat[3] = &Board[0 + lx * 3][1 + ly * 3];
    dat[4] = &Board[1 + lx * 3][1 + ly * 3];
    dat[5] = &Board[2 + lx * 3][1 + ly * 3];
    dat[6] = &Board[0 + lx * 3][2 + ly * 3];
    dat[7] = &Board[1 + lx * 3][2 + ly * 3];
    dat[8] = &Board[2 + lx * 3][2 + ly * 3];
    for (int k = 0; k < 9; k++)
    {
        int minid = 0;
        int min = 10;
        for (int i = 0; i < 9; i++)
        {
            if (min > dat[i]->restcnt && dat[i]->num == 0)
            {
                min = dat[i]->restcnt;
                minid = i;
            }
        }
        if (min == 10) { return true; }
        if (dat[minid]->restcnt == 0) { return true; }
        static int tt = 19;
        static int tt2 = 77;
        srand(time(NULL) * tt + tt * tt * 20 - tt2 / 10);
        tt *= 3; tt -= 2; tt2 *= 77; tt2 -= 36;
        int h = rand() % dat[minid]->restcnt;
        for (int i = 0; i < 9; i++)
        {
            if (h != 0 && dat[minid]->rest[i] != 0)
            {
                h--;
            }
            else if (h == 0 && dat[minid]->rest[i] != 0)
            {
                dat[minid]->num = i + 1;
                for (int g = 0; g < 9; g++)
                {
                    if (dat[g]->rest[i] != 0)
                    {
                        dat[g]->restcnt--;
                    }
                    dat[g]->rest[i] = 0;
                }
                i = 100;
            }
        }
    }
    for (int i = 0; i < 9; i++)
    {
        if (dat[i]->num == 0)
        {
            return false;
        }
    }
    return true;
}
bool SudokuGenerateClass::MaskProcess()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (Board[i][j].mask == 0)
            {
                Board[i][j].num = 0;
            }
        }
    }
    SudokuPuzzle solver1;
    SudokuPuzzle solver2;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            solver1.setBoardValue(i, j, Board[i][j].num);
            solver2.setBoardValue(i, j, Board[i][j].num);
        }
    }
    solver1.NormalModeSet(true);
    solver2.NormalModeSet(false);
    solver1.solve();
    solver2.solve();
    bool flag = true;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (solver1.getBoardValue(i, j) != solver2.getBoardValue(i, j))
            {
                flag = false;
            }
        }
    }
    return flag;
}
bool SudokuGenerateClass::MaskProcess2()
{
    int hintcnt = 81-HintCount;
    for (int i = 0; i < hintcnt; i++)
    {
        static int hw = 25;
        static int hw2 = 15000;
        srand(time(NULL) * hw - hw2);
        hw *= hw2 + 125; hw2 -= 11;
        int tx = rand() % 9;
        int ty = rand() % 9;
        if (Board[tx][ty].num == 0)
        {
            i--;
        }
        Board[tx][ty].num = 0;
    }
    SudokuPuzzle solver1;
    SudokuPuzzle solver2;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            solver1.setBoardValue(i, j, Board[i][j].num);
            solver2.setBoardValue(i, j, Board[i][j].num);
        }
    }
    solver1.NormalModeSet(true);
    solver2.NormalModeSet(false);
    solver1.solve();
    solver2.solve();
    bool flag = true;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (solver1.getBoardValue(i, j) != solver2.getBoardValue(i, j))
            {
                flag = false;
            }
        }
    }
    return flag;
}