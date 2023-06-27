/*
 * Created on June 25 2022
 *
 * Copyright (c) 2020 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2022.06.25
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


#ifndef COMMANDER_ARGUMENTS_HPP_
#define COMMANDER_ARGUMENTS_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Argument{

public:    

    Argument( const char* source_p, int place_p );
    Argument( const char* source_p, char shortName_p );
    Argument( const char* source_p, char shortName_p, const char* longName_p );

    operator int();
    operator bool();

    bool parseInt();
    bool parseFloat();
    bool parseString();

private:

    const char* source = NULL;
    int sourceSize = -1;

    int place = -1;
    char shortName = '\0';
    const char* longName = NULL;

    bool parsed = false;
    int intResult;
    int floatResult;

    int findShortName();
    int findLongName();
    int findPlace();

    int substring( char* str1, char* str2 );

};

#endif