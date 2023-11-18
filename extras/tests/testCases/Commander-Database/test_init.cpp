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

#include "Commander-Database.hpp"

// Unit test module.
#include "unity.h"

// Stream class for testing
#include "../../testStream.hpp"

// For timing.
#include "System.h"

// It defines the size of the test database array.
#define TEST_ARRAY_SIZE 5

// Use test Stream as Channel.
testStream testChannel;

// This class must be used for unit testing.
class CommanderDatabaseUT{
public:

    // Internal variable, that stores the address of the target.
    CommanderDatabase<int>* target;

    // Constructor for the tester class. It has only one parameter
    // which is the address of the target object.
    CommanderDatabaseUT( CommanderDatabase<int>* target_p ){ target = target_p; }

    //---- Test cases ----//
    void test_init();
    void test_init_duplicate();
    void test_initWithDebug();

};

CommanderDatabase<int> targetObject;
CommanderDatabaseUT testerObject( &targetObject );

char itemNames[ TEST_ARRAY_SIZE ][ 10 ];
CommanderDatabase<int>::dataRecord_t testData[ TEST_ARRAY_SIZE ];

// Put any init code here that needs to run before testing.
void setUp(void) {

    // Generic counter.
    int i;

    // Used to generate unique item names.
    char buff[ 100 ];

    // Generate unique item names.
    // from 1 to TEST_ARRAY_SIZE
    for( i = 0; i < TEST_ARRAY_SIZE; i++ ){
        sprintf( buff, "item_%d", i+1 );
        strcpy( itemNames[ i ], buff );
    }

    // Fill the array with default values in reverse order.
    // Te first element will be the last to test the sorting.
    for( i = 0; i < TEST_ARRAY_SIZE; i++ ){
        testData[ i ].name = (const char*)itemNames[ TEST_ARRAY_SIZE - i - 1 ];
        testData[ i ].left = NULL;
        testData[ i ].right = NULL;
        testData[ i ].data = TEST_ARRAY_SIZE - i;
        //sprintf( buff, "index: %d, name: %s, data: %d", i, testData[ i ].name, testData[ i ].data );
        //TEST_MESSAGE( (const char*)buff );
    }
    
    targetObject = CommanderDatabase<int>( testData, TEST_ARRAY_SIZE );

}

// Put any init code here that needs to run after testing.
void tearDown(void) {

}

void CommanderDatabaseUT::test_init(){

    int i;
    bool status;
    char buff[ 100 ];

    status = target -> init();

    TEST_ASSERT_TRUE_MESSAGE( status, "Init return value false!" );

    for( i = 0; i < TEST_ARRAY_SIZE; i++ ){
        sprintf( buff, "index: %d, name: %s, data: %d, place %d", i, testData[ i ].name, testData[ i ].data, testData[ i ].place );
        TEST_MESSAGE( (const char*)buff );
        //TEST_ASSERT_EQUAL_INT_MESSAGE( testData[ i ].data, testData[ i ].place, "Bubble sort problem!" );
    }
    //TEST_ASSERT_EQUAL_INT_MESSAGE( testData[ 0 ].data, testData[ 0 ].place, "Bubble sort problem!" );

}

void test_init( void ){
    testerObject.test_init();
}

void CommanderDatabaseUT::test_init_duplicate(){

    bool status;

    // The first two elements will have the same name.
    strcpy( itemNames[ 0 ], "wrong" );
    strcpy( itemNames[ 1 ], "wrong" );

    status = target -> init();

    TEST_ASSERT_FALSE_MESSAGE( status, "Item 0 and item 1 has the same name! Init should fail!" );

}

void test_init_duplicate( void ){
    testerObject.test_init_duplicate();
}

void CommanderDatabaseUT::test_initWithDebug(){

    bool status;

    testChannel.clearTx();

    target -> setDebugLevel( CommanderDatabase<int>::DEBUG_VERBOSE );
    target -> attachDebugChannel( &testChannel );

    status = target -> init();

    TEST_ASSERT_TRUE_MESSAGE( status, "Init return value false!" );
    TEST_ASSERT_NOT_EQUAL_INT_MESSAGE( 0, testChannel.txWritePointer, "Debug messages are not printed!" );

}

void test_initWithDebug( void ){
    testerObject.test_initWithDebug();
}

int main(){

    UNITY_BEGIN();

    RUN_TEST( test_init );
    RUN_TEST( test_init_duplicate );
    RUN_TEST( test_initWithDebug );

    return UNITY_END();

}