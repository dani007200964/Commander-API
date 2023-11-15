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

void test_commander_neofetch_func_regular(){

    bool status;

    streamObject.clearRx();
    streamObject.clearTx();

    status = commander_neofetch_func( NULL, &streamObject, NULL );

    TEST_ASSERT_TRUE( status );

}

void test_commander_neofetch_func_invalid(){

    bool status;

    status = commander_neofetch_func( NULL, NULL, NULL );

    TEST_ASSERT_FALSE( status );

}

int main(){

    UNITY_BEGIN();

    RUN_TEST( test_commander_neofetch_func_regular );
    RUN_TEST( test_commander_neofetch_func_invalid );

    return UNITY_END();

}