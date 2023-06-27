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

/*

This code is used for unit test. It will test the following test cases:
    - sencBackspace() funcion.
    - clear() funcion.

*/

#include <stdio.h>

// Commander-API Library
#include "Commander-API.hpp"
#include "Commander-IO.hpp"

// Stream class for testing
#include "../testStream.hpp"

// Unit test module.
#include "unity.h"

// For timing.
#include "System.h"

#define FIRST_FUNC_NAME     "firstFunc"
#define FIRST_FUNC_DESC     "To test first function call."
#define FIRST_FUNC_REPLY    "FIRST REPLY"

#define SECOND_FUNC_NAME    "secondFunc"
#define SECOND_FUNC_DESC    "To test second function call."
#define SECOND_FUNC_REPLY   "SECOND REPLY"

#define THIRD_FUNC_NAME     "thirdFunc"
#define THIRD_FUNC_DESC     "To test third function call."
#define THIRD_FUNC_REPLY    "THIRD REPLY"

#define FOURTH_FUNC_NAME    "fourthFunc"
#define FOURTH_FUNC_DESC    "To test fourth function call."
#define FOURTH_FUNC_REPLY   "FOURTH REPLY"

// Use stdio as Channel.
testStream testChannel;

// We have to create an object from Commander class.
Commander commander;

// This function pointer tracks the last command function call's address.
void( *lastCommandFuncPtr )( char*, Stream*, void* ) = NULL;

char* lastCommandArgs = NULL;

Stream* lastCommandStream = NULL;

void* lastCommandParent = NULL;



// We have to create the prototype functions for our commands.
// The arguments has to be the same for all command functions.
void first_func( char *args, Stream *response, void* parent ){
    lastCommandFuncPtr = &first_func;
    lastCommandArgs = args;
    lastCommandStream = response;
    lastCommandParent = parent;

    response -> print( FIRST_FUNC_REPLY );

}

void second_func( char *args, Stream *response, void* parent ){
    lastCommandFuncPtr = &second_func;
    lastCommandArgs = args;
    lastCommandStream = response;
    lastCommandParent = parent;

    if( strcmp( args, FIRST_FUNC_REPLY ) == 0 ){

        response -> print( SECOND_FUNC_REPLY );

    }

    else{

        response -> print( "NOPE" );

    }

}

void third_func( char *args, Stream *response, void* parent ){
    lastCommandFuncPtr = &third_func;
    lastCommandArgs = args;
    lastCommandStream = response;
    lastCommandParent = parent;

    if( strcmp( args, SECOND_FUNC_REPLY ) == 0 ){

        response -> print( THIRD_FUNC_REPLY );

    }

    else{

        response -> print( "NOPE" );

    }

}

void fourth_func( char *args, Stream *response, void* parent ){
    lastCommandFuncPtr = &fourth_func;
    lastCommandArgs = args;
    lastCommandStream = response;
    lastCommandParent = parent;

    if( strcmp( args, THIRD_FUNC_REPLY ) == 0 ){

        response -> print( FOURTH_FUNC_REPLY );

    }

    else{

        response -> print( "NOPE" );

    }

}

// Commander API-tree
Commander::API_t API_tree[] = {
    apiElement( FIRST_FUNC_NAME,  FIRST_FUNC_DESC,  first_func ),
    apiElement( SECOND_FUNC_NAME, SECOND_FUNC_DESC, second_func ),
    apiElement( THIRD_FUNC_NAME,  THIRD_FUNC_DESC,  third_func ),
    apiElement( FOURTH_FUNC_NAME, FOURTH_FUNC_DESC, fourth_func )
};

// Put any init code here that needs to run before testing.
void setUp(void) {
  
}

// Put any init code here that needs to run after testing.
void tearDown(void) {

}

void test_attach_tree(void){

    char expected[] = "API tree attached with 4 commands.\r\n";

    commander.attachDebugChannel( &testChannel );

    // Clear the Tx buffer before the test.
    testChannel.clearTx();

    // Clear the Rx buffer before the test.
    testChannel.clearRx();

    // Attach the API tree to Commander.
    commander.attachTree( API_tree );

    // Check the buffer content. It should match with the known data string.
    TEST_ASSERT_EQUAL_STRING ( (const char*)expected, testChannel.txBuffer );

}

void test_init(void){

    char expected[] = "Commander init start\r\n  Creating alphabetical order... [ OK ]\r\n  Create balanced binary structure... [ OK ]\r\nCommander init finished!\r\n";

    // Clear the Tx buffer before the test.
    testChannel.clearTx();

    // Clear the Rx buffer before the test.
    testChannel.clearRx();

    // Initialize Commander.
    commander.init();

    // Check the buffer content. It should match with the known data string.
    TEST_ASSERT_EQUAL_STRING ( (const char*)expected, testChannel.txBuffer );

}

void test_pipe(void){

    char command[ 10000 ];

    snprintf(   command, sizeof( command ), "%s|%s | %s |%s",
                FIRST_FUNC_NAME,
                SECOND_FUNC_NAME,
                THIRD_FUNC_NAME,
                FOURTH_FUNC_NAME );

    // Clear the Tx buffer before the test.
    testChannel.clearTx();

    // Clear the Rx buffer before the test.
    testChannel.clearRx();

    // Initialize Commander.
    commander.execute( command, &testChannel );

    // Check the buffer content. It should match with the known data string.
    TEST_ASSERT_EQUAL_STRING ( FOURTH_FUNC_REPLY, testChannel.txBuffer );

}

int main(){

    UNITY_BEGIN();

    RUN_TEST( test_attach_tree );
    RUN_TEST( test_init );

    RUN_TEST( test_pipe );

    return UNITY_END();

}