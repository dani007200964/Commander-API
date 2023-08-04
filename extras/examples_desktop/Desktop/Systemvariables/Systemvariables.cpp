
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


// Use stdio as Channel.
stdioStream stdioChannel;





// Main program.
int main(){

    // System init section.
    if( setlocale(LC_ALL, NULL) == NULL ){

        wprintf( L"Error setting locale!\r\n" );

    }


    float reactor = 10.5;
    int index = 3;
    char text[] = "Hello bello";

    Commander::SystemVariable_t systemVariables[] = {
        systemVariableFloat( "reactor",  &reactor ),
        systemVariableInt( "index",  &index ),
        systemVariableString( "text",  text )
    };

    Commander::attachVariables( systemVariables );

    Commander::printSystemVariable( &stdioChannel, "reactor" );
    stdioChannel.println();

    Commander::printSystemVariable( &stdioChannel, "index" );
    stdioChannel.println();

    Commander::printSystemVariable( &stdioChannel, "text" );
    stdioChannel.println();



    // Infinite loop.
    while( 1 ){





    }

    return 0;

}
