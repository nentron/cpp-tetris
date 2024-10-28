#include "common.h"

const RECT* RECT_FOR_KEYS[] = {
    &LEFT, &RIGHT, &V_LEFT, &V_RIGHT, &DOWN, &PAUSE, &ESC
};

int KeyboardButtonRECT::size(){
    return RectNum::LAST;
}

const RECT* KeyboardButtonRECT::operator[](int idx) const {
    return RECT_FOR_KEYS[idx];
}

RECT* KeyboardButtonRECT::operator[](int idx){
    return const_cast<RECT*>(RECT_FOR_KEYS[idx]);
}
