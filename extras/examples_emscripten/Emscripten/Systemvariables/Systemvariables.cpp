
/*
 * Created on 2023.Jun.25
 *
 * Copyright (c) 2023 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2023.Aug.09
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

    // Global system variables.
    float reactor = 10.5;
    int index = 3;
    char text[] = "Hello bello";

    // System Variable array. This array will store the
    // name and the instance of the system variables.
    Commander::SystemVariable_t systemVariables[] = {
        systemVariableFloat( reactor ),
        systemVariableInt( index ),
        systemVariableString( text )
    };

    // Float argument and its text.
    char floatArgumentText[] = "-f $reactor";
    Argument floatArgument( floatArgumentText, 'f', "float" );

    // Integer argument and its text.
    char intArgumentText[] = "-i $index";
    Argument intArgument( intArgumentText, 'i', "int" );

    // String argument, its text and a buffer for the result.
    char stringArgumentText[] = "-s $text";
    Argument stringArgument( stringArgumentText, 's', "str" );
    char stringArgumentBuffer[ 20 ];

    // Attach the system variable array to the command parser.
    Commander::attachVariables( systemVariables );

    // Try to find and print the system variables by their name.
    stdioChannel.print( __CONST_TXT__( "Value of 'reactor' system variable: " ) );
    Commander::printSystemVariable( &stdioChannel, "reactor" );
    stdioChannel.println();

    stdioChannel.print( __CONST_TXT__( "Value of 'index' system variable: " ) );
    Commander::printSystemVariable( &stdioChannel, "index" );
    stdioChannel.println();

    stdioChannel.print( __CONST_TXT__( "Value of 'text' system variable: " ) );
    Commander::printSystemVariable( &stdioChannel, "text" );
    stdioChannel.println();

    // Another way to access system variables is to use Arguments.
    // A system variable in the argument string can be accessed with the '$' character.

    stdioChannel.print( __CONST_TXT__( "Parsing float argument '" ) );
    stdioChannel.print( floatArgumentText );
    stdioChannel.print( __CONST_TXT__( "': " ) );
    floatArgument.parseFloat();

    if( floatArgument ){
        stdioChannel.println( (float)floatArgument );
    }

    stdioChannel.print( __CONST_TXT__( "Parsing int argument '" ) );
    stdioChannel.print( intArgumentText );
    stdioChannel.print( __CONST_TXT__( "': " ) );
    intArgument.parseInt();

    if( intArgument ){
        stdioChannel.println( (int)intArgument );
    }

    stdioChannel.print( __CONST_TXT__( "Parsing string argument '" ) );
    stdioChannel.print( stringArgumentText );
    stdioChannel.print( __CONST_TXT__( "': " ) );
    stringArgument.parseString( stringArgumentBuffer );

    if( stringArgument ){
        stdioChannel.println( (char*)stringArgument );
    }



}

void loop(){

    // Infinite loop.




}