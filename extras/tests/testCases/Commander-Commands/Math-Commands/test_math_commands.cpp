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
#include "Commander-API-Commands.hpp"

// Unit test module.
#include "unity.h"

// For timing.
#include "System.h"

testStream streamObject;

// Put any init code here that needs to run before testing.
void setUp(void) {
  
}

// Put any init code here that needs to run after testing.
void tearDown(void) {

}

void test_commander_abs_func_regular(){

    bool status;

    // Simple negative integer number
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_abs_func( (char*)"-10", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "10.00" );
    TEST_ASSERT_TRUE( status );

    // Simple integer number
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_abs_func( (char*)"10", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "10.00" );
    TEST_ASSERT_TRUE( status );

    // Simple negative float number
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_abs_func( (char*)"-3.41", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "3.41" );
    TEST_ASSERT_TRUE( status );

    // Simple float number
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_abs_func( (char*)"3.41", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "3.41" );
    TEST_ASSERT_TRUE( status );

    // Short negative float number with 10 decimal places
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_abs_func( (char*)"-1 -p 10", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "1.0000000000" );
    TEST_ASSERT_TRUE( status );

    // Long negative float number with 10 decimal places
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_abs_func( (char*)"-1 --places 10", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "1.0000000000" );
    TEST_ASSERT_TRUE( status );


}

