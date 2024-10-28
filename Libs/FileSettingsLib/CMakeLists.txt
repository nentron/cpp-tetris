cmake_minimum_required(VERSION 3.5)

project(FileManager CXX)

set(CMKAE_CXX_STANDARD 17)

add_library(FileManager STATIC file_manager.cpp file_manager.h)
