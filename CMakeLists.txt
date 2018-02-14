# bgfx.cmake - bgfx building in cmake
# Written in 2017 by Joshua Brookover <joshua.al.brookover@gmail.com>

# To the extent possible under law, the author(s) have dedicated all copyright
# and related and neighboring rights to this software to the public domain
# worldwide. This software is distributed without any warranty.

# You should have received a copy of the CC0 Public Domain Dedication along with
# this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

cmake_minimum_required( VERSION 3.0 )
project( bgfx )

set_property( GLOBAL PROPERTY USE_FOLDERS ON )
if( APPLE )
	set( CMAKE_CXX_FLAGS "-ObjC++ --std=c++14" )
elseif(UNIX)
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

option( BGFX_BUILD_TOOLS      "Build bgfx tools."                             ON  )
option( BGFX_BUILD_EXAMPLES   "Build bgfx examples."                          ON  )
option( BGFX_INSTALL          "Create installation target."                   ON  )
option( BGFX_CUSTOM_TARGETS   "Include convenience custom targets."           OFF  )
option( BGFX_USE_OVR          "Build with OVR support."                       OFF )
option( BGFX_AMALGAMATED      "Amalgamated bgfx build for faster compilation" OFF )
option( BX_AMALGAMATED        "Amalgamated bx build for faster compilation"   OFF )
option( BGFX_CONFIG_DEBUG     "Enables debug configuration on all builds" OFF)

if( NOT BX_DIR )
	set( BX_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/bx" CACHE STRING "Location of bx." )
endif()
if( NOT BIMG_DIR )
	set( BIMG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/bimg" CACHE STRING "Location of bimg." )
endif()
if( NOT BGFX_DIR )
	set( BGFX_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/bgfx" CACHE STRING "Location of bgfx." )
endif()

if( NOT APP_DIR )
	set( APP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/app" CACHE STRING "Location of app." )
endif()

set( APP_RUNTIME_DIR "${APP_DIR}/runtime" CACHE STRING "Location of runtime files." )
set( APP_COMMON_DIR "${APP_DIR}/common" CACHE STRING "Location of common files." )
set( GLM_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/glm" CACHE STRING "Location of glm library." )

MACRO(COPY_RUNTIME_FILES name)
      # SDL_Mixer
      add_custom_command(TARGET ${name} POST_BUILD   
          COMMAND ${CMAKE_COMMAND} -E copy_directory  
              "${APP_RUNTIME_DIR}" # <--this is in-file
              $<TARGET_FILE_DIR:${name}>) # <--this is out-file path
ENDMACRO()

if( BGFX_USE_OVR )
	include( cmake/ovr.cmake )
endif()

include( cmake/shared.cmake )
include( cmake/bx.cmake )
include( cmake/bimg.cmake )
include( cmake/bgfx.cmake )

if( BGFX_BUILD_TOOLS )
	include( cmake/tools.cmake )
endif()

include( cmake/glm.cmake )

#include( cmake/examples.cmake )
include( cmake/minecraft.cmake )

COPY_RUNTIME_FILES( minecraft-app )

if( BGFX_INSTALL )
	# install bx
	install( TARGETS bx DESTINATION lib )
	install( DIRECTORY ${BX_DIR}/include DESTINATION . )

	# install bimg
	install( TARGETS bimg DESTINATION lib )
	install( DIRECTORY ${BIMG_DIR}/include DESTINATION . )

	# install bgfx
	install( TARGETS bgfx DESTINATION lib )
	install( DIRECTORY ${BGFX_DIR}/include DESTINATION . )

	# install tools
	if( BGFX_BUILD_TOOLS )
        install( TARGETS shaderc DESTINATION bin )
		install( TARGETS geometryc DESTINATION bin )
	endif()
endif()
