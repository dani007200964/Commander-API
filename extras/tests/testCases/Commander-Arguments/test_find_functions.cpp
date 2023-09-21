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
    void test_findLongName();
    void test_findShortName();
    void test_findPlace();
    void test_find();
    void test_findStart();

};

Argument targetObject( NULL, 0 );
ArgumentUT testerObject( &targetObject );

// Put any init code here that needs to run before testing.
void setUp(void) {
  
}

// Put any init code here that needs to run after testing.
void tearDown(void) {

}

void ArgumentUT::test_findLongName(){

    const char* longName = "longName";
    char shortName = 'l';

    // Simple long name with a valid argument.
    const char* testDataSimple = "--longName 10";
    int testDataSimplePosition = 11;
    char testDataSimpleCharacter = '1';

    // Simple long name without a valid argument.
    const char* testDataSimpleEmpty = "--longName";
    int testDataSimpleEmptyPosition = 10;
    char testDataSimpleEmptyCharacter = '\0';

    // Advanced long name with a valid argument.
    const char* testDataAdvanced = "-h --long -t --longName 20 --lateral";
    int testDataAdvancedPosition = 24;
    char testDataAdvancedCharacter = '2';

    // Advanced long name without a valid argument.
    const char* testDataAdvancedEmpty = "-h --long -t --longName --lateral";
    int testDataAdvancedEmptyPosition = 24;
    char testDataAdvancedEmptyCharacter = '-';

    // Long name string without argument.
    const char* testDataStringEmpty = "-h \"--longName test\" --longName";
    int testDataStringEmptyPosition = 31;
    char testDataStringEmptyCharacter = '\0';

    // Long name string with argument.
    const char* testDataString = "-h \"--longName test\" --longName cat";
    int testDataStringPosition = 32;
    char testDataStringCharacter = 'c';

    // Simple long name without a valid argument with spaces.
    const char* testDataSimpleEmptySpaces = "--longName     ";
    int testDataSimpleEmptySpacesPosition = 15;
    char testDataSimpleEmptySpacesCharacter = '\0';

    // Invalid long name simple.
    const char* testDataInvalidSimple = "--lngName";
    int testDataInvalidSimplePosition = -1;

    // Invalid long name without space.
    const char* testDataInvalidWithoutSpace = "--longName10";
    int testDataInvalidWithoutSpacePosition = -1;

    // It will hold the return value of the function call.
    int result;

    // Call the constructor.
    targetObject = Argument( testDataSimple, shortName, longName );
    
    //-- Try to find the start position. --
    //   Simple long name with a valid argument.
    result = target -> findLongName();
    TEST_ASSERT_EQUAL_INT( testDataSimplePosition, result );
    TEST_ASSERT_TRUE( target -> bFields.found );
    TEST_ASSERT_EQUAL_CHAR( testDataSimpleCharacter, testDataSimple[ result ] );

    // Call the constructor.
    targetObject = Argument( testDataSimpleEmpty, shortName, longName );

    //-- Try to find the start position. --
    //   Simple long name without a valid argument.
    result = target -> findLongName();
    TEST_ASSERT_EQUAL_INT( testDataSimpleEmptyPosition, result );
    TEST_ASSERT_TRUE( target -> bFields.found );
    TEST_ASSERT_EQUAL_CHAR( testDataSimpleEmptyCharacter, testDataSimpleEmpty[ result ] );

    // Call the constructor.
    targetObject = Argument( testDataAdvanced, shortName, longName );

    //-- Try to find the start position. --
    //   Advanced long name with a valid argument.
    result = target -> findLongName();
    TEST_ASSERT_EQUAL_INT( testDataAdvancedPosition, result );
    TEST_ASSERT_TRUE( target -> bFields.found );
    TEST_ASSERT_EQUAL_CHAR( testDataAdvancedCharacter, testDataAdvanced[ result ] );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedEmpty, shortName, longName );

    //-- Try to find the start position. --
    //   Advanced long name without a valid argument.
    result = target -> findLongName();
    TEST_ASSERT_EQUAL_INT( testDataAdvancedEmptyPosition, result );
    TEST_ASSERT_TRUE( target -> bFields.found );
    TEST_ASSERT_EQUAL_CHAR( testDataAdvancedEmptyCharacter, testDataAdvancedEmpty[ result ] );

    // Call the constructor.
    targetObject = Argument( testDataStringEmpty, shortName, longName );

    //-- Try to find the start position. --
    //   Long name string without argument.
    result = target -> findLongName();
    TEST_ASSERT_EQUAL_INT( testDataStringEmptyPosition, result );
    TEST_ASSERT_TRUE( target -> bFields.found );
    TEST_ASSERT_EQUAL_CHAR( testDataStringEmptyCharacter, testDataStringEmpty[ result ] );

    // Call the constructor.
    targetObject = Argument( testDataString, shortName, longName );

    //-- Try to find the start position. --
    //   Long name string with argument.
    result = target -> findLongName();
    TEST_ASSERT_EQUAL_INT( testDataStringPosition, result );
    TEST_ASSERT_TRUE( target -> bFields.found );
    TEST_ASSERT_EQUAL_CHAR( testDataStringCharacter, testDataString[ result ] );

    // Call the constructor.
    targetObject = Argument( testDataSimpleEmptySpaces, shortName, longName );

    //-- Try to find the start position. --
    //   Simple long name without a valid argument with spaces.
    result = target -> findLongName();
    TEST_ASSERT_EQUAL_INT( testDataSimpleEmptySpacesPosition, result );
    TEST_ASSERT_TRUE( target -> bFields.found );
    TEST_ASSERT_EQUAL_CHAR( testDataSimpleEmptySpacesCharacter, testDataSimpleEmptySpaces[ result ] );

    // ---- Invalid usage section ---- //

    // Call the constructor.
    targetObject = Argument( testDataInvalidSimple, shortName, longName );

    //-- Try to find the start position. --
    //   Invalid long name simple.
    result = target -> findLongName();
    TEST_ASSERT_EQUAL_INT( testDataInvalidSimplePosition, result );
    TEST_ASSERT_FALSE( target -> bFields.found );

    // Call the constructor.
    targetObject = Argument( testDataInvalidWithoutSpace, shortName, longName );

    //-- Try to find the start position. --
    //   Invalid long name without space.
    result = target -> findLongName();
    TEST_ASSERT_EQUAL_INT( testDataInvalidWithoutSpacePosition, result );
    TEST_ASSERT_FALSE( target -> bFields.found );

    // Call the constructor.
    targetObject = Argument( NULL, shortName, longName );
    
    //-- Try to find the start position. --
    //   Simple long name with a valid argument.
    result = target -> findLongName();
    TEST_ASSERT_EQUAL_INT( -1, result );

    // Call the constructor.
    targetObject = Argument( testDataInvalidWithoutSpace, shortName, NULL );
    
    //-- Try to find the start position. --
    //   Simple long name with a valid argument.
    result = target -> findLongName();
    TEST_ASSERT_EQUAL_INT( -1, result );

    // Call the constructor.
    targetObject = Argument( testDataInvalidWithoutSpace, shortName, longName );
    target -> sourceSize -= 5;
    
    //-- Try to find the start position. --
    //   Simple long name with a valid argument.
    result = target -> findLongName();
    TEST_ASSERT_EQUAL_INT( -1, result );

    // Call the constructor.
    targetObject = Argument( testDataSimple, shortName, longName );
    target -> sourceSize -= 3;
    
    //-- Try to find the start position. --
    //   Simple long name with a valid argument.
    result = target -> findLongName();
    TEST_ASSERT_EQUAL_INT( -1, result );

}

