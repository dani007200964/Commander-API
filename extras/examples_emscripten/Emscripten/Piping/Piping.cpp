
/*
 * Created on 2023.Jun.25
 *
 * Copyright (c) 2023 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2023.Aug.10
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
    API_ELEMENT_MILLIS,
    API_ELEMENT_MICROS,
    API_ELEMENT_SIN
};

char pipeBuffer[ COMMANDER_PIPE_BUFFER_SIZE ];
commanderPipeChannel pipeChannel;


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

    commander.enablePipeModule( pipeBuffer, &pipeChannel );
    commander.enableFormatting();

    commander.init();

    stdioChannel.println();
    stdioChannel.println( "---- Init Finished ----" );
    stdioChannel.println();

    stdioChannel.println( __CONST_TXT__( "Executing 'millis | micros | sin' command:" ) );
    commander.execute( "millis | micros | sin", &stdioChannel );
    stdioChannel.println();



}

void loop(){

    // Infinite loop.




}