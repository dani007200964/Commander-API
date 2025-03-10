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

Commander::debugLevel_t Commander::debugLevel = Commander::DEBUG_OFF;

const char Commander::empty_string = '\0';

void Commander::attachTreeFunction( Commander::systemCommand_t* API_tree_p, uint32_t API_tree_size_p ){

	regularCommands = CommanderDatabase<API_t>( API_tree_p, API_tree_size_p );

    if( dbgResponse != NULL ){
        regularCommands.setDebugLevel( (CommanderDatabase<Commander::API_t>::debugLevel_t)debugLevel );
        regularCommands.attachDebugChannel( dbgResponse );
    }

    if( ( dbgResponse != NULL ) && ( debugLevel >= DEBUG_DEBUG ) ){

        dbgResponse -> print( __CONST_TXT__( "API tree attached with " ) );
        dbgResponse -> print( API_tree_size_p );
        dbgResponse -> println( __CONST_TXT__( " commands." ) );

    }

}

bool Commander::init(){
    return regularCommands.init();
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

bool Commander::executeCommand( const char *cmd ){

	// The beginning of the argument list will be stored in this pointer
	char *arg;

	// This variable tracks the command name length
	uint32_t cmd_name_cntr;

	// If this flag is set, than the description message will be printed,
	// and the commands function won't be called.
	uint8_t show_description = 0;

	// Pointer to the selected command data.
	systemCommand_t* commandData_ptr;

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

            //if( caller -> channel != NULL ){
                caller -> println( __CONST_TXT__( "The command contains piping but the pipe module is disabled!" ) );
            //}
            return false;
        }

		// Terminate where pipe is found.
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
	commandData_ptr = regularCommands[ tempBuff ];

	// If it is not a NULL pointer, that means we have a match.
	if( commandData_ptr ){

		// Because we have found the command in the API tree we have to choose
		// between description printing and executing.
		// If show_description flag is set, than we have to print the description.
		if( show_description ){

            #ifdef __AVR__
                caller -> print( commandData_ptr -> name );
                caller -> print( ':' );
                caller -> print( ' ' );
                if( commandData_ptr -> data.desc ){
                    caller -> print( commandData_ptr -> data.desc );
                }
                else if( commandData_ptr -> data.desc_P ){
                    caller -> print( commandData_ptr -> data.desc_P );
                }
                caller -> println();
            #else
                caller -> print( commandData_ptr -> name );
                caller -> print( ':' );
                caller -> print( ' ' );
                caller -> println( commandData_ptr -> data.desc );
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
                Stream* tmp = caller -> getChannel();
                caller -> setChannel( pipeChannel );
				executionStat = ( commandData_ptr -> data.func )( arg, caller );
                caller -> setChannel( tmp );
                
                // If the actual command execution was successful, we have to increment the pipeCounter
                if( executionStat ){
                    pipeCounter++;
                }

			}

            // If piping is disabled or we ran out of pipes in the command string,
            // we have to execute the command in the old fashion way.
			else{

				// Execute command function.
				executionStat = ( commandData_ptr -> data.func )( arg, caller );

			}

            // Check if we had a problem during execution.
            // If there is a problem, we have to return with error code.
            if( executionStat == false ){

                /*
                response -> print( "pipeCounter: " );
                response -> println( pipeCounter );
                */

               /*

                // Check if the piping went wrong.
                brokenPipePos = hasChar( originalCommandData, '|', pipeCounter, true );

                if( brokenPipePos >= 0 ){

                    if( response != NULL ){

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

                }

                */

            	if( pipePos > 0 ){
            		tempBuff[ pipePos ] = '|';
            	}

                printBrokenPipe();

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
				if( !executeCommand( &tempBuff[ pipePos + 1 ] ) ){
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

			printHelp( caller, true, formatting );

		}

		else{

			printHelp( caller, false, formatting );

		}

	}

	else{

        //if( caller -> channel != NULL ){
            if( pipePos > 0 ){
				tempBuff[ pipePos ] = '|';
                printBrokenPipe();
            }
            else if( pipeCounter > 0 ){
                printBrokenPipe();

            }

            // If we went through the whole tree and we did not found the command in it,
            // we have to notice the user abut the problem. Maybe a Type-O
            caller -> print( __CONST_TXT__( "Command \'" ) );
            caller -> print( tempBuff );
            caller -> println( __CONST_TXT__( "\' not found!" ) );

        //}
        return false;
		
	}
    return true;
}

bool Commander::execute( const char *cmd, Stream* channel_p, CommandCaller* caller_p ){

    if( channel_p == NULL ){
        caller = &defaultCommandCaller;
        caller -> clearChannel();
    }

    else{
        if( caller_p == NULL ){
            caller = &defaultCommandCaller;
            caller -> setChannel( channel_p );
        }
        else{
            caller = caller_p;
        }
    }

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

void Commander::attachDebugChannel( Stream *resp ){
	dbgResponse = resp;
}

void Commander::setDebugLevel( Commander::debugLevel_t debugLevel_p ){
    debugLevel = debugLevel_p;
}

void Commander::printHelp( Stream* out, bool description, bool style ){

	uint32_t i;

    if( out == NULL ){
        return;
    }

	if( style ){
		out -> println( __CONST_TXT__( "\033[1;31m----\033[1;32m Available commands \033[1;31m----\033[0;37m\r\n" ) );
	}
	else{
		out -> println( __CONST_TXT__( "---- Available commands ----\r\n" ) );
	}

	for( i = 1; i <= regularCommands.getSize(); i++ ){

        if( style ){
            out -> print( __CONST_TXT__( "\033[1;32m" ) );
        }

        //out -> print( API_tree[ find_api_index_by_place( i ) ].name );
        out -> print( regularCommands[ regularCommands.findIndexByPlace( i ) ] -> name );

        if( style ){
            out -> print( __CONST_TXT__( "\033[0;37m" ) );
        }

        // If description is not requested, we can skip the rest of this for loop.
        if( !description ){
            out -> println();
            continue;
        }

        out -> print( __CONST_TXT__( ": " ) );

        #ifdef __AVR__
            if( regularCommands[ regularCommands.findIndexByPlace( i ) ] -> data.desc ){
                out -> print( regularCommands[ regularCommands.findIndexByPlace( i ) ] -> data.desc );
            }
            else if( regularCommands[ regularCommands.findIndexByPlace( i ) ] -> data.desc_P ){
                out -> print( regularCommands[ regularCommands.findIndexByPlace( i ) ] -> data.desc_P );
            }
        #else
            out -> print( regularCommands[ regularCommands.findIndexByPlace( i ) ] -> data.desc );
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

CommanderDatabase<Commander::systemVariableData_t> Commander::systemVariables = CommanderDatabase<systemVariableData_t>();

void Commander::attachVariablesFunction( systemVariable_t* variables_p, uint32_t variables_size_p ){
	systemVariables = CommanderDatabase<systemVariableData_t>( variables_p, variables_size_p );
    systemVariables.setDebugLevel( (CommanderDatabase<Commander::systemVariableData_t>::debugLevel_t)debugLevel );
    
    // Try to init the variables object.
    if( !systemVariables.init() ){
        systemVariables = CommanderDatabase<systemVariableData_t>();
    }
}

Commander::systemVariable_t* Commander::getSystemVariable( const char* name ){
	return systemVariables[ name ];
}

void Commander::printSystemVariable( Stream* channel_p, const char* name, int decimalPlaces ){

	systemVariable_t* var;

	if( channel_p == NULL ){
		return;
	}

	var = getSystemVariable( name );

	if( var == NULL ){

		return;

	}

    switch( var -> data.type ){
        case VARIABLE_FLOAT:
            channel_p -> print( (float)*( var -> data.data.floatData ), decimalPlaces );
            break;
        case VARIABLE_INT:
            channel_p -> print( (int)*( var -> data.data.intData ) );
            break;
        case VARIABLE_STRING:
            channel_p -> print( (char*)( var -> data.data.strData ) );
            break;
        default:
            channel_p -> print( __CONST_TXT__( "Variable ERROR" ) );
            break;
    }

}

void Commander::printSystemVariables( Stream* channel_p ){

	uint32_t i;
	systemVariable_t* var;

	if( channel_p == NULL ){
		return;
	}

	if( systemVariables.getSize() == 0 ){

		channel_p -> print( __CONST_TXT__( "No system variables found!" ) );
		return;

	}

	for( i = 0; i < systemVariables.getSize(); i++ ){

        var = systemVariables[ i ];

		channel_p -> print( var -> name );

        switch( var -> data.type ){
            case VARIABLE_FLOAT:
    			channel_p -> print( __CONST_TXT__( ": float = " ) );
                channel_p -> println( (float)*( var -> data.data.floatData ) );
                break;
            case VARIABLE_INT:
    			channel_p -> print( __CONST_TXT__( ": int = " ) );
                channel_p -> println( (int)*( var -> data.data.intData ) );
                break;
            case VARIABLE_STRING:
    			channel_p -> print( __CONST_TXT__( ": str = " ) );
                channel_p -> println( (char*)( var -> data.data.strData ) );
                break;
            default:
                channel_p -> println( __CONST_TXT__( ": Variable ERROR" ) );
                break;
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

    if( index >= (int)strlen( source ) ){
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

int Commander::floatToString( float number, char* buffer, int bufferSize ){

    // Used to generate string from float.
    bool negative = false;

    // This variable is used to round the float value correctly.
    float roundVal;

    // This will hold the decimal part of the float number.
    int decimalPart;

    // This will hold the fraction part of the float number.
    int fractionPart;

    // Return status for snprintf;
    int status;

    if( bufferSize < 2 ){
        return -1;
    }

    // Check if the number is negative.
    // If it is, set the negative flag,
    // and make it positive.
    if( number < 0 ){
        negative = true;
        number = -number;
    }

    // Round the result correctly.
    // For example 9.999 with precision of 2 will be printed as 10.00.
    roundVal = 0.5f;
    roundVal /= 100.0;
    number += roundVal;

    // Split the number to decimal and fraction parts
    decimalPart = (int)number;
    fractionPart = (int)( ( number - (float)decimalPart ) * 100.0f );

    // If the number is negative, put a '-' character to the first element
    // of the buffer and increment its position. Also decrement the buffer
    // size, because we used the first position.
    if( negative ){
        buffer[ 0 ] = '-';
        buffer++;
        bufferSize--;
    }
    else{
        status = snprintf( buffer, bufferSize, "%d.%02d", decimalPart, fractionPart );
    }

    // If we had to print a '-' character because a negative number,
    // we had to increment the status, if the status is not 0 or negative.
    if( ( status > 0 ) && negative ){
        status++;
    }

    return status;

}

void Commander::printBrokenPipe(){

    int i;
    int brokenPipePos;

    // Check if the piping went wrong.
    brokenPipePos = hasChar( originalCommandData, '|', pipeCounter + 1, true );

    // Check if the first pipe is broken.
    //if( brokenPipePos < 0 ){
    //    brokenPipePos = hasChar( originalCommandData, '|', true );
    //}

    // Check if the last command was bad.
    //if( ( pipeCounter > 0 ) && ( brokenPipePos < 0 ) ){
    //	brokenPipePos = strlen( originalCommandData );
    //}

    if( brokenPipePos >= 0 ){

        //if( caller -> channel != NULL ){

            // In case of broken pipe, inform the user about the problematic section.
            if( formatting ){
                caller -> print( __CONST_TXT__( "\033[1;35m" ) );
            }

            caller -> println( __CONST_TXT__( "\r\nBroken pipe!" ) );

            if( formatting ){
                caller -> print( __CONST_TXT__( "\033[0;37m" ) );
            }

            caller -> println( originalCommandData );
            
            for( i = 0; i < brokenPipePos; i++ ){
                caller -> print( ' ' );
            }

            if( formatting ){
                caller -> print( __CONST_TXT__( "\033[1;31m" ) );
            }

            caller -> println( "\u25B2" );
            
            for( i = 0; i < brokenPipePos; i++ ){
                caller -> print( ' ' );
            }

            caller -> println( "\u2514 The pipe broke here" );
            
            if( formatting ){
                caller -> print( __CONST_TXT__( "\033[0;37m" ) );
            }

            if( pipeChannel -> available() ){
            	caller -> print( __CONST_TXT__( "Pipe data: " ) );
                while( pipeChannel -> available() ){
                	caller -> print( (char)pipeChannel -> read() );
                }
            	caller -> println();

            }

        //}

    }

}

bool Commander::commandExists( const char* cmd, Commander::systemCommand_t** cmd_ptr ){
	// Pointer to the selected command data.
	systemCommand_t* commandData_ptr;
    commandData_ptr = regularCommands[ cmd ];

    if( commandData_ptr ){
        if( cmd_ptr ){
            *cmd_ptr = commandData_ptr;
        }
        return true;
    }

    return false;
}

const char* Commander::getHint( int index, bool only_remaining_chars ){
    if( lastCommandHint && ( lastHint == NULL ) ){
        if( only_remaining_chars ){
            return lastCommandHint + lastCommandHintOffset;
        }
        return lastCommandHint;
    }

    if( lastHint ){
        return lastHint -> getResult( index, only_remaining_chars );
    }
    return &empty_string;
}

int Commander::generateHint( const char *fraction, char *buffer_p, int buffer_size_p ){

    int char_index;
    int prev_char_index;
    int i;
    int number_of_hints;

	// Pointer to the selected command data.
	systemCommand_t* commandData_ptr;

    lastHint = NULL;
    lastCommandHint = NULL;
    lastCommandHintOffset = 0;

    // Check if we have an empty string.
    if( fraction[ 0 ] == '\0' ){
        return 0;
    }

	// Copy the command data to the internal buffer.
	// It is necessary because we have to modify the content
	// of it. If it is points to a const char array we will
	// get a bus-fault error without a buffer.
	strncpy( tempBuff, fraction, COMMANDER_MAX_COMMAND_SIZE );

    // According to the finding in issue #19 this has to be added to make things more safe.
    tempBuff[ sizeof( tempBuff ) - 1 ] = '\0';

    // Try to find the first space character.
    // If we have at least one space characters, that
    // means, we have a command typed in already.
    char_index = hasChar( tempBuff, ' ' );
    if( char_index >= 0 ){
        tempBuff[ char_index ] = '\0';
        if( !commandExists( tempBuff, &commandData_ptr ) ){
            return 0;
        }

        // If we are here, that means, we found a valid command.
        // Let's try to extract some help to the command.
        // Check if help data is added to the object.
        lastHint = commandData_ptr -> data.help;
        if( lastHint == NULL ){
            return 0;
        }

        // If we have some help, we need to find the second last
        // space character.        

        // Change back the \0 character to the original state.
        tempBuff[ char_index ] = ' ';

        i = char_index;
        while( tempBuff[ i ] ){
            if( tempBuff[ i ] == ' ' ){
                prev_char_index = char_index;
                char_index = i;
            }
            i++;
        }

        // Try to generate a hint from the second last space position. For example 'cat -d '.
        number_of_hints = lastHint -> generateHint( &tempBuff[ prev_char_index ], buffer_p, buffer_size_p );

        // Check if we gat any help. If not, try with the last space character. For example ' cat -d "txt" '.
        if( number_of_hints <= 0 ){
            number_of_hints = lastHint -> generateHint( &tempBuff[ char_index ], buffer_p, buffer_size_p );
        }

        // Check if we gat any help. If not, try to list anything at all.
        if( number_of_hints <= 0 ){
            number_of_hints = lastHint -> generateHint( " ", buffer_p, buffer_size_p );
        }

        return number_of_hints;

    }

    // If we are here, that means, we has a command which is not
    // typed fully.

    lastCommandHintOffset = strlen( tempBuff );
    number_of_hints = regularCommands.completeFragment( tempBuff, buffer_p, buffer_size_p );
    if( number_of_hints > 0 ){
        lastCommandHint = buffer_p;
    }
    return number_of_hints;

}
