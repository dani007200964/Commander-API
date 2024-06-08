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
    void test_pipe();

    void test_pipe_without_proper_init();

};


Commander targetObject;
CommanderUT testerObject( &targetObject );

testStream streamObject;

char* lastArg;
Stream* lastResponse;
void* lastParent;
bool(*lastFunc)( char *, Stream *, void* );

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

    if( args != NULL ){
        if( args[ 0 ] == '3' ){
            return true;
        }
    }
    return false;
}

bool command_4_func( char *args, Stream *response, void* parent ){
    lastArg = args;
    lastResponse = response;
    lastParent = parent;
    lastFunc = command_4_func;

    if( args != NULL ){
        if( args[ 0 ] == '4' ){
            return true;
        }
    }
    return false;
}

bool command_5_func( char *args, Stream *response, void* parent ){
    lastArg = args;
    lastResponse = response;
    lastParent = parent;
    lastFunc = command_5_func;
    
    if( response ){
        response -> print( '3' );
    }

    return true;
}

Commander::systemCommand_t API_tree[] = {
    systemCommand( "command_1", "Description for command 1", command_1_func ),
    systemCommand( "command_2", "Description for command 2", command_2_func ),
    systemCommand( "command_3", "Description for command 3", command_3_func ),
    systemCommand( "command_4", "Description for command 4", command_4_func ),
    systemCommand( "command_5", "Description for command 5", command_5_func )
};

typedef struct{

    const char *command;

    bool expectedReturnStatus;
    const char* expectedArgs;
    bool(*expectedFunc)( char *, Stream *, void* );

}functionCallResult_t;

functionCallResult_t combinations[] = {
    { "command_1 | command_2",              true,   NULL, command_2_func },
    { "command_1 |command_2",               true,   NULL, command_2_func },
    { "command_1| command_2",               true,   NULL, command_2_func },
    { "command_1|command_2",                true,   NULL, command_2_func },
    { "command_2 | command_1",              true,   NULL, command_1_func },
    { "command_2 | command_1 | command_5",  true,   NULL, command_5_func },
    { "command_2 | command",                false,  NULL, NULL },
    { "command | command_1",                false,  NULL, NULL },
    { "command_5 | command_3",              true,   NULL, command_3_func },
    { "command_5 | command_4",              false,  NULL, NULL },
    { "command_5 | command_6 | reboot",     false,  NULL, NULL }
};

int numberOfCombinations = sizeof( combinations ) / sizeof( combinations[ 0 ] );

char pipeBuffer[ COMMANDER_PIPE_BUFFER_SIZE ];
char pipeBufferWrong[ COMMANDER_PIPE_BUFFER_SIZE + 1 ];
commanderPipeChannel pipeChannel;

// Put any init code here that needs to run before testing.
void setUp(void) {
    bool stat;

    targetObject = Commander();

    targetObject.attachTree( API_tree );

    pipeChannel = commanderPipeChannel();

    // Testing wrong init.
    stat = targetObject.enablePipeModule( pipeBufferWrong, &pipeChannel );
    TEST_ASSERT_FALSE( stat );

    stat = targetObject.enablePipeModule( pipeBuffer, NULL );
    TEST_ASSERT_FALSE( stat );

    stat = targetObject.enablePipeModuleFunc( NULL, 100, &pipeChannel );
    TEST_ASSERT_FALSE( stat );

    stat = targetObject.enablePipeModuleFunc( pipeBufferWrong, 0, &pipeChannel );
    TEST_ASSERT_FALSE( stat );

    // Testing correct init.
    stat = targetObject.enablePipeModule( pipeBuffer, &pipeChannel );
    TEST_ASSERT_TRUE( stat );

    stat = targetObject.init();
    TEST_ASSERT_TRUE( stat );

}

// Put any init code here that needs to run after testing.
void tearDown(void) {

}

void CommanderUT::test_pipe(){

    bool stat;
    int i;
    char buff[ 1000 ];

    snprintf( buff, sizeof( buff ), "Number of combinations %d", numberOfCombinations );
    TEST_MESSAGE( buff );

    for( i = 0; i < numberOfCombinations; i++ ){

        lastFunc = NULL;
        lastArg = NULL;
        lastParent = NULL;

        streamObject.clearRx();
        streamObject.clearTx();

        stat = target -> execute( combinations[ i ].command, &streamObject );

        snprintf( buff, sizeof( buff ), "index: %d command: %s message: %s --RETURN STATUS--", i, combinations[ i ].command, streamObject.txBuffer );
        TEST_ASSERT_EQUAL_MESSAGE( combinations[ i ].expectedReturnStatus, stat, buff );

        if( combinations[ i ].expectedFunc ){
            snprintf( buff, sizeof( buff ), "index: %d command: %s --FUNCTION POINTER--", i, combinations[ i ].command );
            TEST_ASSERT_EQUAL_PTR_MESSAGE( combinations[ i ].expectedFunc, lastFunc, buff );
        }

        if( combinations[ i ].expectedArgs ){
            snprintf( buff, sizeof( buff ), "index: %d command: %s --ARGUMENT POINTER--", i, combinations[ i ].command );
            TEST_ASSERT_EQUAL_STRING_MESSAGE( combinations[ i ].expectedArgs, lastArg, buff );
        }

    }

}

void test_pipe( void ){
    testerObject.test_pipe();
}

void CommanderUT::test_pipe_without_proper_init(){

    bool stat;

    targetObject = Commander();

    targetObject.attachTree( API_tree );

    stat = targetObject.init();
    TEST_ASSERT_TRUE( stat );

    streamObject.clearRx();
    streamObject.clearTx();

    stat = targetObject.execute( "command_1 | command_2", &streamObject );
    TEST_ASSERT_FALSE( stat );

}

void test_pipe_without_proper_init( void ){
    testerObject.test_pipe_without_proper_init();
}

int main(){

    UNITY_BEGIN();

    RUN_TEST( test_pipe );
    RUN_TEST( test_pipe_without_proper_init );

    return UNITY_END();

}