
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


// We have to create an object from Commander class.
Commander commander;

// We have to create the prototypes functions for our commands.
// The arguments have to be the same for all command functions.
void cat_func( char *args, Stream *response, void* parrent );
void dog_func( char *args, Stream *response, void* parrent );

// To tell Commander how many commands we have, it is necessary
// to create an array, that holds some data that represents our
// commands. The type of this array must be Commander::API_t.
// To simplify the command registration, there is a macro called
// apiElement. This macro helps to add command data to this array.
// -The first argument is the name of the command. Commander will
//  search the commands by its name.
// -The second argument is the description for the command.
//  If you use the help command, or '?' character after the command
//  name, Commander will respond  with its description.
// -The third argument is the wrapper function, that has been defined
//  in the previous step.
Commander::API_t API_tree[] = {
    apiElement( "cat", "Description for cat command.", cat_func ),
    apiElement( "dog", "Description for dog command.", dog_func )
};




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

    // If you know the name of the command, but you need the description of it.
    // You can simply add a question mark after the command name. It will print
    // the description data only for the specified command.
    // It won't execute the command with the question mark operator.
    Serial.println( "Printing description for 'cat' command" );
    commander.execute( "cat?", &Serial );
    Serial.println();

    Serial.println( "Printing description for 'dog' command" );
    commander.execute( "dog?", &Serial );
    Serial.println();


}

// Infinite loop.
void loop(){



}

/// This is an example function for the cat command
void cat_func(char *args, Stream *response, void* parrent ){

  response -> print("Hello from cat function!\r\n");

}

/// This is an example function for the dog command
void dog_func(char *args, Stream *response, void* parrent ){

  response -> print("Hello from dog function!\r\n");

}