void test_commander_abs_func_invalid(){

    bool status;

    // Null response
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_abs_func( (char*)"-10", NULL, NULL );
    TEST_ASSERT_FALSE( status );

    // Empty argument
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_abs_func( (char*)"", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_FALSE( status );

    // Short places without value
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_abs_func( (char*)"-3.41 -p", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "3.41" );
    TEST_ASSERT_TRUE( status );

    // Short places with invalid parameter
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_abs_func( (char*)"-10 -p 0", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_FALSE( status );

    // Long places without value
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_abs_func( (char*)"-3.41 --places", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "3.41" );
    TEST_ASSERT_TRUE( status );

    // Long places with invalid parameter
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_abs_func( (char*)"-10 --places 0", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_FALSE( status );

}

void test_commander_cos_func_regular(){

    bool status;

    // Short degree value of 180deg
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_cos_func( (char*)"-d 180", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "-1.00" );
    TEST_ASSERT_TRUE( status );

    // Short degree value of 90deg
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_cos_func( (char*)"-d 90", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "0.00" );
    TEST_ASSERT_TRUE( status );

    // Short degree value of 0deg
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_cos_func( (char*)"-d 0", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "1.00" );
    TEST_ASSERT_TRUE( status );

    // Short degree value of 0deg with 5 places
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_cos_func( (char*)"-d 0 -p 5", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "1.00000" );
    TEST_ASSERT_TRUE( status );

    // Long degree value of 180deg
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_cos_func( (char*)"--deg 180", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "-1.00" );
    TEST_ASSERT_TRUE( status );

    // Long degree value of 90deg
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_cos_func( (char*)"--deg 90", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "0.00" );
    TEST_ASSERT_TRUE( status );

    // Long degree value of 0deg
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_cos_func( (char*)"--deg 0", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "1.00" );
    TEST_ASSERT_TRUE( status );

    // Long degree value of 0deg with 5 places
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_cos_func( (char*)"--deg 0 --places 5", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "1.00000" );
    TEST_ASSERT_TRUE( status );

    // Short radian value of pi
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_cos_func( (char*)"-r 3.14159265359", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "-1.00" );
    TEST_ASSERT_TRUE( status );

    // Short radian value of pi/2
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_cos_func( (char*)"-r 1.57079632679", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "-0.00" );
    TEST_ASSERT_TRUE( status );

    // Short radian value of 0
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_cos_func( (char*)"-r 0", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "1.00" );
    TEST_ASSERT_TRUE( status );

    // Short radian value of 0 with 5 places
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_cos_func( (char*)"-r 0 -p 5", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "1.00000" );
    TEST_ASSERT_TRUE( status );

    // Long radian value of pi
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_cos_func( (char*)"--rad 3.14159265359", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "-1.00" );
    TEST_ASSERT_TRUE( status );

    // Long radian value of pi/2
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_cos_func( (char*)"--rad 1.57079632679", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "-0.00" );
    TEST_ASSERT_TRUE( status );

    // Long radian value of 0
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_cos_func( (char*)"--rad 0", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "1.00" );
    TEST_ASSERT_TRUE( status );

    // Long radian value of 0 with 5 places
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_cos_func( (char*)"--rad 0 --places 5", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "1.00000" );
    TEST_ASSERT_TRUE( status );

}

void test_commander_cos_func_invalid(){

    bool status;

    // Null response
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_cos_func( (char*)"-10", NULL, NULL );
    TEST_ASSERT_FALSE( status );

    // Empty argument
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_cos_func( (char*)"", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_FALSE( status );

    // Short rad and deg at the same time.
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_cos_func( (char*)"-r 3.14 -d 0", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_FALSE( status );

    // Short places with invalid number
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_cos_func( (char*)"-r 3.14 -p 0", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_FALSE( status );

    // Short radian with empty number
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_cos_func( (char*)"-r", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_FALSE( status );

    // Short degree with empty number
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_cos_func( (char*)"-d", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_FALSE( status );

    // Short places without value
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_abs_func( (char*)"-r 3.14159265359 -p", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "0.00" );
    TEST_ASSERT_TRUE( status );

    // Long rad and deg at the same time.
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_cos_func( (char*)"--rad 3.14 --deg 0", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_FALSE( status );

    // Long places with invalid number
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_cos_func( (char*)"--rad 3.14 --places 0", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_FALSE( status );

    // Long radian with empty number
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_cos_func( (char*)"--rad", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_FALSE( status );

    // Long degree with empty number
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_cos_func( (char*)"--deg", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_FALSE( status );

    // Long places without value
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_abs_func( (char*)"--rad 3.14159265359 --places", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "0.00" );
    TEST_ASSERT_TRUE( status );

}

void test_commander_sin_func_regular(){

    bool status;

    // Short degree value of 180deg
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"-d 180", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "0.00" );
    TEST_ASSERT_TRUE( status );

    // Short degree value of 90deg
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"-d 90", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "1.00" );
    TEST_ASSERT_TRUE( status );

    // Short degree value of -90deg
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"-d -90", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "-1.00" );
    TEST_ASSERT_TRUE( status );

    // Short degree value of -90deg with 5 places
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"-d -90 -p 5", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "-1.00000" );
    TEST_ASSERT_TRUE( status );

    // Long degree value of 180deg
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"--deg 180", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "0.00" );
    TEST_ASSERT_TRUE( status );

    // Long degree value of 90deg
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"--deg 90", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "1.00" );
    TEST_ASSERT_TRUE( status );

    // Long degree value of -90deg
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"--deg -90", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "-1.00" );
    TEST_ASSERT_TRUE( status );

    // Long degree value of -90deg with 5 places
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"--deg -90 --places 5", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "-1.00000" );
    TEST_ASSERT_TRUE( status );

    // Short radian value of pi
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"-r 3.14159265359", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "-0.00" );
    TEST_ASSERT_TRUE( status );

    // Short radian value of pi/2
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"-r 1.57079632679", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "1.00" );
    TEST_ASSERT_TRUE( status );

    // Short radian value of 0
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"-r 0", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "0.00" );
    TEST_ASSERT_TRUE( status );

    // Short radian value of 0 with 5 places
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"-r 0 -p 5", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "0.00000" );
    TEST_ASSERT_TRUE( status );

    // Long radian value of pi
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"--rad 3.14159265359", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "-0.00" );
    TEST_ASSERT_TRUE( status );

    // Long radian value of pi/2
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"--rad 1.57079632679", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "1.00" );
    TEST_ASSERT_TRUE( status );

    // Long radian value of 0
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"--rad 0", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "0.00" );
    TEST_ASSERT_TRUE( status );

    // Long radian value of 0 with 5 places
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"--rad 0 --places 5", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "0.00000" );
    TEST_ASSERT_TRUE( status );

}

