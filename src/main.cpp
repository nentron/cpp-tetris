#include "commands.hpp"
#include "supertetris.h"

#include <tchar.h>
#include <string>
#include <sstream>
#include <windows.h>
#include <windowsx.h>

#include "config.h"
#include "file_manager.h"
#include "keyboard_translater.h"


#define GAME_TIMER 1324
#define PAUSE_TIMER 1876

SuperTetris tetris;
KeyboardTranslater TRANSLATER;
const SettingsManager CONTROLS_MANAGER;


const int TABLE_X = 99;
const int TABLE_Y = 32;
const int SHAPE_Y = 32;
const int SHAPE_X = 326;

enum class GameStage{
    PAUSE,
    GAME,
    END
};

HANDLE RUNNING_APP;

HINSTANCE hinst;

HWND MAIN_WND;
HWND table;
HWND prev_shape;
HBITMAP PAUSE_IMAGE;
HBITMAP SQ;
HBITMAP next_shape;

GameStage STAGE;
bool HELP_IMAGE = true;
bool RESET_SHAPE = true;

bool IS_MOVING_FRAME = false;
POINT PREVIOUS_CURS_POS;

static int time_step = 3000;

LRESULT CALLBACK WinProc(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
);

int WINAPI WinMain(
    HINSTANCE hInst,
    HINSTANCE prevHInst,
    LPSTR lpCmdLine,
    int cmdShow
){
    RUNNING_APP = CreateSemaphore(NULL, 0, 1, ANOTHER_APP_SEM);
    if (GetLastError() == ERROR_ALREADY_EXISTS){
        MessageBox(NULL, "Tetris is running", "Error", MB_OK);
        return 0;
    }

    WNDCLASSEX wcex{sizeof(WNDCLASSEX)};

    wcex.hbrBackground = CreatePatternBrush(
        (HBITMAP) LoadImage(
            nullptr, _T("resource\\frame_2.bmp"),
            IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
        )
    );
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hCursor = (HCURSOR) LoadCursor(hInst, IDC_ARROW);
    wcex.hIcon = (HICON) LoadImage(
        NULL, _T("resource/ST.ico"),
        IMAGE_ICON, 0, 0,
        LR_LOADFROMFILE
    );
    wcex.hIconSm = (HICON) LoadImage(
        NULL, _T("resource/ST.ico"),
        IMAGE_ICON, 0, 0,
        LR_LOADFROMFILE
    );
    wcex.hInstance = hInst;
    wcex.lpfnWndProc = WinProc;
    wcex.lpszClassName = _T("tetris");

    if (!RegisterClassEx(&wcex)){
        MessageBox(
            NULL, _T("unable register class"),
            0, MB_OK
        );
        return -1;
    }

    MAIN_WND = CreateWindowEx(
        0, "tetris", nullptr,
        WS_POPUP, CW_USEDEFAULT,
        CW_USEDEFAULT, 400,
        700, nullptr,
        nullptr, hInst, 0
    );

    if (!MAIN_WND){
        MessageBox(
            NULL, _T("unable to create window"),
            0, MB_OK
        );
    }

    hinst = hInst;
    ShowWindow(MAIN_WND, cmdShow);
    UpdateWindow(MAIN_WND);
    SetTimer(
        MAIN_WND, GAME_TIMER, time_step, NULL
    );

    MSG message;
    while (GetMessage(&message, NULL, 0 , 0)){
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
    CloseHandle(RUNNING_APP);
    UnregisterClass(_T("tetris"), hInst);
    return message.wParam;
}


HBITMAP LoadNextShape(){
    using namespace std::literals;
    using Shape = ShapesShifts::Shape;

    std::string path = "resource/PrevShapeImage/";

    switch (tetris.GetNextShape()){
        case Shape::O:{
            path += "O.bmp";
            break;
        };
        case Shape::I: {
            path += "I.bmp";
            break;
        }

        case Shape::J: {
            path += "J.bmp";
            break;
        }
        case Shape::L: {
            path += "L.bmp";
            break;
        }

        case Shape::S: {
            path += "S.bmp";
            break;
        }
        case Shape::T: {
            path += "T.bmp";
            break;
        }
        default:
            path += "Z.bmp";
            break;
    }

    return (HBITMAP) LoadImage(
        nullptr, path.c_str(), IMAGE_BITMAP, 49, 49, LR_LOADFROMFILE
    );
}

void SetNextShape(){
    next_shape = LoadNextShape();
    SendMessage(prev_shape, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) next_shape);
}

