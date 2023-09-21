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

#include "Commander-API.hpp"
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
    void test_parseIntShort();
    void test_parseFloatShort();
    void test_parseStringShort();

};

Argument targetObject( NULL, 0 );
ArgumentUT testerObject( &targetObject );

// Global system variables.
float floatSysVar = 1.410f;
int intSysVar = -1300;
const char* strSysVar = "String Variable";

// System Variable array. This array will store the
// name and the instance of the system variables.
Commander::systemVariable_t systemVariables[] = {
    systemVariableFloat( floatSysVar ),
    systemVariableInt( intSysVar ),
    systemVariableString( strSysVar )
};


// Put any init code here that needs to run before testing.
void setUp(void) {
    Commander::attachVariables( systemVariables );
}

// Put any init code here that needs to run after testing.
void tearDown(void) {

}

void ArgumentUT::test_parseIntShort(){

    char shortName = 't';

    // Simple short name int
    const char* testDataSimpleShortNameInt = "-t 10";

    // Advanced short name int
    const char* testDataAdvancedShortNameInt = "100 \"  -t 200 string \" -t 20    200";

    // Simple short name float
    const char* testDataSimpleShortNameFloat = "-t 10.6";

    // Advanced short name float
    const char* testDataAdvancedShortNameFloat = "100 \"  -t 200 string \" -t 20.7    200";

    // Simple short name string
    const char* testDataSimpleShortNameString = "-t number";

    // Advanced short name string
    const char* testDataAdvancedShortNameString = "100 \"  -t 200 string \" -t number    200";

    // Simple short name system variable int
    const char* testDataSimpleShortNameSysVarInt = "-t $intSysVar";

    // Simple short name system variable float
    const char* testDataSimpleShortNameSysVarFloat = "-t $floatSysVar";

    // Simple short name system variable string
    const char* testDataSimpleShortNameSysVarString = "-t $strSysVar";

    // Advanced short name system variable int
    const char* testDataAdvancedShortNameSysVarInt = "-t $intSysVar \"-t data\" 25.1";

    // Advanced short name system variable float
    const char* testDataAdvancedShortNameSysVarFloat = "-t $floatSysVar \"-t data\" 25.1";

    // Advanced short name system variable string
    const char* testDataAdvancedShortNameSysVarString = "-t $strSysVar \"-t data\" 25.1";

    // Invalid short name system variable int
    const char* testDataInvalidShortNameSysVarInt = "-t $intSysVarr";

    // Invalid short name system variable float
    const char* testDataInvalidShortNameSysVarFloat = "-t $floatSysVarr";

    // Invalid short name system variable string
    const char* testDataInvalidShortNameSysVarString = "-t $strSysVarr";

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameInt, shortName );

    //-- Try to parse the argument. --
    //   Simple short name int
    TEST_ASSERT_TRUE( target -> parseInt() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_INT( 10, target -> operator int() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameInt, shortName );

    //-- Try to parse the argument. --
    //   Advanced short name int
    TEST_ASSERT_TRUE( target -> parseInt() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_INT( 20, target -> operator int() );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameFloat, shortName );

    //-- Try to parse the argument. --
    //   Simple short name float
    TEST_ASSERT_TRUE( target -> parseInt() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_INT( 10, target -> operator int() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameFloat, shortName );

    //-- Try to parse the argument. --
    //   Advanced short name float
    TEST_ASSERT_TRUE( target -> parseInt() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_INT( 20, target -> operator int() );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameString, shortName );

    //-- Try to parse the argument. --
    //   Simple short name string
    TEST_ASSERT_FALSE( target -> parseInt() );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameString, shortName );

    //-- Try to parse the argument. --
    //   Advanced short name string
    TEST_ASSERT_FALSE( target -> parseInt() );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameSysVarInt, shortName );

    //-- Try to parse the argument. --
    //   Simple short name system variable int
    TEST_ASSERT_TRUE( target -> parseInt() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_INT( intSysVar, target -> operator int() );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameSysVarFloat, shortName );

    //-- Try to parse the argument. --
    //   Simple short name system variable float
    TEST_ASSERT_TRUE( target -> parseInt() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_INT( floatSysVar, target -> operator int() );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameSysVarString, shortName );


    //-- Try to parse the argument. --
    //   Simple short name system variable string
    TEST_ASSERT_FALSE( target -> parseInt() );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameSysVarInt, shortName );

    //-- Try to parse the argument. --
    //   Advanced short name system variable int
    TEST_ASSERT_TRUE( target -> parseInt() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_INT( intSysVar, target -> operator int() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameSysVarFloat, shortName );

    //-- Try to parse the argument. --
    //   Advanced short name system variable float
    TEST_ASSERT_TRUE( target -> parseInt() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_INT( floatSysVar, target -> operator int() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameSysVarString, shortName );

    //-- Try to parse the argument. --
    //   Advanced short name system variable string
    TEST_ASSERT_FALSE( target -> parseInt() );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataInvalidShortNameSysVarInt, shortName );

    //-- Try to parse the argument. --
    //   Invalid short name system variable int
    TEST_ASSERT_FALSE( target -> parseInt() );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataInvalidShortNameSysVarFloat, shortName );

    //-- Try to parse the argument. --
    //   Invalid short name system variable float
    TEST_ASSERT_FALSE( target -> parseInt() );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataInvalidShortNameSysVarString, shortName );

    //-- Try to parse the argument. --
    //   Invalid short name system variable string
    TEST_ASSERT_FALSE( target -> parseInt() );
    TEST_ASSERT_FALSE( target -> operator bool() );

}

