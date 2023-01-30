#include"SudokuEditerClass.h"
extern HINSTANCE hInst;
// SudokuClassApplication.cpp : �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//
#include "framework.h"
#include "SudokuClassApplication.h"

#define MAX_LOADSTRING 100

// �O���[�o���ϐ�:
extern HINSTANCE hInst;    
HINSTANCE hInst2;    // ���݂̃C���^�[�t�F�C�X
WCHAR szTitle2[MAX_LOADSTRING];                  // �^�C�g�� �o�[�̃e�L�X�g
WCHAR szWindowClass2[MAX_LOADSTRING];            // ���C�� �E�B���h�E �N���X��
extern void DrawWindowEdit(HDC hdc);
extern void OnClick2(int x, int y);
extern void OnClose2();

// ���̃R�[�h ���W���[���Ɋ܂܂��֐��̐錾��]�����܂�:
ATOM                MyRegisterClass2(HINSTANCE hInstance);
BOOL                InitInstance2(HINSTANCE, int);
LRESULT CALLBACK    WndProc2 (HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

extern HWND hWnd;
HWND hWnd2;

//  �֐�: MyRegisterClass()
//  �ړI: �E�B���h�E �N���X��o�^���܂��B
ATOM MyRegisterClass2(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc2;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SUDOKUCLASSAPPLICATION));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass2;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   �֐�: InitInstance(HINSTANCE, int)
//
//   �ړI: �C���X�^���X �n���h����ۑ����āA���C�� �E�B���h�E���쐬���܂�
//
//   �R�����g:
//
//        ���̊֐��ŁA�O���[�o���ϐ��ŃC���X�^���X �n���h����ۑ����A
//        ���C�� �v���O���� �E�B���h�E���쐬����ѕ\�����܂��B
//
BOOL InitInstance2(HINSTANCE hInstance, int nCmdShow)
{
    hInst2 = hInstance; // �O���[�o���ϐ��ɃC���X�^���X �n���h�����i�[����
    //hWnd2 = CreateWindowW(szWindowClass2, szTitle2, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
    //if (!hWnd2){return FALSE;}
    //ShowWindow(hWnd2, nCmdShow);
   // UpdateWindow(hWnd2);
    return TRUE;
}

LRESULT CALLBACK WndProc2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_LBUTTONDOWN:
        OnClick2(LOWORD(lParam), HIWORD(lParam));
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        DrawWindowEdit(hdc);
        // TODO: HDC ���g�p����`��R�[�h�������ɒǉ����Ă�������...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        OnClose2();
        //PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
void SudokuEditerClass::WindowCreate()
{
    // TODO: �����ɃR�[�h��}�����Ă��������B

    LoadStringW(hInst, IDS_APP_TITLE, szTitle2, MAX_LOADSTRING);
    LoadStringW(hInst, IDC_SUDOKUCLASSAPPLICATION2, szWindowClass2, MAX_LOADSTRING);
    MyRegisterClass2(hInst2);

    // �A�v���P�[�V�����������̎��s:
    //if (!InitInstance2(hInst, 0)) { return; }

	hWnd2=CreateWindowW(szWindowClass2, L"EDITER", WS_VISIBLE | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,240, 240, windowSize.cx, windowSize.cy, NULL, NULL, hInst2, NULL);
}
void SudokuEditerClass::WindowDelete()
{
    DestroyWindow(hWnd2);

}

