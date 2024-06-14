
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
#include "Commander-Autocomplete.hpp"



// Use stdio as Channel.
stdioStream stdioChannel;

#define COMMAND_SIZE 30

// We have to create an object from Commander class.
Commander commander;

bool cat_func( char *args, CommandCaller* caller );
bool dog_func( char *args, CommandCaller* caller );
bool sum_func( char *args, CommandCaller* caller );

char commandBuffer[ COMMAND_SIZE ];

char pipeBuffer[ COMMANDER_PIPE_BUFFER_SIZE ];
commanderPipeChannel pipeChannel;
/*
AutoComplete::TrieElement_t trie[ 9 ];
uint16_t trie_indexes_element_0[] = { 1, 2 };
uint16_t trie_indexes_element_1[] = { 3 };
uint16_t trie_indexes_element_2[] = { 4, 5 };
uint16_t trie_indexes_element_3[] = { 6, 7 };
uint16_t trie_indexes_element_4[] = { 8 };
*/

// Generated with Commander Trie Generator
// Trie name: trie
uint16_t trie_element_0_indexes[] = { 1 };
uint16_t trie_element_1_indexes[] = { 2 };
uint16_t trie_element_2_indexes[] = { 3, 4, 33, 38 };
uint16_t trie_element_4_indexes[] = { 5, 9, 19 };
uint16_t trie_element_5_indexes[] = { 6 };
uint16_t trie_element_6_indexes[] = { 7 };
uint16_t trie_element_7_indexes[] = { 8 };
uint16_t trie_element_9_indexes[] = { 10 };
uint16_t trie_element_10_indexes[] = { 11 };
uint16_t trie_element_11_indexes[] = { 12 };
uint16_t trie_element_12_indexes[] = { 13 };
uint16_t trie_element_13_indexes[] = { 14 };
uint16_t trie_element_14_indexes[] = { 15 };
uint16_t trie_element_15_indexes[] = { 16 };
uint16_t trie_element_16_indexes[] = { 17 };
uint16_t trie_element_17_indexes[] = { 18 };
uint16_t trie_element_19_indexes[] = { 20 };
uint16_t trie_element_20_indexes[] = { 21 };
uint16_t trie_element_21_indexes[] = { 22 };
uint16_t trie_element_22_indexes[] = { 23 };
uint16_t trie_element_23_indexes[] = { 24 };
uint16_t trie_element_24_indexes[] = { 25 };
uint16_t trie_element_25_indexes[] = { 26 };
uint16_t trie_element_26_indexes[] = { 27 };
uint16_t trie_element_27_indexes[] = { 28 };
uint16_t trie_element_28_indexes[] = { 29 };
uint16_t trie_element_29_indexes[] = { 30 };
uint16_t trie_element_30_indexes[] = { 31 };
uint16_t trie_element_31_indexes[] = { 32 };
uint16_t trie_element_33_indexes[] = { 34 };
uint16_t trie_element_34_indexes[] = { 35 };
uint16_t trie_element_35_indexes[] = { 36 };
uint16_t trie_element_36_indexes[] = { 37 };
uint16_t trie_element_38_indexes[] = { 39 };
uint16_t trie_element_39_indexes[] = { 40 };
uint16_t trie_element_40_indexes[] = { 41 };
uint16_t trie_element_41_indexes[] = { 42 };
uint16_t trie_element_42_indexes[] = { 43 };
uint16_t trie_element_43_indexes[] = { 44 };
uint16_t trie_element_44_indexes[] = { 45 };

