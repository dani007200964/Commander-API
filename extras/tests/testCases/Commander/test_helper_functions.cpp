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

#include "Commander-API.hpp"

#include <stdio.h>

// Unit test module.
#include "unity.h"

// For timing.
#include "System.h"

#include "../../testStream.hpp"

// This class must be used for unit testing.
class CommanderUT{
public:

    // Internal variable, that stores the address of the target.
    Commander* target;

    // Constructor for the tester class. It has only one parameter
    // which is the address of the target object.
    CommanderUT( Commander* target_p ){ target = target_p; }

    //---- Test cases ----//
    void test_printArgumentError();


};


Commander targetObject;
CommanderUT testerObject( &targetObject );

testStream streamObject;

// Put any init code here that needs to run before testing.
void setUp(void) {

}

// Put any init code here that needs to run after testing.
void tearDown(void) {

}

void CommanderUT::test_printArgumentError(){

    streamObject.clearRx();
    streamObject.clearTx();

    Commander::printArgumentError( &streamObject );
    TEST_ASSERT_EQUAL_STRING( "Argument error!", streamObject.txBuffer );

    streamObject.clearRx();
    streamObject.clearTx();

    Commander::printArgumentError( NULL );
    TEST_ASSERT_EQUAL_INT( 0, streamObject.txWritePointer );

}

void test_printArgumentError( void ){
    testerObject.test_printArgumentError();
}

int main(){

    UNITY_BEGIN();

    RUN_TEST( test_printArgumentError );

    return UNITY_END();

}