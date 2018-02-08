get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})

project(${ProjectId} VERSION 0.1.0 LANGUAGES CXX)

FILE(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_LIST_DIR}/*.cpp")
HEADER_DIRECTORIES(INCLUDES ${CMAKE_CURRENT_LIST_DIR})
include_directories(${INCLUDES})

add_executable(NotMineCraft ${SOURCES})


# Bgfx
#[[
include_directories(${BX_DIR}/include)
include_directories(${BIMG_DIR}/include)
include_directories(${BGFX_DIR}/include)
include_directories(${BGFX_DIR}/3rdparty)
include_directories(${BX_DIR}/include/compat/msvc)

FILE(GLOB_RECURSE BGFX_3RDPARTY_SOURCES "${BGFX_DIR}/3rdparty/**/*.cpp")
HEADER_DIRECTORIES(BGFX_3RDPARTY_INCLUDES "${BGFX_DIR}")
message(${BGFX_3RDPARTY_INCLUDES})
set(BGFX_3RDPARTY_INCLUDES ${BGFX_3RDPARTY_INCLUDES} "${BGFX_DIR}/3rdparty/glsl-optimizer/src" "${BGFX_DIR}/3rdparty/glsl-optimizer/src/mesa")
add_library(bgfx_3rdparty ${BGFX_3RDPARTY_SOURCES})
include_directories(${BGFX_3RDPARTY_INCLUDES})

target_link_libraries(NotMineCraft bgfx bgfx_3rdparty)
]]

# Example
include_directories(${CMAKE_CURRENT_LIST_DIR}/examples/common)
FILE(GLOB_RECURSE EXAMPLES_SOURCES "${CMAKE_CURRENT_LIST_DIR}/examples/common/*.cpp")
add_library(examples_sources ${EXAMPLES_SOURCES})

target_link_libraries(NotMineCraft examples_sources)

# Subprojects

set(DEPENDENCY_LIST core)
FOREACH(item ${DEPENDENCY_LIST})
	include_directories(${${item}_INCLUDES})
    target_link_libraries(NotMineCraft ${item})
ENDFOREACH()
