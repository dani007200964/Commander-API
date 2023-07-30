# Created on April 08 2023
# Copyright (c) 2020 - Daniel Hajnal
# hajnal.daniel96@gmail.com
# This file is part of the Shellminator project.

cmake_minimum_required( VERSION 3.24 )
project( Shellminator VERSION 1.1.3 )

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

option(RUN_TESTS "Enable Tests" OFF)
option(BUILD_SIMULATOR "Build Simulator" OFF)
option(BUILD_EXAMPLES "Build Examples" OFF)
option(BUILD_WEBASSEMBLY "Build WebAssembly" OFF)

if (RUN_TESTS)

    add_compile_options( -fprofile-arcs )
    add_compile_options( -ftest-coverage )
    add_compile_options( -O0 )
    add_compile_options( -Wall )
    add_link_options("--coverage")
    set( CMAKE_EXE_LINKER_FLAGS "-lgcov -fprofile-arcs -ftest-coverage" )

endif()

include_directories( 
    src
    extras/simulator
    extras/Unity/src
)

set( SOURCES
    src/Commander-API-Commands.cpp
    src/Commander-API-Digital-IO-Commands.cpp
    src/Commander-API-Commands.hpp
    src/Commander-API.cpp
    src/Commander-API.hpp
    src/Commander-IO.cpp
    src/Commander-IO.hpp
    src/Commander-Utils.cpp
    src/Commander-Utils.hpp
    src/Commander-Arguments.cpp
    src/Commander-Arguments.hpp
    src/Commander-Settings.hpp

    extras/simulator/Arduino.h
    extras/simulator/Print.cpp
    extras/simulator/Print.h
    extras/simulator/Printable.h
    extras/simulator/Stream.cpp
    extras/simulator/Stream.h
    extras/simulator/System.h
    extras/simulator/System.cpp
    extras/simulator/stdioStream.hpp
    extras/simulator/stdioStream.cpp
)

if (RUN_TESTS)


    set( UNIT_TESTING
        extras/Unity/src/unity_internals.h
        extras/Unity/src/unity.c
        extras/Unity/src/unity.h
        extras/tests/testStream.cpp
        extras/tests/testStream.hpp
    )

endif()

if( BUILD_EXAMPLES )

    set( CUSTOM_COMMANDS
        extras/simulator/CustomCommands.cpp
        extras/simulator/CustomCommands.hpp
    )

endif()

# Commander settings
add_compile_definitions(
    # SHELLMINATOR_ENABLE_HIGH_MEMORY_USAGE
    SHELLMINATOR_ENABLE_PROGRESS_BAR_SUPPORT
    SHELLMINATOR_ENABLE_PLOT_MODULE

    #UNITY_OUTPUT_COLOR

)

if( BUILD_SIMULATOR )

    # Build the simulator
    add_executable( Simulator ${SOURCES} extras/simulator/simulator.cpp )

endif()

if(RUN_TESTS)

    # Unit testing
    add_executable( test_init ${SOURCES} ${UNIT_TESTING} extras/tests/testCases/test_init.cpp )
    add_executable( test_piping ${SOURCES} ${UNIT_TESTING} extras/tests/testCases/test_piping.cpp )

endif()

# Do not edit this comment and do not write anything after it!
# It will be generated with the exampleGenerator.py script.
#---- Examples Section ----#

if( BUILD_EXAMPLES )
	add_executable( Argumentadvanced ${SOURCES} ${CUSTOM_COMMANDS} extras/examples_desktop/Desktop/Argumentadvanced/Argumentadvanced.cpp )
	add_executable( Argumentbasic ${SOURCES} ${CUSTOM_COMMANDS} extras/examples_desktop/Desktop/Argumentbasic/Argumentbasic.cpp )
	add_executable( Basic ${SOURCES} ${CUSTOM_COMMANDS} extras/examples_desktop/Desktop/Basic/Basic.cpp )
	add_executable( Blink ${SOURCES} ${CUSTOM_COMMANDS} extras/examples_desktop/Desktop/Blink/Blink.cpp )
	add_executable( Description ${SOURCES} ${CUSTOM_COMMANDS} extras/examples_desktop/Desktop/Description/Description.cpp )
	add_executable( Help ${SOURCES} ${CUSTOM_COMMANDS} extras/examples_desktop/Desktop/Help/Help.cpp )
	add_executable( Interactive ${SOURCES} ${CUSTOM_COMMANDS} extras/examples_desktop/Desktop/Interactive/Interactive.cpp )
endif()
if( BUILD_WEBASSEMBLY )
	add_executable( Argumentadvanced ${SOURCES} ${CUSTOM_COMMANDS} extras/examples_emscripten/Emscripten/Argumentadvanced/Argumentadvanced.cpp )
	target_link_options( Argumentadvanced PUBLIC -sNO_EXIT_RUNTIME=1 -sFORCE_FILESYSTEM=1 -sRETAIN_COMPILER_SETTINGS -sASYNCIFY )

	add_executable( Argumentbasic ${SOURCES} ${CUSTOM_COMMANDS} extras/examples_emscripten/Emscripten/Argumentbasic/Argumentbasic.cpp )
	target_link_options( Argumentbasic PUBLIC -sNO_EXIT_RUNTIME=1 -sFORCE_FILESYSTEM=1 -sRETAIN_COMPILER_SETTINGS -sASYNCIFY )

	add_executable( Basic ${SOURCES} ${CUSTOM_COMMANDS} extras/examples_emscripten/Emscripten/Basic/Basic.cpp )
	target_link_options( Basic PUBLIC -sNO_EXIT_RUNTIME=1 -sFORCE_FILESYSTEM=1 -sRETAIN_COMPILER_SETTINGS -sASYNCIFY )

	add_executable( Blink ${SOURCES} ${CUSTOM_COMMANDS} extras/examples_emscripten/Emscripten/Blink/Blink.cpp )
	target_link_options( Blink PUBLIC -sNO_EXIT_RUNTIME=1 -sFORCE_FILESYSTEM=1 -sRETAIN_COMPILER_SETTINGS -sASYNCIFY )

	add_executable( Description ${SOURCES} ${CUSTOM_COMMANDS} extras/examples_emscripten/Emscripten/Description/Description.cpp )
	target_link_options( Description PUBLIC -sNO_EXIT_RUNTIME=1 -sFORCE_FILESYSTEM=1 -sRETAIN_COMPILER_SETTINGS -sASYNCIFY )

	add_executable( Help ${SOURCES} ${CUSTOM_COMMANDS} extras/examples_emscripten/Emscripten/Help/Help.cpp )
	target_link_options( Help PUBLIC -sNO_EXIT_RUNTIME=1 -sFORCE_FILESYSTEM=1 -sRETAIN_COMPILER_SETTINGS -sASYNCIFY )

	add_executable( Interactive ${SOURCES} ${CUSTOM_COMMANDS} extras/examples_emscripten/Emscripten/Interactive/Interactive.cpp )
	target_link_options( Interactive PUBLIC -sNO_EXIT_RUNTIME=1 -sFORCE_FILESYSTEM=1 -sRETAIN_COMPILER_SETTINGS -sASYNCIFY )

endif()
