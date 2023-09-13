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
#include <stdint.h>
#include "Commander-API.hpp"

/// Try to parse the defined string argument.
///
/// @note Please use this macro instead of parseStringFunction. It helps to avoid buffer overflow.
/// @param buffer Character array to store the extracted string data.
/// @returns It will return true if the parsing was successful.
#define parseString( buffer ) parseStringFunction( buffer, sizeof( buffer ) / sizeof( buffer[ 0 ] ) )

/// Argument class.
///
/// This class is made to parse simply __int__, __float__ and __string__
/// arguments from a source character array with the syntax style of the getopt library.
/// Sadly getopt can not be used with an embedded system, like an AVR. It is
/// too resource hungry. Also the C version of getopt does not support long argument
/// names. This is a lightweight argument parser and it can be used for 4 kinds of arguments:
/// * Place Dependent Argument - A place dependent argument is usually not optional.
///   Also it has a fixed place in the argument string.
///   It can be indexed like a regular array element from 0 to N-1 where N is the number of total arguments.
///   The argument string must be start with the fixed position regular arguments.
///   The first place dependent argument can be
///   optional. It is easy to detect if it exists or not. But it is a good practice
///   to allow __only the first__ place dependent argument to be optional.
/// * Optional Argument - These are optional settings for the command.
///   They must be identified by a name. The name can be short or long.
///   short: __-h__ long: __--help__. The short argument name always starts with
///   a dash character( '-' ). The long argument name always starts with two dash
///   characters( '--' ). After the dashes, the name comes. In case of a short argument
///   the name is always one characters long( this is why it is called short name ).
///   Both long and short names are case sensitive. After the name, at least one
///   white space character is required between the name and the value. Supported white space
///   characters are space or tabulator( ' ' or '\t' ).
/// * Place Independent Argument - The syntax is the same as the optional argument. Only difference
///   is, that this is required by the user code, the value is not optional.
/// * Flag - The flag is basically an optional argument without a value. The naming syntax is
///   the same. Only difference is, that the flag does not have a value. It can be used to indicate
///   something.
///
/// This library supports 3 kinds of values:
/// * __int__ - A regular int value. It is parsed by sscanf. It does not require an external buffer to parse
/// the data. The parsed value is stored internally after parsing.
/// * __float__ - A regular float value. It is parsed by atof. It does not require an external buffer to parse
/// the data. The parsed value is stored internally after parsing. Exponent notation is supported,
/// for more information check [here](https://en.cppreference.com/w/c/string/byte/atof).
/// * string - The string value parsing requires an external buffer to store the parsed string.
/// If the string value contains white space characters, the value must be encapsulated with brackets
/// like this: --text "this is a text with white space characters"
/// @note Be careful with long strings on low power devices like Arduino Uno / Nano with AVR chips.
class Argument{

public:    

    /// Constructor for place dependent argument.
    ///
    /// Use this constructor to create a place dependent argument object.
    /// @param source_p The source argument string.
    /// This character array must contain the whole argument string.
    /// It must be terminated with string end character( '\0' ).
    /// @param place_p The place of the argument in the argument string. It is valid from
    /// 0 - N-1, where N is the number of white space separated tokens in the argument string.
    Argument( const char* source_p, int place_p );

    /// Constructor for optional or place independent argument with only short name.
    ///
    /// Use this constructor to create an optional or place independent argument object.
    /// This version only supports short argument names.
    /// @note If your system does not have a relatively high amount of dynamic memory,
    /// please use this version. It uses much less memory than, the long name version.
    /// It is perfect for UNO / NANO with AVR chipset.
    /// @param source_p The source argument string.
    /// This character array must contain the whole argument string.
    /// It must be terminated with string end character( '\0' ).
    /// @param shortName_p This is a simple character. It is valid from a-z or A-Z.
    /// @note Be careful __shortName_p__ is case sensitive!
    Argument( const char* source_p, char shortName_p );

    /// Constructor for optional or place independent argument with short and long name.
    ///
    /// Use this constructor to create an optional or place independent argument object.
    /// This version supports both short and long names.
    /// @note Only use this version if your system has a relatively high amount of dynamic memory.
    /// My recommendation is at least 10k-bytes of RAM if you need to use this( ESP8266, ESP32, STM32... ).
    /// @param source_p The source argument string.
    /// This character array must contain the whole argument string.
    /// It must be terminated with string end character( '\0' ).
    /// @param shortName_p This is a simple character. It is valid from a-z or A-Z.
    /// @param longName_p Pointer to a character array, that contains the long name.
    /// @note Be careful both __shortName_p__ and __longName_p__ are case sensitive!
    Argument( const char* source_p, char shortName_p, const char* longName_p );

    /// Override return behaviour for int.
    ///
    /// The return behaviour is overriden in such a way, that it will
    /// return the parsed integer number if the __parseInt__ function
    /// was successfully parsed the input argument string. Otherwise it
    /// will return __0__.
    operator int();

    /// Override return behaviour for float.
    ///
    /// The return behaviour is overriden in such a way, that it will
    /// return the parsed float number if the __parseFloat__ function
    /// was successfully parsed the input argument string. Otherwise it
    /// will return __0.0__.
    operator float();

    /// Override return behaviour for char array.
    ///
    /// The return behaviour is overriden in such a way, that it will
    /// return a pointer to the parsed string if the __parseString__ function
    /// was successfully parsed the input argument string. Otherwise it
    /// will return a pointer to an empty string( "" ).
    operator char*();

    /// Override return behaviour for boolean.
    ///
    /// The return behaviour is overriden in such a way, that it will
    /// return __true__ value if the parsing process for the specified type
    /// was successful. Otherwise it will return false.
    operator bool();

    bool parseInt();
    bool parseFloat();
    bool parseStringFunction( char* buffer, int bufferSize );
    bool find();
    bool isFound();
    Commander::SystemVariable_t* getSystemVariable();

private:

    // Because it can only return one thing,
    // an union is made to save som precious memory.
    union returnData {
        int i;      // For int return data.
        float f;    // For float return data.
        char* c;    // For string return data.
    };

    typedef bool boolField;

    struct boolFields{

        boolField parsed : 1;
        boolField found : 1;

    }__attribute__((packed));

    // Pointer to the source buffer.
    const char* source = NULL;

    // Size of the source buffer.
    // It will use strlen to identify
    int sourceSize = -1;

    // If fixed place argument is used, this will store its place.
    int place = -1;

    // If short named argument is used, this will store its short name character.
    char shortName = '\0';

    // If long named argument is used, this will store pointer to its long name.
    const char* longName = NULL;

    Commander::SystemVariable_t* systemVariable = NULL;


    boolFields bFields;

    union returnData ret;
    //int intResult;
    //int floatResult;
    //char* outStringBuffer = NULL;
    static const char failedString;

    int findShortName();
    int findLongName();
    int findPlace();

    int findStart();

    bool inString( int index );

    int substring( char* str1, char* str2 );

};

#endif