void test_findLongName( void ){
    testerObject.test_findLongName();
}

void ArgumentUT::test_findShortName(){

    char shortName = 's';

    // Simple short name with a valid argument.
    const char* testDataSimple = "-s 10";
    int testDataSimplePosition = 3;
    char testDataSimpleCharacter = '1';

    // Simple short name without a valid argument.
    const char* testDataSimpleEmpty = "-s";
    int testDataSimpleEmptyPosition = 2;
    char testDataSimpleEmptyCharacter = '\0';

    // Advanced short name with a valid argument.
    const char* testDataAdvanced = "-h --long -t -s 20 --lateral";
    int testDataAdvancedPosition = 16;
    char testDataAdvancedCharacter = '2';

    // Advanced short name without a valid argument.
    const char* testDataAdvancedEmpty = "-h --long -t -s --lateral";
    int testDataAdvancedEmptyPosition = 16;
    char testDataAdvancedEmptyCharacter = '-';

    // Short name string without argument.
    const char* testDataStringEmpty = "-h \"-s test\" -s";
    int testDataStringEmptyPosition = 15;
    char testDataStringEmptyCharacter = '\0';

    // Short name string with argument.
    const char* testDataString = "-h \"-s test\" -s cat";
    int testDataStringPosition = 16;
    char testDataStringCharacter = 'c';

    // Simple short name without a valid argument with spaces.
    const char* testDataSimpleEmptySpaces = "-s     ";
    int testDataSimpleEmptySpacesPosition = 7;
    char testDataSimpleEmptySpacesCharacter = '\0';

    // Invalid short name simple.
    const char* testDataInvalidSimple = "-S"; // < Upper case S
    int testDataInvalidSimplePosition = -1;

    // Invalid short name without space.
    const char* testDataInvalidWithoutSpace = "-s10";
    int testDataInvalidWithoutSpacePosition = -1;

    // It will hold the return value of the function call.
    int result;

    // Call the constructor.
    targetObject = Argument( testDataSimple, shortName );
    
    //-- Try to find the start position. --
    //   Simple long name with a valid argument.
    result = target -> findShortName();
    TEST_ASSERT_EQUAL_INT( testDataSimplePosition, result );
    TEST_ASSERT_TRUE( target -> bFields.found );
    TEST_ASSERT_EQUAL_CHAR( testDataSimpleCharacter, testDataSimple[ result ] );

    // Call the constructor.
    targetObject = Argument( testDataSimpleEmpty, shortName );

    //-- Try to find the start position. --
    //   Simple long name without a valid argument.
    result = target -> findShortName();
    TEST_ASSERT_EQUAL_INT( testDataSimpleEmptyPosition, result );
    TEST_ASSERT_TRUE( target -> bFields.found );
    TEST_ASSERT_EQUAL_CHAR( testDataSimpleEmptyCharacter, testDataSimpleEmpty[ result ] );

    // Call the constructor.
    targetObject = Argument( testDataAdvanced, shortName );

    //-- Try to find the start position. --
    //   Advanced long name with a valid argument.
    result = target -> findShortName();
    TEST_ASSERT_EQUAL_INT( testDataAdvancedPosition, result );
    TEST_ASSERT_TRUE( target -> bFields.found );
    TEST_ASSERT_EQUAL_CHAR( testDataAdvancedCharacter, testDataAdvanced[ result ] );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedEmpty, shortName );

    //-- Try to find the start position. --
    //   Advanced long name without a valid argument.
    result = target -> findShortName();
    TEST_ASSERT_EQUAL_INT( testDataAdvancedEmptyPosition, result );
    TEST_ASSERT_TRUE( target -> bFields.found );
    TEST_ASSERT_EQUAL_CHAR( testDataAdvancedEmptyCharacter, testDataAdvancedEmpty[ result ] );

    // Call the constructor.
    targetObject = Argument( testDataStringEmpty, shortName );

    //-- Try to find the start position. --
    //   Long name string without argument.
    result = target -> findShortName();
    TEST_ASSERT_EQUAL_INT( testDataStringEmptyPosition, result );
    TEST_ASSERT_TRUE( target -> bFields.found );
    TEST_ASSERT_EQUAL_CHAR( testDataStringEmptyCharacter, testDataStringEmpty[ result ] );

    // Call the constructor.
    targetObject = Argument( testDataString, shortName );

    //-- Try to find the start position. --
    //   Long name string with argument.
    result = target -> findShortName();
    TEST_ASSERT_EQUAL_INT( testDataStringPosition, result );
    TEST_ASSERT_TRUE( target -> bFields.found );
    TEST_ASSERT_EQUAL_CHAR( testDataStringCharacter, testDataString[ result ] );

    // Call the constructor.
    targetObject = Argument( testDataSimpleEmptySpaces, shortName );

    //-- Try to find the start position. --
    //   Simple long name without a valid argument with spaces.
    result = target -> findShortName();
    TEST_ASSERT_EQUAL_INT( testDataSimpleEmptySpacesPosition, result );
    TEST_ASSERT_TRUE( target -> bFields.found );
    TEST_ASSERT_EQUAL_CHAR( testDataSimpleEmptySpacesCharacter, testDataSimpleEmptySpaces[ result ] );

    // ---- Invalid usage section ---- //

    // Call the constructor.
    targetObject = Argument( testDataInvalidSimple, shortName );

    //-- Try to find the start position. --
    //   Invalid long name simple.
    result = target -> findShortName();
    TEST_ASSERT_EQUAL_INT( testDataInvalidSimplePosition, result );
    TEST_ASSERT_FALSE( target -> bFields.found );

    // Call the constructor.
    targetObject = Argument( testDataInvalidWithoutSpace, shortName );

    //-- Try to find the start position. --
    //   Invalid long name without space.
    result = target -> findShortName();
    TEST_ASSERT_EQUAL_INT( testDataInvalidWithoutSpacePosition, result );
    TEST_ASSERT_FALSE( target -> bFields.found );

    // Call the constructor.
    targetObject = Argument( NULL, shortName );
    
    //-- Try to find the start position. --
    //   Simple long name with a valid argument.
    result = target -> findShortName();
    TEST_ASSERT_EQUAL_INT( -1, result );

    // Call the constructor.
    targetObject = Argument( testDataInvalidWithoutSpace, shortName, NULL );
    
    //-- Try to find the start position. --
    //   Simple long name with a valid argument.
    result = target -> findShortName();
    TEST_ASSERT_EQUAL_INT( -1, result );

    // Call the constructor.
    targetObject = Argument( testDataInvalidWithoutSpace, shortName );
    target -> sourceSize -= 5;
    
    //-- Try to find the start position. --
    //   Simple long name with a valid argument.
    result = target -> findShortName();
    TEST_ASSERT_EQUAL_INT( -1, result );

    // Call the constructor.
    targetObject = Argument( testDataSimple, shortName );
    target -> sourceSize -= 3;
    
    //-- Try to find the start position. --
    //   Simple long name with a valid argument.
    result = target -> findShortName();
    TEST_ASSERT_EQUAL_INT( -1, result );

    // Call the constructor.
    targetObject = Argument( testDataSimple, '%' );
    
    //-- Try to find the start position. --
    //   Simple long name with a valid argument.
    result = target -> findShortName();
    TEST_ASSERT_EQUAL_INT( -1, result );

}

