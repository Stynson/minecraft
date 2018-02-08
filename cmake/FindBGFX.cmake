
#if(NOT ${BGFX_ROOT_DIR})
#    message(FATAL_ERROR  "BGFX_ROOT_DIR must be defined")
#endif()

set(_includes 
    "${BGFX_ROOT_DIR}/bx/include/compat/msvc"  # TODO: platforms
    "${BGFX_ROOT_DIR}/bx/include"
    "${BGFX_ROOT_DIR}/bx/3rdparty"
    "${BGFX_ROOT_DIR}/bimg/include"
    "${BGFX_ROOT_DIR}/bimg/3rdparty"
    "${BGFX_ROOT_DIR}/bimg/3rdparty/iqa/include"
    "${BGFX_ROOT_DIR}/bgfx/include"
    "${BGFX_ROOT_DIR}/bgfx/examples/common"
    "${BGFX_ROOT_DIR}/bgfx/3rdparty/khronos"
    "${BGFX_ROOT_DIR}/bgfx/3rdparty/dxsdk/include"
    "${BGFX_ROOT_DIR}/bgfx/3rdparty"
)

set(BGFX_SOURCES ${BGFX_ROOT_DIR}/bgfx/src/amalgamated.cpp)
set(BX_SOURCES ${BGFX_ROOT_DIR}/bx/src/amalgamated.cpp)
FILE(GLOB_RECURSE BIMG_SOURCES ${BGFX_ROOT_DIR}/bimg/src/*.cpp)

FILE (GLOB_RECURSE BGFX_EXAMPLE_COMMON_SOURCES
    "${BGFX_ROOT_DIR}/bgfx/3rdparty/ib-compress/**.cpp"
    "${BGFX_ROOT_DIR}/bgfx/3rdparty/ib-compress/**.h"
    "${BGFX_ROOT_DIR}/bgfx/3rdparty/ocornut-imgui/**.cpp"
    "${BGFX_ROOT_DIR}/bgfx/3rdparty/ocornut-imgui/**.h"
    "${BGFX_ROOT_DIR}/bgfx/examples/common/**.cpp"
    "${BGFX_ROOT_DIR}/bgfx/examples/common/**.h"
    )

include_directories(${_includes})

add_library(bgfx-common STATIC ${BGFX_EXAMPLE_COMMON_SOURCES})
add_library(bgfx STATIC ${BGFX_SOURCES})
add_library(bx STATIC ${BX_SOURCES})
add_library(bimg STATIC ${BIMG_SOURCES})

set(BGFX_INCLUDES ${_includes})