void test_parseIntShort( void ){
    testerObject.test_parseIntShort();
}

void ArgumentUT::test_parseFloatShort(){

    char shortName = 't';

    // Simple short name int
    const char* testDataSimpleShortNameInt = "-t 10";

    // Advanced short name int
    const char* testDataAdvancedShortNameInt = "100 \"  -t 200 string \" -t 20    200";

    // Simple short name float
    const char* testDataSimpleShortNameFloat = "-t 10.6";

    // Advanced short name float
    const char* testDataAdvancedShortNameFloat = "100 \"  -t 200 string \" -t 20.7    200";

    // Simple short name string
    const char* testDataSimpleShortNameString = "-t number";

    // Advanced short name string
    const char* testDataAdvancedShortNameString = "100 \"  -t 200 string \" -t number    200";

    // Simple short name system variable int
    const char* testDataSimpleShortNameSysVarInt = "-t $intSysVar";

    // Simple short name system variable float
    const char* testDataSimpleShortNameSysVarFloat = "-t $floatSysVar";

    // Simple short name system variable string
    const char* testDataSimpleShortNameSysVarString = "-t $strSysVar";

    // Advanced short name system variable int
    const char* testDataAdvancedShortNameSysVarInt = "-t $intSysVar \"-t data\" 25.1";

    // Advanced short name system variable float
    const char* testDataAdvancedShortNameSysVarFloat = "-t $floatSysVar \"-t data\" 25.1";

    // Advanced short name system variable string
    const char* testDataAdvancedShortNameSysVarString = "-t $strSysVar \"-t data\" 25.1";

    // Invalid short name system variable int
    const char* testDataInvalidShortNameSysVarInt = "-t $intSysVarr";

    // Invalid short name system variable float
    const char* testDataInvalidShortNameSysVarFloat = "-t $floatSysVarr";

    // Invalid short name system variable string
    const char* testDataInvalidShortNameSysVarString = "-t $strSysVarr";

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameInt, shortName );

    //-- Try to parse the argument. --
    //   Simple short name int
    TEST_ASSERT_TRUE( target -> parseFloat() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_FLOAT( 10, target -> operator float() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameInt, shortName );

    //-- Try to parse the argument. --
    //   Advanced short name int
    TEST_ASSERT_TRUE( target -> parseFloat() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_FLOAT( 20, target -> operator float() );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameFloat, shortName );

    //-- Try to parse the argument. --
    //   Simple short name float
    TEST_ASSERT_TRUE( target -> parseFloat() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_FLOAT( 10.6, target -> operator float() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameFloat, shortName );

    //-- Try to parse the argument. --
    //   Advanced short name float
    TEST_ASSERT_TRUE( target -> parseFloat() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_FLOAT( 20.7, target -> operator float() );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameString, shortName );

    //-- Try to parse the argument. --
    //   Simple short name string
    TEST_ASSERT_FALSE( target -> parseFloat() );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameString, shortName );

    //-- Try to parse the argument. --
    //   Advanced short name string
    TEST_ASSERT_FALSE( target -> parseFloat() );
    TEST_ASSERT_FALSE( target -> operator bool() );

    targetObject = Argument( testDataSimpleShortNameSysVarInt, shortName );

    //-- Try to parse the argument. --
    //   Simple short name system variable int
    TEST_ASSERT_TRUE( target -> parseFloat() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_FLOAT( intSysVar, target -> operator float() );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameSysVarFloat, shortName );

    //-- Try to parse the argument. --
    //   Simple short name system variable float
    TEST_ASSERT_TRUE( target -> parseFloat() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_FLOAT( floatSysVar, target -> operator float() );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameSysVarString, shortName );

    //-- Try to parse the argument. --
    //   Simple short name system variable string
    TEST_ASSERT_FALSE( target -> parseFloat() );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameSysVarInt, shortName );

    //-- Try to parse the argument. --
    //   Advanced short name system variable int
    TEST_ASSERT_TRUE( target -> parseFloat() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_FLOAT( intSysVar, target -> operator float() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameSysVarFloat, shortName );

    //-- Try to parse the argument. --
    //   Advanced short name system variable float
    TEST_ASSERT_TRUE( target -> parseFloat() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_FLOAT( floatSysVar, target -> operator float() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameSysVarString, shortName );

    //-- Try to parse the argument. --
    //   Advanced short name system variable string
    TEST_ASSERT_FALSE( target -> parseFloat() );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataInvalidShortNameSysVarInt, shortName );

    //-- Try to parse the argument. --
    //   Invalid short name system variable int
    TEST_ASSERT_FALSE( target -> parseFloat() );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataInvalidShortNameSysVarFloat, shortName );

    //-- Try to parse the argument. --
    //   Invalid short name system variable float
    TEST_ASSERT_FALSE( target -> parseFloat() );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataInvalidShortNameSysVarString, shortName );

    //-- Try to parse the argument. --
    //   Invalid short name system variable string
    TEST_ASSERT_FALSE( target -> parseFloat() );
    TEST_ASSERT_FALSE( target -> operator bool() );

}

