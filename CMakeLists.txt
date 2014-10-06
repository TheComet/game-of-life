###############################################################################

cmake_minimum_required (VERSION 2.8.11)

#
# If the user specifies -DCMAKE_BUILD_TYPE on the command line, take their
# definition and dump it in the cache along with proper documentation, otherwise
# set MAKE_BUILD_TYPE to Debug prior to calling PROJECT()
if (DEFINED CMAKE_BUILD_TYPE)
	if (NOT CMAKE_BUILD_TYPE MATCHES Debug)
		set (CMAKE_BUILD_TYPE Debug)
	endif ()
	set (CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
else()
	set (CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
endif()

# project name
project (GameOfLife)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/packages")

###############################################################################
# options
###############################################################################

option (BUILD_TESTS "Whether or not to build unit tests" OFF)
option (BUILD_STATIC "Turn on to build static, turn off to build shared" OFF)

###############################################################################
# set output locations
###############################################################################
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
if (MSVC)
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
else ()
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
endif ()

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Packages")
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Utils")

###############################################################################
# library definitions
###############################################################################

###############################################################################
# compiler definitions and flags
###############################################################################
if (MSVC)
elseif (MINGW)
elseif (APPLE)
elseif (UNIX)
else ()
	message(FATAL_ERROR "Unsupported OS")
endif ()

if (CMAKE_BUILD_TYPE MATCHES Debug)
	add_definitions(
		-D_DEBUG
		-DDEBUG
	)
endif ()

###############################################################################
# generate ignored folders
# these are populate later on during configuration of individual targets
###############################################################################

# generate ignored folders

# cmake's external dependencies
set (EXTERNAL_DEP_DIR "${CMAKE_SOURCE_DIR}/cmake-dep")
file (MAKE_DIRECTORY ${EXTERNAL_DEP_DIR})
file (WRITE "${EXTERNAL_DEP_DIR}/.gitignore" "*")
link_directories ("${EXTERNAL_DEP_DIR}/lib")
include_directories ("${EXTERNAL_DEP_DIR}/include")

###############################################################################
# Dependency settings
###############################################################################

include_directories ("gol/include")

add_subdirectory ("gol")
add_subdirectory ("app2d")
add_subdirectory ("app3d")
if (BUILD_TESTS)
	add_subdirectory ("tests")
endif ()