void DrawEndGameFrame(){
    HBITMAP endgame = (HBITMAP) LoadImage(
        nullptr, _T("resource/ENDGAME.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
    );

    SendMessage(table, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) endgame);
    DeleteObject(endgame);
}

void DrawEndGameResult(HDC& hdc, PAINTSTRUCT& ps){
    std::string text = "Score: ";
    const auto result = tetris.GetResult();
    text += std::to_string(result.score_);
    text += "\nRemoved lines: " + std::to_string(result.rm_lines);

    HFONT fOrigin, fCreated;
    fCreated = CreateFont(
        25, 0, 0, 0, FW_NORMAL,
        true, false, false, DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        NONANTIALIASED_QUALITY, FIXED_PITCH | FF_ROMAN,
        NULL
    );
    fOrigin  = (HFONT) SelectObject(hdc, fCreated);

    RECT rec;
    SetRect(&rec, TABLE_X, 150, TABLE_X, 250);
    SetTextColor(hdc, RGB(128, 128, 128));
    SetBkMode(hdc, TRANSPARENT);
    DrawText(hdc, text.c_str(), text.length(), &rec, DT_CENTER | DT_NOCLIP);

    SelectObject(hdc, fOrigin);
    DeleteObject(fOrigin);
    DeleteObject(fCreated);
}

void DrawGame(HDC& hdc, PAINTSTRUCT& ps){
    if (RESET_SHAPE){
        DeleteObject(next_shape);
        SetNextShape();
        RESET_SHAPE = false;
    }

    FillRect(hdc, &ps.rcPaint, (HBRUSH) WHITE_BRUSH);
    HBRUSH hBrush = CreatePatternBrush(SQ);
    for (int i = 4; i < MAX_ROWS; i++){
        for (int j = 0; j < MAX_COLS; j++){
            if (tetris.GetBoard()[i][j] != Flag::EMPTY){
                RECT rec;
                rec.left = ps.rcPaint.left + 20 * j;
                rec.top = ps.rcPaint.top + 20 * (i - 4);
                rec.right = rec.left + 20;
                rec.bottom = rec.top + 20;
                FillRect(hdc, &rec, hBrush);
            }
        }
    }
    DeleteObject(hBrush);
}

void ProcessDown(){
    if (tetris.Down()){
        if (tetris.CheckGameEnd()){
            KillTimer(MAIN_WND, GAME_TIMER);
            DeleteObject(next_shape);
            tetris.ClearBoard();
            STAGE = GameStage::END;
        } else {
            tetris.ResetShape();
            RESET_SHAPE = true;
            time_step = time_step <= 0 ? 0 : time_step - 50;
            SetTimer(MAIN_WND, GAME_TIMER, time_step, NULL);
        }
    }
}

void ProcessGameInput(int command){
    if (command == CONTROLS_MANAGER.down){
        ProcessDown();
    } else if (CONTROLS_MANAGER.left == command){
        tetris.Left();
    } else if (CONTROLS_MANAGER.right == command){
        tetris.Right();
    } else if (CONTROLS_MANAGER.v_left == command){
        tetris.VeerLeft();
    } else if (CONTROLS_MANAGER.v_right == command){
        tetris.VeerRight();
    } else if (CONTROLS_MANAGER.pause == command){
        SetTimer(MAIN_WND, PAUSE_TIMER, 700, NULL);
        STAGE = GameStage::PAUSE;
    }
}

void ProcessGameEnd(int wParam){
    if (wParam == CONTROLS_MANAGER.esc){
        DestroyWindow(table);
        DestroyWindow(prev_shape);
        DestroyWindow(MAIN_WND);
    } else {
        tetris.ResetGame();
        time_step = 3000;
        SetTimer(MAIN_WND, GAME_TIMER, time_step, NULL);
        STAGE = GameStage::GAME;
    }
}

void DrawPause(){
    DeleteObject(PAUSE_IMAGE);
    if (HELP_IMAGE){
        PAUSE_IMAGE = (HBITMAP) LoadImage(
            NULL, _T("resource/PauseHelp.bmp"), IMAGE_BITMAP,
            0, 0, LR_LOADFROMFILE
        );
        HELP_IMAGE = false;
    } else {
        PAUSE_IMAGE = (HBITMAP) LoadImage(
            NULL, _T("resource/Pause.bmp"), IMAGE_BITMAP,
            0, 0, LR_LOADFROMFILE
        );
        HELP_IMAGE = true;
    }

    SendMessage(table, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) PAUSE_IMAGE);

}

