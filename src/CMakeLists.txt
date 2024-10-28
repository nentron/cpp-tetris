cmake_minimum_required(VERSION 3.5)

project(supertetris CXX)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_SYSTEM_NAME MATCHES "^MINGW")
    set(SYSTEM_LIBS -lstdc++)
else()
    set(SYSTEM_LIBS)
endif()

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../tests" Tests)
enable_testing()

set(SOURCES
    common.cpp shapes.cpp supertetris.cpp
)

set(HEADERS
    barrel.h commands.hpp common.h shapes.h
    supertetris.h
)
set(IncludeDir "${CMAKE_CURRENT_SOURCE_DIR}/../include")
add_executable(supertetris ${HEADERS} ${SOURCES} main.cpp)
target_include_directories(supertetris PRIVATE ${IncludeDir})
target_link_libraries(
    supertetris PRIVATE "${IncludeDir}/SettingsLib/libTetrisControls.a"
)
target_sources(supertetris PRIVATE "${IncludeDir}/st.rc")
