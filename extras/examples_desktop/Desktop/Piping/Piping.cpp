
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
    API_ELEMENT_MILLIS,
    API_ELEMENT_MICROS,
    API_ELEMENT_SIN
};

char pipeBuffer[ COMMANDER_PIPE_BUFFER_SIZE ];
commanderPipeChannel pipeChannel;




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

    commander.enablePipeModule( pipeBuffer, &pipeChannel );
    commander.enableFormatting();

    commander.init();

    stdioChannel.println();
    stdioChannel.println( "---- Init Finished ----" );
    stdioChannel.println();

    stdioChannel.println( __CONST_TXT__( "Executing 'millis | micros | sin' command:" ) );
    commander.execute( "millis | micros | sin", &stdioChannel );
    stdioChannel.println();



    // Infinite loop.
    while( 1 ){





    }

    return 0;

}
