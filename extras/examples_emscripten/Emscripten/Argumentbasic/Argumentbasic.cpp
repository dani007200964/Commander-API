
/*
 * Created on 2023.Jun.25
 *
 * Copyright (c) 2023 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2023.Jun.30
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

    // Simple argument name example
    const char* argsToParseSimple = "Jack -h 174 -w 71";

    // String arguments require a buffer to store the data.
    char nameBuffer[ 30 ];

    // Create an Argument object for each argument
    Argument name( argsToParseSimple, 0 );
    Argument height( argsToParseSimple, 'h', "height" );
    Argument weight( argsToParseSimple, 'w', "weight" );

    // Try to parse each argument.
    name.parseString( nameBuffer );
    height.parseInt();
    weight.parseInt();

    stdioChannel.print( "Parsing these arguments: " );
    stdioChannel.println( argsToParseSimple );

    stdioChannel.print( "\tname: " );

    // Check if the name argument is parsed correctly.
    if( name ){
        stdioChannel.println( (char*)name );
    }
    else{
        stdioChannel.println( "Error!" );
    }

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

    // Detailed argument name example
    const char* argsToParseDetailed = "\"Jack Black\" --height 174 --weight 71";

    // Create an Argument object for each argument
    name = Argument( argsToParseDetailed, 0 );
    height = Argument( argsToParseDetailed, 'h', "height" );
    weight = Argument( argsToParseDetailed, 'w', "weight" );

    // Try to parse each argument.
    name.parseString( nameBuffer );
    height.parseInt();
    weight.parseInt();

    stdioChannel.print( "Parsing these arguments: " );
    stdioChannel.println( argsToParseDetailed );

    stdioChannel.print( "\tname: " );

    // Check if the name argument is parsed correctly.
    if( name ){
        stdioChannel.println( (char*)name );
    }
    else{
        stdioChannel.println( "Error!" );
    }

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