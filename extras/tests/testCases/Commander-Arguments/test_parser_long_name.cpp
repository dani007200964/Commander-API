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
    void test_parseIntLong();
    void test_parseFloatLong();
    void test_parseStringLong();

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

void ArgumentUT::test_parseIntLong(){

    char shortName = 't';
    const char* longName = "testArgument";

    // Simple long name int
    const char* testDataSimpleShortNameInt = "--testArgument 10";

    // Advanced long name int
    const char* testDataAdvancedShortNameInt = "100 \"  --testArgument 200 string \" --testArgument 20    200";

    // Simple long name float
    const char* testDataSimpleShortNameFloat = "--testArgument 10.6";

    // Advanced long name float
    const char* testDataAdvancedShortNameFloat = "100 \"  --testArgument 200 string \" --testArgument 20.7    200";

    // Simple long name string
    const char* testDataSimpleShortNameString = "--testArgument number";

    // Advanced long name string
    const char* testDataAdvancedShortNameString = "100 \"  --testArgument 200 string \" --testArgument number    200";

    // Simple long name system variable int
    const char* testDataSimpleShortNameSysVarInt = "--testArgument $intSysVar";

    // Simple long name system variable float
    const char* testDataSimpleShortNameSysVarFloat = "--testArgument $floatSysVar";

    // Simple long name system variable string
    const char* testDataSimpleShortNameSysVarString = "--testArgument $strSysVar";

    // Advanced long name system variable int
    const char* testDataAdvancedShortNameSysVarInt = "--testArgument $intSysVar \"--testArgument data\" 25.1";

    // Advanced long name system variable float
    const char* testDataAdvancedShortNameSysVarFloat = "--testArgument $floatSysVar \"--testArgument data\" 25.1";

    // Advanced long name system variable string
    const char* testDataAdvancedShortNameSysVarString = "--testArgument $strSysVar \"--testArgument data\" 25.1";

    // Invalid long name system variable int
    const char* testDataInvalidShortNameSysVarInt = "--testArgument $intSysVarr";

    // Invalid long name system variable float
    const char* testDataInvalidShortNameSysVarFloat = "--testArgument $floatSysVarr";

    // Invalid long name system variable string
    const char* testDataInvalidShortNameSysVarString = "--testArgument $strSysVarr";

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameInt, shortName, longName );

    //-- Try to parse the argument. --
    //   Simple long name int
    TEST_ASSERT_TRUE( target -> parseInt() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_INT( 10, target -> operator int() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameInt, shortName, longName );

    //-- Try to parse the argument. --
    //   Advanced long name int
    TEST_ASSERT_TRUE( target -> parseInt() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_INT( 20, target -> operator int() );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameFloat, shortName, longName );

    //-- Try to parse the argument. --
    //   Simple long name float
    TEST_ASSERT_TRUE( target -> parseInt() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_INT( 10, target -> operator int() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameFloat, shortName, longName );

    //-- Try to parse the argument. --
    //   Advanced long name float
    TEST_ASSERT_TRUE( target -> parseInt() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_INT( 20, target -> operator int() );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameString, shortName, longName );

    //-- Try to parse the argument. --
    //   Simple long name string
    TEST_ASSERT_FALSE( target -> parseInt() );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameString, shortName, longName );

    //-- Try to parse the argument. --
    //   Advanced long name string
    TEST_ASSERT_FALSE( target -> parseInt() );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameSysVarInt, shortName, longName );

    //-- Try to parse the argument. --
    //   Simple long name system variable int
    TEST_ASSERT_TRUE( target -> parseInt() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_INT( intSysVar, target -> operator int() );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameSysVarFloat, shortName, longName );

    //-- Try to parse the argument. --
    //   Simple long name system variable float
    TEST_ASSERT_TRUE( target -> parseInt() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_INT( floatSysVar, target -> operator int() );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameSysVarString, shortName, longName );


    //-- Try to parse the argument. --
    //   Simple long name system variable string
    TEST_ASSERT_FALSE( target -> parseInt() );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameSysVarInt, shortName, longName );

    //-- Try to parse the argument. --
    //   Advanced long name system variable int
    TEST_ASSERT_TRUE( target -> parseInt() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_INT( intSysVar, target -> operator int() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameSysVarFloat, shortName, longName );

    //-- Try to parse the argument. --
    //   Advanced long name system variable float
    TEST_ASSERT_TRUE( target -> parseInt() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_INT( floatSysVar, target -> operator int() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameSysVarString, shortName, longName );

    //-- Try to parse the argument. --
    //   Advanced long name system variable string
    TEST_ASSERT_FALSE( target -> parseInt() );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataInvalidShortNameSysVarInt, shortName, longName );

    //-- Try to parse the argument. --
    //   Invalid long name system variable int
    TEST_ASSERT_FALSE( target -> parseInt() );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataInvalidShortNameSysVarFloat, shortName, longName );

    //-- Try to parse the argument. --
    //   Invalid long name system variable float
    TEST_ASSERT_FALSE( target -> parseInt() );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataInvalidShortNameSysVarString, shortName, longName );

    //-- Try to parse the argument. --
    //   Invalid long name system variable string
    TEST_ASSERT_FALSE( target -> parseInt() );
    TEST_ASSERT_FALSE( target -> operator bool() );

}