void test_parseFloatShort( void ){
    testerObject.test_parseFloatShort();
}

void ArgumentUT::test_parseStringShort(){

    char shortName = 't';

    char stringBuffer[ 20 ];

    // Simple short name int
    const char* testDataSimpleShortNameInt = "-t 10";

    // Advanced short name int
    const char* testDataAdvancedShortNameInt = "100 \"  -t 200 string \" -t 20    200";

    // Simple short name float
    const char* testDataSimpleShortNameFloat = "-t 10.6";

    // Advanced short name float
    const char* testDataAdvancedShortNameFloat = "100 \"  -t 200 string \" -t 20.7    200";

    // Simple short name string
    const char* testDataSimpleShortNameString = "-t number";

    // Advanced short name string
    const char* testDataAdvancedShortNameString = "100 \"  -t 200 string \" -t number    200";

    // Simple short name system variable int
    const char* testDataSimpleShortNameSysVarInt = "-t $intSysVar";

    // Simple short name system variable float
    const char* testDataSimpleShortNameSysVarFloat = "-t $floatSysVar";

    // Simple short name system variable string
    const char* testDataSimpleShortNameSysVarString = "-t $strSysVar";

    // Advanced short name system variable int
    const char* testDataAdvancedShortNameSysVarInt = "-t $intSysVar \"-t data\" 25.1";

    // Advanced short name system variable float
    const char* testDataAdvancedShortNameSysVarFloat = "-t $floatSysVar \"-t data\" 25.1";

    // Advanced short name system variable string
    const char* testDataAdvancedShortNameSysVarString = "-t $strSysVar \"-t data\" 25.1";

    // Invalid short name system variable int
    const char* testDataInvalidShortNameSysVarInt = "-t $intSysVarr";

    // Invalid short name system variable float
    const char* testDataInvalidShortNameSysVarFloat = "-t $floatSysVarr";

    // Invalid short name system variable string
    const char* testDataInvalidShortNameSysVarString = "-t $strSysVarr";

    // Short name with a complex string parameter
    const char* testDataStringComplex = "-t \"$This is the string\"";

    // Short name with a complex string not closed parameter
    const char* testDataStringComplexNotClosed = "-t \"This string is not closed";

    // Short name with a complex string too large parameter
    const char* testDataStringComplexTooLarge = "-t \"This will be a very, very long string. I hope it won't cause any overflow!";

    // Short name with a complex string start with dash parameter
    const char* testDataStringStartWithDash = "-t -This is the string";

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameInt, shortName );

    //-- Try to parse the argument. --
    //   Simple short name int
    TEST_ASSERT_TRUE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_STRING( "10", target -> operator char*() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameInt, shortName );

    //-- Try to parse the argument. --
    //   Advanced short name int
    TEST_ASSERT_TRUE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_STRING( "20", target -> operator char*() );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameFloat, shortName );

    //-- Try to parse the argument. --
    //   Simple short name float
    TEST_ASSERT_TRUE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_STRING( "10.6", target -> operator char*() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameFloat, shortName );

    //-- Try to parse the argument. --
    //   Advanced short name float
    TEST_ASSERT_TRUE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_STRING( "20.7", target -> operator char*() );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameString, shortName );

    //-- Try to parse the argument. --
    //   Simple short name string
    TEST_ASSERT_TRUE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_STRING( "number", target -> operator char*() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameString, shortName );

    //-- Try to parse the argument. --
    //   Advanced short name string
    TEST_ASSERT_TRUE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_STRING( "number", target -> operator char*() );

    targetObject = Argument( testDataSimpleShortNameSysVarInt, shortName );

    //-- Try to parse the argument. --
    //   Simple short name system variable int
    TEST_ASSERT_TRUE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_STRING( "-1300", target -> operator char*() );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameSysVarFloat, shortName );

    //-- Try to parse the argument. --
    //   Simple short name system variable float
    TEST_ASSERT_TRUE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_STRING( "1.41", target -> operator char*() );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameSysVarString, shortName );

    //-- Try to parse the argument. --
    //   Simple short name system variable string
    TEST_ASSERT_TRUE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_STRING( strSysVar, target -> operator char*() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameSysVarInt, shortName );

    //-- Try to parse the argument. --
    //   Advanced short name system variable int
    TEST_ASSERT_TRUE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_STRING( "-1300", target -> operator char*() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameSysVarFloat, shortName );

    //-- Try to parse the argument. --
    //   Advanced short name system variable float
    TEST_ASSERT_TRUE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_STRING( "1.41", target -> operator char*() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameSysVarString, shortName );

    //-- Try to parse the argument. --
    //   Advanced short name system variable string
    TEST_ASSERT_TRUE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_STRING( strSysVar, target -> operator char*() );

    // Call the constructor.
    targetObject = Argument( testDataInvalidShortNameSysVarInt, shortName );

    //-- Try to parse the argument. --
    //   Invalid short name system variable int
    TEST_ASSERT_FALSE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataInvalidShortNameSysVarFloat, shortName );

    //-- Try to parse the argument. --
    //   Invalid short name system variable float
    TEST_ASSERT_FALSE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataInvalidShortNameSysVarString, shortName );

    //-- Try to parse the argument. --
    //   Invalid short name system variable string
    TEST_ASSERT_FALSE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataStringComplex, shortName );

    //-- Try to parse the argument. --
    //   Short name with a complex string parameter
    TEST_ASSERT_TRUE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_STRING( "$This is the string", target -> operator char*() );

    // Call the constructor.
    targetObject = Argument( testDataStringComplexNotClosed, shortName );

    //-- Try to parse the argument. --
    //   Short name with a complex string not closed parameter
    TEST_ASSERT_FALSE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataStringComplexTooLarge, shortName );

    //-- Try to parse the argument. --
    //   Short name with a complex string too large parameter
    TEST_ASSERT_FALSE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataStringStartWithDash, shortName );

    //-- Try to parse the argument. --
    //   Short name with a complex string start with dash parameter
    TEST_ASSERT_FALSE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_FALSE( target -> operator bool() );

}

void test_parseStringShort( void ){
    testerObject.test_parseStringShort();
}

int main(){

    UNITY_BEGIN();

    RUN_TEST( test_parseIntShort );
    RUN_TEST( test_parseFloatShort );
    RUN_TEST( test_parseStringShort );

    return UNITY_END();

}