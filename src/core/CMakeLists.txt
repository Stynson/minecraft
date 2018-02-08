get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})

project(${ProjectId})

FILE(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_LIST_DIR}/*.cpp")
HEADER_DIRECTORIES(INCLUDES ${CMAKE_CURRENT_LIST_DIR})

include_directories(${INCLUDES})
add_library(${ProjectId} ${SOURCES})

set(${ProjectId}_INCLUDES ${INCLUDES} PARENT_SCOPE)
