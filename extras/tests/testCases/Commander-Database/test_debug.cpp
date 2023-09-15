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
    void test_attachDebugChannel();
    void test_setDebugLevel();

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

void CommanderDatabaseUT::test_attachDebugChannel(){

    // Call the empty constructor.
    targetObject = CommanderDatabase<int>();

    target -> attachDebugChannel( (Stream*)100 );

    // Test if debug channel is saved correctly.
    TEST_ASSERT_EQUAL_PTR( 100, target -> debugChannel );

}

void test_attachDebugChannel( void ){
    testerObject.test_attachDebugChannel();
}

void CommanderDatabaseUT::test_setDebugLevel(){

    // Call the empty constructor.
    targetObject = CommanderDatabase<int>();

    target -> setDebugLevel( CommanderDatabase<int>::DEBUG_VERBOSE );

    // Test if debug channel is saved correctly.
    TEST_ASSERT_EQUAL_INT( (int)CommanderDatabase<int>::DEBUG_VERBOSE, target -> debugLevel );

}

void test_setDebugLevel( void ){
    testerObject.test_setDebugLevel();
}

int main(){

    UNITY_BEGIN();

    RUN_TEST( test_attachDebugChannel );
    RUN_TEST( test_setDebugLevel );

    return UNITY_END();

}