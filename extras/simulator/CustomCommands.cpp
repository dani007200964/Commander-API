/*
 * Created on Oct. 01 2022
 *
 * Copyright (c) 2020 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2022.10.04
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

#include "Commander-API-Commands.hpp"
#include "System.h"

bool commander_pinMode_func( char *args, Stream *response, void* parent ){

    Argument pin( args, 'p', "pin" );
    Argument outputFlag( args, 'o', "output" );
    Argument inputFlag( args, 'i', "input" );

    pin.parseInt();
    outputFlag.find();
    inputFlag.find();

    if( inputFlag.isFound() && !outputFlag.isFound() ){
    }

    else if( !inputFlag.isFound() && outputFlag.isFound() ){
    }

    else{
        Commander::printArgumentError( response );
        if( response != NULL ){
            response -> print( __CONST_TXT__( " Pin mode has to be defined and can not be input and output at the same time!" ) );
        }
        return false;
    }
    return true;
}

bool commander_digitalWrite_func( char *args, Stream *response, void* parent ){

    Argument pin( args, 'p', "pin" );
    Argument highFlag( args, 'h', "high" );
    Argument lowFlag( args, 'l', "low" );

    pin.parseInt();
    highFlag.find();
    lowFlag.find();

    if( lowFlag.isFound() && !highFlag.isFound() ){
    }

    else if( !lowFlag.isFound() && highFlag.isFound() ){
    }

    else{
        Commander::printArgumentError( response );
        if( response != NULL ){
            response -> print( __CONST_TXT__( " Pin state has to be defined and can not be high and low at the same time!" ) );
        }
        return false;
    }

    return true;
}

bool commander_digitalRead_func( char *args, Stream *response, void* parent ){

    Argument pin( args, 'p', "pin" );
    Argument txtFlag( args, 't', "text" );

    pin.parseInt();
    txtFlag.find();
    int state = 0;

    if( !pin ){
        Commander::printArgumentError( response );
        if( response != NULL ){
            response -> print( __CONST_TXT__( " Pin has to be defined!" ) );
        }
        return false;
    }

    if( txtFlag.isFound() ){

        response -> print( state ? __CONST_TXT__( "HIGH" ) : __CONST_TXT__( "LOW" ) );

    }

    else{

        response -> print( state );

    }

    return true;
}

bool commander_reboot_func( char *args, Stream *response, void* parent ){

    response -> println( __CONST_TXT__( "Rebooting..." ) );
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

bool commander_analogRead_func( char *args, Stream *response, void* parent ){

    Argument pin( args, 'p', "pin" );

    pin.parseInt();

    if( !pin ){
        Commander::printArgumentError( response );
        if( response != NULL ){
            response -> print( __CONST_TXT__( " Pin has to be defined!" ) );
        }
        return false;
    }

    if( (int)pin < 0 ){
        Commander::printArgumentError( response );
        if( response != NULL ){
            response -> print( __CONST_TXT__( " Incorrect pin identifier!" ) );
        }
        return false;
    }

    response -> print( 100 );

    return true;
}

bool commander_analogWrite_func( char *args, Stream *response, void* parent ){

    Argument pin( args, 'p', "pin" );
    Argument duty( args, 'd', "duty" );
    Argument value( args, 'v', "value" );

    pin.parseInt();
    duty.parseInt();
    value.parseInt();

    int arduinoPin;

    if( !pin ){
        Commander::printArgumentError( response );
        if( response != NULL ){
            response -> print( __CONST_TXT__( " Pin has to be defined!" ) );
        }
        return false;
    }

    if( duty && !value ){
    }

    else if( !duty && value ){
    }
    else{
        Commander::printArgumentError( response );
        if( response != NULL ){
            response -> print( __CONST_TXT__( " Duty or value has to be defined, but not both!" ) );
        }
        return false;
    }

    if( (int)pin < 0 ){
        Commander::printArgumentError( response );
        if( response != NULL ){
            response -> print( __CONST_TXT__( " Incorrect pin identifier!" ) );
        }
        return false;
    }

    return true;
}
