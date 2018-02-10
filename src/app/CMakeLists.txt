get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})

project(${ProjectId} VERSION 0.1.0 LANGUAGES CXX)

FILE(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_LIST_DIR}/*.cpp")
HEADER_DIRECTORIES(INCLUDES ${CMAKE_CURRENT_LIST_DIR})
include_directories(${INCLUDES})

add_executable(NotMineCraft ${SOURCES})

# bgfx + link
include_directories(${BGFX_INCLUDES})
target_link_libraries(NotMineCraft ${X11_LIBRARIES} bgfx bgfx-common bx bimg Psapi)

# Subprojects

set(DEPENDENCY_LIST core)
FOREACH(item ${DEPENDENCY_LIST})
	include_directories(${${item}_INCLUDES})
    target_link_libraries(NotMineCraft ${item})
ENDFOREACH()
