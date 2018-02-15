# bgfx.cmake - bgfx building in cmake
# Written in 2017 by Joshua Brookover <joshua.al.brookover@gmail.com>

# To the extent possible under law, the author(s) have dedicated all copyright
# and related and neighboring rights to this software to the public domain
# worldwide. This software is distributed without any warranty.

# You should have received a copy of the CC0 Public Domain Dedication along with
# this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

include( CMakeParseArguments )

include( cmake/util/ConfigureDebugging.cmake )

include( cmake/3rdparty/ib-compress.cmake )
include( cmake/3rdparty/ocornut-imgui.cmake )

function( add_bgfx_shader FILE FOLDER )
	get_filename_component( FILENAME "${FILE}" NAME_WE )
	string( SUBSTRING "${FILENAME}" 0 2 TYPE )
	if( "${TYPE}" STREQUAL "fs" )
		set( TYPE "FRAGMENT" )
		set( D3D_PREFIX "ps" )
	elseif( "${TYPE}" STREQUAL "vs" )
		set( TYPE "VERTEX" )
		set( D3D_PREFIX "vs" )
	else()
		set( TYPE "" )
	endif()
	if( NOT "${TYPE}" STREQUAL "" )
		set( COMMON FILE ${FILE} ${TYPE} INCLUDES ${BGFX_DIR}/src )
		set( OUTPUTS "" )
		set( OUTPUTS_PRETTY "" )
		if( WIN32 )
			# dx9
			set( DX9_OUTPUT ${APP_RUNTIME_DIR}/shaders/dx9/${FILENAME}.bin )
			shaderc_parse( DX9 ${COMMON} WINDOWS PROFILE ${D3D_PREFIX}_3_0 OUTPUT ${DX9_OUTPUT} )
			list( APPEND OUTPUTS "DX9" )
			set( OUTPUTS_PRETTY "${OUTPUTS_PRETTY}DX9, " )

			# dx11
			set( DX11_OUTPUT ${APP_RUNTIME_DIR}/shaders/dx11/${FILENAME}.bin )
			shaderc_parse( DX11 ${COMMON} WINDOWS PROFILE ${D3D_PREFIX}_4_0 OUTPUT ${DX11_OUTPUT} )
			list( APPEND OUTPUTS "DX11" )
			set( OUTPUTS_PRETTY "${OUTPUTS_PRETTY}DX11, " )
		endif()
		if( APPLE )
			# metal
			set( METAL_OUTPUT ${APP_RUNTIME_DIR}/shaders/metal/${FILENAME}.bin )
			shaderc_parse( METAL ${COMMON} OSX OUTPUT ${METAL_OUTPUT} )
			list( APPEND OUTPUTS "METAL" )
			set( OUTPUTS_PRETTY "${OUTPUTS_PRETTY}Metal, " )
		endif()
		# gles
		set( GLES_OUTPUT ${APP_RUNTIME_DIR}/shaders/gles/${FILENAME}.bin )
		shaderc_parse( GLES ${COMMON} ANDROID OUTPUT ${GLES_OUTPUT} )
		list( APPEND OUTPUTS "GLES" )
		set( OUTPUTS_PRETTY "${OUTPUTS_PRETTY}GLES, " )
		# glsl
		set( GLSL_OUTPUT ${APP_RUNTIME_DIR}/shaders/glsl/${FILENAME}.bin )
		shaderc_parse( GLSL ${COMMON} LINUX PROFILE 120 OUTPUT ${GLSL_OUTPUT} )
		list( APPEND OUTPUTS "GLSL" )
		set( OUTPUTS_PRETTY "${OUTPUTS_PRETTY}GLSL" )
		set( OUTPUT_FILES "" )
		set( COMMANDS "" )
		foreach( OUT ${OUTPUTS} )
			list( APPEND OUTPUT_FILES ${${OUT}_OUTPUT} )
			list( APPEND COMMANDS COMMAND "$<TARGET_FILE:shaderc>" ${${OUT}} )
			get_filename_component( OUT_DIR ${${OUT}_OUTPUT} DIRECTORY )
			file( MAKE_DIRECTORY ${OUT_DIR} )
		endforeach()
		file( RELATIVE_PATH PRINT_NAME ${APP_DIR}/${ARG_NAME} ${FILE} )
		add_custom_command(
			MAIN_DEPENDENCY
			${FILE}
			OUTPUT
			${OUTPUT_FILES}
			${COMMANDS}
			COMMENT "Compiling shader ${PRINT_NAME} for ${OUTPUTS_PRETTY}"
		)
	endif()
