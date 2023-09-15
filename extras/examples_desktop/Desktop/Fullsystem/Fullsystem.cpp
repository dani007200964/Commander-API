
/*
 * Created on 2023.Jun.25
 *
 * Copyright (c) 2023 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2023.Sep.06
 *
 * This is a simple example, that demonstrates how
 * to use the base functionality of th Commander-API.
*/


#include <stdio.h>

#include <fcntl.h>
#ifdef _WIN32
#include <io.h>
#endif
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>

#include "System.h"

#include "stdioStream.hpp"

// Necessary includes
#include "Commander-API.hpp"
#include "Commander-IO.hpp"
#include "Commander-API-Commands.hpp"
#include "Commander-Database.hpp"
#include <math.h>

CommanderDatabase<int>::dataRecord_t commandData[] = {
    { 0, NULL, NULL, "Hello", 10 },
    { 0, NULL, NULL, "Mizu", 30 },
    { 0, NULL, NULL, "Cica", 10 },
    { 0, NULL, NULL, "Kutya", 30 },
    { 0, NULL, NULL, "Majom", 10 },
    { 0, NULL, NULL, "Kaja", 10 },
    { 0, NULL, NULL, "Kanya", 10 },
    { 0, NULL, NULL, "Manya", 10 },
    { 0, NULL, NULL, "Franya", 10 },
    { 0, NULL, NULL, "Pia", 30 }
};

CommanderDatabase<int> commands( commandData, 10 );

// Use stdio as Channel.
stdioStream stdioChannel;

// We have to create an object from Commander class.
Commander commander;

/*
// Add echo and env commands to the API tree.
Commander::API_t API_tree[] = {
    API_ELEMENT_REBOOT,
    API_ELEMENT_ECHO,
    API_ELEMENT_ENV,
    API_ELEMENT_EXPORT_TARGET,
    API_ELEMENT_EXPORT,
    API_ELEMENT_MEMDUMP,
    API_ELEMENT_MICROS,
    API_ELEMENT_MILLIS,
    API_ELEMENT_UPTIME,
    API_ELEMENT_NEOFETCH,
    API_ELEMENT_PINMODE,
    API_ELEMENT_DIGITALWRITE,
    API_ELEMENT_DIGITALREAD,
    API_ELEMENT_ANALOGREAD,
    API_ELEMENT_ANALOGWRITE,
    API_ELEMENT_SIN,
    API_ELEMENT_COS,
    API_ELEMENT_ABS,
    API_ELEMENT_RANDOM,
    API_ELEMENT_NOT
};
*/


Commander::systemCommand_t systemCommands[] = {
    API_ELEMENT_REBOOT,
    API_ELEMENT_ECHO,
    API_ELEMENT_ENV,
    API_ELEMENT_EXPORT_TARGET,
    API_ELEMENT_EXPORT,
    API_ELEMENT_MEMDUMP,
    API_ELEMENT_MICROS,
    API_ELEMENT_MILLIS,
    API_ELEMENT_UPTIME,
    API_ELEMENT_NEOFETCH
};



/*
bool cat_func( char *args, Stream *response, void* parrent );
bool dog_func( char *args, Stream *response, void* parrent );

Commander::systemCommand_t systemCommands[] = {
    //{ 0, NULL, NULL, "cat", { "cat func description.", cat_func } },
    //{ 0, NULL, NULL, "dog", { "dog func description.", dog_func } }
    apiElement( "cat", "cat func description.", cat_func ),
    apiElement( "dog", "dog func description.", dog_func )
};
*/

// Global system variables.
float tmpFloat = 0.0;
int tmpInt = -1300;



// System Variable array. This array will store the
// name and the instance of the system variables.
Commander::systemVariable_t systemVariables[] = {
    //systemVariableFloat( tmpFloat ),
    //systemVariableInt( tmpInt )
    //{ 0, NULL, NULL, "temFloat", { Commander::VARIABLE_FLOAT, { (float*)&tmpFloat } } },
    //{ 0, NULL, NULL, "tmpInt", { Commander::VARIABLE_INT, { (float*)&tmpInt } } }
    systemVariableFloat( tmpFloat ),
    systemVariableInt( tmpInt )
};

// This is a buffer to hold the incoming command.
char commandFromSerial[ 30 ];

// This variable tracks the location of the next free
// space in the commandFromSerial buffer.
uint8_t commandIndex = 0;




// Main program.
int main(){

    // System init section.
    if( setlocale(LC_ALL, NULL) == NULL ){

        wprintf( L"Error setting locale!\r\n" );

    }


    //commands.attachDebugChannel( &stdioChannel );
    //commands.setDebugLevel( CommanderDatabase<int>::DEBUG_VERBOSE );

    //commands.init();
    //stdioChannel.println( commands[ "Hello" ] -> name );
    //stdioChannel.println( commands[ "Hello" ] -> place );

    // There is an option to attach a debug channel to Commander.
    // It can be handy to find any problems during the initialization
    // phase. In this example, we will use {{ channel }} for this.
    commander.attachDebugChannel( &stdioChannel );

    // At start, Commander does not know anything about our commands.
    // We have to attach the API_tree array from the previous steps
    // to Commander to work properly.
    commander.attachTree( systemCommands );

    // After we attached the API_tree, Commander has to initialize
    // itself for the fastest runtime possible. It creates a balanced
    // binary tree from the API_tree to boost the search speed.
    // This part uses some recursion, to make the code space small.
    // But recursion is a bit stack hungry, so please initialize
    // Commander at the beginning of your code to prevent stack-overlow.
    commander.init();

    commander.attachVariablesFunction( systemVariables, 2 );

    while( 1 ){
        commander.update( commandFromSerial, sizeof( commandFromSerial ), &stdioChannel );
    }

}

bool cat_func( char *args, Stream *response, void* parrent ){
    response -> println( "Hello from cat func!" );
    return true;
}

bool dog_func( char *args, Stream *response, void* parrent ){
    response -> println( "Hello from dog func!" );
    return true;
}
