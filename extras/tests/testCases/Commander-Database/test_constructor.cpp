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
#define TEST_ARRAY_SIZE 10

// This class must be used for unit testing.
class CommanderDatabaseUT{
public:

    // Internal variable, that stores the address of the target.
    CommanderDatabase<int>* target;

    // Constructor for the tester class. It has only one parameter
    // which is the address of the target object.
    CommanderDatabaseUT( CommanderDatabase<int>* target_p ){ target = target_p; }

    //---- Test cases ----//
    void testConstructor_empty();
    void testConstructor_dataRecord_t_uint16_t();
    void test_getSize();

};

CommanderDatabase<int> targetObject;
CommanderDatabaseUT testerObject( &targetObject );

CommanderDatabase<int>::dataRecord_t testData[ TEST_ARRAY_SIZE ];

// Put any init code here that needs to run before testing.
void setUp(void) {
  
}

// Put any init code here that needs to run after testing.
void tearDown(void) {

}

void CommanderDatabaseUT::testConstructor_empty(){

    // Messing up the data to check if it will be corrected by the empty constructor.
    target -> dataTree = (CommanderDatabase<int>::dataRecord_t*)100;
    target -> dataTreeSize = 30;
    target -> debugChannel = (Stream*)200;
    target -> debugLevel = CommanderDatabase<int>::DEBUG_DEBUG;
    target -> initFlag = true;

    // Test if the incorrect parameters are passed correctly.
    TEST_ASSERT_EQUAL_PTR_MESSAGE( 100, target -> dataTree, "Incorrect value, injection failed!" );
    TEST_ASSERT_EQUAL_INT_MESSAGE( 30, target -> dataTreeSize, "Incorrect value, injection failed!" );
    TEST_ASSERT_EQUAL_PTR_MESSAGE( 200, target -> debugChannel, "Incorrect value, injection failed!" );
    TEST_ASSERT_EQUAL_INT_MESSAGE( (int)CommanderDatabase<int>::DEBUG_DEBUG, target -> debugLevel, "Incorrect value, injection failed!" );
    TEST_ASSERT_TRUE_MESSAGE( target -> initFlag, "Incorrect value, injection failed!" );

    // Call the empty constructor.
    targetObject = CommanderDatabase<int>();

    // Test if the parameters are corrected by the constructor.
    TEST_ASSERT_EQUAL_PTR( NULL, target -> dataTree );
    TEST_ASSERT_EQUAL_INT( 0, target -> dataTreeSize );
    TEST_ASSERT_EQUAL_PTR( NULL, target -> debugChannel );
    TEST_ASSERT_EQUAL_INT( (int)CommanderDatabase<int>::DEBUG_OFF, target -> debugLevel );
    TEST_ASSERT_FALSE( target -> initFlag );

}

void testConstructor_empty( void ){
    testerObject.testConstructor_empty();
}

void CommanderDatabaseUT::testConstructor_dataRecord_t_uint16_t(){

    // Messing up the data to check if it will be corrected by the empty constructor.
    target -> dataTree = (CommanderDatabase<int>::dataRecord_t*)100;
    target -> dataTreeSize = 30;
    target -> debugChannel = (Stream*)200;
    target -> debugLevel = CommanderDatabase<int>::DEBUG_DEBUG;
    target -> initFlag = true;

    // Test if the incorrect parameters are passed correctly.
    TEST_ASSERT_EQUAL_PTR_MESSAGE( 100, target -> dataTree, "Incorrect value, injection failed!" );
    TEST_ASSERT_EQUAL_INT_MESSAGE( 30, target -> dataTreeSize, "Incorrect value, injection failed!" );
    TEST_ASSERT_EQUAL_PTR_MESSAGE( 200, target -> debugChannel, "Incorrect value, injection failed!" );
    TEST_ASSERT_EQUAL_INT_MESSAGE( (int)CommanderDatabase<int>::DEBUG_DEBUG, target -> debugLevel, "Incorrect value, injection failed!" );
    TEST_ASSERT_TRUE_MESSAGE( target -> initFlag, "Incorrect value, injection failed!" );

    // Call the empty constructor.
    targetObject = CommanderDatabase<int>( testData, TEST_ARRAY_SIZE );

    // Test if the parameters are corrected by the constructor.
    TEST_ASSERT_EQUAL_PTR( testData, target -> dataTree );
    TEST_ASSERT_EQUAL_INT( TEST_ARRAY_SIZE, target -> dataTreeSize );
    TEST_ASSERT_EQUAL_PTR( NULL, target -> debugChannel );
    TEST_ASSERT_EQUAL_INT( (int)CommanderDatabase<int>::DEBUG_OFF, target -> debugLevel );
    TEST_ASSERT_FALSE( target -> initFlag );

}

void testConstructor_dataRecord_t_uint16_t(){
    testerObject.testConstructor_dataRecord_t_uint16_t();
}

void CommanderDatabaseUT::test_getSize(){

    // Call the constructor.
    targetObject = CommanderDatabase<int>( testData, TEST_ARRAY_SIZE );

    TEST_ASSERT_EQUAL_INT( TEST_ARRAY_SIZE, target -> getSize() );

}

void test_getSize(){
    testerObject.test_getSize();
}

int main(){

    UNITY_BEGIN();

    RUN_TEST( testConstructor_empty );
    RUN_TEST( testConstructor_dataRecord_t_uint16_t );
    RUN_TEST( test_getSize );

    return UNITY_END();

}