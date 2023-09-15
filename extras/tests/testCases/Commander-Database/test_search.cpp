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

// For timing.
#include "System.h"

// It defines the size of the test database array.
#define TEST_ARRAY_SIZE 5

// This class must be used for unit testing.
class CommanderDatabaseUT{
public:

    // Internal variable, that stores the address of the target.
    CommanderDatabase<int>* target;

    // Constructor for the tester class. It has only one parameter
    // which is the address of the target object.
    CommanderDatabaseUT( CommanderDatabase<int>* target_p ){ target = target_p; }

    //---- Test cases ----//
    void test_findIndexByPlace();
    void test_swapElements();
    void test_indexing_int();
    void test_indexing_str();

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
    char buff[ 10 ];

    // Generate unique item names.
    // from 1 to TEST_ARRAY_SIZE
    for( i = 1; i <= TEST_ARRAY_SIZE; i++ ){
        sprintf( buff, "item_%d", i );
        strcpy( itemNames[ i ], buff );
    }

    // Fill the array with default values in reverse order.
    // Te first element will be the last to test the sorting.
    for( i = 0; i < TEST_ARRAY_SIZE; i++ ){
        testData[ i ].name = (const char*)itemNames[ TEST_ARRAY_SIZE - i - 1 ];
        testData[ i ].left = NULL;
        testData[ i ].right = NULL;
        testData[ i ].data = TEST_ARRAY_SIZE - i;
    }
    
    targetObject = CommanderDatabase<int>( testData, TEST_ARRAY_SIZE );
    targetObject.init();

}

// Put any init code here that needs to run after testing.
void tearDown(void) {

}

void CommanderDatabaseUT::test_findIndexByPlace(){

    int i;
    uint16_t resultIndex;

    // Test findIndexByPlace for each element.
    for( i = 0; i < TEST_ARRAY_SIZE; i++ ){

        // Place starts from 1, not from 0!
        resultIndex = target -> findIndexByPlace( i + 1 );
        TEST_ASSERT_EQUAL_INT( testData[ resultIndex ].place, i + 1 );

    }

    // Test for invalid data.
    TEST_ASSERT_EQUAL_INT( 0, target -> findIndexByPlace( 0 ) );
    TEST_ASSERT_EQUAL_INT( 0, target -> findIndexByPlace( TEST_ARRAY_SIZE + 1 ) );

}

void test_findIndexByPlace( void ){
    testerObject.test_findIndexByPlace();
}

void CommanderDatabaseUT::test_swapElements(){

    uint16_t initialPlaceOfElement_0;
    uint16_t initialPlaceOfElement_1;

    initialPlaceOfElement_0 = testData[ 0 ].place;
    initialPlaceOfElement_1 = testData[ 1 ].place;

    // Swap element 0 and 1.
    target -> swapElements( 0, 1 );

    // Check if swap was done correctly.
    TEST_ASSERT_EQUAL_INT( initialPlaceOfElement_1, testData[ 0 ].place );
    TEST_ASSERT_EQUAL_INT( initialPlaceOfElement_0, testData[ 1 ].place );

    // Check to swap invalid data.
    target -> swapElements( 0, TEST_ARRAY_SIZE + 1 );
    target -> swapElements( TEST_ARRAY_SIZE + 1, 0 );

    // Check if position 0 did not changed.
    TEST_ASSERT_EQUAL_INT( initialPlaceOfElement_1, testData[ 0 ].place );

}

void test_swapElements( void ){
    testerObject.test_swapElements();
}

void CommanderDatabaseUT::test_indexing_int(){

    int i;

    // Test for normal conditions.
    for( i = 0; i < TEST_ARRAY_SIZE; i++ ){
        TEST_ASSERT_EQUAL_PTR( &testData[ i ], target -> operator[]( i ) );
    }

    // Test for invalid conditions
    TEST_ASSERT_EQUAL_PTR( NULL, target -> operator[]( -1 ) );
    TEST_ASSERT_EQUAL_PTR( NULL, target -> operator[]( TEST_ARRAY_SIZE ) );

}

void test_indexing_int( void ){
    testerObject.test_indexing_int();
}

void CommanderDatabaseUT::test_indexing_str(){

    int i;

    // Test for normal conditions.
    for( i = 0; i < TEST_ARRAY_SIZE; i++ ){
        TEST_ASSERT_EQUAL_PTR( &testData[ i ], target -> operator[]( (const char*)testData[ i ].name ) );
    }

    // Test for invalid conditions
    TEST_ASSERT_EQUAL_PTR( NULL, target -> operator[]( "cat" ) );

}

void test_indexing_str( void ){
    testerObject.test_indexing_str();
}

int main(){

    UNITY_BEGIN();

    RUN_TEST( test_findIndexByPlace );
    RUN_TEST( test_swapElements );
    RUN_TEST( test_indexing_int );
    RUN_TEST( test_indexing_str );

    return UNITY_END();

}