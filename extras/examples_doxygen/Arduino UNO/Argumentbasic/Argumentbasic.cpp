
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

// Argument parser module.
#include "Commander-Arguments.hpp"






// System init section.
void setup(){

    Serial.begin(115200);

    // Simple argument name example
    const char* argsToParseSimple = "Jack -h 174 -w 71";

    // String arguments require a buffer to store the data.
    char nameBuffer[ 30 ];

    // Create an Argument object for each argument
    Argument name( argsToParseSimple, 0 );
    Argument height( argsToParseSimple, 'h', "height" );
    Argument weight( argsToParseSimple, 'w', "weight" );

    // Try to parse each argument.
    name.parseString( nameBuffer );
    height.parseInt();
    weight.parseInt();

    Serial.print( "Parsing these arguments: " );
    Serial.println( argsToParseSimple );

    Serial.print( "\tname: " );

    // Check if the name argument is parsed correctly.
    if( name ){
        Serial.println( (char*)name );
    }
    else{
        Serial.println( "Error!" );
    }

    Serial.print( "\theight: " );

    // Check if the height argument is parsed correctly.
    if( height ){
        Serial.println( (int)height );
    }
    else{
        Serial.println( "Error!" );
    }

    Serial.print( "\tweight: " );

    // Check if the weight argument is parsed correctly.
    if( weight ){
        Serial.println( (int)weight );
    }
    else{
        Serial.println( "Error!" );
    }

    // Detailed argument name example
    const char* argsToParseDetailed = "\"Jack Black\" --height 174 --weight 71";

    // Create an Argument object for each argument
    name = Argument( argsToParseDetailed, 0 );
    height = Argument( argsToParseDetailed, 'h', "height" );
    weight = Argument( argsToParseDetailed, 'w', "weight" );

    // Try to parse each argument.
    name.parseString( nameBuffer );
    height.parseInt();
    weight.parseInt();

    Serial.print( "Parsing these arguments: " );
    Serial.println( argsToParseDetailed );

    Serial.print( "\tname: " );

    // Check if the name argument is parsed correctly.
    if( name ){
        Serial.println( (char*)name );
    }
    else{
        Serial.println( "Error!" );
    }

    Serial.print( "\theight: " );

    // Check if the height argument is parsed correctly.
    if( height ){
        Serial.println( (int)height );
    }
    else{
        Serial.println( "Error!" );
    }

    Serial.print( "\tweight: " );

    // Check if the weight argument is parsed correctly.
    if( weight ){
        Serial.println( (int)weight );
    }
    else{
        Serial.println( "Error!" );
    }


}

// Infinite loop.
void loop(){



}