void test_parseIntLong( void ){
    testerObject.test_parseIntLong();
}

void ArgumentUT::test_parseFloatLong(){

    char shortName = 't';
    const char* longName = "testArgument";

    // Simple long name int
    const char* testDataSimpleShortNameInt = "--testArgument 10";

    // Advanced long name int
    const char* testDataAdvancedShortNameInt = "100 \"  --testArgument 200 string \" --testArgument 20    200";

    // Simple long name float
    const char* testDataSimpleShortNameFloat = "--testArgument 10.6";

    // Advanced long name float
    const char* testDataAdvancedShortNameFloat = "100 \"  --testArgument 200 string \" --testArgument 20.7    200";

    // Simple long name string
    const char* testDataSimpleShortNameString = "--testArgument number";

    // Advanced long name string
    const char* testDataAdvancedShortNameString = "100 \"  --testArgument 200 string \" --testArgument number    200";

    // Simple long name system variable int
    const char* testDataSimpleShortNameSysVarInt = "--testArgument $intSysVar";

    // Simple long name system variable float
    const char* testDataSimpleShortNameSysVarFloat = "--testArgument $floatSysVar";

    // Simple long name system variable string
    const char* testDataSimpleShortNameSysVarString = "--testArgument $strSysVar";

    // Advanced long name system variable int
    const char* testDataAdvancedShortNameSysVarInt = "--testArgument $intSysVar \"--testArgument data\" 25.1";

    // Advanced long name system variable float
    const char* testDataAdvancedShortNameSysVarFloat = "--testArgument $floatSysVar \"--testArgument data\" 25.1";

    // Advanced long name system variable string
    const char* testDataAdvancedShortNameSysVarString = "--testArgument $strSysVar \"--testArgument data\" 25.1";

    // Invalid long name system variable int
    const char* testDataInvalidShortNameSysVarInt = "--testArgument $intSysVarr";

    // Invalid long name system variable float
    const char* testDataInvalidShortNameSysVarFloat = "--testArgument $floatSysVarr";

    // Invalid long name system variable string
    const char* testDataInvalidShortNameSysVarString = "--testArgument $strSysVarr";

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameInt, shortName, longName );

    //-- Try to parse the argument. --
    //   Simple long name int
    TEST_ASSERT_TRUE( target -> parseFloat() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_FLOAT( 10, target -> operator float() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameInt, shortName, longName );

    //-- Try to parse the argument. --
    //   Advanced long name int
    TEST_ASSERT_TRUE( target -> parseFloat() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_FLOAT( 20, target -> operator float() );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameFloat, shortName, longName );

    //-- Try to parse the argument. --
    //   Simple long name float
    TEST_ASSERT_TRUE( target -> parseFloat() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_FLOAT( 10.6, target -> operator float() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameFloat, shortName, longName );

    //-- Try to parse the argument. --
    //   Advanced long name float
    TEST_ASSERT_TRUE( target -> parseFloat() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_FLOAT( 20.7, target -> operator float() );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameString, shortName, longName );

    //-- Try to parse the argument. --
    //   Simple long name string
    TEST_ASSERT_FALSE( target -> parseFloat() );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameString, shortName, longName );

    //-- Try to parse the argument. --
    //   Advanced long name string
    TEST_ASSERT_FALSE( target -> parseFloat() );
    TEST_ASSERT_FALSE( target -> operator bool() );

    targetObject = Argument( testDataSimpleShortNameSysVarInt, shortName, longName );

    //-- Try to parse the argument. --
    //   Simple long name system variable int
    TEST_ASSERT_TRUE( target -> parseFloat() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_FLOAT( intSysVar, target -> operator float() );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameSysVarFloat, shortName, longName );

    //-- Try to parse the argument. --
    //   Simple long name system variable float
    TEST_ASSERT_TRUE( target -> parseFloat() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_FLOAT( floatSysVar, target -> operator float() );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameSysVarString, shortName, longName );

    //-- Try to parse the argument. --
    //   Simple long name system variable string
    TEST_ASSERT_FALSE( target -> parseFloat() );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameSysVarInt, shortName, longName );

    //-- Try to parse the argument. --
    //   Advanced long name system variable int
    TEST_ASSERT_TRUE( target -> parseFloat() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_FLOAT( intSysVar, target -> operator float() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameSysVarFloat, shortName, longName );

    //-- Try to parse the argument. --
    //   Advanced long name system variable float
    TEST_ASSERT_TRUE( target -> parseFloat() );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_FLOAT( floatSysVar, target -> operator float() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameSysVarString, shortName, longName );

    //-- Try to parse the argument. --
    //   Advanced long name system variable string
    TEST_ASSERT_FALSE( target -> parseFloat() );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataInvalidShortNameSysVarInt, shortName, longName );

    //-- Try to parse the argument. --
    //   Invalid long name system variable int
    TEST_ASSERT_FALSE( target -> parseFloat() );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataInvalidShortNameSysVarFloat, shortName, longName );

    //-- Try to parse the argument. --
    //   Invalid long name system variable float
    TEST_ASSERT_FALSE( target -> parseFloat() );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataInvalidShortNameSysVarString, shortName, longName );

    //-- Try to parse the argument. --
    //   Invalid long name system variable string
    TEST_ASSERT_FALSE( target -> parseFloat() );
    TEST_ASSERT_FALSE( target -> operator bool() );

}