void test_findShortName( void ){
    testerObject.test_findShortName();
}

void ArgumentUT::test_findPlace(){

    // Simple input first
    const char* testDataSimple = "200 10";
    int testDataSimplePosition = 0;
    int testDataSimplePlace = 0;

    // Simple input second
    const char* testDataSimpleSecond = "200 10";
    int testDataSimpleSecondPosition = 0;
    int testDataSimpleSecondPlace = 0;

    // Simple input with spaces first
    const char* testDataSimpleSpacesFirst = "200       10   ";
    int testDataSimpleSpacesFirstPosition = 0;
    int testDataSimpleSpacesFirstPlace = 0;

    // Simple input with spaces second
    const char* testDataSimpleSpacesSecond = "200       10   ";
    int testDataSimpleSpacesSecondPosition = 10;
    int testDataSimpleSpacesSecondPlace = 1;

    // Input with string first
    const char* testDataStringFirst = "  \"hello first argument\" \"Bello second argument\"";
    int testDataStringFirstPosition = 2;
    int testDataStringFirstPlace = 0;

    // Input with string second
    const char* testDataStringSecond = "  \"hello first argument\" \"Bello second argument\"";
    int testDataStringSecondPosition = 25;
    int testDataStringSecondPlace = 1;

    // It will hold the return value of the function call.
    int result;

    // Call the constructor.
    targetObject = Argument( testDataSimple, testDataSimplePlace );

    //-- Try to find the start position. --
    //   Simple input first
    result = target -> findByPlace();
    TEST_ASSERT_EQUAL_INT( testDataSimplePosition, result );

    // Call the constructor.
    targetObject = Argument( testDataSimpleSecond, testDataSimpleSecondPlace );

    //-- Try to find the start position. --
    //   Simple input second
    result = target -> findByPlace();
    TEST_ASSERT_EQUAL_INT( testDataSimpleSecondPosition, result );

    // Call the constructor.
    targetObject = Argument( testDataSimpleSpacesFirst, testDataSimpleSpacesFirstPlace );

    //-- Try to find the start position. --
    //   Simple input with spaces first
    result = target -> findByPlace();
    TEST_ASSERT_EQUAL_INT( testDataSimpleSpacesFirstPosition, result );

    // Call the constructor.
    targetObject = Argument( testDataSimpleSpacesSecond, testDataSimpleSpacesSecondPlace );

    //-- Try to find the start position. --
    //   Simple input with spaces second
    result = target -> findByPlace();
    TEST_ASSERT_EQUAL_INT( testDataSimpleSpacesSecondPosition, result );

    // Call the constructor.
    targetObject = Argument( testDataStringFirst, testDataStringFirstPlace );

    //-- Try to find the start position. --
    //   Input with string first
    result = target -> findByPlace();
    TEST_ASSERT_EQUAL_INT( testDataStringFirstPosition, result );

    // Call the constructor.
    targetObject = Argument( testDataStringSecond, testDataStringSecondPlace );

    //-- Try to find the start position. --
    //   Input with string second
    result = target -> findByPlace();
    TEST_ASSERT_EQUAL_INT( testDataStringSecondPosition, result );

    // ---- Invalid usage section ---- //

    // Call the constructor.
    targetObject = Argument( NULL, 0 );

    //-- Try to find the start position. --
    result = target -> findByPlace();
    TEST_ASSERT_EQUAL_INT( -1, result );

    // Call the constructor.
    targetObject = Argument( "    ", 1 );

    //-- Try to find the start position. --
    result = target -> findByPlace();
    TEST_ASSERT_EQUAL_INT( -1, result );

    // Call the constructor.
    targetObject = Argument( "    1    ", 1 );

    //-- Try to find the start position. --
    result = target -> findByPlace();
    TEST_ASSERT_EQUAL_INT( -1, result );

    // Call the constructor.
    targetObject = Argument( "hello", -1 );

    //-- Try to find the start position. --
    result = target -> findByPlace();
    TEST_ASSERT_EQUAL_INT( -1, result );

}

