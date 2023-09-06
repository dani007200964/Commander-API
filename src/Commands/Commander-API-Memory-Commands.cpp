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

#ifdef __AVR__

#else

uint32_t memDumpAddressRanges[][ 2 ] = {
    { 0x00000000, 0xFFFFFFFF }
};

#endif

#define BYTE_TO_BINARY_PATTERN  "0b%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY( x )     ( (x) & 0x80 ? '1' : '0' ),     \
                                ( (x) & 0x40 ? '1' : '0' ),     \
                                ( (x) & 0x20 ? '1' : '0' ),     \
                                ( (x) & 0x10 ? '1' : '0' ),     \
                                ( (x) & 0x08 ? '1' : '0' ),     \
                                ( (x) & 0x04 ? '1' : '0' ),     \
                                ( (x) & 0x02 ? '1' : '0' ),     \
                                ( (x) & 0x01 ? '1' : '0' ) 

const char* memDumpTypes[] = {
    "u8",
    "s8",
    "u16",
    "s16",
    "u32",
    "s32",
    "U8",
    "S8",
    "U16",
    "S16",
    "U32",
    "S32"
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
    FORMAT_BIN
}memDumpFormat_t;

bool commander_memDump_func( char *args, Stream *response, void* parent ){

    // Generic counter.
    uint32_t i;

    // Generic counter.
    uint32_t j;

    // Start address argument object.
    Argument startAddress( args, 0 );

    // This buffer will hold the address string.
    char addressBuffer[ 15 ] = { 0 };

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

    Argument decFlag( args, 'd', "dec" );
    Argument hexFlag( args, 'h', "hex" );
    Argument binFlag( args, 'b', "bin" );

    memDumpFormat_t outputFormat = FORMAT_HEX;

    // If response is not available, return.
    if( response == NULL ){
        return false;
    }

    // Try to parse the arguments
    startAddress.parseString( addressBuffer );
    dataType.parseString( dataTypeBuffer );
    number.parseInt();

    decFlag.find();
    hexFlag.find();
    binFlag.find();

    if( decFlag.isFound() ){
        outputFormat = FORMAT_DEC;
    }
    
    if( hexFlag.isFound() ){
        outputFormat = FORMAT_HEX;
    }
    
    if( binFlag.isFound() ){
        outputFormat = FORMAT_BIN;
    }
    
    // Start address is not optional.
    if( !startAddress ){
        Commander::printArgumentError( response );
        response -> print( " Start address is not specified!" );
        return false;
    }

    // Data type is not optional.
    if( !dataType ){
        Commander::printArgumentError( response );
        response -> print( " Data type is not specified!" );
        return false;
    }

    if( ( addressBuffer[ 0 ] != '0' ) || ( ( addressBuffer[ 1 ] != 'x' ) && ( addressBuffer[ 1 ] != 'X' ) ) ){
        Commander::printArgumentError( response );
        response -> print( " Start address format is not correct! It has to start with 0x..." );
        return false;
    }

    if( sscanf( &addressBuffer[ 2 ],"%x", &startAddressNumber ) != 1 ){
        Commander::printArgumentError( response );
        response -> print( " Start address format is not correct! Example: 0x012ABC" );
        return false;
    }

    response -> print( "Start Address Number: " );
    response -> println( startAddressNumber, HEX );

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
    response -> println( i );

    endAddress.parseString( addressBuffer );
    if( endAddress && !number ){

        if( ( addressBuffer[ 0 ] != '0' ) || ( ( addressBuffer[ 1 ] != 'x' ) && ( addressBuffer[ 1 ] != 'X' ) ) ){
            return false;
        }

        if( sscanf( &addressBuffer[ 2 ],"%x", &endAddressNumber ) != 1 ){
            return false;
        }

        if( endAddressNumber < startAddressNumber ){
            Commander::printArgumentError( response );
            response -> print( " Start address is greater, than end address!" );
            return false;
        }

        response -> print( "End Address Number: " );
        response -> println( endAddressNumber, HEX );

        numberOfData = ( endAddressNumber - startAddressNumber ) / bytesInData;

    }

    else if( number && !endAddress ){
        numberOfData = (int)number;
    }

    else if( number && endAddress ){
        Commander::printArgumentError( response );
        response -> print( " Number and end address can not be defined at the same time!" );
        return false;
    }

    else{
        numberOfData = 1;
    }

    response -> print( "Number of data: " );
    response -> println( numberOfData );

    response -> print( "  Address  |" );

    for( i = 0; i < bytesInData; i++ ){

        if( outputFormat == FORMAT_BIN ){
            for( j = 0; j < 5; j++ ){
                response -> print( ' ' );
            }
        }

        j = 8 * ( bytesInData - i - 1 );
        snprintf( addressBuffer, sizeof( addressBuffer ), " %02d:%02d |", j + 7, j);
        addressBuffer[ sizeof( addressBuffer ) - 1 ] = '\0';
        response -> print( addressBuffer );

    }

    response -> println( " Value" );

    for( i = 0; i < numberOfData; i++ ){

        dataPointer = (uint32_t)( startAddressNumber + i * bytesInData );
        response -> print( "0x" );
        snprintf( addressBuffer, sizeof( addressBuffer ), "%08x", dataPointer );
        addressBuffer[ sizeof( addressBuffer ) - 1 ] = '\0';
        response -> print( addressBuffer );
        response -> print( " |" );

        for( j = 0; j < bytesInData; j++ ){
            dataPointer = (uint32_t)( startAddressNumber + i * bytesInData + ( bytesInData - j - 1 ) );
            //response -> print( (uint8_t)*( (uint8_t*)dataPointer ), HEX );

            switch( outputFormat ){
                case FORMAT_BIN:
                    snprintf( addressBuffer, sizeof( addressBuffer ), " " BYTE_TO_BINARY_PATTERN " |", BYTE_TO_BINARY( (uint8_t)*( (uint8_t*)( (intptr_t)dataPointer ) ) ) );
                    break;

                case FORMAT_DEC:
                    snprintf( addressBuffer, sizeof( addressBuffer ), "  %3d  |", (uint8_t)*( (uint8_t*)( (intptr_t)dataPointer ) ) );
                    break;

                default:
                    snprintf( addressBuffer, sizeof( addressBuffer ), " 0x%02x  |", (uint8_t)*( (uint8_t*)( (intptr_t)dataPointer ) ) );
                    break;
                    
            }

            addressBuffer[ sizeof( addressBuffer ) - 1 ] = '\0';
            response -> print( addressBuffer );

        }

        dataPointer = (uint32_t)( startAddressNumber + i * bytesInData );
        response -> print( ' ' );
        switch( type ){
            case UNSIGNED_8_BIT:
                response -> print( (uint8_t)*( (uint8_t*)( (intptr_t)dataPointer ) ) );
                break;
            case SIGNED_8_BIT:
                response -> print( (int8_t)*( (int8_t*)( (intptr_t)dataPointer ) ) );
                break;
            case UNSIGNED_16_BIT:
                response -> print( (uint16_t)*( (uint16_t*)( (intptr_t)dataPointer ) ) );
                break;
            case SIGNED_16_BIT:
                response -> print( (int16_t)*( (int16_t*)( (intptr_t)dataPointer ) ) );
                break;
            case UNSIGNED_32_BIT:
                response -> print( (uint32_t)*( (uint32_t*)( (intptr_t)dataPointer ) ) );
                break;
            default:
                response -> print( (int32_t)*( (int32_t*)( (intptr_t)dataPointer ) ) );
                break;
        }

        response -> println();

    }

    return true;
}