void SudokuEditerClass::DrawData(HDC hDC)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            RECT cellRect;
            cellRect.left = pos.x + i * largeCellSize.cx;
            cellRect.top = pos.y + j * largeCellSize.cy;
            cellRect.right = pos.x + (i + 1) * largeCellSize.cx;
            cellRect.bottom = pos.y + (j + 1) * largeCellSize.cy;
            if (Mask[i][j] == 1/* && chk1 == true*/)
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
            DrawCellData(hDC, i, j);
        }
    }
    for (int i = 0; i < 10; i++)
    {
        MoveToEx(hDC, pos.x + i * largeCellSize.cx, pos.y, NULL);
        LineTo(hDC, pos.x + i * largeCellSize.cx, pos.y + largeCellSize.cy * 9);
        if (i % 3 == 0)
        {
            MoveToEx(hDC, pos.x + i * largeCellSize.cx + 2, pos.y, NULL);
            LineTo(hDC, pos.x + i * largeCellSize.cx + 2, pos.y + largeCellSize.cy * 9);
        }
    }
    for (int i = 0; i < 10; i++)
    {
        MoveToEx(hDC, pos.x, pos.y + i * largeCellSize.cy, NULL);
        LineTo(hDC, pos.x + largeCellSize.cx * 9, pos.y + i * largeCellSize.cy);
        if (i % 3 == 0)
        {
            MoveToEx(hDC, pos.x, pos.y + i * largeCellSize.cy + 2, NULL);
            LineTo(hDC, pos.x + largeCellSize.cx * 9, pos.y + i * largeCellSize.cy + 2);
        }
    }
}
void SudokuEditerClass::CellSizeSmallSet(int cx, int cy)
{
    smallCellSize.cx = cx;
    smallCellSize.cy = cy;
    largeCellSize.cx = smallCellSize.cx * 3;
    largeCellSize.cy = smallCellSize.cy * 3;
}
void SudokuEditerClass::WindowPosSet(int x, int y)
{
    pos.x = x;
    pos.y = y;
}
void SudokuEditerClass::WindowSizeSet(int cx, int cy)
{
    windowSize.cx = cx;
    windowSize.cy = cy;
}
void SudokuEditerClass::DrawCellData(HDC hDC,int lx, int ly)
{
    POINT p;
    p.x = lx * largeCellSize.cx + pos.x+7;// lx ->1-9
    p.y = ly * largeCellSize.cy + pos.y+5;// ly ->1-9
    if (Board[lx][ly] == 0)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                char buffer[256];
                _itoa_s(i * 3 + j + 1, buffer, 10);
                SetBkMode(hDC, TRANSPARENT);
                TextOutA(hDC, p.x + j * smallCellSize.cx, p.y + i * smallCellSize.cy, buffer, 1);
            }
        }
    }
    else
    {
        HFONT hFont1 = CreateFont(45, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_ROMAN, NULL);
        HFONT hFont2 = (HFONT)SelectObject(hDC, hFont1);
        char buffer[256];
        _itoa_s(Board[lx][ly], buffer, 10);
        SetBkMode(hDC, TRANSPARENT);
        TextOutA(hDC, p.x + 17, p.y + 10, buffer, 1);
        SelectObject(hDC, hFont2);
        DeleteObject(hFont1);
    }
    
}
void SudokuEditerClass::SelectNumberSet(int click_x, int click_y)
{
    int lx = (click_x - pos.x - 7) / largeCellSize.cx;
    int ly = (click_y - pos.y - 5) / largeCellSize.cy;
    int sx = ((click_x - pos.x - 7) % largeCellSize.cx) / smallCellSize.cx;
    int sy = ((click_y - pos.y - 7) % largeCellSize.cy) / smallCellSize.cy;
    char buffer[256];
    if (chk1 == false)
    {
        if (Board[lx][ly] == 0)
        {
            Board[lx][ly] = sx + sy * 3 + 1;
        }
        else
        {
            Board[lx][ly] = 0;
        }
    }
    else
    {
        if (Mask[lx][ly] == 0)
        {
            Mask[lx][ly] = 1;
        }
        else
        {
            Mask[lx][ly] = 0;
        }
    }
 
    InvalidateRect(hWnd2, NULL, true);
}
void SudokuEditerClass::CopyData(SudokuViewClass* view)
{

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            Board[i][j] = view->DataGet(i, j);
            Mask[i][j] = view->DataMaskGet(i, j);
        }
    }
}
void SudokuEditerClass::CopyDataTo(SudokuViewClass* view)
{

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            view->DataSet(i, j, Board[i][j]);
            view->DataMaskSet(i, j, Mask[i][j]);
        }
    }
}

void SudokuEditerClass::CheckMarkSet(bool ch1)
{
    chk1 = ch1;
}