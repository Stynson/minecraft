cmake_minimum_required(VERSION 3.2)

project(NotMineCraft VERSION 0.1.0 LANGUAGES CXX)
 
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -pthread)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/")
set(BGFX_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/lib")
find_package(BGFX REQUIRED) 
include_directories(${BGFX_INCLUDES})
find_package(OpenGL REQUIRED)

option(BUILD_TESTS "Build tests." ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
 
MACRO(HEADER_DIRECTORIES return_list root_dir)
    FILE(GLOB_RECURSE new_list "${root_dir}/**/*.h")
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

set(PROJECT_LIST core) 

foreach(item ${PROJECT_LIST})
  add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/${item})
endforeach(item) 

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/app)
 
if(${BUILD_TESTS})
  #[[ gtest ]]
  set(GTEST_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/lib/googletest)
  enable_testing()
  add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/test)
endif()
