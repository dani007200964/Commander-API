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

	dbgResponse -> print( __CONST_TXT__( "API tree attached with " ) );
	dbgResponse -> print( API_tree_size );
	dbgResponse -> println( __CONST_TXT__( " commands." ) );
}

void Commander::init(){

	// Generic conter variables.
	uint32_t i;
	uint32_t j;

	// Temporary variable, used to flip elements.
	API_t temp;

	commander_strcmp = &Commander::commander_strcmp_regular;
	commander_strcmp_tree_ram = &Commander::commander_strcmp_tree_ram_regular;

	#ifdef __AVR__

	if( API_tree[ 0 ].name == NULL ){

		memoryType = MEMORY_PROGMEM;
		commander_strcmp = &Commander::commander_strcmp_progmem;
		commander_strcmp_tree_ram = &Commander::commander_strcmp_tree_ram_progmem;

	}

	#endif

	dbgResponse -> println( __CONST_TXT__( "Commander init start" ) );

	// Make the tree ordered by alphabet.
	dbgResponse -> print( __CONST_TXT__( "  Creating alphabetical order... " ) );

	// Bubble sort. We need to sort the commands into an alphabetical order.
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

	dbgResponse -> println( __CONST_TXT__( "[ OK ]" ) );

	// Optimize the tree to make it balanced.
	// It is necessary to speed up the command
	// search phase.
	dbgResponse -> print( __CONST_TXT__( "  Create balanced binary structure... " ) );
	optimize_api_tree();

	dbgResponse -> println( __CONST_TXT__( "[ OK ]" ) );
	dbgResponse -> println( __CONST_TXT__( "Commander init finished!" ) );

}

