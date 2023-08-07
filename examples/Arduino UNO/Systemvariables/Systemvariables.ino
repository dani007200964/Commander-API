
/*
 * Created on 2023.Jun.25
 *
 * Copyright (c) 2023 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2023.Aug.07
 *
 * This is a simple example, that demonstrates how
 * to use the base functionality of th Commander-API.
*/


// Necessary includes.
#include "Commander-API.hpp"
#include "Commander-IO.hpp"
#include "Commander-Arguments.hpp"






// System init section.
void setup(){

    Serial.begin(115200);

    // Global system variables.
    float reactor = 10.5;
    int index = 3;
    char text[] = "Hello bello";

    // System Variable array. This array will store the
    // name and the instance of the system variables.
    Commander::SystemVariable_t systemVariables[] = {
        systemVariableFloat( reactor ),
        systemVariableInt( index ),
        systemVariableString( text )
    };

    // Float argument and its text.
    char floatArgumentText[] = "-f $reactor";
    Argument floatArgument( floatArgumentText, 'f', "float" );

    // Integer argument and its text.
    char intArgumentText[] = "-i $index";
    Argument intArgument( intArgumentText, 'i', "int" );

    // String argument, its text and a buffer for the result.
    char stringArgumentText[] = "-s $text";
    Argument stringArgument( stringArgumentText, 's', "str" );
    char stringArgumentBuffer[ 20 ];

    // Attach the system variable array to the command parser.
    Commander::attachVariables( systemVariables );

    // Try to find and print the system variables by their name.
    Serial.print( __CONST_TXT__( "Value of 'reactor' system variable: " ) );
    Commander::printSystemVariable( &Serial, "reactor" );
    Serial.println();

    Serial.print( __CONST_TXT__( "Value of 'index' system variable: " ) );
    Commander::printSystemVariable( &Serial, "index" );
    Serial.println();

    Serial.print( __CONST_TXT__( "Value of 'text' system variable: " ) );
    Commander::printSystemVariable( &Serial, "text" );
    Serial.println();

    // Another way to access system variables is to use Arguments.
    // A system variable in the argument string can be accessed with the '$' character.

    Serial.print( __CONST_TXT__( "Parsing float argument '" ) );
    Serial.print( floatArgumentText );
    Serial.print( __CONST_TXT__( "': " ) );
    floatArgument.parseFloat();

    if( floatArgument ){
        Serial.println( (float)floatArgument );
    }

    Serial.print( __CONST_TXT__( "Parsing int argument '" ) );
    Serial.print( intArgumentText );
    Serial.print( __CONST_TXT__( "': " ) );
    intArgument.parseInt();

    if( intArgument ){
        Serial.println( (int)intArgument );
    }

    Serial.print( __CONST_TXT__( "Parsing string argument '" ) );
    Serial.print( stringArgumentText );
    Serial.print( __CONST_TXT__( "': " ) );
    stringArgument.parseString( stringArgumentBuffer );

    if( stringArgument ){
        Serial.println( (char*)stringArgument );
    }


}

// Infinite loop.
void loop(){



}
