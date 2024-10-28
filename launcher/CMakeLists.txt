cmake_minimum_required(VERSION 3.5)

project(launcher CXX)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_SYSTEM_NAME MATCHES "^MINGW")
    set(SYSTEM_LIBS -lstdc++)
else()
    set(SYSTEM_LIBS)
endif()
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/../resource" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/build")

enable_testing()
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../src/" SuperTetris)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../settings" Settings)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../include/" launcher)
add_executable(launcher main.cpp)
target_sources(launcher PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include/st.rc")
