#include <file_manager.h>

#include <iostream>
#include <string>

#include "windows.h"
#include "windowsx.h"

#include "config.h"
#include "common.h"
#include "keyboard_translater.h"


#define KEY_TIMER 2001

bool IS_KEY_SHOWN = true;

const char SETTING_CLS[] = "settings";

using KBR = KeyboardButtonRECT;

KBR BUTTONS_RECT;
int USED_RECT = KBR::LAST;
bool WAIT_PRESS = false;

SettingsManager SETTINGS_MANAGER;
KeyboardTranslater TRANSLATER;

int VK_FOR_KEYBOARD[] = {
    SETTINGS_MANAGER.left, SETTINGS_MANAGER.right,
    SETTINGS_MANAGER.v_left, SETTINGS_MANAGER.v_right,
    SETTINGS_MANAGER.down, SETTINGS_MANAGER.pause,
    SETTINGS_MANAGER.esc
};

HANDLE RUNNING_APP;
HINSTANCE HINST;

HBITMAP CLOSE_IMAGE;
HBITMAP SETTINGS_BG;

bool IS_DRAG_SETTING = false;
POINT LAST_POS_CURSOR;

void LoadImages(){
    SETTINGS_BG = (HBITMAP) LoadImage(
        0, "resource/MAIN_WND/SETTINGS.bmp", IMAGE_BITMAP,
        0, 0, LR_LOADFROMFILE
    );

    CLOSE_IMAGE = (HBITMAP) LoadImage(
        0, "resource/MAIN_WND/CLOSE.bmp", IMAGE_BITMAP,
        0, 0, LR_LOADFROMFILE
    );
}

void ReleaseImages(){
    DeleteObject(SETTINGS_BG);
    DeleteObject(CLOSE_IMAGE);
}

LRESULT CALLBACK WinProc(
    HWND hWnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
);

int CALLBACK WinMain(
    HINSTANCE hInst,
    HINSTANCE prevHinst,
    LPSTR lCmd,
    int nCmdShow
){
    RUNNING_APP = CreateSemaphore(0, 0, 1, ANOTHER_APP_SEM);
    if (GetLastError() == ERROR_ALREADY_EXISTS){
        MessageBox(NULL, "Tetris is running", "Error", MB_OK);
        return 0;
    }

    LoadImages();
    WNDCLASSEX wndx{sizeof(WNDCLASSEX)};

    wndx.cbClsExtra = 0;
    wndx.cbWndExtra = 0;
    wndx.hbrBackground = CreatePatternBrush(SETTINGS_BG);
    wndx.hIcon = (HICON)LoadImage(
        NULL,
        "resource/tetris_icon_v2.ico",
        IMAGE_ICON,
        LR_DEFAULTSIZE,
        LR_DEFAULTSIZE,
        LR_LOADFROMFILE
    );
    wndx.hIconSm        = (HICON)LoadImage(
        NULL,
        "resource/tetris_icon_v2.ico",
        IMAGE_ICON,
        LR_DEFAULTSIZE,
        LR_DEFAULTSIZE,
        LR_LOADFROMFILE
    );
    wndx.lpfnWndProc = WinProc;
    wndx.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndx.lpszClassName = SETTING_CLS;
    wndx.style = CS_DBLCLKS;

    if(!RegisterClassEx(&wndx)){
        MessageBox(
            NULL,
            "Failed to register class",
            "Window State",
            0
        );
        return -1;
    }
    HINST = hInst;

    HWND MAIN_WND = CreateWindow(
        wndx.lpszClassName, 0, WS_POPUP | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 390, 381,
        NULL, NULL, hInst, NULL
    );

    if (!MAIN_WND){
        MessageBox(
            NULL,
            "Fail to create window",
            "Wnd state",
            0
        );
        return -1;
    }

    ShowWindow(MAIN_WND, nCmdShow);
    UpdateWindow(MAIN_WND);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnregisterClass(SETTING_CLS, HINST);
    DeleteObject(MAIN_WND);
    ReleaseImages();
    CloseHandle(RUNNING_APP);
    return msg.wParam;
}

