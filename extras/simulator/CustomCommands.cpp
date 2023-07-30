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

#include "CustomCommands.hpp"
#include "Commander-API-Commands.hpp"

void commander_pinMode_func( char *args, Stream *response, void* parent ){

    Argument pin( args, 'p', "pin" );
    Argument outputFlag( args, 'o', "output" );
    Argument inputFlag( args, 'i', "input" );

    pin.parseInt();
    outputFlag.find();
    inputFlag.find();

    if( !pin ){
        Commander::printArgumentError( response );
        if( response != NULL ){
            response -> print( __CONST_TXT__( " Pin has to be defined!" ) );
        }
        return;
    }

    if( outputFlag.isFound() && inputFlag.isFound() ){
        Commander::printArgumentError( response );
        if( response != NULL ){
            response -> print( __CONST_TXT__( " Mode can not be input and output at the same time!" ) );
        }
        return;
    }

}

void commander_digitalWrite_func( char *args, Stream *response, void* parent ){

    Argument pin( args, 'p', "pin" );
    Argument highFlag( args, 'h', "high" );
    Argument lowFlag( args, 'l', "low" );

    pin.parseInt();
    highFlag.find();
    lowFlag.find();

    if( !pin ){
        Commander::printArgumentError( response );
        if( response != NULL ){
            response -> print( __CONST_TXT__( " Pin has to be defined!" ) );
        }
        return;
    }

    if( highFlag.isFound() && lowFlag.isFound() ){
        Commander::printArgumentError( response );
        if( response != NULL ){
            response -> print( __CONST_TXT__( " State can not be high and low at the same time!" ) );
        }
        return;
    }

}

void commander_digitalRead_func( char *args, Stream *response, void* parent ){

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
        return;
    }

    if( txtFlag.isFound() ){

        response -> print( state ? __CONST_TXT__( "HIGH" ) : __CONST_TXT__( "LOW" ) );

    }

    else{

        response -> print( state );

    }

}