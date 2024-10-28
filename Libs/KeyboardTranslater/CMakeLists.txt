cmake_minimum_required(VERSION 3.5)

project(KeyboardTranslater CXX)

set(CMAKE_CXX_STANDARD 17)

add_library(KeyboardTranslater english.h keyboard_translater.h keyboard_translater.cpp)
