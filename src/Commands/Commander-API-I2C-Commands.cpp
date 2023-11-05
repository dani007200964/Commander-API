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
    #include "Wire.h"
#endif

bool commander_i2cScan_func( char *args, Stream *response, void* parent ){

    uint8_t error;
    uint8_t address;

    uint8_t x = 0;
    uint8_t lineCounter = 1;

    char printBuffer[ 10 ];

    // If response is not available, return.
    if( response == NULL ){
        return false;
    }

    response -> println( __CONST_TXT__( "     0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F" ) );
    response -> print( __CONST_TXT__( "00:" ) );

    for( address = 0x00; address < 128; address++ ){

        #ifdef ARDUINO
            Wire.beginTransmission( address );
            error = Wire.endTransmission();
            //error = 0;
        #else
            error != error;
        #endif

        if( error == 0 ){

            snprintf( printBuffer, sizeof( printBuffer ) - 1, " %02X", address );
            response -> print( printBuffer );
            
        }

        else{

            response -> print( __CONST_TXT__( " --" ) );      
            
        }

        x++;

        if( x >= 16 ){

            x = 0;

            response -> println();

            if( lineCounter < 8 ){
            
            snprintf( printBuffer, sizeof( printBuffer ) - 1, "%d0:", lineCounter );
            response -> print( printBuffer );
            lineCounter++;
            
            }
            
        }

    }

    return true;
}