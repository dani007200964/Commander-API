
/*
 * Created on 2023.July.30
 *
 * Copyright (c) 2023 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2023.Aug.07
 *
 * This is a simple example, that demonstrates how
 * to use the base functionality of th Commander-API.
*/


#include <stdio.h>

#include <fcntl.h>
#ifdef _WIN32
#include <io.h>
#endif
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>

#include "System.h"

#include "stdioStream.hpp"

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




// Main program.
int main(){

    // System init section.
    if( setlocale(LC_ALL, NULL) == NULL ){

        wprintf( L"Error setting locale!\r\n" );

    }


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



    // Infinite loop.
    while( 1 ){


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

    return 0;

}
