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

#define RECIVE_BUFFER_LENGTH 30

char recive_buffer[ RECIVE_BUFFER_LENGTH ] = { '\0' };
uint8_t recive_buffer_cntr = 0;

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

}

/// Infinite loop
void loop() {

  /// This variable will store the character that
  /// has been read from the serial port
  char c;

  /// While there is data available to read from the serial port,
  /// we try to read as many characters as possible.
  while( Serial.available() > 0  ){

    /// Read one character
    c = Serial.read();

    /// We have to check if the character is not a '\r'( carriage return ) character,
    /// because '\r' means that we have to execute the command.
    if( c != '\r' ){

      /// We add the character to the buffer
      recive_buffer[ recive_buffer_cntr ] = c;

      /// And we have to increment the buffer counter to point to the next free 'slot'
      /// in the buffer
      recive_buffer_cntr++;

      /// We have to check for buffer overflow.
      if( recive_buffer_cntr >= RECIVE_BUFFER_LENGTH ){

        /// If a buffer oveflow occures it is useful to let the user know.
        Serial.println( "Command buffer overflow" );

        /// And we simply reset recive_buffer_cntr variable.
        recive_buffer_cntr = 0;

      }

    }

    else{

      /// '\r' character recived, so we execute the command,
      /// that has been stored in the buffer
      execute( recive_buffer, arduino_printf );

      /// Reset the recive_buffer_cntr variable to prepare
      /// the buffer for a new command.
      recive_buffer_cntr = 0;

    }

  }

}
