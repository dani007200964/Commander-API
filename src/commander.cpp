/*
 * commander.cpp
 *
 *  Created on: Feb 5, 2022
 *      Author: dani0
 */

#include "commander.hpp"


void Commander::attachTreeFunction( API_t *API_tree_p, uint32_t API_tree_size_p ){

	API_tree      = API_tree_p;
	API_tree_size = API_tree_size_p;

}

void Commander::attachDebugPort( Serial *debugPort_p ){

	debugPort = debugPort_p;

}

void Commander::init(){

	uint32_t i;
	uint32_t  j;

	API_t temp;

	if( debugPort ){

		debugPort -> println( "Rendezes elott:" );
		for( i = 0; i < API_tree_size; i++ ){

			debugPort -> printf( "%d. %s\r\n", i, API_tree[ i ].name );

		}
		debugPort -> println();

	}

	// Nev szerint sorba rendezzuk a parancsokat.
	for( i = 0; i < API_tree_size; i++ ){

		for( j = i + 1; j < API_tree_size; j++ ){

			//if( API_tree[ i ] > API_tree[ j ] ){
			if( strcmp( API_tree[ i ].name, API_tree[ j ].name ) > 0 ){

				temp = API_tree[ i ];
				API_tree[ i ] = API_tree[ j ];
				API_tree[ j ] = temp;

			}

		}

	}

	if( debugPort ){

		debugPort -> println( "Rendezes utan:" );
		for( i = 0; i < API_tree_size; i++ ){

			debugPort -> printf( "%d. %s\r\n", i, API_tree[ i ].name );

		}
		debugPort -> println();

	}

	// Elmentjuk a nevsorrend szerinti helyet a place valtozoba.
	for( i = 0; i < API_tree_size; i++ ){

		API_tree[ i ].place = i;

	}

	// Optimalizaljuk a sorrendet.
	optimise_api_tree();

	if( debugPort ){

		debugPort -> println( "Optimalizalas utan:" );
		for( i = 0; i < API_tree_size; i++ ){

			debugPort -> printf( "%d. %s\r\n", i, API_tree[ i ].name );

		}
		debugPort -> println();

	}


}

uint16_t Commander::find_api_index_by_place( uint16_t place ){

	// Generic counter variable
	uint16_t i;

	// Go through all commands
	for( i = 0; i < API_tree_size; i++ ){

		// Check that if we found the desired command
		if( API_tree[i].place == place ){

			// If we found it, return the index of it.
			return i;

		}

	}

	// else return 0
	return 0;

}

void Commander::swap_api_elements( uint16_t index, uint16_t place ){

  // Buffer that will temporarly hold an element.
  // This is required for a swap.
  API_t buffer;

  // This variable will store the address of the element defined by the second argument( place ).
  uint16_t current_index;

  // Find the index in the array by place of the 'i'-th element
  current_index = find_api_index_by_place( place );

  // save the context of the 'i'-th element to the buffer
  buffer = API_tree[index];

  // write the 'current_index'-th element to the 'i'-th element
  API_tree[index] = API_tree[current_index];

  // write the buffer to the 'current_index'-th element
  API_tree[current_index] = buffer;

}

void Commander::optimise_api_tree(){

	uint32_t i;

	//API_t buffer;

	// Stores the next elements address in the tree
	API_t *next;

	// Stores the previous elements address in the tree
	API_t *prev;

	// It will store string compersation result
	int32_t comp_res;

	// recursive optimiser need to initialise 'API_cntr' to 0
	elementCounter = 0;

	// recursively finds the order which is optimal for a balanced tree
	recursive_optimiser( 0, API_tree_size - 1 );

	// The order is good, but the connection between the branches broken,
	// because we swapped the API_tree array elements.
	// To fix this problem we have to reinitialise the tree, and use
	// 'add_interpreter_command' function again for all elements.
	for( i = 1; i < API_tree_size; i++ ){

		prev = &API_tree[ 0 ];
		comp_res = strcmp( prev -> name, API_tree[ i ].name );

		(comp_res > 0) ? (next = (prev->left)) : ( next = (prev->right));

		while( next != NULL ){

			prev = next;
			comp_res = strcmp( prev -> name, API_tree[ i ].name );
			(comp_res > 0) ? (next = (prev->left)) : ( next = (prev->right));

		}

		( comp_res > 0 ) ? ( ( prev->left ) = &API_tree[ i ] ) : ( ( prev->right ) = &API_tree[ i ] );

	}

}

