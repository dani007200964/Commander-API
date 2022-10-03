/*
 * Created on June 18 2020
 *
 * Copyright (c) 2020 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2022.02.06
*/

/*
MIT License

Copyright (c) 2020 Daniel Hajnal

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#include "Commander-API.hpp"

const char *Commander::version = COMMANDER_API_VERSION;

void Commander::attachTreeFunction( API_t *API_tree_p, uint32_t API_tree_size_p ){

	// Save parameters to internal variables.
	API_tree      = API_tree_p;
	API_tree_size = API_tree_size_p;

	#if defined( ARDUINO ) && defined( __AVR__ )

	dbgResponse -> print( F( "API tree attached with " ) );
	dbgResponse -> print( API_tree_size );
	dbgResponse -> println( F( " commands." ) );

	#else

	dbgResponse -> print( (const char*)"API tree attached with "  );
	dbgResponse -> print( API_tree_size );
	dbgResponse -> println( " commands." );

	#endif

}

void Commander::init(){

	// Generic conter variables.
	uint32_t i;
	uint32_t  j;

	// Temporary variable, used to flip elements.
	API_t temp;

	#ifdef __AVR__

	if( API_tree[ 0 ].name == NULL ){

		memoryType = MEMORY_PROGMEM;
		commander_strcmp = &Commander::commander_strcmp_progmem;
		commander_strcmp_tree_ram = &Commander::commander_strcmp_tree_ram_progmem;

	}

	#endif

	#if defined( ARDUINO ) && defined( __AVR__ )

	dbgResponse -> println( F( "Commander init start" ) );

	#else

	dbgResponse -> println( (const char*)"Commander init start" );

	#endif

	// Make the tree ordered by alphabet.
	#if defined( ARDUINO ) && defined( __AVR__ )

	dbgResponse -> print( F( "\tCreating alphabetical order... " ) );

	#else

	dbgResponse -> print( (const char*)"\tCreating alphabetical order... " );

	#endif

	for( i = 0; i < API_tree_size; i++ ){

		for( j = i + 1; j < API_tree_size; j++ ){

			if( ( this ->* commander_strcmp )( &API_tree[ i ], &API_tree[ j ] ) > 0 ){

				temp = API_tree[ i ];
				API_tree[ i ] = API_tree[ j ];
				API_tree[ j ] = temp;

			}

		}

	}

	// Fill the place variable in the tree with
	// correct alphabetical place.
	for( i = 0; i < API_tree_size; i++ ){

		API_tree[ i ].place = i;

	}

	#if defined( ARDUINO ) && defined( __AVR__ )

	dbgResponse -> println( F( "[ OK ]" ) );

	#else

	dbgResponse -> println( (const char*)"[ OK ]" );

	#endif


	// Optimize the tree to make it balanced.
	// It is necessary to speed up the command
	// search phase.
	#if defined( ARDUINO ) && defined( __AVR__ )

	dbgResponse -> print( F( "\tCreate balanced binary structure... " ) );

	#else

	dbgResponse -> print( (const char*)"\tCreate balanced binary structure... " );

	#endif
	optimize_api_tree();

	#if defined( ARDUINO ) && defined( __AVR__ )

	dbgResponse -> println( F( "[ OK ]" ) );
	dbgResponse -> println( F( "Commander init finished!" ) );

	#else

	dbgResponse -> println( (const char*)"[ OK ]" );
	dbgResponse -> println( (const char*)"Commander init finished!" );

	#endif

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

	return 0;

}

void Commander::swap_api_elements( uint16_t index, uint16_t place ){

  // Buffer that will temporary hold an element.
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

void Commander::optimize_api_tree(){

	uint32_t i;

	//API_t buffer;

	// Stores the next elements address in the tree
	API_t *next;

	// Stores the previous elements address in the tree
	API_t *prev;

	// It will store string comparison result
	int32_t comp_res;

	// recursive optimizer need to initialize elementCounter to 0
	elementCounter = 0;

	// recursively finds the order which is optimal for a balanced tree
	recursive_optimizer( 0, API_tree_size - 1 );

	// The order is good, but the connection between the branches broken,
	// because we swapped the API_tree array elements.
	// To fix this problem we have to add elements from index 1 and
	// place them in the binary tree.
	for( i = 1; i < API_tree_size; i++ ){

		prev = &API_tree[ 0 ];

		comp_res = ( this ->* commander_strcmp )( prev, &API_tree[ i ] );

		(comp_res > 0) ? (next = (prev->left)) : ( next = (prev->right));

		while( next != NULL ){

			prev = next;
			comp_res = ( this ->* commander_strcmp )( prev, &API_tree[ i ] );
			(comp_res > 0) ? (next = (prev->left)) : ( next = (prev->right));

		}

		( comp_res > 0 ) ? ( ( prev->left ) = &API_tree[ i ] ) : ( ( prev->right ) = &API_tree[ i ] );

	}

}

void Commander::recursive_optimizer( int32_t start_index, int32_t stop_index ){

	// The middle number between start and stop index
	// will be stored in this variable.
	int32_t mid;

	// Detect the end of recursion.
	if( start_index > stop_index ){

		return;

	}

	// Find the middle of the interval
	mid = ( start_index + stop_index ) / 2;

	// Put the right element to it's place
	swap_api_elements( elementCounter, mid );
	elementCounter++;

	// Do some recursion for the other intervals
	recursive_optimizer( start_index, mid - 1 );
	recursive_optimizer( mid + 1, stop_index );


}

void Commander::executeCommand( char *cmd ){

	// The beginning of the argument list will be stored in this pointer
	char *arg;

	// This variable tracks the command name length
	uint32_t cmd_name_cntr;

	// If this flag is set, than the description message will be printed,
	// and the commands function won't be called.
	uint8_t show_description = 0;

	// Pointer to the selected command data.
	API_t *commandData_ptr;

	int32_t pipePos;

	uint32_t i;

	// Copy the command data to the internal buffer.
	// It is necessary because we have to modify the content
	// of it. If it is points to a const char array we will
	// get a bus-fault error without a buffer.
	strncpy( tempBuff, cmd, COMMANDER_MAX_COMMAND_SIZE );

	pipePos = hasChar( tempBuff, '|' );

	if( pipePos >= 0 ){

		// Terminate where pip is found.
		tempBuff[ pipePos ] = '\0';

	}

	// tempBuff is the address of the first character of the incoming command.
	// If we give arg variable the value stored in tempBuff means arg will point to
	// the first character of the command as well.
	arg = tempBuff;

	// Reset the name counter before we start counting
	cmd_name_cntr = 0;

	// Find the first space, question mark or a string-end character.
	// At this time count how long is the command name( in characters )
	while( ( *arg != '\0' ) && ( *arg != ' ' ) && ( *arg != '?' ) ){

		cmd_name_cntr++;
		arg++;

	}

	// If a space character found we have to terminate the string there.
	// It is important because strcmp function will search for string terminator
	// character, and this way we can separate the command name from its arguments.
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

	// Try to find the command datata.
	commandData_ptr = (*this)[ tempBuff ];

	// If it is not a NULL pointer, that means we have a mtach.
	if( commandData_ptr ){

		// Because we have found the command in the API tree we have to choose
		// between description printing and executing.
		// If show_description flag is set, than we have to print the description.
		if( show_description ){

			if( memoryType == MEMORY_REGULAR ){

				// Print the description text to the output channel.
				response -> print( commandData_ptr -> name );
				response -> print( ':' );
				response -> print( ' ' );
				response -> println( commandData_ptr -> desc );

			}

			#ifdef __AVR__

			else if( memoryType == MEMORY_PROGMEM ){

				// Print the description text to the output channel.
				response -> print( commandData_ptr -> name_P );
				response -> print( ':' );
				response -> print( ' ' );
				response -> println( commandData_ptr -> desc_P );

			}

			#endif


		}

		// If show_description flag is not set, than we have to execute the commands function.
		else{

			// TODO if the pipe buffer has data, the arg has to be replaced with that.
			if( pipeChannel.available() > 0 ){

				// pipeChannel.readBytesUntil( '\0', pipeArgBuffer, COMMANDER_MAX_COMMAND_SIZE );

				i = 0;

				while( pipeChannel.available() ){

					if( i < COMMANDER_MAX_COMMAND_SIZE ){

						pipeArgBuffer[ i ] = pipeChannel.read();

					}

					else{

						pipeChannel.read();

					}

					i++;

				}

				if( i < COMMANDER_MAX_COMMAND_SIZE ){

					pipeArgBuffer[ i ] = '\0';

				}

				pipeArgBuffer[ COMMANDER_MAX_COMMAND_SIZE - 1 ] = '\0';

				arg = pipeArgBuffer;

			}

			if( pipePos > 0 ){

				// Execute commands function and redirect the output to pipe.
				(commandData_ptr -> func)( arg, &pipeChannel );

			}

			else{

				(commandData_ptr -> func)( arg, response );

			}

			if( pipePos > 0 ){

				// To remowe whitespace from the new command begin.
				while( tempBuff[ pipePos + 1 ] == ' ' ){
					pipePos++;
				}

				executeCommand( &tempBuff[ pipePos + 1 ] );

			}

		}

	}

	// If it is not an added function, we have to check for internal functions.
	// 'help' is an internal function that prints the available commands in order.
	else if( strcmp( tempBuff, (const char*)"help" ) == 0 ){

		// We have to check for single or described help function.
		if( strcmp( arg, (const char*)"-d" ) == 0 ){

			helpFunction( true );

		}

		else{

			helpFunction();

		}

	}

	else{

		// If we went through the whole tree and we did not found the command in it,
		// we have to notice the user abut the problem. Maybe a Type-O
		#if defined( ARDUINO ) && defined( __AVR__ )

		response -> print( F( "Command \'" ) );
		response -> print( tempBuff );
		response -> println( F( "\' not found!" ) );

		#else

		response -> print( (const char*)"Command \'" );
		response -> print( tempBuff );
		response -> println( (const char*)"\' not found!" );

		#endif

		// Clear the pipe at error.
		while( pipeChannel.available() ){

			pipeChannel.read();

		}

	}

}

void Commander::execute( char *cmd ){

	// Default execute handler, so the default response will be chosen.
	response = &defaultResponse;

	// Execute the command.
	executeCommand( cmd );

}

void Commander::execute( const char *cmd ){

	// Default execute handler, so the default response will be chosen.
	response = &defaultResponse;

	// Execute the command.
	executeCommand( (char*)cmd );

}

void Commander::execute( char *cmd, Stream *resp ){

	response = resp;

	// Execute the command.
	executeCommand( cmd );

}

void Commander::execute( const char *cmd, Stream *resp ){

	response = resp;

	// Execute the command.
	executeCommand( (char*)cmd );

}

void Commander::attachDebugChannel( Stream *resp ){

	dbgResponse = resp;

	// Enable debug messages.
	debugEnabled = true;

}

void Commander::enableDebug(){

	debugEnabled = true;

}

void Commander::disableDebug(){

	debugEnabled = false;

}

Commander::API_t* Commander::operator [] ( int i ){

	// Detect wrong addressing.
	if( ( i < 0 ) || ( i >= (int)API_tree_size ) ){

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

	comp_res = ( this ->* commander_strcmp_tree_ram )( prev, name );

	(comp_res > 0) ? (next = (prev->left)) : ( next = (prev->right));

	// Go through the binary tree until you find a match, or until you find the
	// end of the tree.
	while( ( comp_res !=0 ) && ( next != NULL ) ){

		prev = next;
		comp_res = ( this ->* commander_strcmp_tree_ram )( prev, name );
		(comp_res > 0) ? (next = (prev->left)) : ( next = (prev->right));

	}

	// If comp_res variable has a zero in it, that means in the last iteration
	// we had a match.
	if( comp_res == 0 ){

		return prev;

	}

	// If we did not found the command we return NULL.
	return NULL;

}

Commander::API_t* Commander::operator [] ( const char* name ){

	return (*this)[ (char*)name ];

}

void Commander::helpFunction( bool description ){

	helpFunction( description, response );

}

void Commander::helpFunction( bool description, Stream* out, bool style ){

	uint32_t i;
	uint32_t j;

	if( style ){

		#if defined( ARDUINO ) && defined( __AVR__ )

		out -> println( F( "\033[1;31m----\033[1;32m Available commands \033[1;31m----\033[0;37m\r\n" ) );

		#else

		out -> println( (const char*)"\033[1;31m----\033[1;32m Available commands \033[1;31m----\033[0;37m\r\n" );

		#endif

	}

	else{

		#if defined( ARDUINO ) && defined( __AVR__ )

		out -> println( F( "---- Available commands ----\r\n" ) );

		#else

		out -> println( (const char*)"---- Available commands ----\r\n" );

		#endif

	}

	for( i = 0; i < API_tree_size; i++ ){

		for( j = 0; j < API_tree_size; j++ ){

			if( API_tree[ j ].place == i ){

				// Check if the description is required to print.
				if( description ){

					// Check if style is enabled.
					if( style ){

						if( memoryType == MEMORY_REGULAR ){

							out -> print( (const char*)"\033[1;32m" );
							out -> print( API_tree[ j ].name );
							out -> print( (const char*)"\033[0;37m" );
							out -> print( ':' );
							out -> print( ' ' );
							out -> print( API_tree[ j ].desc );
							out -> println();

						}

						#ifdef __AVR__

						else if( memoryType == MEMORY_PROGMEM ){

							out -> print( F( "\033[1;32m" ) );
							out -> print( API_tree[ j ].name_P );
							out -> print( F( "\033[0;37m" ) );
							out -> print( ':' );
							out -> print( ' ' );
							out -> print( API_tree[ j ].desc_P );
							out -> println();
							out -> println();

						}

						#endif

					}

					else{

						if( memoryType == MEMORY_REGULAR ){

							out -> print( API_tree[ j ].name );
							out -> println( ':' );
							out -> print( '\t' );
							out -> print( API_tree[ j ].desc );
							out -> println();
							out -> println();

						}

						#ifdef __AVR__

						else if( memoryType == MEMORY_PROGMEM ){

							out -> print( API_tree[ j ].name_P );
							out -> println( ':' );
							out -> print( '\t' );
							out -> print( API_tree[ j ].desc_P );
							out -> println();
							out -> println();

						}

						#endif

					}

				}

				else{

					if( memoryType == MEMORY_REGULAR ){

						out -> println( API_tree[ j ].name );

					}

					#ifdef __AVR__

					else if( memoryType == MEMORY_PROGMEM ){

						out -> println( API_tree[ j ].name_P );

					}

					#endif

				}

				continue;

			}

		}

	}

}

int32_t Commander::hasChar( char* str, char c ){

	int32_t cntr = 0;

	while( str[ cntr ] ){

		if( str[ cntr ] == c ){

			return cntr;

		}

		cntr++;

	}

	return -1;

}

void Commander::printHelp( Stream* out ){

	helpFunction( true, out, true );

}

int Commander::commander_strcmp_regular( API_t* element1, API_t* element2 ){

	return strcmp( element1 -> name, element2 -> name );

}

int Commander::commander_strcmp_tree_ram_regular( API_t* element1, char* element2 ){

	return strcmp( element1 -> name, element2 );

}

#ifdef __AVR__

int Commander::commander_strcmp_progmem( API_t* element1, API_t* element2 ){

	strncpy_P( progmemBuffer, (	PGM_P ) element1 -> name_P, COMMANDER_MAX_COMMAND_SIZE );
	return strcmp_P( progmemBuffer, (	PGM_P )element2 -> name_P );

}

int Commander::commander_strcmp_tree_ram_progmem( API_t* element1, char* element2 ){

	return strcmp_P( element2, (PGM_P)element1 -> name_P ) * -1;

}

#endif