void test_parseFloatLong( void ){
    testerObject.test_parseFloatLong();
}

void ArgumentUT::test_parseStringLong(){

    char shortName = 't';
    const char* longName = "testArgument";

    char stringBuffer[ 20 ];

    // Simple long name int
    const char* testDataSimpleShortNameInt = "--testArgument 10";

    // Advanced long name int
    const char* testDataAdvancedShortNameInt = "100 \"  --testArgument 200 string \" --testArgument 20    200";

    // Simple long name float
    const char* testDataSimpleShortNameFloat = "--testArgument 10.6";

    // Advanced long name float
    const char* testDataAdvancedShortNameFloat = "100 \"  --testArgument 200 string \" --testArgument 20.7    200";

    // Simple long name string
    const char* testDataSimpleShortNameString = "--testArgument number";

    // Advanced long name string
    const char* testDataAdvancedShortNameString = "100 \"  --testArgument 200 string \" --testArgument number    200";

    // Simple long name system variable int
    const char* testDataSimpleShortNameSysVarInt = "--testArgument $intSysVar";

    // Simple long name system variable float
    const char* testDataSimpleShortNameSysVarFloat = "--testArgument $floatSysVar";

    // Simple long name system variable string
    const char* testDataSimpleShortNameSysVarString = "--testArgument $strSysVar";

    // Advanced long name system variable int
    const char* testDataAdvancedShortNameSysVarInt = "--testArgument $intSysVar \"--testArgument data\" 25.1";

    // Advanced long name system variable float
    const char* testDataAdvancedShortNameSysVarFloat = "--testArgument $floatSysVar \"--testArgument data\" 25.1";

    // Advanced long name system variable string
    const char* testDataAdvancedShortNameSysVarString = "--testArgument $strSysVar \"--testArgument data\" 25.1";

    // Invalid long name system variable int
    const char* testDataInvalidShortNameSysVarInt = "--testArgument $intSysVarr";

    // Invalid long name system variable float
    const char* testDataInvalidShortNameSysVarFloat = "--testArgument $floatSysVarr";

    // Invalid long name system variable string
    const char* testDataInvalidShortNameSysVarString = "--testArgument $strSysVarr";

    // Short name with a complex string parameter
    const char* testDataStringComplex = "--testArgument \"$This is the string\"";

    // Short name with a complex string not closed parameter
    const char* testDataStringComplexNotClosed = "--testArgument \"This string is not closed";

    // Short name with a complex string too large parameter
    const char* testDataStringComplexTooLarge = "--testArgument \"This will be a very, very long string. I hope it won't cause any overflow!";

    // Short name with a complex string start with dash parameter
    const char* testDataStringStartWithDash = "--testArgument -This is the string";

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameInt, shortName, longName );

    //-- Try to parse the argument. --
    //   Simple long name int
    TEST_ASSERT_TRUE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_STRING( "10", target -> operator char*() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameInt, shortName, longName );

    //-- Try to parse the argument. --
    //   Advanced long name int
    TEST_ASSERT_TRUE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_STRING( "20", target -> operator char*() );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameFloat, shortName, longName );

    //-- Try to parse the argument. --
    //   Simple long name float
    TEST_ASSERT_TRUE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_STRING( "10.6", target -> operator char*() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameFloat, shortName, longName );

    //-- Try to parse the argument. --
    //   Advanced long name float
    TEST_ASSERT_TRUE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_STRING( "20.7", target -> operator char*() );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameString, shortName, longName );

    //-- Try to parse the argument. --
    //   Simple long name string
    TEST_ASSERT_TRUE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_STRING( "number", target -> operator char*() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameString, shortName, longName );

    //-- Try to parse the argument. --
    //   Advanced long name string
    TEST_ASSERT_TRUE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_STRING( "number", target -> operator char*() );

    targetObject = Argument( testDataSimpleShortNameSysVarInt, shortName, longName );

    //-- Try to parse the argument. --
    //   Simple long name system variable int
    TEST_ASSERT_TRUE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_STRING( "-1300", target -> operator char*() );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameSysVarFloat, shortName, longName );

    //-- Try to parse the argument. --
    //   Simple long name system variable float
    TEST_ASSERT_TRUE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_STRING( "1.41", target -> operator char*() );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortNameSysVarString, shortName, longName );

    //-- Try to parse the argument. --
    //   Simple long name system variable string
    TEST_ASSERT_TRUE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_STRING( strSysVar, target -> operator char*() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameSysVarInt, shortName, longName );

    //-- Try to parse the argument. --
    //   Advanced long name system variable int
    TEST_ASSERT_TRUE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_STRING( "-1300", target -> operator char*() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameSysVarFloat, shortName, longName );

    //-- Try to parse the argument. --
    //   Advanced long name system variable float
    TEST_ASSERT_TRUE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_STRING( "1.41", target -> operator char*() );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortNameSysVarString, shortName, longName );

    //-- Try to parse the argument. --
    //   Advanced long name system variable string
    TEST_ASSERT_TRUE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_STRING( strSysVar, target -> operator char*() );

    // Call the constructor.
    targetObject = Argument( testDataInvalidShortNameSysVarInt, shortName, longName );

    //-- Try to parse the argument. --
    //   Invalid long name system variable int
    TEST_ASSERT_FALSE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataInvalidShortNameSysVarFloat, shortName, longName );

    //-- Try to parse the argument. --
    //   Invalid long name system variable float
    TEST_ASSERT_FALSE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataInvalidShortNameSysVarString, shortName, longName );

    //-- Try to parse the argument. --
    //   Invalid long name system variable string
    TEST_ASSERT_FALSE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataStringComplex, shortName, longName );

    //-- Try to parse the argument. --
    //   Short name with a complex string parameter
    TEST_ASSERT_TRUE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_TRUE( target -> operator bool() );
    TEST_ASSERT_EQUAL_STRING( "$This is the string", target -> operator char*() );

    // Call the constructor.
    targetObject = Argument( testDataStringComplexNotClosed, shortName, longName );

    //-- Try to parse the argument. --
    //   Short name with a complex string not closed parameter
    TEST_ASSERT_FALSE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataStringComplexTooLarge, shortName, longName );

    //-- Try to parse the argument. --
    //   Short name with a complex string too large parameter
    TEST_ASSERT_FALSE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_FALSE( target -> operator bool() );

    // Call the constructor.
    targetObject = Argument( testDataStringStartWithDash, shortName, longName );

    //-- Try to parse the argument. --
    //   Short name with a complex string start with dash parameter
    TEST_ASSERT_FALSE( target -> parseString( stringBuffer ) );
    TEST_ASSERT_FALSE( target -> operator bool() );

}

void test_parseStringLong( void ){
    testerObject.test_parseStringLong();
}

int main(){

    UNITY_BEGIN();

    RUN_TEST( test_parseIntLong );
    RUN_TEST( test_parseFloatLong );
    RUN_TEST( test_parseStringLong );

    return UNITY_END();

}