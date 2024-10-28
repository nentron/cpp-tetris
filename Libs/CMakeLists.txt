cmake_minimum_required(VERSION 3.5)

project(TetrisControls CXX)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_SYSTEM_NAME MATCHES "^MINGW")
    set(SYSTEM_LIBS -lstdc++)
else()
    set(SYSTEM_LIBS)
endif()

set(ControlsDir "${CMAKE_CURRENT_SOURCE_DIR}/FileSettingsLib/")
set(TranslaterDir "${CMAKE_CURRENT_SOURCE_DIR}/KeyboardTranslater/")
add_library(Translater OBJECT
            "${TranslaterDir}/english.h"
            "${TranslaterDir}/keyboard_translater.h"
            "${TranslaterDir}/keyboard_translater.cpp")
add_library(Controls OBJECT
            "${ControlsDir}/file_manager.h"
            "${ControlsDir}/file_manager.cpp")

add_library(TetrisControls STATIC
            $<TARGET_OBJECTS:Translater>
            $<TARGET_OBJECTS:Controls>)
