set(TESTS Tests)
project(${TESTS} VERSION 0.1.0 LANGUAGES CXX)

HEADER_DIRECTORIES(INCLUDES ${CMAKE_CURRENT_LIST_DIR})
include_directories(${INCLUDES})

set(gtest_include_dirs "${GTEST_ROOT_DIR}/googletest"
                       "${GTEST_ROOT_DIR}/googletest/include"
                       "${GTEST_ROOT_DIR}/googlemock"
                       "${GTEST_ROOT_DIR}/googlemock/include")


include_directories(${gtest_include_dirs})

add_library(gtest STATIC "${GTEST_ROOT_DIR}/googletest/src/gtest-all.cc"
                         "${GTEST_ROOT_DIR}/googletest/src/gtest_main.cc")
add_library(gmock STATIC "${GTEST_ROOT_DIR}/googlemock/src/gmock-all.cc"
                         "${GTEST_ROOT_DIR}/googlemock/src/gmock_main.cc")


FILE(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_LIST_DIR}/**/*.cpp")

add_executable(${TESTS} main.cpp ${TEST_SOURCES})
target_link_libraries(${TESTS} ${MINO_ENGINE} gtest gmock)

# Subprojects
FOREACH(item ${PROJECT_LIST})
	include_directories(${${item}_INCLUDES})
    target_link_libraries(${TESTS} ${item}) 
ENDFOREACH()

