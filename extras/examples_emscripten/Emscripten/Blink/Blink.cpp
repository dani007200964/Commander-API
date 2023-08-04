
/*
 * Created on 2023.July.30
 *
 * Copyright (c) 2023 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2023.Aug.04
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


// Use stdio as Channel.
stdioStream stdioChannel;

// We have to create an object from Commander class.
Commander commander;

Commander::API_t API_tree[] = {
    API_ELEMENT_PINMODE,
    API_ELEMENT_DIGITALREAD,
    API_ELEMENT_DIGITALWRITE
};


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

    // After we attached the API_tree, Commander has to initialize
    // itself for the fastest runtime possible. It creates a balanced
    // binary tree from the API_tree to boost the search speed.
    // This part uses some recursion, to make the code space small.
    // But recursion is a bit stack hungry, so please initialize
    // Commander at the beginning of your code to prevent stack-overflow.
    commander.init();

    stdioChannel.println();
    stdioChannel.println( __CONST_TXT__( "---- Init Finished ----" ) );
    stdioChannel.println();

    // List all the available commands.
    stdioChannel.println( __CONST_TXT__( "Executing 'help -d' command:" ) );
    commander.execute( "help -d", &stdioChannel );
    stdioChannel.println();

    // Set pin 13 to output. Usually the LED is on this pin.
    stdioChannel.println( __CONST_TXT__( "Executing 'pinMode -p 13 -o' command:" ) );
    commander.execute( "pinMode -p 13 -o", &stdioChannel );
    stdioChannel.println();



}

void loop(){

    // Infinite loop.

    // Set pin 13 to logic high. It will turn on the built in LED on most boards.
    stdioChannel.println( __CONST_TXT__( "Executing 'digitalWrite -p 13 -h' command:" ) );
    commander.execute( "digitalWrite -p 13 -h", &stdioChannel );
    stdioChannel.println();

    // Read the state of pin 13.
    stdioChannel.println( __CONST_TXT__( "Executing 'digitalRead -p 13' command:" ) );
    commander.execute( "digitalRead -p 13", &stdioChannel );
    stdioChannel.println();

    // Delay one seconds.
    delay( 1000 );

    // Set pin 13 to logic low. It will turn off the built in LED on most boards.
    stdioChannel.println( __CONST_TXT__( "Executing 'digitalWrite -p 13 -l' command:" ) );
    commander.execute( "digitalWrite -p 13 -h", &stdioChannel );
    stdioChannel.println();

    // Read the state of pin 13.
    stdioChannel.println( __CONST_TXT__( "Executing 'digitalRead -p 13' command:" ) );
    commander.execute( "digitalRead -p 13", &stdioChannel );
    stdioChannel.println();

    // Delay one seconds.
    delay( 1000 );



}