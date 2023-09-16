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

#include "Commander-Arguments.hpp"

// Unit test module.
#include "unity.h"

// For timing.
#include "System.h"

// This class must be used for unit testing.
class ArgumentUT{
public:

    // Internal variable, that stores the address of the target.
    Argument* target;

    // Constructor for the tester class. It has only one parameter
    // which is the address of the target object.
    ArgumentUT( Argument* target_p ){ target = target_p; }

    //---- Test cases ----//
    void testConstructor_constCharPtr_int();
    void testConstructor_constCharPtr_char();

};

Argument targetObject( NULL, 0 );
ArgumentUT testerObject( &targetObject );

// Put any init code here that needs to run before testing.
void setUp(void) {
  
}

// Put any init code here that needs to run after testing.
void tearDown(void) {

}

void ArgumentUT::testConstructor_constCharPtr_int(){

    const char* testData = "test argument list";
    int testPlace = 0;

    // Messing up the data to check if it will be corrected by the empty constructor.
    target -> source = (const char*) 30;
    target -> sourceSize = 10;
    target -> place = 20;
    target -> shortName = 'A';
    target -> longName = (const char*) 40;
    target -> bFields.parsed = true;
    target -> bFields.found = true;

    // Test if the incorrect parameters are passed correctly.
    TEST_ASSERT_EQUAL_PTR_MESSAGE( 30, target -> source, "Incorrect value, injection failed!" );
    TEST_ASSERT_EQUAL_INT_MESSAGE( 10, target -> sourceSize, "Incorrect value, injection failed!" );
    TEST_ASSERT_EQUAL_INT_MESSAGE( 20, target -> place, "Incorrect value, injection failed!" );
    TEST_ASSERT_EQUAL_CHAR_MESSAGE( 'A', target -> shortName, "Incorrect value, injection failed!" );
    TEST_ASSERT_EQUAL_PTR_MESSAGE( 40, target -> longName, "Incorrect value, injection failed!" );
    TEST_ASSERT_TRUE_MESSAGE( target -> bFields.parsed, "Incorrect value, injection failed!" );
    TEST_ASSERT_TRUE_MESSAGE( target -> bFields.found, "Incorrect value, injection failed!" );

    // Call the constructor.
    targetObject = Argument( testData, testPlace );

    // Test if the constructor sets them correctly.
    TEST_ASSERT_EQUAL_PTR_MESSAGE( testData, target -> source, "Incorrect value, injection failed!" );
    TEST_ASSERT_EQUAL_INT_MESSAGE( strlen( testData ), target -> sourceSize, "Incorrect value, injection failed!" );
    TEST_ASSERT_EQUAL_INT_MESSAGE( testPlace, target -> place, "Incorrect value, injection failed!" );
    TEST_ASSERT_EQUAL_CHAR_MESSAGE( '\0', target -> shortName, "Incorrect value, injection failed!" );
    TEST_ASSERT_EQUAL_PTR_MESSAGE( NULL, target -> longName, "Incorrect value, injection failed!" );
    TEST_ASSERT_FALSE_MESSAGE( target -> bFields.parsed, "Incorrect value, injection failed!" );
    TEST_ASSERT_FALSE_MESSAGE( target -> bFields.found, "Incorrect value, injection failed!" );

    // Call the constructor with wrong source parameter.
    targetObject = Argument( NULL, testPlace );

    // Test if the constructor detects the problem.
    TEST_ASSERT_EQUAL_PTR_MESSAGE( NULL, target -> source, "Incorrect value, injection failed!" );
    TEST_ASSERT_EQUAL_INT_MESSAGE( -1, target -> sourceSize, "Incorrect value, injection failed!" );
}

void testConstructor_constCharPtr_int( void ){
    testerObject.testConstructor_constCharPtr_int();
}

void ArgumentUT::testConstructor_constCharPtr_char(){

    const char* testData = "test argument list";
    char testShortName = 's';

    // Messing up the data to check if it will be corrected by the empty constructor.
    target -> source = (const char*) 30;
    target -> sourceSize = 10;
    target -> place = 20;
    target -> shortName = 'A';
    target -> longName = (const char*) 40;
    target -> bFields.parsed = true;
    target -> bFields.found = true;

    // Test if the incorrect parameters are passed correctly.
    TEST_ASSERT_EQUAL_PTR_MESSAGE( 30, target -> source, "Incorrect value, injection failed!" );
    TEST_ASSERT_EQUAL_INT_MESSAGE( 10, target -> sourceSize, "Incorrect value, injection failed!" );
    TEST_ASSERT_EQUAL_INT_MESSAGE( 20, target -> place, "Incorrect value, injection failed!" );
    TEST_ASSERT_EQUAL_CHAR_MESSAGE( 'A', target -> shortName, "Incorrect value, injection failed!" );
    TEST_ASSERT_EQUAL_PTR_MESSAGE( 40, target -> longName, "Incorrect value, injection failed!" );
    TEST_ASSERT_TRUE_MESSAGE( target -> bFields.parsed, "Incorrect value, injection failed!" );
    TEST_ASSERT_TRUE_MESSAGE( target -> bFields.found, "Incorrect value, injection failed!" );

    // Call the constructor.
    targetObject = Argument( testData, testShortName );

    // Test if the constructor sets them correctly.
    TEST_ASSERT_EQUAL_PTR_MESSAGE( testData, target -> source, "Incorrect value, injection failed!" );
    TEST_ASSERT_EQUAL_INT_MESSAGE( strlen( testData ), target -> sourceSize, "Incorrect value, injection failed!" );
    TEST_ASSERT_EQUAL_INT_MESSAGE( -1, target -> place, "Incorrect value, injection failed!" );
    TEST_ASSERT_EQUAL_CHAR_MESSAGE( testShortName, target -> shortName, "Incorrect value, injection failed!" );
    TEST_ASSERT_EQUAL_PTR_MESSAGE( NULL, target -> longName, "Incorrect value, injection failed!" );
    TEST_ASSERT_FALSE_MESSAGE( target -> bFields.parsed, "Incorrect value, injection failed!" );
    TEST_ASSERT_FALSE_MESSAGE( target -> bFields.found, "Incorrect value, injection failed!" );

    // Call the constructor with wrong source parameter.
    targetObject = Argument( NULL, testShortName );

    // Test if the constructor detects the problem.
    TEST_ASSERT_EQUAL_PTR_MESSAGE( NULL, target -> source, "Incorrect value, injection failed!" );
    TEST_ASSERT_EQUAL_INT_MESSAGE( -1, target -> sourceSize, "Incorrect value, injection failed!" );
}

void testConstructor_constCharPtr_char( void ){
    testerObject.testConstructor_constCharPtr_char();
}

int main(){

    UNITY_BEGIN();

    RUN_TEST( testConstructor_constCharPtr_int );
    RUN_TEST( testConstructor_constCharPtr_char );

    return UNITY_END();

}