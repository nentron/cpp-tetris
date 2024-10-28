#pragma once

#include "english.h"

#include <string>
#include <unordered_map>

const int NUM_LANGS = 1;

class KeyboardTranslater{
private:
    const std::unordered_map<
        int, std::string>* langs[NUM_LANGS] = {&ENGLISH};
    int lang_number = 0;
    const std::string cnn_translate{""};
public:
    KeyboardTranslater() = default;

    KeyboardTranslater(int lang_num);

    const std::string& TranslateVkToString(int vk) const;
    void SetLangNumber(int lang_num);
};