int Commander::find_api_index_by_place( int place ){

	// Generic counter variable
	uint32_t i;

	if( place < 0 ){

		return 0;

	}

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
	int comp_res;

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

bool Commander::enablePipeModuleFunc( char* buffer, int bufferSize, commanderPipeChannel* pipeChannel_p ){

    // If the size of the specified buffer is not equal to the
    // required size, we have to return with error code.
    if( bufferSize != COMMANDER_PIPE_BUFFER_SIZE ){
        return false;
    }

    // If the commanderPipeChannel object is not specified correctly,
    // we have to return with error code.
    if( pipeChannel_p == NULL ){
        return false;
    }

    // Save the parameters to the internal variables.
    pipeArgBuffer = buffer;
    pipeChannel = pipeChannel_p;

    return true;
}

bool Commander::executeCommand( const char *cmd, void* parent ){

	// The beginning of the argument list will be stored in this pointer
	char *arg;

	// This variable tracks the command name length
	uint32_t cmd_name_cntr;

	// If this flag is set, than the description message will be printed,
	// and the commands function won't be called.
	uint8_t show_description = 0;

	// Pointer to the selected command data.
	API_t *commandData_ptr;

	int pipePos;

    bool executionStat;

	int i;

	// Copy the command data to the internal buffer.
	// It is necessary because we have to modify the content
	// of it. If it is points to a const char array we will
	// get a bus-fault error without a buffer.
	strncpy( tempBuff, cmd, COMMANDER_MAX_COMMAND_SIZE );

    // According to the finding in issue #19 this has to be added to make things more safe.
    tempBuff[ sizeof( tempBuff ) - 1 ] = '\0';

    // Try to find a pipe character in the input string.
	pipePos = hasChar( tempBuff, '|', true );

	if( pipePos >= 0 ){

        // Check if piping is requested, but disabled.
        if( pipeArgBuffer == NULL ){
            response -> print( __CONST_TXT__( "The command contains piping but the pipe module is disabled!" ) );
            return false;
        }

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

	// If it is not a NULL pointer, that means we have a match.
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

            // Check if piping is enabled.
            // If so, check if we have any data in the pipe channel.
			if( ( pipeArgBuffer != NULL ) && ( pipeChannel -> available() > 0 ) ){

				i = 0;

                // Copy all the data from the pipe channel to the pipe buffer.
				while( pipeChannel -> available() ){

                    // Check and handle overflow.
					if( i < COMMANDER_MAX_COMMAND_SIZE ){

						pipeArgBuffer[ i ] = pipeChannel -> read();

					}

					else{

						pipeChannel -> read();

					}

					i++;

				}

                // If the data fits in the buffer, terminate after the last valid data.
				if( i < COMMANDER_MAX_COMMAND_SIZE ){

					pipeArgBuffer[ i ] = '\0';

				}

                // Just in case terminate at the end of the pipe buffer.
				pipeArgBuffer[ COMMANDER_MAX_COMMAND_SIZE - 1 ] = '\0';

                // Use the pipe buffer as argument.
				arg = pipeArgBuffer;

			}

            // Check if piping is enabled.
            // Check if we have at least one pipe left.
			if( ( pipeArgBuffer != NULL ) && ( pipePos > 0 ) ){

				// Execute commands function and redirect the output to the pipe channel.
				executionStat = (commandData_ptr -> func)( arg, pipeChannel, parent );
                
                // If the actual command execution was successful, we have to increment the pipeCounter
                if( executionStat ){
                    pipeCounter++;
                }

			}

            // If piping is disabled or we ran out of pipes in the command string,
            // we have to execute the command in the old fashion way.
			else{

				// Execute command function.
				executionStat = (commandData_ptr -> func)( arg, response, parent );

			}

            // Check if we had a problem during execution.
            // If there is a problem, we have to return with error code.
            if( executionStat == false ){

                /*
                response -> print( "pipeCounter: " );
                response -> println( pipeCounter );
                */

                // Check if the piping went wrong.
                int brokenPipePos = hasChar( originalCommandData, '|', pipeCounter, true );

                if( brokenPipePos >= 0 ){

                    // In case of broken pipe, inform the user about the problematic section.
                    if( formatting ){
                        response -> print( __CONST_TXT__( "\033[1;35m" ) );
                    }

                    response -> println( __CONST_TXT__( "\r\nBroken pipe!" ) );

                    if( formatting ){
                        response -> print( __CONST_TXT__( "\033[0;37m" ) );
                    }

                    response -> println( originalCommandData );
                    
                    for( i = 0; i < brokenPipePos; i++ ){
                        response -> print( ' ' );
                    }

                    if( formatting ){
                        response -> print( __CONST_TXT__( "\033[1;31m" ) );
                    }

                    response -> println( "\u25B2" );
                    
                    for( i = 0; i < brokenPipePos; i++ ){
                        response -> print( ' ' );
                    }

                    response -> print( "\u2514 The pipe broke here" );
                    
                    if( formatting ){
                        response -> print( __CONST_TXT__( "\033[0;37m" ) );
                    }

                }

                return false;
            }

            // Check if piping is enabled.
            // Check if we have at least one pipe left.
			if( ( pipeArgBuffer != NULL ) && pipePos > 0 ){

				// To remove whitespace from the new command begin.
				while( tempBuff[ pipePos + 1 ] == ' ' ){
					pipePos++;
				}

                // Execute the next command in the pipe.
				if( executeCommand( &tempBuff[ pipePos + 1 ] ) ){
                    // If the command execution fails, we have to return to break recursion.
                    return false;
                }

			}

		}

	}

	// If it is not an added function, we have to check for internal functions.
	// 'help' is an internal function that prints the available commands in order.
	else if( strcmp( tempBuff, (const char*)"help" ) == 0 ){

		// We have to check for single or described help function.
		if( strcmp( arg, (const char*)"-d" ) == 0 ){

			printHelp( response, true, formatting );

		}

		else{

			printHelp( response, false, formatting );

		}

	}

	else{

		// If we went through the whole tree and we did not found the command in it,
		// we have to notice the user abut the problem. Maybe a Type-O
		response -> print( __CONST_TXT__( "Command \'" ) );
		response -> print( tempBuff );
		response -> print( __CONST_TXT__( "\' not found!" ) );
		
	}
    return true;
}

bool Commander::execute( const char *cmd ){

	// Default execute handler, so the default response will be chosen.
	response = &defaultResponse;

    // Reset the pipe position tracker.
    pipeCounter = 0;

    // Save the address of the original message.
    originalCommandData = cmd;

    // If piping is enabled, we have to flush the pipe channel before command execution.
    if( pipeArgBuffer != NULL ){
        while( pipeChannel -> available() ){
            pipeChannel -> read();
        }
    }

	// Execute the command.
	return( executeCommand( cmd ) );

}

