/*
 * Created on July. 30 2023
 *
 * Copyright (c) 2020 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2023.08.30
*/

/*
MIT License

Copyright (c) 2020 Daniel Hajnal

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "../Commander-API-Commands.hpp"

bool commander_echo_func( char *args, Stream *response, void* parent ){

    Commander::systemVariable_t* systemVariable;

    if( response == NULL ){
        return false;
    }

    // Check for system variable request. System variables
    // can be accessed with the '$' character.
    if( args[ 0 ] == '$' ){

        systemVariable = Commander::getSystemVariable( (const char*)&args[ 1 ] );

        if( systemVariable != NULL ){

            Commander::printSystemVariable( response, (const char*)&args[ 1 ], 5 );

        }

        else{

            response -> print( __CONST_TXT__( "System variable '" ) );
            response -> print( &args[ 1 ] );
            response -> print( __CONST_TXT__( "' NOT found!" ) );
            return false;

        }

    }

    else{

        response -> print( args );

    }

    return true;

}

bool commander_env_func( char *args, Stream *response, void* parent ){

    if( response == NULL ){
        return false;
    }

    Commander::printSystemVariables( response );
    return true;

}

Commander::systemVariable_t* exportTarget = NULL;

bool commander_exportTarget_func( char *args, Stream *response, void* parent ){

    Argument intNumber( args, 0 );
    Argument floatNumber( args, 0 );

    if( response == NULL ){
        return false;
    }

    intNumber.parseInt();
    floatNumber.parseFloat();

    if( strncmp( (const char*)args, "", 2 ) == 0 ){

        if( exportTarget == NULL ){
            response -> print( __CONST_TXT__( " Target for export is not set!" ) );
        }

        else{
            response -> print( __CONST_TXT__( "Export target is: " ) );
            response -> print( exportTarget -> name );
        }

        return true;

    }

    if( intNumber ){
        exportTarget = intNumber.getSystemVariable();
    }

    else if( floatNumber ){
        exportTarget = floatNumber.getSystemVariable();
    }

    else{
        Commander::printArgumentError( response );
        response -> print( __CONST_TXT__( " Variable '" ) );
        response -> print( args );
        response -> print( __CONST_TXT__( "' is not found in the system variables!" ) );
        return false;        
    }

    return true;

}

bool commander_export_func( char *args, Stream *response, void* parent ){

    Argument number( args, 0 );

    if( response == NULL ){
        return false;
    }

    if( exportTarget == NULL ){
        response -> print( __CONST_TXT__( " Target for export is not set!" ) );
        return false;
    }

    number.parseFloat();

    if( number ){

        if( ( exportTarget -> data.type ) == Commander::VARIABLE_FLOAT ){
            *( exportTarget -> data.data.floatData ) = (float)number;
        }

        else if( ( exportTarget -> data.type ) == Commander::VARIABLE_INT ){
            *( exportTarget -> data.data.intData ) = (int)( (float)number );
        }

        else{
            Commander::printArgumentError( response );
            response -> print( __CONST_TXT__( " Only integer or float targets are supported!" ) );
            return false;
        }
    }

    else{
        Commander::printArgumentError( response );
        response -> print( __CONST_TXT__( " Input has to be an integer or a float!" ) );
        return false;
    }
    
    return true;
}

// These commands only work inside the Arduino environment by default.
#ifdef ARDUINO

bool commander_reboot_func( char *args, Stream *response, void* parent ){

    response -> print( __CONST_TXT__( "Rebooting..." ) );

    #if defined( ESP32 ) || ( ESP8266 )

        ESP.restart();

    #elif __AVR__

        wdt_enable( WDTO_15MS );
        while( 1 );

    #else

        #warning Reboot function is not implemented on your platform. Please open Commander-API-System-Commands.cpp::commander_reboot_func and implement the reboot functionality.

    #endif

    return true;
}

bool commander_millis_func( char *args, Stream *response, void* parent ){

    char buff[ 20 ];

    sprintf( buff, "%lu", millis() );

    response -> print( buff );

    return true;
}

bool commander_micros_func( char *args, Stream *response, void* parent ){

    char buff[ 20 ];

    sprintf( buff, "%lu", micros() );

    response -> print( buff );

    return true;
}

bool commander_uptime_func( char *args, Stream *response, void* parent ){

    char buff[ 20 ];

    int day;
    int hour;
    int minute;
    unsigned long second;

    second = millis() / 1000;

    day = ( second / 24 ) / 3600;
    second %= (unsigned long)24 * 3600;

    hour = second / 3600;
    second %= 3600;

    minute = second / 60;
    second %= 60;

    snprintf( buff, sizeof( buff ), "%d days, %d:%02d:%02lu", day, hour, minute, second );

    response -> print( buff );

    return true;

}

#endif
