/*
* Created on June 18 2020
*
* Copyright (c) 2020 - Daniel Hajnal
* hajnal.daniel96@gmail.com
* This file is part of the Commander-API project.
*/

#include <stdio.h>
#include <stdarg.h>

/// Include Commander-API
#include "interpreter.hpp"

/// Setup function
void setup() {

  /// Initialise Serial with 115200 baudrate
  Serial.begin( 115200 );

  /// Wait for connection
  while( !Serial );

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

  /// Try the interpreter with a valid command,
  /// and not use the response function.
  execute( (char*)"stop 10 c", NULL );

  /// Try the interpreter with a valid command,
  /// and use the arduino_printf function as
  /// response function.
  execute( (char*)"stop 10 c", arduino_printf );

  /// Try the interpreter with another valid command,
  execute( (char*)"left 20 d", NULL );

  /// Try the interpreter with an invalid command
  execute( (char*)"self-destruct", NULL );

  /// Try to show the description of a command
  execute( (char*)"right?", NULL );

}

void loop() {
  // put your main code here, to run repeatedly:

}