AutoComplete::TrieElement_t trie[] = {
	{ '\0', false, 1, trie_element_0_indexes },
	{ ' ', false, 1, trie_element_1_indexes },
	{ '-', false, 4, trie_element_2_indexes },
	{ 'h', true, 0, NULL },
	{ '-', false, 3, trie_element_4_indexes },
	{ 'h', false, 1, trie_element_5_indexes },
	{ 'e', false, 1, trie_element_6_indexes },
	{ 'l', false, 1, trie_element_7_indexes },
	{ 'p', true, 0, NULL },
	{ 'r', false, 1, trie_element_9_indexes },
	{ 'e', false, 1, trie_element_10_indexes },
	{ 'b', false, 1, trie_element_11_indexes },
	{ 'o', false, 1, trie_element_12_indexes },
	{ 'o', false, 1, trie_element_13_indexes },
	{ 't', true, 1, trie_element_14_indexes },
	{ ' ', false, 1, trie_element_15_indexes },
	{ 'n', false, 1, trie_element_16_indexes },
	{ 'o', false, 1, trie_element_17_indexes },
	{ 'w', true, 0, NULL },
	{ 'd', false, 1, trie_element_19_indexes },
	{ 'i', false, 1, trie_element_20_indexes },
	{ 's', false, 1, trie_element_21_indexes },
	{ 'p', false, 1, trie_element_22_indexes },
	{ 'l', false, 1, trie_element_23_indexes },
	{ 'a', false, 1, trie_element_24_indexes },
	{ 'y', false, 1, trie_element_25_indexes },
	{ ' ', false, 1, trie_element_26_indexes },
	{ '"', false, 1, trie_element_27_indexes },
	{ 'T', false, 1, trie_element_28_indexes },
	{ 'e', false, 1, trie_element_29_indexes },
	{ 'x', false, 1, trie_element_30_indexes },
	{ 't', false, 1, trie_element_31_indexes },
	{ '"', true, 0, NULL },
	{ 'r', true, 1, trie_element_33_indexes },
	{ ' ', false, 1, trie_element_34_indexes },
	{ 'n', false, 1, trie_element_35_indexes },
	{ 'o', false, 1, trie_element_36_indexes },
	{ 'w', true, 0, NULL },
	{ 'd', false, 1, trie_element_38_indexes },
	{ ' ', false, 1, trie_element_39_indexes },
	{ '"', false, 1, trie_element_40_indexes },
	{ 'T', false, 1, trie_element_41_indexes },
	{ 'e', false, 1, trie_element_42_indexes },
	{ 'x', false, 1, trie_element_43_indexes },
	{ 't', false, 1, trie_element_44_indexes },
	{ '"', true, 0, NULL }
};

AutoComplete help_test( trie );


// Add echo and env commands to the API tree.
Commander::systemCommand_t API_tree[] = {
    systemCommandWithHelp( "cat", "Description for cat command.", cat_func, &help_test ),
    systemCommandWithHelp( "dog", "Description for dog command.", dog_func, &help_test ),
    systemCommandWithHelp( "sum", "This function sums two number from the argument list.", sum_func, &help_test )    
};


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

    // commander.enablePipeModule( pipeBuffer, &pipeChannel );

    stdioChannel.println();
    stdioChannel.println( "---- Init Finished ----" );
    stdioChannel.println();

    char buffer[ 200 ];
    int buffer_size = sizeof( buffer );
    int num_of_hints;
    int i;

    num_of_hints = commander.generateHint( "cat --reboot ", buffer, buffer_size );
    stdioChannel.print( "number of hints: " );
    stdioChannel.println( num_of_hints );
    for( i = 0; i < num_of_hints; i++ ){
        stdioChannel.print( "\t" );
        stdioChannel.println( commander.getHint( i ) );
    }

    num_of_hints = commander.generateHint( "cat --rebo", buffer, buffer_size );
    stdioChannel.print( "number of hints: " );
    stdioChannel.println( num_of_hints );
    for( i = 0; i < num_of_hints; i++ ){
        stdioChannel.print( "\t" );
        stdioChannel.println( commander.getHint( i, true ) );
    }

    num_of_hints = commander.generateHint( "c", buffer, buffer_size );
    stdioChannel.print( "number of hints: " );
    stdioChannel.println( num_of_hints );
    for( i = 0; i < num_of_hints; i++ ){
        stdioChannel.print( "\t" );
        stdioChannel.println( commander.getHint( i, true ) );
    }

    // stdioChannel.println( "Type something" );
    // stdioChannel.print( "$: " );



    // Infinite loop.
    while( 1 ){


        // commander.update( commandBuffer, COMMAND_SIZE, &stdioChannel );




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