void test_findPlace( void ){
    testerObject.test_findPlace();
}

void ArgumentUT::test_find(){

    const char* longName = "longName";
    char shortName = 's';

    // Simple short name
    const char* testDataSimpleShortName = "-s";

    // Advanced short name
    const char* testDataAdvancedShortName = "--long -name \" -s help\" -s --find  ";

    // Simple long name
    const char* testDataSimpleLongName = "--longName";

    // Advanced long name
    const char* testDataAdvancedLongName = "--long -name \" --longName help\" --longName --find  ";

    // Invalid short name simple
    const char* testDataInvalidShortNameSimple = "-t";

    // Invalid short name advanced
    const char* testDataInvalidShortNameAdvanced = "--long -name \" -s help\" --find  ";

    // Invalid long name simple
    const char* testDataInvalidLongNameSimple = "--lizard";

    // Invalid long name advanced
    const char* testDataInvalidLongNameAdvanced = "--long -name \" --longName help\" --find  ";

    // It will hold the return value of the function call.
    bool result;

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortName, shortName );

    //-- Try to find the argument. --
    //   Simple short name
    result = target -> find();
    TEST_ASSERT_TRUE( result );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedShortName, shortName );

    //-- Try to find the argument. --
    //   Advanced short name
    result = target -> find();
    TEST_ASSERT_TRUE( result );

    // Call the constructor.
    targetObject = Argument( testDataSimpleLongName, shortName, longName );

    //-- Try to find the argument. --
    //   Simple long name
    result = target -> find();
    TEST_ASSERT_TRUE( result );

    // Call the constructor.
    targetObject = Argument( testDataAdvancedLongName, shortName, longName );

    //-- Try to find the argument. --
    //   Advanced long name
    result = target -> find();
    TEST_ASSERT_TRUE( result );

    // Call the constructor.
    targetObject = Argument( testDataInvalidShortNameSimple, shortName );

    //-- Try to find the argument. --
    //   Invalid short name simple
    result = target -> find();
    TEST_ASSERT_FALSE( result );

    // Call the constructor.
    targetObject = Argument( testDataInvalidShortNameAdvanced, shortName );

    //-- Try to find the argument. --
    //   Invalid short name simple
    result = target -> find();
    TEST_ASSERT_FALSE( result );

    // Call the constructor.
    targetObject = Argument( testDataInvalidLongNameSimple, shortName, longName );

    //-- Try to find the argument. --
    //   Invalid short name simple
    result = target -> find();
    TEST_ASSERT_FALSE( result );

    // Call the constructor.
    targetObject = Argument( testDataInvalidLongNameAdvanced, shortName, longName );

    //-- Try to find the argument. --
    //   Invalid short name simple
    result = target -> find();
    TEST_ASSERT_FALSE( result );

}

