/*
* Created on June 18 2020
*
* Copyright (c) 2020 - Daniel Hajnal
* hajnal.daniel96@gmail.com
* This file is part of the Commander-API project.
*/

/// This demo requires Shellminator library.
/// You can find it here: https://github.com/dani007200964/Shellminator

#include <stdio.h>
#include <stdarg.h>

/// Include Commander-API
#include "interpreter.hpp"

/// Include Shellminator library
#include "Shellminator.hpp"

/// Declaration of the execution function.
/// This function will be called every time when
/// a command arrives.
void execution_function( char *cmd );

/// Create a Shellminator object, and initialise it to use Serial
Shellminator shell( &Serial, execution_function );

/// Setup function
void setup() {

  /// Initialise Serial with 115200 baudrate
  Serial.begin( 115200 );

  /// Wait for connection
  while( !Serial );

  /// Clear the terminal
  shell.clear();

  /// Wait 2 seconds before initialising the program.
  /// It is optional, just simply give you some time to open
  /// a terminal application after sketch upload.
  delay( 2000 );

  /// Print start message
  Serial.println( "Program start...\r\n" );

  /// Initialise the interpreter.
  /// This function is better to called in your program
  /// as early as possible, because ot will make a binary
  /// tree of your commands, and this process uses some
  /// recursive functions. The recursive function calls
  /// can eat up some stack memory. After the initialisation
  /// this memory will be freed up.
  init_interpreter();

  /// Initialise shell object.
  shell.begin( "arnold" );

}

/// Infinite loop
void loop() {

  /// Feed Shellminator's update function.
  shell.update();

}

/// You need a wrapper function to connect
/// Shellminator to Commander API.
/// This wrapper function is very simple.
/// Shellminator will call execution_function
/// every time when a command arrives to Serial.
/// This function will pass that command to
/// Commander API and configures Commander to
/// genberate the response back to Serial.
void execution_function( char *cmd ){

  execute( cmd, arduino_printf );

}
