cmake_minimum_required(VERSION 3.5)

project(settings CXX)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_SYSTEM_NAME MATCHES "^MINGW")
    set(SYSTEM_LIBS -lstdc++)
else()
    SET(SYSTEM_LIBS)
endif()

set(IncludeDir "${CMAKE_CURRENT_SOURCE_DIR}/../include")

add_executable(settings common.h rect.cpp main.cpp)

target_include_directories(settings PRIVATE ${IncludeDir})
target_link_libraries(settings PRIVATE
                      "${IncludeDir}/SettingsLib/libTetrisControls.a")
target_sources(settings PRIVATE "${IncludeDir}/st.rc")