bool Commander::execute( const char *cmd, Stream *resp, void* parent ){

    // Redirect the response to the specified Stream.
	response = resp;

    // Reset the pipe position tracker.
    pipeCounter = 0;

    // Save the address of the original message.
    originalCommandData = cmd;

    // If piping is enabled, we have to flush the pipe channel before command execution.
    if( pipeArgBuffer != NULL ){
        while( pipeChannel -> available() ){
            pipeChannel -> read();
        }
    }

	// Execute the command.
	return( executeCommand( cmd, parent ) );

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

Commander::API_t* Commander::operator [] ( const char* name ){

	// Stores the next elements address in the tree
	API_t *next;

	// Stores the previous elements address in the tree
	API_t *prev;

	// It will store string compersation result
	int comp_res;

	prev = &API_tree[ 0 ];

	comp_res = ( (*this).*(commander_strcmp_tree_ram) )( prev, name );
	
	(comp_res > 0) ? (next = (prev->left)) : ( next = (prev->right));

	// Go through the binary tree until you find a match, or until you find the
	// end of the tree.
	while( ( comp_res !=0 ) && ( next != NULL ) ){

		prev = next;
		comp_res = ( (*this).*(commander_strcmp_tree_ram) )( prev, name );
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

void Commander::printHelp( Stream* out, bool description, bool style ){

	uint32_t i;

	if( style ){
		out -> println( __CONST_TXT__( "\033[1;31m----\033[1;32m Available commands \033[1;31m----\033[0;37m\r\n" ) );
	}
	else{
		out -> println( __CONST_TXT__( "---- Available commands ----\r\n" ) );
	}

	for( i = 0; i < API_tree_size; i++ ){

        if( style ){
            out -> print( __CONST_TXT__( "\033[1;32m" ) );
        }

        if( memoryType == MEMORY_REGULAR ){
            out -> print( API_tree[ find_api_index_by_place( i ) ].name );
        }
        #ifdef __AVR__
        else if( memoryType == MEMORY_PROGMEM ){
            out -> print( API_tree[ find_api_index_by_place( i ) ].name_P );
        }
        #endif

        if( style ){
            out -> print( __CONST_TXT__( "\033[0;37m" ) );
        }

        // If description is not requested, we can skip the rest of this for loop.
        if( !description ){
            continue;
        }

        out -> print( __CONST_TXT__( ": " ) );

        if( memoryType == MEMORY_REGULAR ){
            out -> print( API_tree[ find_api_index_by_place( i ) ].desc );
        }
        #ifdef __AVR__
        else if( memoryType == MEMORY_PROGMEM ){
            out -> print( API_tree[ find_api_index_by_place( i ) ].desc_P );
        }
        #endif

        out -> println();

	}

}

int Commander::hasChar( const char* str, char c, bool ignoreString ){

	int cntr = 0;

	while( str[ cntr ] ){

        // Check if we have to ignore characters inside a string.
        // If so, we have to check if we are in a string.
        if( ignoreString && inString( str, cntr ) ){
            // In this case we can skip to the next character.
            cntr++;
            continue;
        }

        // Check if the current character is the searched one.
		if( str[ cntr ] == c ){
            // If it is, return with its position( index ).
			return cntr;

		}

        // Increment the counter.
		cntr++;

	}

    // If we are here, that means, we did not found the character in the string :(
    // Return with an invalid address.
	return -1;

}

int Commander::hasChar( const char* str, char c, int number, bool ignoreString ){

    // Generic counter.
    int i;

    // It will store the current result.
    int result;

    // It will store te total position.
    int cntr = 0;

    // Try to find the number'th occurrence in the input string.
    for( i = 0; i < number; i++ ){

        result = hasChar( &str[ cntr ], c, ignoreString );

        if( result < 0 ){
            return -1;
        }

        cntr += ( result + 1 );

    }

    return cntr - 1;

}

int Commander::commander_strcmp_regular( API_t* element1, API_t* element2 ){

	return strcmp( element1 -> name, element2 -> name );

}

int Commander::commander_strcmp_tree_ram_regular( API_t* element1, const char* element2 ){

	return strcmp( element1 -> name, element2 );

}

#ifdef __AVR__

int Commander::commander_strcmp_progmem( API_t* element1, API_t* element2 ){

	strncpy_P( progmemBuffer, (	PGM_P ) element1 -> name_P, COMMANDER_MAX_COMMAND_SIZE );
	return strcmp_P( progmemBuffer, (	PGM_P )element2 -> name_P );

}

int Commander::commander_strcmp_tree_ram_progmem( API_t* element1, const char* element2 ){

	return strcmp_P( element2, (PGM_P)element1 -> name_P ) * -1;

}

#endif

void Commander::enableFormatting(){
	formatting = true;
}
void Commander::disableFormatting(){
	formatting = false;
}

void Commander::printArgumentError( Stream* channel_p ){

	// Check and handle invalid channel pointer.
	if( channel_p == NULL ){
		return;
	}

	channel_p -> print( __CONST_TXT__( "Argument error!" ) );

}

Commander::SystemVariable_t* Commander::variables = NULL;
uint32_t Commander::variables_size = 0;

void Commander::attachVariablesFunction( Commander::SystemVariable_t* variables_p, uint32_t variables_size_p ){
	variables = variables_p;
	variables_size = variables_size_p;
}

Commander::SystemVariable_t* Commander::getSystemVariable( const char* name ){

	int i;

	for( i = 0; i < variables_size; i++ ){

		if( strcmp( name, variables[ i ].name ) == 0 ){
			return &variables[ i ];
		}

	}

	return NULL;

}

void Commander::printSystemVariable( Stream* channel_p, const char* name, int decimalPlaces ){

	SystemVariable_t* var;

	if( channel_p == NULL ){
		return;
	}

	var= getSystemVariable( name );

	if( var == NULL ){

		return;

	}

	if( ( var -> floatData ) != NULL ){
        channel_p -> print( *var -> floatData, decimalPlaces );
		return;
	}

	if( ( var -> intData ) != NULL ){
		channel_p -> print( *var -> intData );
		return;
	}

	if( ( var -> strData ) != NULL ){
		channel_p -> print( var -> strData );
		return;
	}

}

void Commander::printSystemVariables( Stream* channel_p ){

	uint32_t i;

	if( channel_p == NULL ){
		return;
	}

	if( ( variables_size == 0 ) || ( variables == NULL ) ){

		channel_p -> print( __CONST_TXT__( "No system variables found!" ) );
		return;

	}

	for( i = 0; i < variables_size; i++ ){

		channel_p -> print( variables[ i ].name );

		if( variables[ i ].floatData != NULL ){
			channel_p -> print( __CONST_TXT__( ": float = " ) );
			channel_p -> println( *variables[ i ].floatData );
		}

		else if( variables[ i ].intData != NULL ){
			channel_p -> print( __CONST_TXT__( ": int = " ) );
			channel_p -> println( *variables[ i ].intData );
		}

		else if( variables[ i ].strData != NULL ){
			channel_p -> print( __CONST_TXT__( ": str = " ) );
			channel_p -> println( variables[ i ].strData );
		}

	}

}

bool Commander::inString( const char* source, int index ){

    // Generic counter.
    int i;

    // It will store the return value.
    bool ret = false;

    // Check if the source is not set correctly.
    if( source == NULL ){
        return false;
    }

    // Check if the index is not set correctly.
    if( index < 0 ){
        return false;
    }

    if( index >= strlen( source ) ){
        return false;
    }

    // Go through every character from the first to the indexed one.
    for( i = 0; i < index; i++ ){

        // Every time we find a string start/end character, which is the " character,
        // we negate the return value.
        if( source[ i ] == '\"' ){
            ret = !ret;
        }

    }

    // Return with the result.
    return ret;
    
}

void Commander::update( char* buffer, int bufferSize, Stream* channel_p ){

    // It will hold the nex incoming character from the channel.
    char c;

    if( bufferSize <=0 ){
        return;
    }

    if( channel_p == NULL ){
        return;
    }

    // Check if there is any data incoming.
    while( channel_p -> available() ){

        // Read the next incoming character.
        c = channel_p -> read();

        // Every command from Serial is terminated with a new-line
        // character. If a new-line character arrives, we have to
        // terminate the string in the commandFromSerial buffer,
        // and execute it. After execution, we have to reset the
        // commandIndex counter to zero.
        if( c == '\r' ){
            buffer[ updateBufferCounter ] = '\0';
            channel_p -> println();
            execute( buffer, channel_p );
            updateBufferCounter = 0;
            channel_p -> print( "\r\n$: " );
        }

        // If we have a carriage-return character we simply
        // ignore it.
        else if( c == '\n' ){
            continue;
        }

        // Handle backspace events.
        else if( ( c == '\b' ) || ( c == 127 ) ){
            if( updateBufferCounter > 0 ){
                updateBufferCounter--;
                channel_p -> print( "\b \b" );
            }
        }

        // Every other case we just put the data to the next
        // free space in the commandFromSerial buffer, increment
        // the commandIndex, and check if it wants to overflow.
        else{
            buffer[ updateBufferCounter ] = c;
            updateBufferCounter++;
            if( updateBufferCounter >= bufferSize ){
                updateBufferCounter = bufferSize - 1;
            }
            else{
                channel_p -> print( c );
            }
        }

    }

}


