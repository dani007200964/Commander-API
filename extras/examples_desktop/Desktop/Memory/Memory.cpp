
/*
 * Created on 2023.Jun.25
 *
 * Copyright (c) 2023 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2023.Oct.20
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
#include "Commander-API-Commands.hpp"


// Use stdio as Channel.
stdioStream stdioChannel;

#define COMMAND_SIZE 30

// We have to create an object from Commander class.
Commander commander;

bool cat_func( char *args, CommandCaller* caller );
bool dog_func( char *args, CommandCaller* caller );
bool sum_func( char *args, CommandCaller* caller );

// Add echo and env commands to the API tree.
Commander::systemCommand_t API_tree[] = {
    systemCommand( "cat", "Description for cat command.", cat_func ),
    systemCommand( "dog", "Description for dog command.", dog_func ),
    systemCommand( "sum", "This function sums two number from the argument list.", sum_func )    
};

char commandBuffer[ COMMAND_SIZE ];

char pipeBuffer[ COMMANDER_PIPE_BUFFER_SIZE ];
commanderPipeChannel pipeChannel;



// Main program.
int main(){

    // System init section.
    if( setlocale(LC_ALL, NULL) == NULL ){

        wprintf( L"Error setting locale!\r\n" );

    }


    // There is an option to attach a debug channel to Commander.
    // It can be handy to find any problems during the initialization
    // phase. In this example, we will use stdioChannel for this.
    commander.attachDebugChannel( &stdioChannel );

    // At start, Commander does not know anything about our commands.
    // We have to attach the API_tree array from the previous steps
    // to Commander to work properly.
    commander.attachTree( API_tree );

    // After we attached the API_tree, Commander has to initialize
    // itself for the fastest runtime possible. It creates a balanced
    // binary tree from the API_tree to boost the search speed.
    // This part uses some recursion, to make the code space small.
    // But recursion is a bit stack hungry, so pleacatse initialize
    // Commander at the beginning of your code to prevent stack-overlow.
    commander.init();

    commander.enablePipeModule( pipeBuffer, &pipeChannel );

    stdioChannel.println();
    stdioChannel.println( "---- Init Finished ----" );
    stdioChannel.println();

    stdioChannel.println( "Type something" );
    stdioChannel.print( "$: " );



    // Infinite loop.
    while( 1 ){


        commander.update( commandBuffer, COMMAND_SIZE, &stdioChannel );




    }

    return 0;

}


/// This is an example function for the cat command
bool cat_func( char *args, CommandCaller* caller ){

  caller -> print("Hello from cat function!\r\n");
  return true;

}

/// This is an example function for the dog command
bool dog_func( char *args, CommandCaller* caller ){

  caller -> print("Hello from dog function!\r\n");
  return true;

}

/// This is an example function for the sum command
bool sum_func( char *args, CommandCaller* caller ){

  // These variables will hold the value of the
  // two numbers, that has to be summed.
  int a = 0;
  int b = 0;

  // This variable will hold the result of the
  // argument parser.
  int argResult;

  // This variable will hold the sum result.
  int sum = 0;

  argResult = sscanf( args, "%d %d", &a, &b );

  // We have to check that we parsed successfully the two
  // numbers from the argument string.
  if( argResult != 2 ){

    // If we could not parse two numbers, we have an argument problem.
    // We print out the problem to the response channel.
    caller -> print( "Argument error! Two numbers required, separated with a blank space.\r\n" );

    // Sadly we have to stop the command execution and return.
    return false;

  }

  // Calculate the sum.
  sum = a + b;

  // Print out the result.
  caller -> print( a );
  caller -> print( " + " );
  caller -> print( b );
  caller -> print( " = " );
  caller -> println( sum );
    return true;
}
