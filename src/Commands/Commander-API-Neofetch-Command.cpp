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

void set_neofetch_field_format( Stream* response ){
    if( response == NULL ){
        return;
    }
    response -> print( __CONST_TXT__( NEOFETCH_FIELD_FORMAT ) );
}

void reset_neofetch_field_format( Stream* response ){
    if( response == NULL ){
        return;
    }
    response -> print( __CONST_TXT__( "\033[0m" ) );
}

bool commander_neofetch_func( char *args, Stream *response, void* parent ){

    int i;
    uint32_t rowCounter = 0;

    if( response == NULL ){
        return false;
    }

    //--- Print the logo first.
    response -> print( __CONST_TXT__( NEOFETCH_LOGO_FORMAT ) );
    response -> print( __CONST_TXT__( NEOFETCH_TEXT ) );
    reset_neofetch_field_format( response );

    // Move the cursor up as much as heigh is the logo.
    response -> print( __CONST_TXT__( "\033[" ) );
    response -> print( NEOFETCH_LOGO_HEIGHT );
    response -> print( __CONST_TXT__( "A\033[" ) );
    // Move the cursor right as much as wide is the logo.
    response -> print( NEOFETCH_LOGO_WIDTH );
    response -> print( __CONST_TXT__( "C" ) );

    //--- Print the firmware information
    set_neofetch_field_format( response );
    response -> print( __CONST_TXT__( "FW: " ) );
    reset_neofetch_field_format( response );
    response -> print( __CONST_TXT__( NEOFETCH_FW_NAME ) );
    response -> print( __CONST_TXT__( "\r\n\033[" ) );
    // Move the cursor right as much as wide is the logo.
    response -> print( NEOFETCH_LOGO_WIDTH );
    response -> print( __CONST_TXT__( "C" ) );
    rowCounter++;

    //--- Print the CPU information
    set_neofetch_field_format( response );
    response -> print( __CONST_TXT__( "CPU: " ) );
    reset_neofetch_field_format( response );
    response -> print( __CONST_TXT__( NEOFETCH_CPU_TYPE ) );
    response -> print( __CONST_TXT__( "\r\n\033[" ) );
    // Move the cursor right as much as wide is the logo.
    response -> print( NEOFETCH_LOGO_WIDTH );
    response -> print( __CONST_TXT__( "C" ) );
    rowCounter++;

    //--- Print the compiler information
    set_neofetch_field_format( response );
    response -> print( __CONST_TXT__( "Compiler: " ) );
    reset_neofetch_field_format( response );
    response -> print( __CONST_TXT__( NEOFETCH_COMPILER ) );
    response -> print( __CONST_TXT__( "\r\n\033[" ) );
    // Move the cursor right as much as wide is the logo.
    response -> print( NEOFETCH_LOGO_WIDTH );
    response -> print( __CONST_TXT__( "C" ) );
    rowCounter++;

    //--- Print the compile date information
    set_neofetch_field_format( response );
    response -> print( __CONST_TXT__( "Compile Date: " ) );
    reset_neofetch_field_format( response );
    response -> print( __CONST_TXT__( NEOFETCH_COMPILE_DATE ) );
    response -> print( __CONST_TXT__( "\r\n\033[" ) );
    // Move the cursor right as much as wide is the logo.
    response -> print( NEOFETCH_LOGO_WIDTH );
    response -> print( __CONST_TXT__( "C" ) );
    rowCounter++;

    //--- Print the author information
    set_neofetch_field_format( response );
    response -> print( __CONST_TXT__( "Author: " ) );
    reset_neofetch_field_format( response );
    response -> print( __CONST_TXT__( NEOFETCH_AUTHOR ) );
    response -> print( __CONST_TXT__( "\r\n\033[" ) );
    // Move the cursor right as much as wide is the logo.
    response -> print( NEOFETCH_LOGO_WIDTH );
    response -> print( __CONST_TXT__( "C" ) );
    rowCounter++;

    //--- Print the license information
    set_neofetch_field_format( response );
    response -> print( __CONST_TXT__( "License: " ) );
    reset_neofetch_field_format( response );
    response -> print( __CONST_TXT__( NEOFETCH_LICENSE ) );
    response -> print( __CONST_TXT__( "\r\n\r\n\033[" ) );
    // Move the cursor right as much as wide is the logo.
    response -> print( NEOFETCH_LOGO_WIDTH );
    response -> print( __CONST_TXT__( "C" ) );
    rowCounter+=2;

    //--- Print color test for dimmed
    for( i = 30; i < 38; i++ ){
        response -> print( __CONST_TXT__( "\033[2;" ) );
        response -> print( i );
        response -> print( "m\u2588\u2588" );
    }
    response -> print( __CONST_TXT__( "\r\n\033[" ) );
    // Move the cursor right as much as wide is the logo.
    response -> print( NEOFETCH_LOGO_WIDTH );
    response -> print( __CONST_TXT__( "C" ) );

    //--- Print color test for bright
    for( i = 30; i < 38; i++ ){
        response -> print( __CONST_TXT__( "\033[1;" ) );
        response -> print( i );
        response -> print( "m\u2588\u2588" );
    }

    // Set the cursor to bottom
    if( rowCounter > NEOFETCH_LOGO_HEIGHT ){
        // If the number of information lines is greater, than the logo height,
        // we are finished.
        return true;
    }
    response -> print( __CONST_TXT__( "\033[" ) );
    response -> print( NEOFETCH_LOGO_HEIGHT - rowCounter );
    response -> print( 'B' );

    return true;

}
