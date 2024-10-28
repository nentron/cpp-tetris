#include "file_manager.h"

#include <filesystem>


void SettingsManager::WriteToFile(){
    std::ofstream f(path + FILE_NAME, std::ios::trunc | std::ios::binary);
    f.write((char*) this, sizeof(KeyBoardSettings));
    f.close();
}

void SettingsManager::LoadSettings(){
        if (!std::filesystem::exists(path + FILE_NAME)){
            WriteToFile();
        } else {
            std::ifstream f(path + FILE_NAME, std::ios::binary);
            f.read((char*) this, sizeof(KeyBoardSettings));
            f.close();
        }
}