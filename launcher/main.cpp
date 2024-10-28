#include <iostream>
#include <tchar.h>
#include <string>

#include <windows.h>
#include <windowsx.h>

#include "config.h"


const char MAIN_CLS_NAME[] = "SuperTetris";

HINSTANCE hinst;

HWND MAIN_WND;

HBITMAP MAIN_BG;
HBITMAP START_BUTTON;
HBITMAP HELP_BUTTON;
HBITMAP EXIT_BUTTON;


const int EDIT_ST_X = 191;
const int EDIT_ST_Y = 34;


void LoadFrameImages(){
    MAIN_BG = (HBITMAP) LoadImage(
        NULL, _T("resource/MAIN_WND/MAIN.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
    );

    START_BUTTON = (HBITMAP) LoadImage(
        NULL, _T("resource/MAIN_WND/START_GAME.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
    );

    HELP_BUTTON = (HBITMAP) LoadImage(
        NULL, _T("resource/MAIN_WND/HELP.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
    );

    EXIT_BUTTON = (HBITMAP) LoadImage(
        NULL, _T("resource/MAIN_WND/EXIT.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
    );
}

void ReleaseFrameImages(){
    DeleteObject(MAIN_BG);
    DeleteObject(START_BUTTON);
    DeleteObject(HELP_BUTTON);
    DeleteObject(EXIT_BUTTON);
}

BOOL InitApplication(WNDPROC proc, const char* name, HBITMAP background, HINSTANCE hInstance);

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

LRESULT CALLBACK WinProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
);


int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow
){
    MSG msg;
    LoadFrameImages();
    if (!InitApplication(WinProc, MAIN_CLS_NAME, MAIN_BG, hInstance)){
        MessageBox(
            NULL,
            _T("Failed to register class"),
            _T("Window State"),
            0
        );
        return -1;
    }

    if (!InitInstance(hInstance, nCmdShow)){
        MessageBox(
            NULL,
            _T("Failed to create window"),
            _T("State of App"),
            0
        );
        return -1;
    }
    while (GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    ReleaseFrameImages();
    UnregisterClass(MAIN_CLS_NAME, hinst);
    return msg.wParam;
}

BOOL InitApplication(WNDPROC proc, const char* name, HBITMAP background, HINSTANCE hInstance){
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_BYTEALIGNWINDOW;
    wcex.lpfnWndProc    = proc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = (HICON)LoadImage(
        NULL,
        _T("resource/tetris_icon_v2.ico"),
        IMAGE_ICON,
        LR_DEFAULTSIZE,
        LR_DEFAULTSIZE,
        LR_LOADFROMFILE
    );
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreatePatternBrush(background);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = name;
    wcex.hIconSm        = (HICON)LoadImage(
        NULL,
        _T("resource/tetris_icon_v2.ico"),
        IMAGE_ICON,
        LR_DEFAULTSIZE,
        LR_DEFAULTSIZE,
        LR_LOADFROMFILE
    );
    
    return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow){

    hinst = hInstance;

    HWND MAIN_WND = CreateWindow(
        _T("SuperTetris"),
        NULL,
        WS_POPUP,
        CW_USEDEFAULT, CW_USEDEFAULT,
        500, 400,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!MAIN_WND){
        return FALSE;
    }
    ShowWindow(MAIN_WND, nCmdShow);
    UpdateWindow(MAIN_WND);
    return TRUE;
}


LRESULT CALLBACK WinProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam)
{

    switch (message)
    {
        case WM_CREATE: {
            RECT rc;
            GetWindowRect(hWnd, &rc);
            HWND start_button = CreateWindow(
                _T("BUTTON"),
                0,
                WS_VISIBLE | WS_CHILD | BS_BITMAP,
                (abs(rc.right - rc.left) / 2) - 75, 25, 150, 100,
                hWnd,
                reinterpret_cast<HMENU>(3),
                NULL,
                NULL
            );
            SendMessage(start_button, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) START_BUTTON);

            HWND help = CreateWindow(
                _T("BUTTON"),
                0,
                WS_VISIBLE | WS_CHILD | BS_BITMAP,
                (abs(rc.right - rc.left) / 2) - 75, 150, 150, 100,
                hWnd,
                reinterpret_cast<HMENU>(2),
                NULL,
                NULL
            );
            SendMessage(help, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) HELP_BUTTON);

            HWND exit = CreateWindow(
                _T("BUTTON"),
                0,
                WS_VISIBLE | WS_CHILD | BS_BITMAP,
                (abs(rc.right - rc.left) / 2) - 75, 275, 150, 100,
                hWnd,
                reinterpret_cast<HMENU>(1),
                NULL,
                NULL
            );
            SendMessage(exit, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) EXIT_BUTTON);
            break;
        }
        case WM_COMMAND:{
            switch (LOWORD(wParam))
            {
                case 1:
                    DestroyWindow(hWnd);
                    break;
                case 2:{
                    HANDLE other_app;
                    if (other_app = OpenSemaphore(0, false, ANOTHER_APP_SEM); other_app){
                        CloseHandle(other_app);
                        MessageBox(NULL, "APP is always running", "ERROR", MB_OK);
                        return 1;
                    }

                    STARTUPINFO si;
                    PROCESS_INFORMATION pi;
                    ZeroMemory(&si, sizeof(si));
                    si.cb = sizeof(si);
                    ZeroMemory(&pi, sizeof(pi));

                    if (CreateProcess(
                        _T("Settings/settings.exe"), nullptr,
                        nullptr, nullptr, true, 0, nullptr, nullptr,
                        &si, &pi
                    )){ 
                        const HANDLE handles[] = {pi.hProcess};
                        MsgWaitForMultipleObjectsEx(1, handles, INFINITE, 0, 0);
                        CloseHandle(pi.hProcess);
                        CloseHandle(pi.hThread);
                    }

                    break;
                }

                case 3:{
                    HANDLE other_app;
                    if (other_app = OpenSemaphore(0, false, ANOTHER_APP_SEM); other_app){
                        CloseHandle(other_app);
                        MessageBox(NULL, "APP is always running", "ERROR", MB_OK);
                        return 1;
                    }
                    STARTUPINFO si;
                    PROCESS_INFORMATION pi;
                    ZeroMemory(&si, sizeof(si));
                    si.cb = sizeof(si);
                    ZeroMemory(&pi, sizeof(pi));

                    if (CreateProcess(
                        _T("SuperTetris/supertetris.exe"), nullptr,
                        nullptr, nullptr, false, 0, nullptr, nullptr,
                        &si, &pi
                    )){
                        const HANDLE handles[] = {pi.hProcess};
                        MsgWaitForMultipleObjects(2, handles, false, INFINITE, 0);
                        CloseHandle(pi.hProcess);
                        CloseHandle(pi.hThread);
                    }

                }
            }
            break;
        }
        case WM_NCHITTEST: {
            LRESULT hit = DefWindowProc(hWnd, message, wParam, lParam);
            if (hit == HTCLIENT){
                hit = HTCAPTION;
            }
            return hit;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}
