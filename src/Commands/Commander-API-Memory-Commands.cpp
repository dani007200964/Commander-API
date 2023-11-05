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

#include "inttypes.h"
#include "../Commander-API-Commands.hpp"

#define BYTE_TO_BINARY_PATTERN  "0b%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY( x )     ( (x) & 0x80 ? '1' : '0' ),     \
                                ( (x) & 0x40 ? '1' : '0' ),     \
                                ( (x) & 0x20 ? '1' : '0' ),     \
                                ( (x) & 0x10 ? '1' : '0' ),     \
                                ( (x) & 0x08 ? '1' : '0' ),     \
                                ( (x) & 0x04 ? '1' : '0' ),     \
                                ( (x) & 0x02 ? '1' : '0' ),     \
                                ( (x) & 0x01 ? '1' : '0' ) 

#if defined( AVR_UNO ) || defined( AVR_DUEMILANOVE ) || defined( AVR_NANO )
    uint32_t memDumpAddressRanges[][ 2 ] = {
        { 0x00000000, 0x08FF }
    };
#else
    uint32_t memDumpAddressRanges[][ 2 ] = {
        { 0x00000000, 0x0FFFFFFF }
    };
#endif

uint8_t numberOfMemDumpAddressRanges = sizeof( memDumpAddressRanges ) / sizeof( memDumpAddressRanges[ 0 ] );

const char* memDumpTypes[] = {
    "u8",
    "i8",
    "u16",
    "i16",
    "u32",
    "i32",
    "U8",
    "I8",
    "U16",
    "I16",
    "U32",
    "I32"
};

typedef enum{
    UNSIGNED_8_BIT,
    SIGNED_8_BIT,
    UNSIGNED_16_BIT,
    SIGNED_16_BIT,
    UNSIGNED_32_BIT,
    SIGNED_32_BIT
}memDumpType_t;

typedef enum{
    FORMAT_HEX,
    FORMAT_DEC,
    FORMAT_BIN,
    FORMAT_CHAR
}memDumpFormat_t;