endfunction()

function( add_example ARG_NAME )
	# Parse arguments
	cmake_parse_arguments( ARG "COMMON" "" "DIRECTORIES;SOURCES" ${ARGN} )

	# Get all source files
	if( ARG_COMMON )
		#list( APPEND ARG_DIRECTORIES "${BGFX_DIR}/examples/${ARG_NAME}" )
		list( APPEND ARG_DIRECTORIES "${APP_DIR}/${ARG_NAME}" )
	else()
		list( APPEND ARG_DIRECTORIES "${APP_DIR}" )
	endif()
	set( SOURCES "" )
	set( SHADERS "" )
	foreach( DIR ${ARG_DIRECTORIES} )
		if( APPLE )
			file( GLOB GLOB_SOURCES ${DIR}/*.mm )
			list( APPEND SOURCES ${GLOB_SOURCES} )
		endif()
		file( GLOB GLOB_SOURCES ${DIR}/*.c ${DIR}/*.cpp ${DIR}/*.h ${DIR}/*.sc )
		list( APPEND SOURCES ${GLOB_SOURCES} )
		file( GLOB GLOB_SHADERS ${DIR}/*.sc )
		list( APPEND SHADERS ${GLOB_SHADERS} )
	endforeach()

	# Add target
	if( ARG_COMMON )
		add_library( minecraft-${ARG_NAME} STATIC EXCLUDE_FROM_ALL ${SOURCES} )
		target_include_directories( minecraft-${ARG_NAME} PUBLIC ${APP_COMMON_DIR} )
		target_link_libraries( minecraft-${ARG_NAME} PUBLIC bgfx ib-compress ocornut-imgui )
		if( UNIX AND NOT APPLE )
			target_link_libraries( minecraft-${ARG_NAME} PUBLIC X11 )
		endif()
	else()
		if( BGFX_INSTALL_EXAMPLES )
			add_executable( minecraft-${ARG_NAME} WIN32 ${SOURCES} )
		else()
			add_executable( minecraft-${ARG_NAME} WIN32 EXCLUDE_FROM_ALL ${SOURCES} )
		endif()
		target_link_libraries( minecraft-${ARG_NAME} minecraft-common glm )
		configure_debugging( minecraft-${ARG_NAME} WORKING_DIR ${APP_RUNTIME_DIR} )
		if( MSVC )
			set_target_properties( minecraft-${ARG_NAME} PROPERTIES LINK_FLAGS "/ENTRY:\"mainCRTStartup\"" )
		endif()
		if( BGFX_CUSTOM_TARGETS )
			add_dependencies( examples minecraft-${ARG_NAME} )
		endif()
	endif()
	target_compile_definitions( minecraft-${ARG_NAME} PRIVATE "-D_CRT_SECURE_NO_WARNINGS" "-D__STDC_FORMAT_MACROS" "-DENTRY_CONFIG_IMPLEMENT_MAIN=1" )

	# Configure shaders
	if( NOT ARG_COMMON )
		foreach( SHADER ${SHADERS} )
			add_bgfx_shader( ${SHADER} ${APP_DIR} )
		endforeach()
		source_group( "Shader Files" FILES ${SHADERS})
	endif()

	# Directory name
	set_target_properties( minecraft-${ARG_NAME} PROPERTIES FOLDER "minecraft" )
endfunction()

# Build all examples target
if( BGFX_CUSTOM_TARGETS )
	add_custom_target( examples )
	set_target_properties( examples PROPERTIES FOLDER "minecraft" )
endif()

# Add common library for examples
add_example(
	common
	COMMON
	DIRECTORIES
	${APP_COMMON_DIR}/debugdraw
	${APP_COMMON_DIR}/entry
	${APP_COMMON_DIR}/font
	${APP_COMMON_DIR}/imgui
	${APP_COMMON_DIR}/nanovg
	${APP_COMMON_DIR}/ps
)

add_example( app )