// This function is used to order the elements in API_tree array to
// get the fastest search speed
// this function needs 'API_cntr' to be zeroed out before the first call
void Commander::recursive_optimiser( int32_t start_index, int32_t stop_index ){

  int32_t mid;

  // End of recursive algorythm
  if( start_index > stop_index ){

    return;

  }

  // Find the middle of the intervall
  mid = ( start_index + stop_index ) / 2;

  // Put the right element to it's place
  swap_api_elements( elementCounter, mid );
  elementCounter++;

  // Do some recursion for the other intervalls
  recursive_optimiser( start_index, mid - 1 );
  recursive_optimiser( mid + 1, stop_index );


}

void Commander::executeCommand( char *cmd ){

	// The begining of the argument list will be stored in this pointer
	char *arg;

	// This variable tracks the command name length
	uint32_t cmd_name_cntr;

	// If this flag is set, than the description message will be printed,
	// and the commands function won't be called.
	uint8_t show_description = 0;

	API_t *commandData_ptr;

	strncpy( tempBuff, cmd, COMMANDER_MAX_COMMAND_SIZE );


	// tempBuff is the address of the first character of the incoming command.
	// If we give arg variable the value stored in tempBuff means arg will point to
	// the first character of the command as well.
	arg = tempBuff;

	// Reset the name counter before we start counting
	cmd_name_cntr = 0;

	// Find the first space character or a string-end character.
	// At this time count how long is the command name( in characters )
	while( ( *arg != '\0' ) && ( *arg != ' ' ) && ( *arg != '?' ) ){

		cmd_name_cntr++;
		arg++;

	}

	// If a space character found we have to terminate the string there.
	// It is important because strcmp function will search for string terminator
	// character, and this way we can separate the command name from its arguments.
	// This method has a downside. If we pass a const char as command
	// to the execution function it will try to overwrite a character in it.
	// It is impossible if the input string is constant and it will result hard fault!
	// To prevent this we nead a buffer. This is why INTERPRETER_BUFFER_SIZE macro has
	// been created. If you want to pass const chars to your interpreter directly, you
	// have to define INTERPRETER_BUFFER_SIZE with a resonable size.
	// But if you can prove it, that there is no chace in your program to use const chars,
	// you can comment out INTERPRETER_BUFFER_SIZE macro. This can save some space in your RAM.
	if( *arg == ' ' ){

		*arg = '\0';
		arg++;

	}

	// The process is the same as above. The only difference is that this time
	// we have to set the show_description flag.
	else if( *arg == '?' ){

		*arg = '\0';
		arg++;
		show_description = 1;

	}

	// Megnézzük, hogy a parancs létezik-e.
	commandData_ptr = (*this)[ tempBuff ];

	if( commandData_ptr ){

		// Because we have found the command in the API tree we have to choose
		// between description printing and executing.
		// If show_description flag is set, than we have to print the description.
		if( show_description ){

			// Print the description text to the output channel.

			response -> printf( "%s: %s\r\n", commandData_ptr -> name, commandData_ptr -> desc );


		}

		// If show_description flag is not set, than we have to execute the commands function.
		else{

			// Execute commands function.
			(commandData_ptr -> func)( arg, response );

		}

	}

	else{

		// If we went through the whole tree and we did not found the command in it,
		// we have to notice the user abut the problem. Maybe a Type-O
		response -> printf( "Command \'%s\' not found!!!\r\n", tempBuff );

	}

}

void Commander::execute( char *cmd ){

	response = &defaultResponse;
	executeCommand( cmd );

}

void Commander::execute( char *cmd, Serial *resp ){

	serialResponse.select( resp );
	response = &serialResponse;
	executeCommand( cmd );

}

Commander::API_t* Commander::operator [] ( int i ){

	if( i < 0 ){

		return NULL;

	}

	return &API_tree[ i ];

}

Commander::API_t* Commander::operator [] ( char* name ){

	// Stores the next elements address in the tree
	API_t *next;

	// Stores the previous elements address in the tree
	API_t *prev;

	// It will store string compersation result
	int8_t comp_res;

	prev = &API_tree[ 0 ];

	comp_res = strcmp( prev -> name, name );

	(comp_res > 0) ? (next = (prev->left)) : ( next = (prev->right));

	// Go through the binary tree until you find a match, or until you find the
	// end of the tree.
	while( ( comp_res !=0 ) && ( next != NULL ) ){

		prev = next;
		comp_res = strcmp( prev -> name, name );
		(comp_res > 0) ? (next = (prev->left)) : ( next = (prev->right));

	}

	// If comp_res variable has a zero in it, that means in the last iteration
	// we had a match.
	if( comp_res == 0 ){

		return prev;

	}

	return NULL;

}

Commander::API_t* Commander::operator [] ( const char* name ){

	return (*this)[ (char*)name ];

}

