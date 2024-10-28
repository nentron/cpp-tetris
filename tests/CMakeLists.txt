cmake_minimum_required(VERSION 3.5)

project(Tests)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_SYSTEM_NAME MATCHES "^MINGW")
    set(SYSTEM_LIBS -lstdc++)
else()
    set(SYSTEM_LIBS)
endif()
set(PARENT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../src/")
set(
    PARENT_TEST_FILES
    "${PARENT_DIR}/common.cpp" "${PARENT_DIR}/common.h"
    "${PARENT_DIR}/shapes.cpp" "${PARENT_DIR}/shapes.h"
    "${PARENT_DIR}/barrel.h"
)
include(CTest)
include_directories(${PARENT_DIR})
add_executable(
    Tests ${PARENT_TEST_FILES} test_shapes.h test.h unit_tests.h main.cpp
)
add_test(NAME tests COMMAND Tests)