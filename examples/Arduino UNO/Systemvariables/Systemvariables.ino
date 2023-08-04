
/*
 * Created on 2023.Jun.25
 *
 * Copyright (c) 2023 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2023.Aug.04
 *
 * This is a simple example, that demonstrates how
 * to use the base functionality of th Commander-API.
*/


// Necessary includes.
#include "Commander-API.hpp"
#include "Commander-IO.hpp"






// System init section.
void setup(){

    Serial.begin(115200);

    float reactor = 10.5;
    int index = 3;
    char text[] = "Hello bello";

    Commander::SystemVariable_t systemVariables[] = {
        systemVariable( "reactor", Commander::VARIABLE_FLOAT, &reactor ),
        systemVariable( "index", Commander::VARIABLE_INT, &index ),
        systemVariable( "text", Commander::VARIABLES_STRING, text )
    };

    Commander::attachVariables( systemVariables );

    Commander::SystemVariable_t* var = Commander::getSystemVariable( "reactor" );

    if( var != NULL ){
        print( var -> data.f );
    }


}

// Infinite loop.
void loop(){



}
