
/*
 * Created on 2023.Jun.25
 *
 * Copyright (c) 2023 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2023.Aug.07
 *
 * This is a simple example, that demonstrates how
 * to use the base functionality of th Commander-API.
*/


// std library.
#include <stdio.h>
#include <stdlib.h>

// Core System Functions.
#include "System.h"

// Contains a modified Stream class for communication.
#include "stdioStream.hpp"

// Contains Emscripten related functions.
#include <emscripten.h>

// Necessary includes
#include "Commander-API.hpp"
#include "Commander-IO.hpp"
#include "Commander-API-Commands.hpp"
#include <math.h>


// Use stdio as Channel.
stdioStream stdioChannel;

// We have to create an object from Commander class.
Commander commander;

// Add echo and env commands to the API tree.
Commander::API_t API_tree[] = {
    API_ELEMENT_ECHO,
    API_ELEMENT_ENV
};

// Global system variables.
float constPI = M_PI;
int adcValue = 532;
char boardID[] = "This is a very special board.";
char swVersion[] = "V0.0.1";

// System Variable array. This array will store the
// name and the instance of the system variables.
Commander::SystemVariable_t systemVariables[] = {
    systemVariableFloat( constPI ),
    systemVariableInt( adcValue ),
    systemVariableString( boardID ),
    systemVariableString( swVersion )
};

// This is a buffer to hold the incoming command.
char commandFromSerial[ 30 ];

// This variable tracks the location of the next free
// space in the commandFromSerial buffer.
uint8_t commandIndex = 0;


// Infinite Loop.
void loop();

// Init Section.
void setup();



// Main program.
int main(){

    // Call init section.
    setup();

    // Setup the infinite loop and start it.
    emscripten_set_main_loop( loop, 0, 1 );

    // If we are lucky, the code never reaches this.
    return 0;

}



void setup(){

    // Init code.

    // There is an option to attach a debug channel to Commander.
    // It can be handy to find any problems during the initialization
    // phase. In this example, we will use stdioChannel for this.
    commander.attachDebugChannel( &stdioChannel );

    // At start, Commander does not know anything about our commands.
    // We have to attach the API_tree array from the previous steps
    // to Commander to work properly.
    commander.attachTree( API_tree );

    // Attach the system variable array to the command parser.
    Commander::attachVariables( systemVariables );

    // After we attached the API_tree, Commander has to initialize
    // itself for the fastest runtime possible. It creates a balanced
    // binary tree from the API_tree to boost the search speed.
    // This part uses some recursion, to make the code space small.
    // But recursion is a bit stack hungry, so please initialize
    // Commander at the beginning of your code to prevent stack-overlow.
    commander.init();

    stdioChannel.println();
    stdioChannel.println( "---- Init Finished ----" );
    stdioChannel.println();

    stdioChannel.println( "Type something" );
    stdioChannel.print( "$: " );



}

void loop(){

    // Infinite loop.

    // Check if there is any data incoming.
    while( stdioChannel.available() ){

        // Read the next incoming character.
        char c = stdioChannel.read();

        // Every command from Serial is terminated with a new-line
        // character. If a new-line character arrives, we have to
        // terminate the string in the commandFromSerial buffer,
        // and execute it. After execution, we have to reset the
        // commandIndex counter to zero.
        if( c == '\r' ){
            commandFromSerial[ commandIndex ] = '\0';
            stdioChannel.println();
            commander.execute( commandFromSerial, &stdioChannel );
            commandIndex = 0;
            stdioChannel.print( "$: " );
        }

        // If we have a carriage-return character we simply
        // ignore it.
        else if( c == '\n' ){
            continue;
        }

        // Handle backspace events.
        else if( ( c == '\b' ) || ( c == 127 ) ){
            if( commandIndex > 0 ){
                commandIndex--;
                stdioChannel.print( "\b \b" );
            }
        }

        // Every other case we just put the data to the next
        // free space in the commandFromSerial buffer, increment
        // the commandIndex, and check if it wants to overflow.
        else{
            commandFromSerial[ commandIndex ] = c;
            commandIndex++;
            if( commandIndex >= sizeof( commandFromSerial ) ){
                commandIndex = sizeof( commandFromSerial ) - 1;
            }
            else{
                stdioChannel.print( c );
            }
        }

    }



}