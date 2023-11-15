/*
 * Created on June 25 2023
 *
 * Copyright (c) 2020 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2023.06.25
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

#include <stdio.h>
#include <stdint.h>

#include "../../../testStream.hpp"
#include "Commander-API.hpp"
#include "Commander-API-Commands.hpp"

// Unit test module.
#include "unity.h"

// For timing.
#include "System.h"

testStream streamObject;

// Dummy memory array.
uint8_t array[ 100 ];
char startAddress[ 20 ];
char endAddress[ 20 ];

// Put any init code here that needs to run before testing.
void setUp(void) {
    int i;

    for( i = 0; i < 100; i++ ){
        array[ i ] = i;
    }

    sprintf( startAddress, "0x%x", (int32_t)( (intptr_t)(&array[0]) ) );
    sprintf( endAddress, "0x%x", (int32_t)( (intptr_t)(&array[99]) ) );
}

// Put any init code here that needs to run after testing.
void tearDown(void) {

}

void test_commander_memDump_func_regular(){

    bool status;
    char command[ 1000 ];

    //---- u8 section ----//
    // Simple memDump with 1 u8 type
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s u8", startAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    // Simple memDump with 10 u8 type
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s u8 -n 10", startAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    // Simple memDump with u8 type with end address
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s u8 -e %s", startAddress, endAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    // Simple memDump with 10 u8 type with decimal formatting
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s u8 -n 10 -d", startAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    // Simple memDump with 10 u8 type with binary formatting
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s u8 -n 10 -b", startAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    //---- i8 section ----//
    // Simple memDump with 1 i8 type
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s i8", startAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    // Simple memDump with 10 i8 type
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s i8 -n 10", startAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );
    
    // Simple memDump with i8 type with end address
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s i8 -e %s", startAddress, endAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    // Simple memDump with 10 i8 type with hex formatting
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s i8 -n 10 -h", startAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    // Simple memDump with 10 i8 type with decimal formatting
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s i8 -n 10 -d", startAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    // Simple memDump with 10 i8 type with binary formatting
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s i8 -n 10 -b", startAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    // Simple memDump with 10 i8 type with character formatting
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s i8 -n 50 -c", startAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    //---- u16 section ----//
    // Simple memDump with 1 u16 type
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s u16", startAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    // Simple memDump with 10 u16 type
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s u16 -n 10", startAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    // Simple memDump with u16 type with end address
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s u16 -e %s", startAddress, endAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    // Simple memDump with 10 u16 type with decimal formatting
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s u16 -n 10 -d", startAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    // Simple memDump with 10 u16 type with binary formatting
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s u16 -n 10 -b", startAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    //---- i16 section ----//
    // Simple memDump with 1 i16 type
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s i16", startAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    // Simple memDump with 10 i16 type
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s i16 -n 10", startAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    // Simple memDump with i16 type with end address
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s i16 -e %s", startAddress, endAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    // Simple memDump with 10 i16 type with decimal formatting
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s i16 -n 10 -d", startAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    // Simple memDump with 10 i16 type with binary formatting
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s i16 -n 10 -b", startAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    //---- u32 section ----//
    // Simple memDump with 1 u32 type
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s u32", startAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    // Simple memDump with 10 u32 type
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s u32 -n 10", startAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    // Simple memDump with u32 type with end address
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s u32 -e %s", startAddress, endAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    // Simple memDump with 10 u32 type with decimal formatting
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s u32 -n 10 -d", startAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    //---- i32 section ----//
    // Simple memDump with 1 i32 type
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s i32", startAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    // Simple memDump with 10 i32 type
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s i32 -n 10", startAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    // Simple memDump with i32 type with end address
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s i32 -e %s", startAddress, endAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    // Simple memDump with 10 i32 type with decimal formatting
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s i32 -n 10 -d", startAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

    //TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "" );

}

void test_commander_memDump_func_invalid(){

    bool status;
    char command[ 1000 ];

    // memDump without startAddress
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "u8" );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_FALSE( status );

    // memDump without type
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "%s", startAddress );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_FALSE( status );

    // memDump with wrong start address format
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "1x123 u8" );
    status = commander_memDump_func( command, &streamObject, NULL );

    sprintf( command, "1X123 u8" );
    status = commander_memDump_func( command, &streamObject, NULL );

    sprintf( command, "0b123 u8" );
    status |= commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_FALSE( status );

    // memDump with wrong start address number
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "0xwrong u8" );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_FALSE( status );

    // memDump with wrong type
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "0XABC u9" );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_FALSE( status );

    // memDump with wrong end address format
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "0xABC u8 -e 1x123" );
    status = commander_memDump_func( command, &streamObject, NULL );

    sprintf( command, "0xABC u8 -e 1X123" );
    status = commander_memDump_func( command, &streamObject, NULL );

    sprintf( command, "0xABC u8 -e 0b123" );
    status |= commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_FALSE( status );

    // memDump with wrong end address number
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "0xABC u8 -e 0xwrong" );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_FALSE( status );

    // memDump with greater start address, than end address
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "0xABC u8 -e 0x000" );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_FALSE( status );

    // memDump with both end address and number defined
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "0x000 u8 -e 0xABC -n 10" );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_FALSE( status );

    // memDump with negative number defined
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "0x000 u8 -n -10" );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_FALSE( status );

    // memDump command without response channel
    status = commander_memDump_func( (char*)"", NULL, NULL );

    TEST_ASSERT_FALSE( status );

    // memDump with negative number defined
    streamObject.clearRx();
    streamObject.clearTx();

    sprintf( command, "0x00 u8 -e 0xF0000000" );
    status = commander_memDump_func( command, &streamObject, NULL );

    TEST_ASSERT_FALSE( status );

}

int main(){

    UNITY_BEGIN();

    RUN_TEST( test_commander_memDump_func_regular );
    RUN_TEST( test_commander_memDump_func_invalid );

    return UNITY_END();

}