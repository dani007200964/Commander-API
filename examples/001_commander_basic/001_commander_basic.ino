/*
 * Created on Aug 10 2020
 *
 * Copyright (c) 2023 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2025.02.22
*/

#include "Commander-API.hpp"

#define COMMAND_SIZE 30

// We have to create an object from Commander class.
Commander commander;

// Command callbacks
bool cat_func( char *args, CommandCaller* caller );
bool dog_func( char *args, CommandCaller* caller );

// Command tree
Commander::systemCommand_t API_tree[] = {
    systemCommand( "cat", "Description for cat command.", cat_func ),
    systemCommand( "dog", "Description for dog command.", dog_func )
};

// This buffer is used to store command from Serial port.
char commandBuffer[ COMMAND_SIZE ];

// System init section.
void setup(){
    Serial.begin(115200);

    commander.attachTree( API_tree );
    commander.init();

    Serial.println();
    Serial.println( "---- Init Finished ----" );
    Serial.println();

    Serial.println( "Type something" );
    Serial.print( "$: " );
}

// Infinite loop.
void loop(){
    commander.update( commandBuffer, COMMAND_SIZE, &Serial );
}

/// This is an example function for the cat command
bool cat_func(char *args, CommandCaller* caller ){
    caller -> print( "Hello from cat function!\r\n" );
    return true;
}

/// This is an example function for the dog command
bool dog_func(char *args, CommandCaller* caller ){
    caller -> print( "Hello from dog function!\r\n" );
    return true;
}