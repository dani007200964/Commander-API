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

#include "../../../testStream.hpp"
#include "Commander-API.hpp"
#include "Commander-API-Commands.hpp"

// Unit test module.
#include "unity.h"

// For timing.
#include "System.h"

testStream streamObject;

// Global system variables.
float tmpFloat = 0.0;
int tmpInt = -1300;
const char* tmpStr = "Hello!";

// System Variable array. This array will store the
// name and the instance of the system variables.
Commander::systemVariable_t systemVariables[] = {
    systemVariableFloat( tmpFloat ),
    systemVariableInt( tmpInt ),
    systemVariableString( tmpStr )
};

// Put any init code here that needs to run before testing.
void setUp(void) {
  
}

// Put any init code here that needs to run after testing.
void tearDown(void) {

}

void test_commander_env_func_regular(){

    bool status;
    char expected[ 1000 ];

    // Simple env first run
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_env_func( (char*)"", &streamObject, NULL );

    sprintf( expected, "tmpInt: int = %d\r\ntmpStr: str = %s\r\ntmpFloat: float = %.2f\r\n", tmpInt, tmpStr, tmpFloat );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, expected );
    TEST_ASSERT_TRUE( status );

    // Simple env modified run
    tmpInt = 15;
    tmpFloat = 3.14;

    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_env_func( (char*)"", &streamObject, NULL );

    sprintf( expected, "tmpInt: int = %d\r\ntmpStr: str = %s\r\ntmpFloat: float = %.2f\r\n", tmpInt, tmpStr, tmpFloat );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, expected );
    TEST_ASSERT_TRUE( status );


}

void test_commander_env_func_invalid(){

    bool status;

    // env command without response channel
    status = commander_env_func( (char*)"", NULL, NULL );

    TEST_ASSERT_FALSE( status );

}

void test_commander_echo_func_regular(){

    bool status;
    char expected[ 1000 ] = "echo test";

    // Simple echo text
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_echo_func( expected, &streamObject, NULL );

    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, expected );
    TEST_ASSERT_TRUE( status );

    // Simple echo float system variable.
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_echo_func( (char*)"$tmpFloat", &streamObject, NULL );

    sprintf( expected, "%.5f", tmpFloat );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, expected );
    TEST_ASSERT_TRUE( status );

    // Simple echo int system variable.
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_echo_func( (char*)"$tmpInt", &streamObject, NULL );

    sprintf( expected, "%d", tmpInt );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, expected );
    TEST_ASSERT_TRUE( status );

    // Simple echo string system variable.
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_echo_func( (char*)"$tmpStr", &streamObject, NULL );

    sprintf( expected, "%s", tmpStr );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, expected );
    TEST_ASSERT_TRUE( status );

}

void test_commander_echo_func_invalid(){

    bool status;
    char expected[ 1000 ];

    // Invalid echo system variable.
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_echo_func( (char*)"$notFound", &streamObject, NULL );

    sprintf( expected, "System variable 'notFound' NOT found!" );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, expected );
    TEST_ASSERT_FALSE( status );

    // echo command without response channel
    status = commander_echo_func( (char*)"", NULL, NULL );

    TEST_ASSERT_FALSE( status );

}

void test_commander_exportTarget_func_regular(){

    bool status;

    // Simple exportTarget with float variable.
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_exportTarget_func( (char*)"$tmpFloat", &streamObject, NULL );

    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "" );
    TEST_ASSERT_TRUE( status );

    // Simple exportTarget with int variable.
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_exportTarget_func( (char*)"$tmpInt", &streamObject, NULL );

    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "" );
    TEST_ASSERT_TRUE( status );

}

