
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
#include <math.h>


// Use stdio as Channel.
stdioStream stdioChannel;

// We have to create an object from Commander class.
Commander commander;

// Add echo and env commands to the API tree.
Commander::API_t API_tree[] = {
    API_ELEMENT_REBOOT,
    API_ELEMENT_ECHO,
    API_ELEMENT_ENV,
    API_ELEMENT_MICROS,
    API_ELEMENT_MILLIS,
    API_ELEMENT_UPTIME,
    API_ELEMENT_NEOFETCH,
    API_ELEMENT_PINMODE,
    API_ELEMENT_DIGITALWRITE,
    API_ELEMENT_DIGITALREAD,
    API_ELEMENT_ANALOGREAD,
    API_ELEMENT_ANALOGWRITE,
    API_ELEMENT_SIN,
    API_ELEMENT_COS,
    API_ELEMENT_ABS,
    API_ELEMENT_RANDOM,
    API_ELEMENT_NOT
};

// This is a buffer to hold the incoming command.
char commandFromSerial[ 30 ];

// This variable tracks the location of the next free
// space in the commandFromSerial buffer.
uint8_t commandIndex = 0;




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
    // Commander at the beginning of your code to prevent stack-overlow.
    commander.init();

    stdioChannel.println();
    stdioChannel.println( "---- Init Finished ----" );
    stdioChannel.println();

    stdioChannel.println( "Type something" );
    stdioChannel.print( "$: " );



    // Infinite loop.
    while( 1 ){


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

    return 0;

}
