
/*
 * Created on June 25 2023
 *
 * Copyright (c) 2023 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Shellminator project.
 * Modified 2023.05.13
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

// Necessary includes.
#include "Commander-API.hpp"
#include "Commander-IO.hpp"

// Argument parser module.
#include "Commander-Arguments.hpp"


// Use stdio as Channel.
stdioStream stdioChannel;



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

    const char* argsToParseSimple = "Jack -h 174 -w 71";

    Argument name( argsToParseSimple, 0 );
    Argument height( argsToParseSimple, 'h', "height" );
    Argument weight( argsToParseSimple, 'w', "weight" );

    height.parseInt();
    weight.parseInt();

    stdioChannel.print( "Parsing this arguments: " );
    stdioChannel.println( argsToParseSimple );

    stdioChannel.print( "\theight: " );

    // Check if the height argument is parsed correctly.
    if( height ){
        stdioChannel.println( (int)height );
    }
    else{
        stdioChannel.println( "Error!" );
    }

    stdioChannel.print( "\tweight: " );

    // Check if the weight argument is parsed correctly.
    if( weight ){
        stdioChannel.println( (int)weight );
    }
    else{
        stdioChannel.println( "Error!" );
    }

    const char* argsToParseDetailed = "Jack --height 174 --weight 71";

    name = Argument( argsToParseDetailed, 0 );
    height = Argument( argsToParseDetailed, 'h', "height" );
    weight = Argument( argsToParseDetailed, 'w', "weight" );

    stdioChannel.print( "Parsing this arguments: " );
    stdioChannel.println( argsToParseDetailed );

    stdioChannel.print( "\theight: " );

    // Check if the height argument is parsed correctly.
    if( height ){
        stdioChannel.println( (int)height );
    }
    else{
        stdioChannel.println( "Error!" );
    }

    stdioChannel.print( "\tweight: " );

    // Check if the weight argument is parsed correctly.
    if( weight ){
        stdioChannel.println( (int)weight );
    }
    else{
        stdioChannel.println( "Error!" );
    }



}

void loop(){

    // Infinite loop.




}