
/*
 * Created on 2023.Jun.25
 *
 * Copyright (c) 2023 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2023.Oct.20
 *
 * This is a simple example, that demonstrates how
 * to use the base functionality of th Commander-API.
*/


// Necessary includes
#include "Commander-API.hpp"
#include "Commander-API-Commands.hpp"


#define COMMAND_SIZE 30

// We have to create an object from Commander class.
Commander commander;

// Add echo and env commands to the API tree.
Commander::systemCommand_t API_tree[] = {
    SYSTEM_COMMAND_MEMDUMP
};

char commandBuffer[ COMMAND_SIZE ];




// System init section.
void setup(){

    Serial.begin(115200);

    // There is an option to attach a debug channel to Commander.
    // It can be handy to find any problems during the initialization
    // phase. In this example, we will use Serial for this.
    commander.attachDebugChannel( &Serial );

    // At start, Commander does not know anything about our commands.
    // We have to attach the API_tree array from the previous steps
    // to Commander to work properly.
    commander.attachTree( API_tree );

    // After we attached the API_tree, Commander has to initialize
    // itself for the fastest runtime possible. It creates a balanced
    // binary tree from the API_tree to boost the search speed.
    // This part uses some recursion, to make the code space small.
    // But recursion is a bit stack hungry, so please initialize
    // Commander at the beginning of your code to prevent stack-overlow.
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
