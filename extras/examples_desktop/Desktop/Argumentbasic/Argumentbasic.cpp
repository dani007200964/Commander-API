
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

// Necessary includes.
#include "Commander-API.hpp"
#include "Commander-IO.hpp"

// Argument parser module.
#include "Commander-Arguments.hpp"


// Use stdio as Channel.
stdioStream stdioChannel;





// Main program.
int main(){

    // System init section.
    if( setlocale(LC_ALL, NULL) == NULL ){

        wprintf( L"Error setting locale!\r\n" );

    }


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



    // Infinite loop.
    while( 1 ){





    }

    return 0;

}
