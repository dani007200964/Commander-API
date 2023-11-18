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
    void testInit();
    void testInitBad();

    void testSetDebugLevel();
    void testSetDebugChannel();

    void testInitWithDebugChannel();

};


Commander targetObject;
CommanderUT testerObject( &targetObject );

testStream streamObject;

char* lastArg;
Stream* lastResponse;
void* lastParent;
bool(*lastFunc)( char *, Stream *, void* );

// Put any init code here that needs to run before testing.
void setUp(void) {
  
}

// Put any init code here that needs to run after testing.
void tearDown(void) {

}

bool command_1_func( char *args, Stream *response, void* parent ){
    lastArg = args;
    lastResponse = response;
    lastParent = parent;
    lastFunc = command_1_func;
    return true;
}

bool command_2_func( char *args, Stream *response, void* parent ){
    lastArg = args;
    lastResponse = response;
    lastParent = parent;
    lastFunc = command_2_func;
    return true;
}

bool command_3_func( char *args, Stream *response, void* parent ){
    lastArg = args;
    lastResponse = response;
    lastParent = parent;
    lastFunc = command_3_func;
    return true;
}

bool command_4_func( char *args, Stream *response, void* parent ){
    lastArg = args;
    lastResponse = response;
    lastParent = parent;
    lastFunc = command_4_func;
    return true;
}

bool command_5_func( char *args, Stream *response, void* parent ){
    lastArg = args;
    lastResponse = response;
    lastParent = parent;
    lastFunc = command_5_func;
    return true;
}

Commander::systemCommand_t API_tree[] = {
    systemCommand( "command_1", "Description for command 1", command_1_func ),
    systemCommand( "command_2", "Description for command 2", command_2_func ),
    systemCommand( "command_3", "Description for command 3", command_3_func ),
    systemCommand( "command_4", "Description for command 4", command_4_func ),
    systemCommand( "command_5", "Description for command 5", command_5_func )
};

Commander::systemCommand_t API_tree_bad[] = {
    systemCommand( "command_1", "Description for command 1", command_1_func ),
    systemCommand( "command_1", "Description for command 1", command_1_func )
};


void CommanderUT::testInit(){

    bool stat;

    target -> attachTree( API_tree_bad );
    TEST_ASSERT_EQUAL_INT( 2, target -> regularCommands.getSize() );

    stat = target -> init();
    TEST_ASSERT_FALSE( stat );

}

void testInit( void ){
    testerObject.testInit();
}

void CommanderUT::testInitBad(){

    bool stat;

    target -> attachTree( API_tree );
    TEST_ASSERT_EQUAL_INT( 5, target -> regularCommands.getSize() );

    stat = target -> init();
    TEST_ASSERT_TRUE( stat );

}

void testInitBad( void ){
    testerObject.testInitBad();
}

void CommanderUT::testSetDebugLevel(){

    target->setDebugLevel( Commander::DEBUG_OFF );
    TEST_ASSERT_EQUAL_INT( Commander::DEBUG_OFF, target -> debugLevel );

    target->setDebugLevel( Commander::DEBUG_ERROR );
    TEST_ASSERT_EQUAL_INT( Commander::DEBUG_ERROR, target -> debugLevel );

    target->setDebugLevel( Commander::DEBUG_DEBUG );
    TEST_ASSERT_EQUAL_INT( Commander::DEBUG_DEBUG, target -> debugLevel );

    target->setDebugLevel( Commander::DEBUG_VERBOSE );
    TEST_ASSERT_EQUAL_INT( Commander::DEBUG_VERBOSE, target -> debugLevel );

}

void testSetDebugLevel( void ){
    testerObject.testSetDebugLevel();
}

void CommanderUT::testSetDebugChannel(){

    bool stat;

    target -> setDebugLevel( Commander::DEBUG_VERBOSE );

    target -> attachDebugChannel( &streamObject );

    TEST_ASSERT_EQUAL_PTR( &streamObject, target -> dbgResponse );

}

void testSetDebugChannel( void ){
    testerObject.testSetDebugChannel();
}

void CommanderUT::testInitWithDebugChannel(){

    bool stat;

    // Test with DEBUG_OFF setting.
    // This case it won't print anything.
    target -> setDebugLevel( Commander::DEBUG_OFF );

    target -> attachDebugChannel( &streamObject );

    streamObject.clearRx();
    streamObject.clearTx();

    target -> attachTree( API_tree );

    TEST_ASSERT_EQUAL_INT( 0, streamObject.txWritePointer );

    // Test with DEBUG_DEBUG setting
    // This case it should print the attached tree size.
    target -> setDebugLevel( Commander::DEBUG_VERBOSE );

    target -> attachDebugChannel( &streamObject );

    streamObject.clearRx();
    streamObject.clearTx();

    target -> attachTree( API_tree );

    TEST_ASSERT_NOT_EQUAL_INT( 0, streamObject.txWritePointer );

    // Try the init with debug.
    streamObject.clearRx();
    streamObject.clearTx();
    stat = target -> init();
    TEST_ASSERT_TRUE( stat );

}

void testInitWithDebugChannel( void ){
    testerObject.testInitWithDebugChannel();
}

int main(){

    UNITY_BEGIN();

    RUN_TEST( testInit );
    RUN_TEST( testInitBad );
 
    RUN_TEST( testSetDebugLevel );
    RUN_TEST( testSetDebugChannel );

    RUN_TEST( testInitWithDebugChannel );

    return UNITY_END();

}