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
#include <math.h>

#define DEG2RAD( x ) ( ( x ) * ( M_PI / 180.0 ) )
#define RAD2DEG( x ) ( ( x ) * ( 180.0 / M_PI ) )

bool commander_sin_func( char *args, Stream *response, void* parent ){

    // AVR microcontrollers has small amount of dynamic memory.
    // For this reason the built in commands do not support long
    // argument names on AVR platforms.
    #ifdef __AVR__
        Argument deg( args, 'd' );
        Argument rad( args, 'r' );
        Argument places( args, 'p' );
    #else
        Argument deg( args, 'd', "deg" );
        Argument rad( args, 'r', "rad" );
        Argument places( args, 'p', "places" );
    #endif

    // It will hold the result.
    float result;

    // It is used to calculate the correct decimal places.
    int resolution = 2;

    if( response == NULL ){
        return false;
    }

    deg.parseFloat();
    rad.parseFloat();
    places.parseInt();

    if( places ){

        if( (int)places < 1 ){
            Commander::printArgumentError( response );
            response -> print( __CONST_TXT__( " Decimal places has to be at least 1!" ) );
            return false;
        }

        resolution = (int)places;

    }

    if( deg && !rad ){
        result = sin( DEG2RAD( (float)deg ) );
    }

    else if( !deg && rad ){
        result = sin( (float)rad );
    }

    else{
        Commander::printArgumentError( response );
        response -> print( __CONST_TXT__( " degree or radian parameter has to be defined, but not both!" ) );
        return false;
    }

    response -> print( result, resolution );

    return true;
}

bool commander_cos_func( char *args, Stream *response, void* parent ){

    // AVR microcontrollers has small amount of dynamic memory.
    // For this reason the built in commands do not support long
    // argument names on AVR platforms.
    #ifdef __AVR__
        Argument deg( args, 'd' );
        Argument rad( args, 'r' );
        Argument places( args, 'p' );
    #else
        Argument deg( args, 'd', "deg" );
        Argument rad( args, 'r', "rad" );
        Argument places( args, 'p', "places" );
    #endif

    // It will hold the result.
    float result;

    // It is used to calculate the correct decimal places.
    int resolution = 2;

    if( response == NULL ){
        return false;
    }

    deg.parseFloat();
    rad.parseFloat();
    places.parseInt();

    if( places ){

        if( (int)places < 1 ){
            Commander::printArgumentError( response );
            response -> print( __CONST_TXT__( " Decimal places has to be at least 1!" ) );
            return false;
        }

        resolution = (int)places;

    }

    if( deg && !rad ){
        result = cos( DEG2RAD( (float)deg ) );
    }

    else if( !deg && rad ){
        result = cos( (float)rad );
    }

    else{
        Commander::printArgumentError( response );
        response -> print( __CONST_TXT__( " degree or radian parameter has to be defined, but not both!" ) );
        return false;
    }

    response -> print( result, resolution );

    return true;
}

bool commander_abs_func( char *args, Stream *response, void* parent ){

    // AVR microcontrollers has small amount of dynamic memory.
    // For this reason the built in commands do not support long
    // argument names on AVR platforms.
    #ifdef __AVR__
        Argument places( args, 'p' );
    #else
        Argument places( args, 'p', "places" );
    #endif

    Argument number( args, 0 );

    // It is used to calculate the correct decimal places.
    int resolution = 2;

    if( response == NULL ){
        return false;
    }

    number.parseFloat();
    places.parseInt();

    if( places ){

        if( (int)places < 1 ){
            Commander::printArgumentError( response );
            response -> print( __CONST_TXT__( " Decimal places has to be at least 1!" ) );
            return false;
        }

        resolution = (int)places;

    }

    if( (float)number < 0.0f ){
        response -> print( -1.0 * (float)number, resolution );
    }
    else{
        response -> print( (float)number, resolution );
    }   

    return true;
}

bool commander_random_func( char *args, Stream *response, void* parent ){

    // AVR microcontrollers has small amount of dynamic memory.
    // For this reason the built in commands do not support long
    // argument names on AVR platforms.
    #ifdef __AVR__
        Argument upper( args, 'u' );
        Argument lower( args, 'l' );
    #else
        Argument upper( args, 'u', "upper" );
        Argument lower( args, 'l', "lower" );
    #endif

    if( response == NULL ){
        return false;
    }

    upper.parseInt();
    lower.parseInt();

    if( !upper ){
        Commander::printArgumentError( response );
        response -> print( __CONST_TXT__( " Upper value has to be defined!" ) );
        return false;
    }

    if( lower ){
        response -> print( random( (int)lower, (int)upper ) );
    }

    else{
        response -> print( random( (int)upper ) );
    }

    return true;
}

bool commander_not_func( char *args, Stream *response, void* parent ){

    Argument number( args, 0 );

    if( response == NULL ){
        return false;
    }

    number.parseInt();

    if( (int)number == 0 ){
        response -> print( 1 );
    }
    else{
        response -> print( 0 );
    }   

    return true;
}