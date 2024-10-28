#pragma once

#include <string>
#include <unordered_map>

const std::unordered_map<int, std::string> ENGLISH = {
    {0x01, "LMouse"}, {0x02, "RMouse"}, {0x08, "BackSpace"},
    {0x09, "TAB"}, {0x0C, "Clear"}, {0x0D, "Enter"},
    {0x10, "Shift"}, {0x11, "Ctrl"}, {0x12, "Alt"},
    {0x13, "Pause"}, {0x14, "CAPSLock"}, {0x1B, "ESC"},
    {0x20, "SPACE"}, {0x21, "PageUp"}, {0x22, "PageDown"},
    {0x23, "End"},
    {0x30, "1"}, {0x31, "2"}, {0x32, "2"}, {0x33, "3"},
    {0x34, "4"}, {0x35, "5"}, {0x36, "6"}, {0x37, "7"},
    {0x38, "8"}, {0x39, "9"}, {0x3A, "-"},
    {0x41, "A"}, {0x42, "B"}, {0x43, "C"}, {0x44, "D"},
    {0x45, "E"}, {0x46, "F"}, {0x47, "G"}, {0x48, "H"},
    {0x49, "I"}, {0x4A, "J"}, {0x4B, "K"}, {0x4C, "L"},
    {0x4D, "M"}, {0x4E, "N"}, {0x4F, "O"}, {0x50, "P"},
    {0x51, "Q"}, {0x52, "R"}, {0x53, "S"}, {0x54, "T"},
    {0x55, "U"}, {0x56, "V"}, {0x57, "W"}, {0x58, "X"},
    {0x59, "Y"}, {0x5A, "Z"},
    {0x60, "Num0"}, {0x61, "Num1"}, {0x62, "Num2"}, {0x63, "Num3"},
    {0x64, "Num4"}, {0x65, "Num5"}, {0x66, "Num6"}, {0x67, "Num7"},
    {0x68, "Num8"}, {0x69, "Num9"},
    {0x70, "F1"}, {0x71, "F2"}, {0x72, "F3"}, {0x73, "F4"},
    {0x74, "F5"}, {0x75, "F6"}, {0x76, "F7"}, {0x77, "F8"},
    {0x78, "F9"}, {0x79, "F10"}, {0x7A, "F11"}, {0x7B, "F12"},
    {0x7C, "F13"}, {0x7D, "F14"}, {0x7E, "F15"}, {0x7F, "F16"},
    {0x80, "F17"}, {0x81, "F18"}, {0x82, "F19"}, {0x83, "F20"},
    {0x84, "F21"}, {0x85, "F22"}, {0x86, "F23"}, {0x87, "F24"},
    {0xA0, "LShift"}, {0xA1, "RShift"}, {0xA2, "LCtrl"}, {0xA3, "RCtrl"},
    {0xA4, "LAlt"}, {0xA5, "RAlt"}
};