void ProcessPause(int message){
    if (message == CONTROLS_MANAGER.pause){
        KillTimer(MAIN_WND, PAUSE_TIMER);
        STAGE = GameStage::GAME;
        InvalidateRect(MAIN_WND, NULL, false);
    } else if (message == CONTROLS_MANAGER.esc){
        KillTimer(MAIN_WND, PAUSE_TIMER);
        DestroyWindow(table);
        DestroyWindow(prev_shape);
        DestroyWindow(MAIN_WND);
    }
}

void ProcessGameClick(HWND hWnd, GameStage stage, int message){
    switch (STAGE){
        case GameStage::END:{
            ProcessGameEnd(message);
            break;
        }
        case GameStage::GAME:{
            ProcessGameInput(message);
            InvalidateRect(hWnd, NULL, false);
            break;
        }
        case GameStage::PAUSE: {
            ProcessPause(message);
        }
    }
}

LRESULT CALLBACK WinProc(
    HWND hWnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
){
    switch (msg){
        case WM_DESTROY: {
            DeleteObject(next_shape);
            DeleteObject(PAUSE_IMAGE);
            KillTimer(MAIN_WND, GAME_TIMER);
            PostQuitMessage(0);
            return 0;
        }
        case WM_LBUTTONDOWN: {
            PREVIOUS_CURS_POS.x = GET_X_LPARAM(lParam);
            PREVIOUS_CURS_POS.y = GET_Y_LPARAM(lParam);
            RECT r{0, 0, 400, 25};
            if (PtInRect(&r, PREVIOUS_CURS_POS)){
                SetCapture(hWnd);
                IS_MOVING_FRAME = true;
            } else {
                ProcessGameClick(hWnd, STAGE, wParam);
            }
            break;
        }
        case WM_MOUSEMOVE: {
            if (IS_MOVING_FRAME){
                POINT p;
                RECT r;
                GetCursorPos(&p);
                GetWindowRect(hWnd, &r);
                MoveWindow(
                    hWnd, p.x - PREVIOUS_CURS_POS.x,
                    p.y - PREVIOUS_CURS_POS.y, r.right - r.left,
                    r.bottom - r.top, false
                );
            }
            break;
        }
        case WM_LBUTTONUP: {
            if (IS_MOVING_FRAME){
                IS_MOVING_FRAME = false;
                ReleaseCapture();
            }
            break;
        }
        case WM_RBUTTONDOWN: {
            ProcessGameClick(hWnd, STAGE, wParam);
            break;
        }
        case WM_KEYDOWN: {
            ProcessGameClick(hWnd, STAGE, wParam);
            break;
        }
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(table, &ps);
            switch (STAGE){
                case GameStage::END:{
                    DrawEndGameFrame();
                    DrawEndGameResult(hdc, ps);
                    break;
                }
                case GameStage::GAME: {
                    DrawGame(hdc, ps);
                    break;
                }
                case GameStage::PAUSE: {
                    DrawPause();
                }
            }
            EndPaint(table, &ps);
            break;
        }
        case WM_TIMER:{
            switch (wParam){
                case GAME_TIMER:{
                    if (STAGE == GameStage::GAME){
                        ProcessDown();
                        InvalidateRect(hWnd, NULL, false);
                    }
                    break;
                }
                case PAUSE_TIMER:{
                    InvalidateRect(hWnd, NULL, false);
                }
            }

            break;
        }
        case WM_CREATE: {
            STAGE = GameStage::GAME;
        
            table = CreateWindow(
                _T("STATIC"), 0, WS_CHILD | SS_BITMAP | WS_VISIBLE,
                TABLE_X, TABLE_Y, 200, 400, hWnd, nullptr,
                nullptr, nullptr
            );

            prev_shape = CreateWindow(
                _T("STATIC"), 0, WS_CHILD | WS_VISIBLE | SS_BITMAP,
                SHAPE_X, SHAPE_Y, 49, 49, hWnd, nullptr,
                nullptr, nullptr
            );

            SQ = (HBITMAP) LoadImage(
                nullptr, _T("resource/SQ.bmp"), IMAGE_BITMAP,
                0, 0, LR_LOADFROMFILE
            );
            break;
        }
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