void DrawTextInRect(HDC hdc, const std::string& text, RECT* rec){
    DrawTextA(hdc, text.c_str(), text.size(), rec, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
}

bool CheckSameKey(int value){
    for (int i = 0; i < KBR::LAST; i++){
        if (value == VK_FOR_KEYBOARD[i]){
            return true;
        }
    }
    return false;
}

void SetKeyForControls(SettingsManager& manager, int idx, int value){
    switch (idx){
        case KBR::LEFT: {
            manager.left = value;
            break;
        }
        case KBR::RIGHT: {
            manager.right = value;
            break;
        }
        case KBR::V_LEFT: {
            manager.v_left = value;
            break;
        }
        case KBR::V_RIGHT: {
            manager.v_right = value;
            break;
        }
        case KBR::DOWN: {
            manager.down = value;
            break;
        }
        case KBR::ESC: {
            manager.esc = value;
            break;
        }
    }
}

const std::string& ConvertVkToString(int vk){
    return TRANSLATER.TranslateVkToString(vk);
}

void InstallKey(const KeyboardTranslater& translater, SettingsManager& manager, int idx, int val){
    if (translater.TranslateVkToString(val) != ""){
        manager.LoadSettings();
        if (!CheckSameKey(val)){
            VK_FOR_KEYBOARD[USED_RECT] = val;
            SetKeyForControls(manager, USED_RECT, val);
            SETTINGS_MANAGER.WriteToFile();
        } else {
            MessageBox(NULL, "Usage of same key is restricted", "Try Another", MB_OK);
        }
    } else {
        MessageBox(NULL, "Can't bind a key. Try another", "WRONG KEY", MB_OK);
    }
    USED_RECT = KBR::LAST;
    WAIT_PRESS = false;
    IS_KEY_SHOWN = true;
}

LRESULT CALLBACK WinProc(
    HWND hWnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
){
    HWND close_button;
    switch (msg){
        case WM_PAINT: {
            SETTINGS_MANAGER.LoadSettings();
            PAINTSTRUCT rc;
            HDC hdc = BeginPaint(hWnd, &rc);
            SetBkMode(hdc, TRANSPARENT);
            SetTextColor(hdc, 0x00FFFFFF);
            if (WAIT_PRESS){
                if (IS_KEY_SHOWN){
                    DrawTextInRect(hdc, "Press Any", BUTTONS_RECT[USED_RECT]);
                    IS_KEY_SHOWN = false;
                } else {
                    IS_KEY_SHOWN = true;
                }
            } else {
                for (int i = 0; i < KBR::LAST; i++){
                    DrawTextInRect(hdc, ConvertVkToString(VK_FOR_KEYBOARD[i]), BUTTONS_RECT[i]);
                }
            }
            SetTextColor(hdc, 0);
            SetBkMode(hdc, OPAQUE);
            EndPaint(hWnd, &rc);
            break;
        }
        case WM_LBUTTONDBLCLK: {
            if (!WAIT_PRESS){
                POINT curs_pos{GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
                for (int i = 0; i < KBR::LAST; i++){
                    if (PtInRect(BUTTONS_RECT[i], curs_pos)){
                        USED_RECT = i;
                        WAIT_PRESS = true;
                        SetTimer(hWnd, KEY_TIMER, 1500, NULL);
                        InvalidateRect(hWnd, BUTTONS_RECT[USED_RECT], true);
                    }
                }
            }
            break;
        }
        case WM_CREATE:{
            close_button = CreateWindow(
                "BUTTON", NULL, WS_CHILD | BS_BITMAP | WS_VISIBLE | BS_FLAT,
                    354, 3, 25, 25, hWnd, reinterpret_cast<HMENU>(1), NULL, NULL
            );
            SendMessage(close_button, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) CLOSE_IMAGE);
            break;
        }
        case WM_RBUTTONDOWN: {
            if (WAIT_PRESS){
                InstallKey(TRANSLATER, SETTINGS_MANAGER, USED_RECT, wParam);
                KillTimer(hWnd, KEY_TIMER);
                InvalidateRect(hWnd, NULL, true);
            }
            break;
        }
        case WM_LBUTTONDOWN: {
            if (WAIT_PRESS){
                InstallKey(TRANSLATER, SETTINGS_MANAGER, USED_RECT, wParam);
                KillTimer(hWnd, KEY_TIMER);
                InvalidateRect(hWnd, NULL, true);
            }

            LAST_POS_CURSOR.x = GET_X_LPARAM(lParam);
            LAST_POS_CURSOR.y = GET_Y_LPARAM(lParam);

            RECT r{0, 0, 390, 50};

            if (PtInRect(&r, LAST_POS_CURSOR)){
                SetCapture(hWnd);
                IS_DRAG_SETTING = true;
            }
            break;
        }
        case WM_MOUSEMOVE: {
            if (IS_DRAG_SETTING){
                RECT rec;
                POINT pos;

                GetCursorPos(&pos);
                GetWindowRect(hWnd, &rec);
                MoveWindow(
                    hWnd, pos.x - LAST_POS_CURSOR.x, pos.y - LAST_POS_CURSOR.y,
                    rec.right - rec.left, rec.bottom - rec.top, false
                );
            }
            break;
        }
        case WM_LBUTTONUP: {
            if (IS_DRAG_SETTING){
                IS_DRAG_SETTING = false;
                ReleaseCapture();
            }
            break;
        }
        case WM_KEYDOWN: {
            if (WAIT_PRESS){
                InstallKey(TRANSLATER, SETTINGS_MANAGER, USED_RECT, wParam);
                KillTimer(hWnd, KEY_TIMER);
                InvalidateRect(hWnd, BUTTONS_RECT[USED_RECT], true);
            }
            break;
        }
        case WM_TIMER : {
            InvalidateRect(hWnd, BUTTONS_RECT[USED_RECT], true);
            break;
        }
        case WM_COMMAND: {
            switch (LOWORD(wParam)){
                case 1: {
                    if (WAIT_PRESS){
                        KillTimer(hWnd, KEY_TIMER);
                    }
                    DestroyWindow(close_button);
                    PostQuitMessage(0);
                    return 0;
                }
            }
            break;
        }
        case WM_CLOSE:{
            DestroyWindow(hWnd);
            break;
        }
        case WM_DESTROY:{
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
