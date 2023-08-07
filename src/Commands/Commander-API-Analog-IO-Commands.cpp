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

typedef struct{
    int adcPinIndex;
    int boardPinName;
} adcPinNameLookUp_t;

#if defined( ARDUINO_AVR_NANO )

adcPinNameLookUp_t adcLookUp[] = {
    { 0, A0 },
    { 1, A1 },
    { 2, A2 },
    { 3, A3 },
    { 4, A4 },
    { 5, A5 },
    { 6, A6 },
    { 7, A7 }
};

int adcLookUpSize = sizeof( adcLookUp ) / sizeof( adcLookUp[ 0 ] );

#elif defined( ARDUINO_AVR_UNO )

adcPinNameLookUp_t adcLookUp[] = {
    { 0, A0 },
    { 1, A1 },
    { 2, A2 },
    { 3, A3 },
    { 4, A4 },
    { 5, A5 }
};

int adcLookUpSize = sizeof( adcLookUp ) / sizeof( adcLookUp[ 0 ] );

#else

adcPinNameLookUp_t* adcLookUp;
int adcLookUpSize = 0;

#endif

void commander_analogRead_func( char *args, Stream *response, void* parent ){

    // AVR microcontrollers has small amount of dynamic memory.
    // For this reason the built in commands do not support long
    // argument names on AVR platforms.
    #ifdef __AVR__
        Argument pin( args, 'p' );
    #else
        Argument pin( args, 'p', "pin" );
    #endif

    pin.parseInt();
    int arduinoPin = -1;
    int value;
    int i;

    if( !pin ){
        Commander::printArgumentError( response );
        if( response != NULL ){
            response -> print( __CONST_TXT__( " Pin has to be defined!" ) );
        }
        return;
    }

    // If adcLookUpSize is zero, that means the pin identifier is
    // directly represent the ADC pin identifier.
    if( adcLookUpSize == 0 ){
        arduinoPin = pin;
    }

    // Otherwise we have to find the corresponding ADC pin from the look-up table.
    else{

        for( i = 0; i < adcLookUpSize; i++ ){

            if( adcLookUp[ i ].adcPinIndex == (int)pin ){
                arduinoPin = adcLookUp[ i ].boardPinName;
                break;
            }

        }

    }

    if( arduinoPin < 0 ){
        Commander::printArgumentError( response );
        if( response != NULL ){
            response -> print( __CONST_TXT__( " Incorrect pin identifier!" ) );
        }
        return;
    }

    value = analogRead( arduinoPin );

    response -> print( value );

}

#if defined( ARDUINO_AVR_NANO ) || defined( ARDUINO_AVR_UNO ) || defined( ARDUINO_AVR_MINI )

int pwmLookUp[] = {
    3,
    5,
    6,
    9,
    10,
    11
};

int pwmLookUpSize = sizeof( pwmLookUp ) / sizeof( pwmLookUp[ 0 ] );

#else

int* pwmLookUp;
int pwmLookUpSize = 0;

#endif

void commander_analogWrite_func( char *args, Stream *response, void* parent ){

    // AVR microcontrollers has small amount of dynamic memory.
    // For this reason the built in commands do not support long
    // argument names on AVR platforms.
    #ifdef __AVR__
        Argument pin( args, 'p' );
        Argument duty( args, 'd' );
        Argument value( args, 'v' );
    #else
        Argument pin( args, 'p', "pin" );
        Argument duty( args, 'd', "duty" );
        Argument value( args, 'v', "value" );
    #endif

    pin.parseInt();
    duty.parseInt();
    value.parseInt();

    int arduinoPin = -1;
    int i;
    int pwm = 0;

    if( !pin ){
        Commander::printArgumentError( response );
        if( response != NULL ){
            response -> print( __CONST_TXT__( " Pin has to be defined!" ) );
        }
        return;
    }

    if( duty && !value ){
        pwm = (int)duty;
    }

    else if( !duty && value ){
        pwm = (int)( (float)( value / 100.0 ) * 255.0 );
        if( pwm > 255 ){
            pwm = 255;
        }
        if( pwm < 0 ){
            pwm = 0;
        }
    }
    else{
        Commander::printArgumentError( response );
        if( response != NULL ){
            response -> print( __CONST_TXT__( " Duty or value has to be defined, but not both!" ) );
        }
        return;
    }

    // If adcLookUpSize is zero, that means the pin identifier is
    // directly represent the ADC pin identifier.
    if( pwmLookUpSize == 0 ){
        arduinoPin = pin;
    }

    // Otherwise we have to find the corresponding ADC pin from the look-up table.
    else{

        for( i = 0; i < adcLookUpSize; i++ ){

            if( pwmLookUp[ i ] == (int)pin ){
                arduinoPin = pwmLookUp[ i ];
                break;
            }

        }

    }

    if( arduinoPin < 0 ){
        Commander::printArgumentError( response );
        if( response != NULL ){
            response -> print( __CONST_TXT__( " Incorrect pin identifier!" ) );
        }
        return;
    }

    analogWrite( arduinoPin, pwm );

}


#endif