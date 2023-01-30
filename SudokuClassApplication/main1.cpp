// SudokuClassApplication.cpp : アプリケーションのエントリ ポイントを定義します。
//
#include "SudokuPuzzle.h"
#include "framework.h"
#include "SudokuClassApplication.h"

#define MAX_LOADSTRING 100

// グローバル変数:
extern HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

extern SudokuPuzzle sudoku;
extern HWND hWnd;
extern void Init();
extern void Init2();
extern void DrawWindow(HDC hdc);
extern void OnClick(int x, int y);
extern void OnCheck();
extern bool filereadis;
extern void FileReadCommand();
extern void FileReadCommandMask();
extern void EditWindowCreate(bool chk1);
extern void WindowDestroy();
extern void MaskDataFlag(bool ch1);
extern void ExecuteMakeData();
extern int HintCount;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPWSTR    lpCmdLine,_In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ここにコードを挿入してください。
    Init();
    // グローバル文字列を初期化する
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SUDOKUCLASSAPPLICATION, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // アプリケーション初期化の実行:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
    Init2();

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SUDOKUCLASSAPPLICATION));

    MSG msg;

    // メイン メッセージ ループ:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SUDOKUCLASSAPPLICATION));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SUDOKUCLASSAPPLICATION);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // グローバル変数にインスタンス ハンドルを格納する

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 650, 720,  nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND  - アプリケーション メニューの処理
//  WM_PAINT    - メイン ウィンドウを描画する
//  WM_DESTROY  - 中止メッセージを表示して戻る
//
//


// バージョン情報ボックスのメッセージ ハンドラーです。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

bool chk1 = false;
bool chk2 = false;
void chk2allcheckout(HMENU menu)
{
    CheckMenuItem(menu, 32778, MF_UNCHECKED);
    CheckMenuItem(menu, 32779, MF_UNCHECKED);
    CheckMenuItem(menu, 32780, MF_UNCHECKED);
    CheckMenuItem(menu, 32781, MF_UNCHECKED);
    CheckMenuItem(menu, 32782, MF_UNCHECKED);
    CheckMenuItem(menu, 32783, MF_UNCHECKED);
    CheckMenuItem(menu, 32784, MF_UNCHECKED);
    CheckMenuItem(menu, 32785, MF_UNCHECKED);
    CheckMenuItem(menu, 32786, MF_UNCHECKED);
    CheckMenuItem(menu, 32787, MF_UNCHECKED);
    CheckMenuItem(menu, 32788, MF_UNCHECKED);
    CheckMenuItem(menu, 32775, MF_UNCHECKED);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        HMENU menu;
        MENUITEMINFOA menuinfo;
        bool menuret;
        menu = GetMenu(hWnd);
        // 選択されたメニューの解析:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case 32771://ファイル読み込み
            FileReadCommand();
            InvalidateRect(hWnd, NULL, true);
            //MessageBoxA(NULL, "", "", MB_OK);
            break;
        case 32789:
            FileReadCommandMask();
            InvalidateRect(hWnd, NULL, true);
            break;
        case 32772://マニュアル:
            EditWindowCreate(chk1);
            break;
        case 32773:
            OnClick(LOWORD(lParam), HIWORD(lParam));
            break;
        case 32774://複数解チェック
            OnCheck();
            break;
        case 32775:
            HintCount = -1;
            chk2allcheckout(menu);
            if (chk1 ==true)
            {
                chk1 = false;
                CheckMenuItem(menu, 32775, MF_UNCHECKED);
            }
            else if (chk1==false)
            {
                chk1 = true;
                CheckMenuItem(menu, 32775, MF_CHECKED);
            }
            MaskDataFlag(chk1);
            break;
        case 32777:
            ExecuteMakeData();
            break;
        case 32778:
            HintCount = 20;
            chk2allcheckout(menu);
            CheckMenuItem(menu, 32778, MF_CHECKED);
            break;
        case 32779:
            HintCount = 21;
            chk2allcheckout(menu);
            CheckMenuItem(menu, 32779, MF_CHECKED);
            break;
        case 32780:
            HintCount = 22;
            chk2allcheckout(menu);
            CheckMenuItem(menu, 32780, MF_CHECKED);
            break;
        case 32781:
            HintCount = 23;
            chk2allcheckout(menu);
            CheckMenuItem(menu, 32781, MF_CHECKED);
            break;
        case 32782:
            HintCount = 24;
            chk2allcheckout(menu);
            CheckMenuItem(menu, 32782, MF_CHECKED);
            break;
        case 32783:
            HintCount = 25;
            chk2allcheckout(menu);
            CheckMenuItem(menu, 32783, MF_CHECKED);
            break;
        case 32784:
            HintCount = 26;
            chk2allcheckout(menu);
            CheckMenuItem(menu, 32784, MF_CHECKED);
            break;
        case 32785:
            HintCount = 27;
            chk2allcheckout(menu);
            CheckMenuItem(menu, 32785, MF_CHECKED);
            break;
        case 32786:
            HintCount = 28;
            chk2allcheckout(menu);
            CheckMenuItem(menu, 32786, MF_CHECKED);
            break;
        case 32787:
            HintCount = 29;
            chk2allcheckout(menu);
            CheckMenuItem(menu, 32787, MF_CHECKED);
            break;
        case 32788:
            HintCount = 30;
            chk2allcheckout(menu);
            CheckMenuItem(menu, 32788, MF_CHECKED);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_CREATE:
        HMENU menu;
        menu = GetMenu(hWnd);
        //CheckMenuItem(menu, 32784, MF_CHECKED);
        break;
    case WM_LBUTTONDOWN:
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        DrawWindow(hdc);
        // TODO: HDC を使用する描画コードをここに追加してください...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        WindowDestroy();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}