void test_commander_sin_func_invalid(){

    bool status;

    // Null response
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"-10", NULL, NULL );
    TEST_ASSERT_FALSE( status );

    // Empty argument
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_FALSE( status );

    // Short rad and deg at the same time.
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"-r 3.14 -d 0", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_FALSE( status );

    // Short places with invalid number
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"-r 3.14 -p 0", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_FALSE( status );

    // Short radian with empty number
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"-r", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_FALSE( status );

    // Short degree with empty number
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"-d", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_FALSE( status );

    // Short places without value
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"-r 3.14159265359 -p", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "-0.00" );
    TEST_ASSERT_TRUE( status );

    // Long rad and deg at the same time.
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"--rad 3.14 --deg 0", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_FALSE( status );

    // Long places with invalid number
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"--rad 3.14 --places 0", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_FALSE( status );

    // Long radian with empty number
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"--rad", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_FALSE( status );

    // Long degree with empty number
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"--deg", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_FALSE( status );

    // Long places without value
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_sin_func( (char*)"--rad 3.14159265359 --places", &streamObject, NULL );
    TEST_ASSERT_EQUAL_STRING( streamObject.txBuffer, "-0.00" );
    TEST_ASSERT_TRUE( status );

}

void test_commander_random_func_regular(){

    bool status;

    // Short upper value
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_random_func( (char*)"-u 100", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_TRUE( status );

    // Short upper and lower value
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_random_func( (char*)"-l -100 -u 100", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_TRUE( status );

    // Long upper value
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_random_func( (char*)"--upper 100", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_TRUE( status );

    // Long upper and lower value
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_random_func( (char*)"--lower -100 --upper 100", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_TRUE( status );

}

void test_commander_random_func_invalid(){

    bool status;

    // Null response
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_random_func( (char*)"-u 100", NULL, NULL );
    TEST_ASSERT_FALSE( status );

    // Empty argument
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_random_func( (char*)"", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_FALSE( status );

    // Short only lower value defined
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_random_func( (char*)"-l 100", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_FALSE( status );

    // Short only upper value defined
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_random_func( (char*)"--lower 100", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_FALSE( status );

}








void test_commander_not_func_regular(){

    bool status;

    // non-zero value
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_not_func( (char*)"100", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_TRUE( status );

    // zero value
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_not_func( (char*)"0", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_TRUE( status );

}

void test_commander_not_func_invalid(){

    bool status;

    // Null response
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_not_func( (char*)"100", NULL, NULL );
    TEST_ASSERT_FALSE( status );

    // Empty argument
    streamObject.clearRx();
    streamObject.clearTx();
    status = commander_not_func( (char*)"", &streamObject, NULL );
    TEST_ASSERT_GREATER_THAN_INT( 0, streamObject.txWritePointer );
    TEST_ASSERT_FALSE( status );

}

int main(){

    UNITY_BEGIN();

    RUN_TEST( test_commander_abs_func_regular );
    RUN_TEST( test_commander_abs_func_invalid );

    RUN_TEST( test_commander_cos_func_regular );
    RUN_TEST( test_commander_cos_func_invalid );

    RUN_TEST( test_commander_sin_func_regular );
    RUN_TEST( test_commander_sin_func_invalid );

    RUN_TEST( test_commander_random_func_regular );
    RUN_TEST( test_commander_random_func_invalid );

    RUN_TEST( test_commander_not_func_regular );
    RUN_TEST( test_commander_not_func_invalid );

    return UNITY_END();

}