/*
 * Created on Oct. 2 2020
 *
 * Copyright (c) 2020 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2022.10.02
 *
 * You need the Shellminator library for this demo.
*/

#include "Shellminator.hpp"

// Necessary includes
#include "Commander-API.hpp"
#include "Commander-API-Commands.hpp"

// Create a Shellminator object, and initialize it to use WiFiServer
Shellminator shell( &Serial );

// We have to create an object from Commander class.
Commander commander;

// Commander API-tree
Commander::API_t API_tree[ 14 ];

void setup() {

  __FlashStringHelper *logo = F(
    "   _____ __         ____          _             __            \r\n"
    "  / ___// /_  ___  / / /___ ___  (_)___  ____ _/ /_____  _____\r\n"
    "  \\__ \\/ __ \\/ _ \\/ / / __ `__ \\/ / __ \\/ __ `/ __/ __ \\/ ___/\r\n"
    " ___/ / / / /  __/ / / / / / / / / / / / /_/ / /_/ /_/ / /    \r\n"
    "/____/_/ /_/\\___/_/_/_/ /_/ /_/_/_/ /_/\\__,_/\\__/\\____/_/     \r\n"
    "                                                              \r\n"
  );

  API_ELEMENT_P_MILLIS( API_tree[ 0 ] );
  API_ELEMENT_P_MICROS( API_tree[ 1 ] );
  API_ELEMENT_P_UPTIME( API_tree[ 2 ] );
  API_ELEMENT_P_PINMODE( API_tree[ 3 ] );
  API_ELEMENT_P_DIGITALWRITE( API_tree[ 4 ] );
  API_ELEMENT_P_DIGITALREAD( API_tree[ 5 ] );
  API_ELEMENT_P_ANALOGREAD( API_tree[ 6 ] );
  API_ELEMENT_P_NEOFETCH( API_tree[ 7 ] );
  API_ELEMENT_P_SIN( API_tree[ 8 ] );
  API_ELEMENT_P_COS( API_tree[ 9 ] );
  API_ELEMENT_P_ABS( API_tree[ 10 ] );
  API_ELEMENT_P_RANDOM( API_tree[ 11 ] );
  API_ELEMENT_P_NOT( API_tree[ 12 ] );
  API_ELEMENT_P_REBOOT( API_tree[ 13 ] );

  // Initialize Serial with 115200 baudrate.
  Serial.begin( 115200 );

  // If you using Atmega32U4, the code will wait, until
  // you open the serial port.
  while( !Serial );

  // Clear the terminal
  shell.clear();

  // Attach the logo.
  shell.attachLogo( logo );

  // Print start message
  Serial.println( F( "Program begin..." ) );

  // There is an option to attach a debug channel to Commander.
  // It can be handy to find any problems during the initialization
  // phase. In this example we will use Serial for this.
  commander.attachDebugChannel( &Serial );

  // At start, Commander does not know anything about our commands.
  // We have to attach the API_tree array from the previous steps
  // to Commander to work properly.
  commander.attachTree( API_tree );

  // Initialize Commander.
  commander.init();

  shell.attachCommander( &commander );

  // initialize shell object.
  shell.begin( "arnold" );

}

void loop() {

  shell.update();

}
