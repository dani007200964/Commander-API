
/*
 * Created on 2023.Jun.25
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

// Necessary includes.
#include "Commander-API.hpp"
#include "Commander-IO.hpp"


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

    float reactor = 10.5;
    int index = 3;
    char text[] = "Hello bello";

    Commander::SystemVariable_t systemVariables[] = {
        systemVariable( "reactor", Commander::VARIABLE_FLOAT, &reactor ),
        systemVariable( "index", Commander::VARIABLE_INT, &index ),
        systemVariable( "text", Commander::VARIABLES_STRING, text )
    };

    Commander::attachVariables( systemVariables );

    Commander::SystemVariable_t* var = Commander::getSystemVariable( "reactor" );

    if( var != NULL ){
        print( var -> data.f );
    }



}

void loop(){

    // Infinite loop.




}