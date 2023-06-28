
/*
 * Created on June 25 2023
 *
 * Copyright (c) 2023 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Shellminator project.
 * Modified 2023.05.13
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

    const char* argsToParseSimple = "Jack -h 174 -w 71";

    Argument name( argsToParseSimple, 0 );
    Argument height( argsToParseSimple, 'h', "height" );
    Argument weight( argsToParseSimple, 'w', "weight" );

    height.parseInt();
    weight.parseInt();

    Serial.print( "Parsing this arguments: " );
    Serial.println( argsToParseSimple );

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

    const char* argsToParseDetailed = "Jack --height 174 --weight 71";

    name = Argument( argsToParseDetailed, 0 );
    height = Argument( argsToParseDetailed, 'h', "height" );
    weight = Argument( argsToParseDetailed, 'w', "weight" );

    Serial.print( "Parsing this arguments: " );
    Serial.println( argsToParseDetailed );

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
