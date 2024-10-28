#pragma once

#include "windows.h"


const int START_SETTINGS_X = 192;
const int START_SETTINGS_Y = 32;
const int RECT_SETTINGS_W = 192;
const int RECT_SETTINGS_H = 48;

constexpr RECT LEFT{
    START_SETTINGS_X, START_SETTINGS_Y,
    START_SETTINGS_X + RECT_SETTINGS_W,
    START_SETTINGS_Y + RECT_SETTINGS_H
};

constexpr RECT RIGHT{
    START_SETTINGS_X, START_SETTINGS_Y + RECT_SETTINGS_H + 5,
    START_SETTINGS_X + RECT_SETTINGS_W,
    RIGHT.top + RECT_SETTINGS_H
};

constexpr RECT V_LEFT{
    START_SETTINGS_X, START_SETTINGS_Y + RECT_SETTINGS_H * 2 + 5,
    START_SETTINGS_X + RECT_SETTINGS_W,
    V_LEFT.top + RECT_SETTINGS_H
};

constexpr RECT V_RIGHT{
    START_SETTINGS_X, START_SETTINGS_Y + RECT_SETTINGS_H * 3 + 5,
    START_SETTINGS_X + RECT_SETTINGS_W,
    V_RIGHT.top + RECT_SETTINGS_H
};

constexpr RECT DOWN{
    START_SETTINGS_X, START_SETTINGS_Y + RECT_SETTINGS_H * 4 + 5,
    START_SETTINGS_X + RECT_SETTINGS_W,
    DOWN.top + RECT_SETTINGS_H
};

constexpr RECT PAUSE{
    START_SETTINGS_X, START_SETTINGS_Y + RECT_SETTINGS_H * 5 + 5,
    START_SETTINGS_X + RECT_SETTINGS_W,
    PAUSE.top + RECT_SETTINGS_H
};

constexpr RECT ESC{
    START_SETTINGS_X, START_SETTINGS_Y + RECT_SETTINGS_H * 6 + 10,
    START_SETTINGS_X + RECT_SETTINGS_W,
    ESC.top + RECT_SETTINGS_H
};


struct KeyboardButtonRECT{

    enum RectNum{
        LEFT = 0,
        RIGHT = 1,
        V_LEFT = 2,
        V_RIGHT = 3,
        DOWN = 4,
        PAUSE = 5,
        ESC = 6,
        LAST = 7
    };

    int size();

    const RECT* operator[](int idx) const;

    RECT* operator[](int idx);
};
