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
    src/Commands/Commander-API-Commands.cpp
    src/Commands/Commander-API-Digital-IO-Commands.cpp
    src/Commands/Commander-API-Analog-IO-Commands.cpp
    src/Commands/Commander-API-System-Commands.cpp
    src/Commands/Commander-API-Neofetch-Command.cpp
    src/Commands/Commander-API-Math-Commands.cpp
    src/Commands/Commander-API-Memory-Commands.cpp
    src/Commander-API-Commands.hpp
    src/Commander-API.cpp
    src/Commander-API.hpp
    src/Commander-IO.cpp
    src/Commander-IO.hpp
    src/Commander-Arguments.cpp
    src/Commander-Arguments.hpp
    #src/Commander-Database.cpp
    src/Commander-Database.hpp
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
        #extras/tests/testCases/Commander-Database/test_constructor.cpp
        #extras/tests/testCases/Commander-Database/test_debug.cpp
    )

endif()

if( BUILD_EXAMPLES )

    set( CUSTOM_COMMANDS
        extras/simulator/CustomCommands.cpp
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
    # Every target has to be started with 'test_'

    # -- Commander-Database --
    #add_executable( test_commander_database_constructor ${SOURCES} ${UNIT_TESTING} extras/tests/testCases/Commander-Database/test_constructor.cpp )
    #add_executable( test_commander_database_debug ${SOURCES} ${UNIT_TESTING} extras/tests/testCases/Commander-Database/test_debug.cpp )
    #add_executable( test_commander_database_init ${SOURCES} ${UNIT_TESTING} extras/tests/testCases/Commander-Database/test_init.cpp )
    #add_executable( test_commander_database_search ${SOURCES} ${UNIT_TESTING} extras/tests/testCases/Commander-Database/test_search.cpp )

    # -- Commander-Arguments --
    #add_executable( test_commander_arguments_constructor ${SOURCES} ${UNIT_TESTING} extras/tests/testCases/Commander-Arguments/test_constructor.cpp )
    #add_executable( test_commander_arguments_find_functions ${SOURCES} ${UNIT_TESTING} extras/tests/testCases/Commander-Arguments/test_find_functions.cpp )
    #add_executable( test_commander_arguments_parser_short_name ${SOURCES} ${UNIT_TESTING} extras/tests/testCases/Commander-Arguments/test_parser_short_name.cpp )
    #add_executable( test_commander_arguments_parser_long_name ${SOURCES} ${UNIT_TESTING} extras/tests/testCases/Commander-Arguments/test_parser_long_name.cpp )

    # -- Commander-IO --
    #add_executable( test_commander_io_constructor ${SOURCES} ${UNIT_TESTING} extras/tests/testCases/Commander-IO/test_constructor.cpp )
    #add_executable( test_commander_io_write ${SOURCES} ${UNIT_TESTING} extras/tests/testCases/Commander-IO/test_write.cpp )
    #add_executable( test_commander_io_available ${SOURCES} ${UNIT_TESTING} extras/tests/testCases/Commander-IO/test_available.cpp )
    #add_executable( test_commander_io_read ${SOURCES} ${UNIT_TESTING} extras/tests/testCases/Commander-IO/test_read.cpp )
    #add_executable( test_commander_io_peek ${SOURCES} ${UNIT_TESTING} extras/tests/testCases/Commander-IO/test_peek.cpp )

    # -- Commander-Commands / Analog-IO-Commands --
    #add_executable( test_commander_commands_analog_io_commands ${SOURCES} ${UNIT_TESTING} extras/tests/testCases/Commander-Commands/Analog-IO-Commands/test_analog_io_commands.cpp )

    # -- Commander-Commands / Analog-IO-Commands --
    #add_executable( test_commander_commands_digital_io_commands ${SOURCES} ${UNIT_TESTING} extras/tests/testCases/Commander-Commands/Digital-IO-Commands/test_digital_io_commands.cpp )

    # -- Commander-Commands / Math-Commands --
    add_executable( test_commander_commands_math_commands ${SOURCES} ${UNIT_TESTING} extras/tests/testCases/Commander-Commands/Math-Commands/test_math_commands.cpp )

endif()

# Do not edit this comment and do not write anything after it!
# It will be generated with the exampleGenerator.py script.
#---- Examples Section ----#

if( BUILD_EXAMPLES )
	add_executable( Fullsystem ${SOURCES} ${CUSTOM_COMMANDS} extras/examples_desktop/Desktop/Fullsystem/Fullsystem.cpp )
endif()
if( BUILD_WEBASSEMBLY )
	add_executable( Fullsystem ${SOURCES} ${CUSTOM_COMMANDS} extras/examples_emscripten/Emscripten/Fullsystem/Fullsystem.cpp )
	target_link_options( Fullsystem PUBLIC -sNO_EXIT_RUNTIME=1 -sFORCE_FILESYSTEM=1 -sRETAIN_COMPILER_SETTINGS -sASYNCIFY )

endif()