bool commander_memDump_func( char *args, Stream *response, void* parent ){

    // Generic counter.
    uint32_t i;

    // Generic counter.
    uint32_t j;

    // Start address argument object.
    Argument startAddress( args, 0 );

    // This buffer will hold the address string.
    char buffer[ 30 ] = { 0 };

    // This will hold the start address.
    uint32_t startAddressNumber;

    // Type argument object.
    Argument dataType( args, 1 );

    // This buffer will hold the type string.
    char dataTypeBuffer[ 4 ] = { 0 };

    // This will hold the type enumeration.
    memDumpType_t type;

    // End address argument object.
    Argument endAddress( args, 'e', "end" );

    // This will hold the end address.
    uint32_t endAddressNumber;

    // Number argument object.
    Argument number( args, 'n', "number" );

    // This will hold how many cells needs to be printed.
    uint32_t numberOfData;

    // This will tell how many bytes are in the selected data type.
    uint8_t bytesInData;

    uint32_t dataPointer;

    // This variable will hold the data itself;
    uint8_t data[ 4 ];

    Argument decFlag( args, 'd', "dec" );
    Argument hexFlag( args, 'h', "hex" );
    Argument binFlag( args, 'b', "bin" );
    Argument charFlag( args, 'c', "char" );

    memDumpFormat_t outputFormat = FORMAT_HEX;

    // If response is not available, return.
    if( response == NULL ){
        return false;
    }

    // Try to parse the arguments
    startAddress.parseString( buffer );
    dataType.parseString( dataTypeBuffer );
    number.parseInt();

    decFlag.find();
    hexFlag.find();
    binFlag.find();
    charFlag.find();

    if( decFlag.isFound() ){
        outputFormat = FORMAT_DEC;
    }
    
    if( binFlag.isFound() ){
        outputFormat = FORMAT_BIN;
    }
    
    if( charFlag.isFound() ){
        outputFormat = FORMAT_CHAR;
    }

    if( hexFlag.isFound() ){
        outputFormat = FORMAT_HEX;
    }    
    
    // Start address and data type is not optional.
    if( !startAddress || !dataType ){
        Commander::printArgumentError( response );
        response -> print( " Start address and data type has to be specified!" );
        return false;
    }

    if( ( buffer[ 0 ] != '0' ) || ( ( buffer[ 1 ] != 'x' ) && ( buffer[ 1 ] != 'X' ) ) ){
        Commander::printArgumentError( response );
        response -> print( " Start address format is not correct! It has to start with 0x..." );
        return false;
    }

    if( sscanf( &buffer[ 2 ],"%x", &startAddressNumber ) != 1 ){
        Commander::printArgumentError( response );
        response -> print( " Start address format is not correct! Example: 0x012ABC" );
        return false;
    }

    for( i = 0; i < 12; i++ ){

        if( strcmp( (char*)dataType, memDumpTypes[ i ] ) == 0 ){
            break;
        }

    }

    if( i >= 12 ){
        Commander::printArgumentError( response );
        response -> print( " Data type format is not correct! Example: u8" );
        return false;
    }

    if( i > 5 ){
        i -= 6;
    }

    type = (memDumpType_t)i;

    // By default set one byte mode wide data.
    bytesInData = 1;

    // Check if the data is two bytes wide.
    if( ( type == UNSIGNED_16_BIT ) || ( type == SIGNED_16_BIT ) ){
        bytesInData = 2;
    }

    // Check if the data is four bytes wide.
    if( ( type == UNSIGNED_32_BIT ) || ( type == SIGNED_32_BIT ) ){
        bytesInData = 4;
    }

    response -> print( "Data Type: " );
    response -> println( memDumpTypes[ i ] );

    endAddress.parseString( buffer );
    if( endAddress && !number ){

        if( ( buffer[ 0 ] != '0' ) || ( ( buffer[ 1 ] != 'x' ) && ( buffer[ 1 ] != 'X' ) ) ){
            return false;
        }

        if( sscanf( &buffer[ 2 ],"%x", &endAddressNumber ) != 1 ){
            return false;
        }

        if( endAddressNumber < startAddressNumber ){
            Commander::printArgumentError( response );
            response -> print( " Start address is greater, than end address!" );
            return false;
        }

        numberOfData = ( endAddressNumber - startAddressNumber ) / bytesInData;

        // It is required, because we want to print the data in the end address as well.
        numberOfData += 1;

    }

    else if( number && !endAddress ){
        if( (int)number < 0 ){
            Commander::printArgumentError( response );
            response -> print( " Number can not be negative!" );
            return false;
        }

        numberOfData = (uint32_t)(int)number;
        endAddressNumber = ( numberOfData - 1 ) * bytesInData + startAddressNumber;
    }

    else if( number && endAddress ){
        Commander::printArgumentError( response );
        response -> print( " Number and end address can not be defined at the same time!" );
        return false;
    }

    else{
        numberOfData = 1;
    }

    // Check if the address range is valid.
    j = 0;
    for( i = 0; i < numberOfMemDumpAddressRanges; i++ ){

        j =      startAddressNumber >= memDumpAddressRanges[ i ][ 0 ];
        j = j && startAddressNumber <  memDumpAddressRanges[ i ][ 1 ];
        j = j && endAddressNumber   >= memDumpAddressRanges[ i ][ 0 ];
        j = j && endAddressNumber   <  memDumpAddressRanges[ i ][ 1 ];

        if( j ){
            break;
        }

    }

    if( !j ){
        Commander::printArgumentError( response );
        response -> print( " The specified address range is not accessible!" );
        return false;
    }

    response -> print( "Start Address: 0x" );
    snprintf( buffer, sizeof( buffer ), "%08x", startAddressNumber );
    response -> println( buffer );

    response -> print( "End Address: 0x" );
    snprintf( buffer, sizeof( buffer ), "%08x", endAddressNumber );
    response -> println( buffer );

    response -> print( "Number of elements: " );
    snprintf( buffer, sizeof( buffer ), "%" PRIu32, numberOfData );
    response -> println( buffer );

    response -> print( "  Address  |" );

    for( i = 0; i < bytesInData; i++ ){

        if( outputFormat == FORMAT_BIN ){
            for( j = 0; j < 5; j++ ){
                response -> print( ' ' );
            }
        }

        j = 8 * ( bytesInData - i - 1 );
        snprintf( buffer, sizeof( buffer ), " %02d:%02d |", j + 7, j);
        buffer[ sizeof( buffer ) - 1 ] = '\0';
        response -> print( buffer );

    }

    response -> println( " Value" );

    for( i = 0; i < numberOfData; i++ ){

        dataPointer = (uint32_t)( startAddressNumber + i * bytesInData );
        response -> print( "0x" );
        snprintf( buffer, sizeof( buffer ), "%08x", dataPointer );
        buffer[ sizeof( buffer ) - 1 ] = '\0';
        response -> print( buffer );
        response -> print( " |" );

        *data = (uint32_t)*( (uint32_t*)( (intptr_t)dataPointer ) );

        for( j = 0; j < bytesInData; j++ ){
            //dataPointer = (uint32_t)( startAddressNumber + i * bytesInData + ( bytesInData - j - 1 ) );
            //response -> print( (uint8_t)*( (uint8_t*)dataPointer ), HEX );

            switch( outputFormat ){
                case FORMAT_BIN:
                    //snprintf( buffer, sizeof( buffer ), " " BYTE_TO_BINARY_PATTERN " |", BYTE_TO_BINARY( (uint8_t)*( (uint8_t*)( (intptr_t)dataPointer ) ) ) );
                    snprintf( buffer, sizeof( buffer ), " " BYTE_TO_BINARY_PATTERN " |", BYTE_TO_BINARY( data[ bytesInData - j - 1 ] ) );
                    break;

                case FORMAT_DEC:
                    //snprintf( buffer, sizeof( buffer ), "  %3d  |", (uint8_t)*( (uint8_t*)( (intptr_t)dataPointer ) ) );
                    snprintf( buffer, sizeof( buffer ), "  %3d  |", data[ bytesInData - j - 1 ] );
                    break;

                case FORMAT_CHAR:
                    if( ( data[ bytesInData - j - 1 ] > 31 ) && ( data[ bytesInData - j - 1 ] < 127 ) ){
                        snprintf( buffer, sizeof( buffer ), "  '%c'  |", data[ bytesInData - j - 1 ] );
                    }
                    else{
                        snprintf( buffer, sizeof( buffer ), " 0x%02x  |", data[ bytesInData - j - 1 ] );
                    }
                    break;

                default:
                    snprintf( buffer, sizeof( buffer ), " 0x%02x  |", data[ bytesInData - j - 1 ] );
                    break;
                    
            }

            buffer[ sizeof( buffer ) - 1 ] = '\0';
            response -> print( buffer );

        }

        response -> print( ' ' );
        switch( type ){
            case UNSIGNED_8_BIT:
                //response -> print( (uint8_t)*( (uint8_t*)( (intptr_t)dataPointer ) ) );
                //snprintf( buffer, sizeof( buffer ), "%3d", (uint8_t)*( (uint8_t*)( (intptr_t)dataPointer ) ) );
                snprintf( buffer, sizeof( buffer ), "%3d", (uint8_t)*(uint8_t*)data );
                response -> print( buffer );
                break;
            case SIGNED_8_BIT:
                //response -> print( (int8_t)*( (int8_t*)( (intptr_t)dataPointer ) ) );
                //snprintf( buffer, sizeof( buffer ), "%3d", (uint8_t)*( (uint8_t*)( (intptr_t)dataPointer ) ) );
                snprintf( buffer, sizeof( buffer ), "%3d", (int8_t)*(int8_t*)data );
                response -> print( buffer );
                break;
            case UNSIGNED_16_BIT:
                //response -> print( (uint16_t)*( (uint16_t*)( (intptr_t)dataPointer ) ) );
                //snprintf( buffer, sizeof( buffer ), "%" PRIu16, (uint16_t)*( (uint16_t*)( (intptr_t)dataPointer ) ) );
                snprintf( buffer, sizeof( buffer ), "%" PRIu16, (uint16_t)*(uint16_t*)data );
                response -> print( buffer );
                break;
            case SIGNED_16_BIT:
                //response -> print( (int16_t)*( (int16_t*)( (intptr_t)dataPointer ) ) );
                //snprintf( buffer, sizeof( buffer ), "%" PRId16, (uint16_t)*( (uint16_t*)( (intptr_t)dataPointer ) ) );
                snprintf( buffer, sizeof( buffer ), "%" PRId16, (int16_t)*(int16_t*)data );
                response -> print( buffer );
                break;
            case UNSIGNED_32_BIT:
                //response -> print( (uint32_t)*( (uint32_t*)( (intptr_t)dataPointer ) ) );
                //snprintf( buffer, sizeof( buffer ), "%" PRIu32, (uint32_t)*( (uint32_t*)( (intptr_t)dataPointer ) ) );
                snprintf( buffer, sizeof( buffer ), "%" PRIu32, (uint32_t)*(uint32_t*)data );
                response -> print( buffer );
                break;
            default:
                //response -> print( (int32_t)*( (int32_t*)( (intptr_t)dataPointer ) ) );
                //snprintf( buffer, sizeof( buffer ), "%" PRId32, (uint32_t)*( (uint32_t*)( (intptr_t)dataPointer ) ) );
                snprintf( buffer, sizeof( buffer ), "%" PRId32, (int32_t)*(int32_t*)data );
                response -> print( buffer );
                break;
        }

        response -> println();

    }

    return true;
}