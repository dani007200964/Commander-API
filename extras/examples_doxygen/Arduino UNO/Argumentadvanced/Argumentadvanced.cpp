
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


// Necessary includes
#include "Commander-API.hpp"
#include "Commander-IO.hpp"

#include "Commander-Arguments.hpp"


// We have to create an object from Commander class.
Commander commander;

// We have to create the prototypes functions for our commands.
// The arguments have to be the same for all command functions.
void dog_func( char *args, Stream *response, void* parrent );


const char* dogGraphicsLine0 = {
    "\\ __      _"
};

const char* dogGraphicsLine1 = {
    ")}____//"
};

const char* dogGraphicsLine2 = {
    " `_/      )"
};

const char* dogGraphicsLine3 = {
    " (_(_/-(_/"
};

const char* dogCommandDescription = {
    "\r\n\tGenerates ASCII art pictures of a dog with a message.\r\n\t"
    "[ text ]    : Text to display [ opt str ]\r\n\t"
    "-b --borg   : Borg mode [ opt flag ]\r\n\t"
    "-d --dead   : Dead mode [ opt flag ]\r\n\t"
    "-g --greedy : Greedy mode [ opt flag ]\r\n\t"
    "-p --poop   : Poop mode [ opt flag ]\r\n\t"
    "-e --eyes   : Manual eye type like [ opt str ]"
};

Commander::API_t API_tree[] = {
    apiElement( "dog", dogCommandDescription, dog_func )
};

// This is a buffer to hold the incoming command.
char commandFromSerial[ 30 ];

// This variable tracks the location of the next free
// space in the commandFromSerial buffer.
uint8_t commandIndex = 0;




// System init section.
void setup(){

    Serial.begin(115200);

    // There is an option to attach a debug channel to Commander.
    // It can be handy to find any problems during the initialization
    // phase. In this example, we will use Serial for this.
    commander.attachDebugChannel( &Serial );

    // At start, Commander does not know anything about our commands.
    // We have to attach the API_tree array from the previous steps
    // to Commander to work properly.
    commander.attachTree( API_tree );

    // After we attached the API_tree, Commander has to initialize
    // itself for the fastest runtime possible. It creates a balanced
    // binary tree from the API_tree to boost the search speed.
    // This part uses some recursion, to make the code space small.
    // But recursion is a bit stack hungry, so please initialize
    // Commander at the beginning of your code to prevent stack-overlow.
    commander.init();

    Serial.println();
    Serial.println( "---- Init Finished ----" );
    Serial.println();

    Serial.println( "Type something" );
    Serial.print( "$: " );


}

// Infinite loop.
void loop(){

    // Check if there is any data incoming.
    while( Serial.available() ){

        // Read the next incoming character.
        char c = Serial.read();

        // Every command from Serial is terminated with a new-line
        // character. If a new-line character arrives, we have to
        // terminate the string in the commandFromSerial buffer,
        // and execute it. After execution, we have to reset the
        // commandIndex counter to zero.
        if( c == '\r' ){
            commandFromSerial[ commandIndex ] = '\0';
            Serial.println();
            commander.execute( commandFromSerial, &Serial );
            commandIndex = 0;
            Serial.print( "$: " );
        }

        // If we have a carriage-return character we simply
        // ignore it.
        else if( c == '\n' ){
            continue;
        }

        // Handle backspace events.
        else if( ( c == '\b' ) || ( c == 127 ) ){
            if( commandIndex > 0 ){
                commandIndex--;
                Serial.print( "\b \b" );
            }
        }

        // Every other case we just put the data to the next
        // free space in the commandFromSerial buffer, increment
        // the commandIndex, and check if it wants to overflow.
        else{
            commandFromSerial[ commandIndex ] = c;
            commandIndex++;
            if( commandIndex >= sizeof( commandFromSerial ) ){
                commandIndex = sizeof( commandFromSerial ) - 1;
            }
            else{
                Serial.print( c );
            }
        }

    }


}

/// This is an example function for the cat command
void dog_func(char *args, Stream *response, void* parrent ){

    // Generic counter
    int i;

    // The user specified text will be copied to this buffer.
    char textBuffer[ 20 ];

    // Default text!
    char defaultText[] = "Who?Who?Who?Who?";

    // The user specified eyes will be copied here.
    char eyesBuffer[ 3 ];

    // Built-in eye configurations
    char defaultEyes[] = "''";
    char deadEyes[] = "XX";
    char borgEyes[] = "==";
    char greedyEyes[] = "$$";

    // Set a pointer to the default values.
    char *printedTextPtr = defaultText;
    char *printedEyesPtr = defaultEyes;

    // Create the argument objects.
    Argument text( args, 0 );
    Argument eyes( args, 'e', "eyes" );
    Argument dead( args, 'd', "dead" );
    Argument borg( args, 'b', "borg" );
    Argument greedy( args, 'g', "greedy" );
    Argument poop( args, 'p', "poop" );

    // Parse the arguments with their expected values.
    text.parseString( textBuffer );
    eyes.parseString( eyesBuffer );

    // Parse arguments without values assigned( these are basically flags ).
    dead.find();
    borg.find();
    greedy.find();
    poop.find();

    // Check if the arguments are parsed correctly.
    if( text ){
        printedTextPtr = textBuffer;
    }

    if( eyes ){
        if( strlen( eyesBuffer ) == 2 ){
            printedEyesPtr = eyesBuffer;
        }
    }

    if( dead.isFound() ){

        printedEyesPtr = deadEyes;

    }

    if( borg.isFound() ){

        printedEyesPtr = borgEyes;

    }

    if( greedy.isFound() ){

        printedEyesPtr = greedyEyes;

    }

    // Print the graphics.
    if( !text ){
        response -> println( "Who let the dogs out???\r\n" );
    }

    response -> print( '+' );
    for( i = 0; i < strlen( (const char*)printedTextPtr ) + 2; i++ ){
        response -> print( "-" );
    }
    response -> println( '+' );

    response -> print( "| " );
    response -> print( printedTextPtr );
    response -> println( " |" );

    response -> print( '+' );
    for( i = 0; i < strlen( (const char*)printedTextPtr ) + 2; i++ ){
        response -> print( "-" );
    }
    response -> println( '+' );

    for( i = 0; i < strlen( (const char*)printedTextPtr ) + 4; i++ ){
        response -> print( ' ' );
    }
    response -> println( dogGraphicsLine0 );

    for( i = 0; i < strlen( (const char*)printedTextPtr ) + 4; i++ ){
        response -> print( ' ' );
    }
    response -> print( 'o' );
    response -> print( printedEyesPtr );
    response -> println( dogGraphicsLine1 );


    for( i = 0; i < strlen( (const char*)printedTextPtr ) + 4; i++ ){
        response -> print( ' ' );
    }
    response -> println( dogGraphicsLine2 );


    for( i = 0; i < strlen( (const char*)printedTextPtr ) + 4; i++ ){
        response -> print( ' ' );
    }
    response -> print( dogGraphicsLine3 );

    if( poop.isFound() ){
        response -> print(  " ,^," );
    }

    response -> println();


}