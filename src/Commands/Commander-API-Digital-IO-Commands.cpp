/*
 * Created on July. 30 2023
 *
 * Copyright (c) 2020 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2023.07.30
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

// These commands only work inside the Arduino environment by default.
#ifdef ARDUINO
    #include "Arduino.h"
#endif

bool commander_pinMode_func( char *args, Stream *response, void* parent ){

    // AVR microcontrollers has small amount of dynamic memory.
    // For this reason the built in commands do not support long
    // argument names on AVR platforms.
    #ifdef __AVR__
        Argument pin( args, 'p' );
        Argument outputFlag( args, 'o' );
        Argument inputFlag( args, 'i' );
    #else
        Argument pin( args, 'p', "pin" );
        Argument outputFlag( args, 'o', "output" );
        Argument inputFlag( args, 'i', "input" );
    #endif

    pin.parseInt();
    outputFlag.find();
    inputFlag.find();

    if( !pin ){
        Commander::printArgumentError( response );
        if( response != NULL ){
            response -> print( __CONST_TXT__( " Pin has to be defined!" ) );
        }
        return false;
    }

    if( inputFlag.isFound() && !outputFlag.isFound() ){
        #ifdef ARDUINO
            pinMode( (int)pin, INPUT );
        #endif
    }

    else if( !inputFlag.isFound() && outputFlag.isFound() ){
        #ifdef ARDUINO
            pinMode( (int)pin, OUTPUT );
        #endif
    }

    else{
        Commander::printArgumentError( response );
        if( response != NULL ){
            response -> print( __CONST_TXT__( " Pin mode has to be defined and can not be input and output at the same time!" ) );
        }
    }

    return true;
}

bool commander_digitalWrite_func( char *args, Stream *response, void* parent ){

    // AVR microcontrollers has small amount of dynamic memory.
    // For this reason the built in commands do not support long
    // argument names on AVR platforms.
    #ifdef __AVR__
        Argument pin( args, 'p' );
        Argument highFlag( args, 'h' );
        Argument lowFlag( args, 'l' );
    #else
        Argument pin( args, 'p', "pin" );
        Argument highFlag( args, 'h', "high" );
        Argument lowFlag( args, 'l', "low" );
    #endif

    pin.parseInt();
    highFlag.find();
    lowFlag.find();

    if( !pin ){
        Commander::printArgumentError( response );
        if( response != NULL ){
            response -> print( __CONST_TXT__( " Pin has to be defined!" ) );
        }
        return false;
    }

    if( lowFlag.isFound() && !highFlag.isFound() ){
        #ifdef ARDUINO
            digitalWrite( (int)pin, LOW );
        #endif
    }

    else if( !lowFlag.isFound() && highFlag.isFound() ){
        #ifdef ARDUINO
            digitalWrite( (int)pin, HIGH );
        #endif
    }

    else{
        Commander::printArgumentError( response );
        if( response != NULL ){
            response -> print( __CONST_TXT__( " Pin state has to be defined and can not be high and low at the same time!" ) );
        }
    }

    return true;
}

bool commander_digitalRead_func( char *args, Stream *response, void* parent ){

    // AVR microcontrollers has small amount of dynamic memory.
    // For this reason the built in commands do not support long
    // argument names on AVR platforms.
    #ifdef __AVR__
        Argument pin( args, 'p' );
        Argument txtFlag( args, 't' );
    #else
        Argument pin( args, 'p', "pin" );
        Argument txtFlag( args, 't', "text" );
    #endif

    pin.parseInt();
    txtFlag.find();
    int state;

    if( !pin ){
        Commander::printArgumentError( response );
        if( response != NULL ){
            response -> print( __CONST_TXT__( " Pin has to be defined!" ) );
        }
        return false;
    }

    #ifdef ARDUINO
        state = digitalRead( (int)pin );
    #else
        state = 0;
    #endif

    if( txtFlag.isFound() ){

        response -> print( state ? __CONST_TXT__( "HIGH" ) : __CONST_TXT__( "LOW" ) );

    }

    else{

        response -> print( state );

    }

    return true;
}