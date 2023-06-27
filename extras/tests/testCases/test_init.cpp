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

#define FIRST_FUNC_NAME  "firstFunc"
#define FIRST_FUNC_DESC  "To test first function call."

#define SECOND_FUNC_NAME "secondFunc"
#define SECOND_FUNC_DESC "To test second function call."

#define THIRD_FUNC_NAME  "thirdFunc"
#define THIRD_FUNC_DESC  "To test third function call."

#define FOURTH_FUNC_NAME  "fourthFunc"
#define FOURTH_FUNC_DESC  "To test fourth function call."

#define PARENT_ADDRESS_TEST 0xC0FE

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
}

void second_func( char *args, Stream *response, void* parent ){
    lastCommandFuncPtr = &second_func;
    lastCommandArgs = args;
    lastCommandStream = response;
    lastCommandParent = parent;
}

void third_func( char *args, Stream *response, void* parent ){
    lastCommandFuncPtr = &third_func;
    lastCommandArgs = args;
    lastCommandStream = response;
    lastCommandParent = parent;
}

void fourth_func( char *args, Stream *response, void* parent ){
    lastCommandFuncPtr = &fourth_func;
    lastCommandArgs = args;
    lastCommandStream = response;
    lastCommandParent = parent;
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

void test_function_call(void){

    // Clear the Tx buffer before the test.
    testChannel.clearTx();

    // Clear the Rx buffer before the test.
    testChannel.clearRx();

    // Call the first function
    lastCommandFuncPtr = NULL;
    lastCommandArgs    = NULL;
    lastCommandStream  = NULL;
    lastCommandParent  = NULL;

    commander.execute( (char*)FIRST_FUNC_NAME, &testChannel, (void*)PARENT_ADDRESS_TEST );
    TEST_ASSERT_EQUAL_PTR ( first_func, lastCommandFuncPtr );
    TEST_ASSERT_EQUAL_PTR ( lastCommandStream, &testChannel );
    TEST_ASSERT_EQUAL_PTR ( lastCommandParent, (void*)PARENT_ADDRESS_TEST );
    TEST_ASSERT_EQUAL_STRING( lastCommandArgs, "" );

    // Call the second function
    lastCommandFuncPtr = NULL;
    lastCommandArgs    = NULL;
    lastCommandStream  = NULL;
    lastCommandParent  = NULL;

    commander.execute( (char*)SECOND_FUNC_NAME, &testChannel, (void*)PARENT_ADDRESS_TEST );
    TEST_ASSERT_EQUAL_PTR ( second_func, lastCommandFuncPtr );
    TEST_ASSERT_EQUAL_PTR ( lastCommandStream, &testChannel );
    TEST_ASSERT_EQUAL_PTR ( lastCommandParent, (void*)PARENT_ADDRESS_TEST );
    TEST_ASSERT_EQUAL_STRING( lastCommandArgs, "" );

    // Call the third function
    lastCommandFuncPtr = NULL;
    lastCommandArgs    = NULL;
    lastCommandStream  = NULL;
    lastCommandParent  = NULL;

    commander.execute( (char*)THIRD_FUNC_NAME, &testChannel, (void*)PARENT_ADDRESS_TEST );
    TEST_ASSERT_EQUAL_PTR ( third_func, lastCommandFuncPtr );
    TEST_ASSERT_EQUAL_PTR ( lastCommandStream, &testChannel );
    TEST_ASSERT_EQUAL_PTR ( lastCommandParent, (void*)PARENT_ADDRESS_TEST );
    TEST_ASSERT_EQUAL_STRING( lastCommandArgs, "" );

    // Call the fourth function
    lastCommandFuncPtr = NULL;
    lastCommandArgs    = NULL;
    lastCommandStream  = NULL;
    lastCommandParent  = NULL;

    commander.execute( (char*)FOURTH_FUNC_NAME, &testChannel, (void*)PARENT_ADDRESS_TEST );
    TEST_ASSERT_EQUAL_PTR ( fourth_func, lastCommandFuncPtr );
    TEST_ASSERT_EQUAL_PTR ( lastCommandStream, &testChannel );
    TEST_ASSERT_EQUAL_PTR ( lastCommandParent, (void*)PARENT_ADDRESS_TEST );
    TEST_ASSERT_EQUAL_STRING( lastCommandArgs, "" );

}

void test_function_call_simple(void){

    // Clear the Tx buffer before the test.
    testChannel.clearTx();

    // Clear the Rx buffer before the test.
    testChannel.clearRx();

    // Call the first function
    lastCommandFuncPtr = NULL;
    lastCommandArgs    = NULL;
    lastCommandStream  = NULL;

    commander.execute( (char*)FIRST_FUNC_NAME, &testChannel );
    TEST_ASSERT_EQUAL_PTR ( first_func, lastCommandFuncPtr );
    TEST_ASSERT_EQUAL_PTR ( lastCommandStream, &testChannel );
    TEST_ASSERT_EQUAL_STRING( lastCommandArgs, "" );

    // Call the second function
    lastCommandFuncPtr = NULL;
    lastCommandArgs    = NULL;
    lastCommandStream  = NULL;
    lastCommandParent  = NULL;

    commander.execute( (char*)SECOND_FUNC_NAME, &testChannel );
    TEST_ASSERT_EQUAL_PTR ( second_func, lastCommandFuncPtr );
    TEST_ASSERT_EQUAL_PTR ( lastCommandStream, &testChannel );
    TEST_ASSERT_EQUAL_STRING( lastCommandArgs, "" );

    // Call the third function
    lastCommandFuncPtr = NULL;
    lastCommandArgs    = NULL;
    lastCommandStream  = NULL;
    lastCommandParent  = NULL;

    commander.execute( (char*)THIRD_FUNC_NAME, &testChannel );
    TEST_ASSERT_EQUAL_PTR ( third_func, lastCommandFuncPtr );
    TEST_ASSERT_EQUAL_PTR ( lastCommandStream, &testChannel );
    TEST_ASSERT_EQUAL_STRING( lastCommandArgs, "" );

    // Call the fourth function
    lastCommandFuncPtr = NULL;
    lastCommandArgs    = NULL;
    lastCommandStream  = NULL;
    lastCommandParent  = NULL;

    commander.execute( (char*)FOURTH_FUNC_NAME, &testChannel );
    TEST_ASSERT_EQUAL_PTR ( fourth_func, lastCommandFuncPtr );
    TEST_ASSERT_EQUAL_PTR ( lastCommandStream, &testChannel );
    TEST_ASSERT_EQUAL_STRING( lastCommandArgs, "" );

}

void test_function_call_simplest(void){

    // Clear the Tx buffer before the test.
    testChannel.clearTx();

    // Clear the Rx buffer before the test.
    testChannel.clearRx();

    // Call the first function
    lastCommandFuncPtr = NULL;
    lastCommandArgs    = NULL;

    commander.execute( (char*)FIRST_FUNC_NAME );
    TEST_ASSERT_EQUAL_PTR ( first_func, lastCommandFuncPtr );
    TEST_ASSERT_EQUAL_STRING( lastCommandArgs, "" );

    // Call the second function
    lastCommandFuncPtr = NULL;
    lastCommandArgs    = NULL;
    lastCommandStream  = NULL;
    lastCommandParent  = NULL;

    commander.execute( (char*)SECOND_FUNC_NAME );
    TEST_ASSERT_EQUAL_PTR ( second_func, lastCommandFuncPtr );
    TEST_ASSERT_EQUAL_STRING( lastCommandArgs, "" );

    // Call the third function
    lastCommandFuncPtr = NULL;
    lastCommandArgs    = NULL;
    lastCommandStream  = NULL;
    lastCommandParent  = NULL;

    commander.execute( (char*)THIRD_FUNC_NAME );
    TEST_ASSERT_EQUAL_PTR ( third_func, lastCommandFuncPtr );
    TEST_ASSERT_EQUAL_STRING( lastCommandArgs, "" );

    // Call the fourth function
    lastCommandFuncPtr = NULL;
    lastCommandArgs    = NULL;
    lastCommandStream  = NULL;
    lastCommandParent  = NULL;

    commander.execute( (char*)FOURTH_FUNC_NAME );
    TEST_ASSERT_EQUAL_PTR ( fourth_func, lastCommandFuncPtr );
    TEST_ASSERT_EQUAL_STRING( lastCommandArgs, "" );

}

void test_function_call_const(void){

    // Clear the Tx buffer before the test.
    testChannel.clearTx();

    // Clear the Rx buffer before the test.
    testChannel.clearRx();

    // Call the first function
    lastCommandFuncPtr = NULL;
    lastCommandArgs    = NULL;
    lastCommandStream  = NULL;
    lastCommandParent  = NULL;

    commander.execute( FIRST_FUNC_NAME, &testChannel, (void*)PARENT_ADDRESS_TEST );
    TEST_ASSERT_EQUAL_PTR ( first_func, lastCommandFuncPtr );
    TEST_ASSERT_EQUAL_PTR ( lastCommandStream, &testChannel );
    TEST_ASSERT_EQUAL_PTR ( lastCommandParent, (void*)PARENT_ADDRESS_TEST );
    TEST_ASSERT_EQUAL_STRING( lastCommandArgs, "" );

    // Call the second function
    lastCommandFuncPtr = NULL;
    lastCommandArgs    = NULL;
    lastCommandStream  = NULL;
    lastCommandParent  = NULL;

    commander.execute( SECOND_FUNC_NAME, &testChannel, (void*)PARENT_ADDRESS_TEST );
    TEST_ASSERT_EQUAL_PTR ( second_func, lastCommandFuncPtr );
    TEST_ASSERT_EQUAL_PTR ( lastCommandStream, &testChannel );
    TEST_ASSERT_EQUAL_PTR ( lastCommandParent, (void*)PARENT_ADDRESS_TEST );
    TEST_ASSERT_EQUAL_STRING( lastCommandArgs, "" );

    // Call the third function
    lastCommandFuncPtr = NULL;
    lastCommandArgs    = NULL;
    lastCommandStream  = NULL;
    lastCommandParent  = NULL;

    commander.execute( THIRD_FUNC_NAME, &testChannel, (void*)PARENT_ADDRESS_TEST );
    TEST_ASSERT_EQUAL_PTR ( third_func, lastCommandFuncPtr );
    TEST_ASSERT_EQUAL_PTR ( lastCommandStream, &testChannel );
    TEST_ASSERT_EQUAL_PTR ( lastCommandParent, (void*)PARENT_ADDRESS_TEST );
    TEST_ASSERT_EQUAL_STRING( lastCommandArgs, "" );

    // Call the fourth function
    lastCommandFuncPtr = NULL;
    lastCommandArgs    = NULL;
    lastCommandStream  = NULL;
    lastCommandParent  = NULL;

    commander.execute( FOURTH_FUNC_NAME, &testChannel, (void*)PARENT_ADDRESS_TEST );
    TEST_ASSERT_EQUAL_PTR ( fourth_func, lastCommandFuncPtr );
    TEST_ASSERT_EQUAL_PTR ( lastCommandStream, &testChannel );
    TEST_ASSERT_EQUAL_PTR ( lastCommandParent, (void*)PARENT_ADDRESS_TEST );
    TEST_ASSERT_EQUAL_STRING( lastCommandArgs, "" );

}

void test_function_call_simple_const(void){

    // Clear the Tx buffer before the test.
    testChannel.clearTx();

    // Clear the Rx buffer before the test.
    testChannel.clearRx();

    // Call the first function
    lastCommandFuncPtr = NULL;
    lastCommandArgs    = NULL;
    lastCommandStream  = NULL;

    commander.execute( FIRST_FUNC_NAME, &testChannel );
    TEST_ASSERT_EQUAL_PTR ( first_func, lastCommandFuncPtr );
    TEST_ASSERT_EQUAL_PTR ( lastCommandStream, &testChannel );
    TEST_ASSERT_EQUAL_STRING( lastCommandArgs, "" );

    // Call the second function
    lastCommandFuncPtr = NULL;
    lastCommandArgs    = NULL;
    lastCommandStream  = NULL;
    lastCommandParent  = NULL;

    commander.execute( SECOND_FUNC_NAME, &testChannel );
    TEST_ASSERT_EQUAL_PTR ( second_func, lastCommandFuncPtr );
    TEST_ASSERT_EQUAL_PTR ( lastCommandStream, &testChannel );
    TEST_ASSERT_EQUAL_STRING( lastCommandArgs, "" );

    // Call the third function
    lastCommandFuncPtr = NULL;
    lastCommandArgs    = NULL;
    lastCommandStream  = NULL;
    lastCommandParent  = NULL;

    commander.execute( THIRD_FUNC_NAME, &testChannel );
    TEST_ASSERT_EQUAL_PTR ( third_func, lastCommandFuncPtr );
    TEST_ASSERT_EQUAL_PTR ( lastCommandStream, &testChannel );
    TEST_ASSERT_EQUAL_STRING( lastCommandArgs, "" );

    // Call the fourth function
    lastCommandFuncPtr = NULL;
    lastCommandArgs    = NULL;
    lastCommandStream  = NULL;
    lastCommandParent  = NULL;

    commander.execute( FOURTH_FUNC_NAME, &testChannel );
    TEST_ASSERT_EQUAL_PTR ( fourth_func, lastCommandFuncPtr );
    TEST_ASSERT_EQUAL_PTR ( lastCommandStream, &testChannel );
    TEST_ASSERT_EQUAL_STRING( lastCommandArgs, "" );

}

void test_function_call_simplest_const(void){

    // Clear the Tx buffer before the test.
    testChannel.clearTx();

    // Clear the Rx buffer before the test.
    testChannel.clearRx();

    // Call the first function
    lastCommandFuncPtr = NULL;
    lastCommandArgs    = NULL;

    commander.execute( FIRST_FUNC_NAME );
    TEST_ASSERT_EQUAL_PTR ( first_func, lastCommandFuncPtr );
    TEST_ASSERT_EQUAL_STRING( lastCommandArgs, "" );

    // Call the second function
    lastCommandFuncPtr = NULL;
    lastCommandArgs    = NULL;
    lastCommandStream  = NULL;
    lastCommandParent  = NULL;

    commander.execute( SECOND_FUNC_NAME );
    TEST_ASSERT_EQUAL_PTR ( second_func, lastCommandFuncPtr );
    TEST_ASSERT_EQUAL_STRING( lastCommandArgs, "" );

    // Call the third function
    lastCommandFuncPtr = NULL;
    lastCommandArgs    = NULL;
    lastCommandStream  = NULL;
    lastCommandParent  = NULL;

    commander.execute( THIRD_FUNC_NAME );
    TEST_ASSERT_EQUAL_PTR ( third_func, lastCommandFuncPtr );
    TEST_ASSERT_EQUAL_STRING( lastCommandArgs, "" );

    // Call the fourth function
    lastCommandFuncPtr = NULL;
    lastCommandArgs    = NULL;
    lastCommandStream  = NULL;
    lastCommandParent  = NULL;

    commander.execute( FOURTH_FUNC_NAME );
    TEST_ASSERT_EQUAL_PTR ( fourth_func, lastCommandFuncPtr );
    TEST_ASSERT_EQUAL_STRING( lastCommandArgs, "" );

}

void test_help_command(void){

    char expected[10000];

    snprintf(   expected,
                sizeof( expected ),
                "---- Available commands ----\r\n\r\n%s\r\n%s\r\n%s\r\n%s\r\n",
                API_tree[ commander.find_api_index_by_place( 0 ) ].name,
                API_tree[ commander.find_api_index_by_place( 1 ) ].name,
                API_tree[ commander.find_api_index_by_place( 2 ) ].name,
                API_tree[ commander.find_api_index_by_place( 3 ) ].name );

    // Clear the Tx buffer before the test.
    testChannel.clearTx();

    // Clear the Rx buffer before the test.
    testChannel.clearRx();

    // Execute help command
    commander.execute( "help", &testChannel );

    // Check the buffer content. It should match with the known data string.
    TEST_ASSERT_EQUAL_STRING ( (const char*)expected, testChannel.txBuffer );

}

void test_help_command_description(void){

    char expected[10000];

    snprintf(   expected,
                sizeof( expected ),
                "---- Available commands ----\r\n\r\n%s:\r\n\t%s\r\n\r\n%s:\r\n\t%s\r\n\r\n%s:\r\n\t%s\r\n\r\n%s:\r\n\t%s\r\n\r\n",
                API_tree[ commander.find_api_index_by_place( 0 ) ].name,
                API_tree[ commander.find_api_index_by_place( 0 ) ].desc,
                API_tree[ commander.find_api_index_by_place( 1 ) ].name,
                API_tree[ commander.find_api_index_by_place( 1 ) ].desc,
                API_tree[ commander.find_api_index_by_place( 2 ) ].name,
                API_tree[ commander.find_api_index_by_place( 2 ) ].desc,
                API_tree[ commander.find_api_index_by_place( 3 ) ].name,
                API_tree[ commander.find_api_index_by_place( 3 ) ].desc );

    // Clear the Tx buffer before the test.
    testChannel.clearTx();

    // Clear the Rx buffer before the test.
    testChannel.clearRx();

    // Execute help command with description.
    commander.execute( "help -d", &testChannel );

    // Check the buffer content. It should match with the known data string.
    TEST_ASSERT_EQUAL_STRING ( (const char*)expected, testChannel.txBuffer );

}

void test_help_function(void){

    char expected[10000];

    snprintf(   expected,
                sizeof( expected ),
                "---- Available commands ----\r\n\r\n%s:\r\n\t%s\r\n\r\n%s:\r\n\t%s\r\n\r\n%s:\r\n\t%s\r\n\r\n%s:\r\n\t%s\r\n\r\n",
                API_tree[ commander.find_api_index_by_place( 0 ) ].name,
                API_tree[ commander.find_api_index_by_place( 0 ) ].desc,
                API_tree[ commander.find_api_index_by_place( 1 ) ].name,
                API_tree[ commander.find_api_index_by_place( 1 ) ].desc,
                API_tree[ commander.find_api_index_by_place( 2 ) ].name,
                API_tree[ commander.find_api_index_by_place( 2 ) ].desc,
                API_tree[ commander.find_api_index_by_place( 3 ) ].name,
                API_tree[ commander.find_api_index_by_place( 3 ) ].desc );

    // Clear the Tx buffer before the test.
    testChannel.clearTx();

    // Clear the Rx buffer before the test.
    testChannel.clearRx();

    // Print help without style.
    commander.printHelp( &testChannel, true, false );

    // Check the buffer content. It should match with the known data string.
    TEST_ASSERT_EQUAL_STRING ( (const char*)expected, testChannel.txBuffer );

}


void test_help_function_style(void){

    char expected[10000];

    snprintf(   expected,
                sizeof( expected ),
                "\x1B[1;31m----\x1B[1;32m Available commands \x1B[1;31m----\x1B[0;37m\r\n\r\n\x1B[1;32m%s\x1B[0;37m: %s\r\n\x1B[1;32m%s\x1B[0;37m: %s\r\n\x1B[1;32m%s\x1B[0;37m: %s\r\n\x1B[1;32m%s\x1B[0;37m: %s\r\n",
                API_tree[ commander.find_api_index_by_place( 0 ) ].name,
                API_tree[ commander.find_api_index_by_place( 0 ) ].desc,
                API_tree[ commander.find_api_index_by_place( 1 ) ].name,
                API_tree[ commander.find_api_index_by_place( 1 ) ].desc,
                API_tree[ commander.find_api_index_by_place( 2 ) ].name,
                API_tree[ commander.find_api_index_by_place( 2 ) ].desc,
                API_tree[ commander.find_api_index_by_place( 3 ) ].name,
                API_tree[ commander.find_api_index_by_place( 3 ) ].desc );

    // Clear the Tx buffer before the test.
    testChannel.clearTx();

    // Clear the Rx buffer before the test.
    testChannel.clearRx();

    // Print help without style.
    commander.printHelp( &testChannel, true, true );

    // Check the buffer content. It should match with the known data string.
    TEST_ASSERT_EQUAL_STRING ( (const char*)expected, testChannel.txBuffer );

}

void test_description(void){

    char command[ 10000 ];
    char expected[ 10000 ];

    snprintf( command, sizeof( command ), "%s?", FIRST_FUNC_NAME );
    snprintf( expected, sizeof( expected ), "%s: %s\r\n", FIRST_FUNC_NAME, FIRST_FUNC_DESC );

    // Clear the Tx buffer before the test.
    testChannel.clearTx();

    // Clear the Rx buffer before the test.
    testChannel.clearRx();

    // Initialize Commander.
    commander.execute( command, &testChannel );

    // Check the buffer content. It should match with the known data string.
    TEST_ASSERT_EQUAL_STRING ( expected, testChannel.txBuffer );

}

void test_not_found(void){

    char command[ 10000 ] = "avada_kedavra";
    char expected[ 10000 ];

    snprintf( expected, sizeof( expected ), "Command '%s' not found!\r\n", command );

    // Clear the Tx buffer before the test.
    testChannel.clearTx();

    // Clear the Rx buffer before the test.
    testChannel.clearRx();

    // Initialize Commander.
    commander.execute( command, &testChannel );

    // Check the buffer content. It should match with the known data string.
    TEST_ASSERT_EQUAL_STRING ( expected, testChannel.txBuffer );

}

int main(){

    UNITY_BEGIN();

    RUN_TEST( test_attach_tree );
    RUN_TEST( test_init );

    RUN_TEST( test_function_call );
    RUN_TEST( test_function_call_simple );
    RUN_TEST( test_function_call_simplest );
    
    RUN_TEST( test_function_call_const );
    RUN_TEST( test_function_call_simple_const );
    RUN_TEST( test_function_call_simplest_const );
    
    RUN_TEST( test_help_command );
    RUN_TEST( test_help_command_description );
    RUN_TEST( test_help_function );
    RUN_TEST( test_help_function_style );

    RUN_TEST( test_description );

    RUN_TEST( test_not_found );

    return UNITY_END();

}