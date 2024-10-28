#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

const std::string FILE_NAME = "controls.cfg";

const std::string FILE_TITLE = "[SETTINGS]";

const std::string FILE_END_S = "[END]";

struct KeyBoardSettings {
    int left = 0x41; // A
    int right = 0x44; // D
    int v_left = 0x51; // Q
    int v_right = 0x45; // E
    int down = 0x53; // S
    int pause = VK_SPACE;
    int esc = VK_ESCAPE;
};

class SettingsManager : public KeyBoardSettings {
private:
    std::string path;
public:
    SettingsManager(){
        LoadSettings();
    }

    SettingsManager(const std::string& p)
        : path(p)
    {
        LoadSettings();
    }
    void WriteToFile();
    void LoadSettings();
};