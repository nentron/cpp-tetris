#include "keyboard_translater.h"


KeyboardTranslater::KeyboardTranslater(int lang_num)
{
    SetLangNumber(lang_num);
}

const std::string& KeyboardTranslater::TranslateVkToString(int vk) const {
    if (langs[lang_number] -> count(vk)){
        return langs[lang_number] -> at(vk);
    }
    return cnn_translate;
}

void KeyboardTranslater::SetLangNumber(int lang_num){
    if (lang_num < NUM_LANGS){
        lang_number = lang_num;
    }
}
