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

bool commander_neofetch_func( char *args, Stream *response, void* parent ){

  uint32_t rowCounter = 0;

  response -> print( __CONST_TXT__( NEOFETCH_TEXT ) );

  response -> print( __CONST_TXT__( "\033[" ) );
  response -> print( NEOFETCH_LOGO_HEIGHT );
  response -> print( __CONST_TXT__( "A\033[51C" ) );

  response -> print( __CONST_TXT__( "\033[1;31mFW\033[0;37m: " ) );
  response -> print( __CONST_TXT__( NEOFETCH_FW_NAME ) );
  response -> print( __CONST_TXT__( "\r\n\033[51C" ) );
  rowCounter++;

  response -> print( __CONST_TXT__( "\033[1;31mCPU\033[0;37m: " ) );
  response -> print( __CONST_TXT__( NEOFETCH_CPU_TYPE ) );
  response -> print( __CONST_TXT__( "\r\n\033[51C" ) );
  rowCounter++;

  response -> print( __CONST_TXT__( "\033[1;31mCompiler\033[0;37m: GCC " ) );
  response -> print( __CONST_TXT__( NEOFETCH_COMPILER ) );
  response -> print( __CONST_TXT__( "\r\n\033[51C" ) );
  rowCounter++;

  response -> print( __CONST_TXT__( "\033[1;31mCompile Date\033[0;37m: " ) );
  response -> print( __CONST_TXT__( NEOFETCH_COMPILE_DATE ) );
  response -> print( __CONST_TXT__( "\r\n\033[51C" ) );
  rowCounter++;

  response -> print( __CONST_TXT__( "\033[1;31mTerminal\033[0;37m: " ) );
  response -> print( __CONST_TXT__( NEOFETCH_TERMINAL ) );
  response -> print( __CONST_TXT__( "\r\n\033[51C" ) );
  rowCounter++;

  response -> print( __CONST_TXT__( "\033[1;31mCMD Parser\033[0;37m: " ) );
  response -> print( __CONST_TXT__( NEOFETCH_COMMAND_PARSER ) );
  response -> print( __CONST_TXT__( "\r\n\033[51C" ) );
  rowCounter++;

  response -> print( __CONST_TXT__( "\033[1;31mAuthor\033[0;37m: " ) );
  response -> print( __CONST_TXT__( NEOFETCH_AUTHOR ) );
  response -> print( __CONST_TXT__( "\r\n\033[51C" ) );
  rowCounter++;

  response -> print( __CONST_TXT__( "\033[1;31mLicense\033[0;37m: " ) );
  response -> print( __CONST_TXT__( NEOFETCH_LICENSE ) );
  response -> print( __CONST_TXT__( "\r\n\033[51C" ) );
  rowCounter++;

  response -> print( __CONST_TXT__( "\033[" ) );
  response -> print( NEOFETCH_LOGO_HEIGHT - rowCounter );
  response -> print( 'B' );

  return true;

}