void test_find( void ){
    testerObject.test_find();
}

void ArgumentUT::test_findStart(){

    const char* longName = "longName";
    char shortName = 's';

    // Simple long name
    const char* testDataSimpleLongName = "--longName 10";
    int testDataSimpleLongNamePosition = 11;

    // Simple short name
    const char* testDataSimpleShortName = "-s 10";
    int testDataSimpleShortNamePosition = 3;

    // Simple place dependent
    const char* testDataSimplePlaceDependent = "20 10";
    int testDataSimplePlaceDependentPosition = 3;




    // Invalid long name
    const char* testDataInvalidLongName = "--longNamee 10";

    // Invalid short name
    const char* testDataInvalidShortName = "-h 10";

    // Invalid place dependent
    const char* testDataInvalidPlaceDependent = "20 10";



    // It will hold the return value of the function call.
    int result;

    // Call the constructor.
    targetObject = Argument( testDataSimpleLongName, shortName, longName );

    //-- Try to find the argument. --
    //   Simple short name
    result = target -> findStart();
    TEST_ASSERT_EQUAL_INT( testDataSimpleLongNamePosition, result );

    // Call the constructor.
    targetObject = Argument( testDataSimpleShortName, shortName, longName );

    //-- Try to find the argument. --
    //   Simple short name
    result = target -> findStart();
    TEST_ASSERT_EQUAL_INT( testDataSimpleShortNamePosition, result );

    // Call the constructor.
    targetObject = Argument( testDataSimplePlaceDependent, 1 );

    //-- Try to find the argument. --
    //   Simple short name
    result = target -> findStart();
    TEST_ASSERT_EQUAL_INT( testDataSimplePlaceDependentPosition, result );




    // Call the constructor.
    targetObject = Argument( testDataInvalidLongName, shortName, longName );

    //-- Try to find the argument. --
    //   Simple short name
    result = target -> findStart();
    TEST_ASSERT_EQUAL_INT( -1, result );

    // Call the constructor.
    targetObject = Argument( testDataInvalidShortName, shortName, longName );

    //-- Try to find the argument. --
    //   Simple short name
    result = target -> findStart();
    TEST_ASSERT_EQUAL_INT( -1, result );

    // Call the constructor.
    targetObject = Argument( testDataInvalidPlaceDependent, 2 );

    //-- Try to find the argument. --
    //   Simple short name
    result = target -> findStart();
    TEST_ASSERT_EQUAL_INT( -1, result );

}

void test_findStart(){
    testerObject.test_findStart();
}

int main(){

    UNITY_BEGIN();

    RUN_TEST( test_findLongName );
    RUN_TEST( test_findShortName );
    RUN_TEST( test_findStart );
    RUN_TEST( test_find );

    return UNITY_END();

}