void test_commander_exportTarget_func_invalid(){

    bool status;

    // Empty target
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_exportTarget_func( (char*)"", &streamObject, NULL );

    TEST_ASSERT_FALSE( status );

    // String target
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_exportTarget_func( (char*)"$tmpStr", &streamObject, NULL );

    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "Argument error! Variable '$tmpStr' is a string. String system variables can not be modified!" );
    TEST_ASSERT_FALSE( status );

    // Invalid target
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_exportTarget_func( (char*)"oops", &streamObject, NULL );

    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "Argument error! Variable 'oops' is not found in the system variables!" );
    TEST_ASSERT_FALSE( status );

    // exportTarget command without response channel
    status = commander_exportTarget_func( (char*)"", NULL, NULL );

    TEST_ASSERT_FALSE( status );

}

void test_commander_export_func_regular(){

    bool status;
    char expected[ 1000 ];

    // Simple export with float to float variable.
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_exportTarget_func( (char*)"$tmpFloat", &streamObject, NULL ); // Set the float system variable as target.

    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "" );
    TEST_ASSERT_TRUE( status );

    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_export_func( (char*)"10.51", &streamObject, NULL );

    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "" );
    TEST_ASSERT_TRUE( status );

    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_echo_func( (char*)"$tmpFloat", &streamObject, NULL );

    sprintf( expected, "%.5f", tmpFloat );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, expected );
    TEST_ASSERT_TRUE( status );

    // Simple export with float to int variable.
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_exportTarget_func( (char*)"$tmpInt", &streamObject, NULL ); // Set the float system variable as target.

    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "" );
    TEST_ASSERT_TRUE( status );

    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_export_func( (char*)"10.51", &streamObject, NULL );

    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "" );
    TEST_ASSERT_TRUE( status );

    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_echo_func( (char*)"$tmpInt", &streamObject, NULL );

    sprintf( expected, "%d", (int)tmpFloat );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, expected );
    TEST_ASSERT_TRUE( status );

    // Simple export with int to int variable.
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_exportTarget_func( (char*)"$tmpInt", &streamObject, NULL ); // Set the float system variable as target.

    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "" );
    TEST_ASSERT_TRUE( status );

    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_export_func( (char*)"32", &streamObject, NULL );

    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "" );
    TEST_ASSERT_TRUE( status );

    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_echo_func( (char*)"$tmpInt", &streamObject, NULL );

    sprintf( expected, "%d", tmpInt );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, expected );
    TEST_ASSERT_TRUE( status );

    // Simple export with int to float variable.
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_exportTarget_func( (char*)"$tmpFloat", &streamObject, NULL ); // Set the float system variable as target.

    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "" );
    TEST_ASSERT_TRUE( status );

    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_export_func( (char*)"32", &streamObject, NULL );

    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "" );
    TEST_ASSERT_TRUE( status );

    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_echo_func( (char*)"$tmpFloat", &streamObject, NULL );

    sprintf( expected, "%.5f", tmpFloat );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, expected );
    TEST_ASSERT_TRUE( status );

}

void test_commander_export_func_invalid(){

    bool status;
    char expected[ 1000 ];

    // Invalid export with string to float
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_exportTarget_func( (char*)"$tmpFloat", &streamObject, NULL ); // Set the float system variable as target.

    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "" );
    TEST_ASSERT_TRUE( status );

    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_export_func( (char*)"string", &streamObject, NULL );

    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "Argument error! Input has to be an integer or a float!" );
    TEST_ASSERT_FALSE( status );

    // export command without response channel
    status = commander_export_func( (char*)"", NULL, NULL );

    TEST_ASSERT_FALSE( status );

}

int main(){

    Commander::attachVariables( systemVariables );

    UNITY_BEGIN();

    RUN_TEST( test_commander_env_func_regular );
    RUN_TEST( test_commander_env_func_invalid );

    RUN_TEST( test_commander_echo_func_regular );
    RUN_TEST( test_commander_echo_func_invalid );

    RUN_TEST( test_commander_exportTarget_func_regular );
    RUN_TEST( test_commander_exportTarget_func_invalid );

    RUN_TEST( test_commander_export_func_regular );
    RUN_TEST( test_commander_export_func_invalid );

    return UNITY_END();

}