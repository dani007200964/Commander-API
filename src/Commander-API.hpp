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


#ifndef COMMANDER_API_SRC_COMMANDER_HPP_
#define COMMANDER_API_SRC_COMMANDER_HPP_

#define COMMANDER_API_VERSION (const char*)"2.1.0"

#include "stdint.h"
#include "string.h"

#include "Commander-Settings.hpp"
#include "Commander-IO.hpp"

/// Arduino detection
#ifdef ARDUINO
#include "Arduino.h"
#endif

#ifndef __weak
	#define __weak __attribute__((weak))
#endif

#if defined(ARDUINO) && defined(__AVR__)
#define __CONST_TXT__(s) F(s)
#else
#define __CONST_TXT__(s) (const char*)(s)
#endif

#include "Stream.h"

#ifdef COMMANDER_USE_WIFI_CLIENT_RESPONSE
	#ifdef ESP8266
	#include <ESP8266WiFi.h>
	#endif

	#ifdef ESP32
	#include <WiFi.h>
	#endif
#endif

#ifdef __AVR__
#include <avr/pgmspace.h>
#endif

/// This macro simplifies the API element creation.
///
/// With this macro you can fill the API tree structure easily.
#define apiElement( name, desc, func ) { 0, NULL, NULL, (const char*)name, (const char*)desc, func }

#ifdef __AVR__

/// This macro simplifies the API element creation for PROGMEM implementation.
///
/// With this macro you can fill the API tree structure easily.
/// It is used for PROGMEM implementation.
#define apiElement_P( element, name, desc, func_arg ) { element.name_P = F( name ); element.desc_P = F( desc ); element.func = func_arg; }

#endif

/// This macro simplifies the attachment of the API-tree.
///
/// With this macro you can attach the API-tree to the
/// class easier and faster than with attachTreeFunction.
#define attachTree( name ) attachTreeFunction( name, sizeof( name ) / sizeof( name[ 0 ] ) )



#define systemVariableFloat( name, data ) { name, data, NULL, NULL }
#define systemVariableInt( name, data ) { name, NULL, data, NULL }
#define systemVariableString( name, data ) { name, NULL, NULL, (char*)data }
#define attachVariables( name ) attachVariablesFunction( name, sizeof( name ) / sizeof( name[ 0 ] ) )

/// Commander class.
///
/// This class can be used to create a command parser.
/// Its job is to parse a command from a character
/// array( string ) and find the matching function for
/// that command from a database. This database consists
/// an array of API_t-type elements, and these elements
/// are store the relevant information for that specific
/// command.
class Commander{

public:

	/// Library version string.
	static const char *version;

	/// Structure for command data
	///
	/// Every command will get a structure like this.
	/// This structure is used to store your commands
	/// in a balanced binary tree.
	typedef struct API_t{

	  	uint16_t place;                                   //  This will store the alphabetical place of the command in the tree
	  	struct API_t *left;                               //  Left element on a binary tree branch
	  	struct API_t *right;                              //  Right element on a binary tree branch
	  	const char *name;                                 //  Name of the command
	  	const char *desc;                                 //  Description of the command

	  	void(*func)( char*, Stream *response, void* parent );  					//  Function pointer to the command function

		#ifdef __AVR__
		__FlashStringHelper *name_P;											// Name of the command( stored in PROGMEM )
		__FlashStringHelper *desc_P;											// Description of the command( stored in PROGMEM )
		#endif

	}API_t;

	enum variableType_t{
		VARIABLE_FLOAT,
		VARIABLE_INT,
		VARIABLES_STRING
	};

	typedef struct{

	  	const char *name;                                 //  Name of the command

		float* floatData;
		int* intData;
		char* strData;

		#ifdef __AVR__
		__FlashStringHelper *name_P;											// Name of the command( stored in PROGMEM )
		__FlashStringHelper *desc_P;											// Description of the command( stored in PROGMEM )
		#endif


	}SystemVariable_t;

	enum memoryType_t{
		MEMORY_REGULAR,		///< Regular memory implementation
		MEMORY_PROGMEM		///< Progmem memory implementation
	};

	/// Flag for memory type.
	memoryType_t memoryType = MEMORY_REGULAR;

	/// Attach API-tree to the object.
	///
	/// With this function you can attach the API-tree
	/// structure array to the object. This array contains
	/// the data for each command.
	/// @note There is a macro( attachTree ) to simplify this process.
	void attachTreeFunction( API_t *API_tree_p, uint32_t API_tree_size_p );

	static void attachVariablesFunction( SystemVariable_t* variables_p, uint32_t variables_size_p );
	static SystemVariable_t* getSystemVariable( const char* name );
	static void printSystemVariable( Stream* channel_p, const char* name );

	/// Initializer.
	///
	/// This function initializes the object and its internal parts.
	/// Firstly it makes the API-tree alphabetically ordered, then
	/// creates a balanced binary tree from it. It is necessary to
	/// speed up the search process.
	void init();

	/// Array index operator overload for int type.
	///
	/// With this function you can get a pointer to an element
	/// from the API-tree by it's index. If the index is invalid,
	/// the return value will be NULL.
	API_t* operator [] ( int i );

	/// Array index operator overload for char array( string ).
	///
	/// With this function you can get a pointer to an element
	/// from the API-tree by it's name. If the name is not found
	/// the return value will be NULL.
	API_t* operator [] ( char* name );

	/// Array index operator overload for const char array( string ).
	///
	/// With this function you can get a pointer to an element
	/// from the API-tree by it's name. If the name is not found
	/// the return value will be NULL.
	API_t* operator [] ( const char* name );

	/// Default execution function.
	///
	/// This function tries to execute a command.
	/// It uses the default response channel, so
	/// the messages from the command handler wont
	/// be visible.
	void execute( char *cmd );

	/// Default execution function.
	///
	/// This function tries to execute a command.
	/// It uses the default response channel, so
	/// the messages from the command handler wont
	/// be visible.
	void execute( const char *cmd );

	/// Execution function for Stream response.
	///
	/// This function tries to execute a command.
	/// It uses the Stream response channel, so
	/// the messages from the command handler
	/// will be passed to the selected Stream
	/// object.
	void execute( char *cmd, Stream *resp );

	/// Execution function for Stream response.
	///
	/// This function tries to execute a command.
	/// It uses the Stream response channel, so
	/// the messages from the command handler
	/// will be passed to the selected Stream
	/// object.
	void execute( const char *cmd, Stream *resp );

	void execute( char *cmd, Stream *resp, void* parent );
	void execute( const char *cmd, Stream *resp, void* parent );

	/// Debug channel for Stream.
	///
	/// This function attaches a Serial channel
	/// for debug messages. It also enables
	/// the debug functionality.
	void attachDebugChannel( Stream *resp );

	/// Enables debug messages.
	void enableDebug();

	/// Disables debug messages.
	void disableDebug();

	/// Find an API element in the tree by alphabetical place.
	int find_api_index_by_place( int place );

	/// Help function
	///
	/// It prints all the available commands in
	/// alphabetical order. If the description
	/// argument is set to true, it also prints
	/// the description data for all commands.
	/// todo Finish description.
	void printHelp( bool description = false );

	/// Help function
	///
	/// It prints all the available commands in
	/// alphabetical order. If the description
	/// argument is set to true, it also prints
	/// the description data for all commands.
	/// todo Finish description.
	void printHelp( Stream* out, bool description, bool style = false );

	bool enablePipeModule();

	void enableFormatting();
	void disableFormatting();

	/// Print 'Argument error!' to a specified Serial channel.
	///
	/// This is a relatively common message, when arguments are used in a command.
	/// To avoid duplication and save som precious memory, this function is dedicated
	/// to print this message.
	/// @param channel_p Pointer to the Stream object where the message will be printed.
	static void printArgumentError( Stream* channel_p );

private:

	/// Starting address of the API-tree.
	API_t *API_tree = NULL;

	/// Number of elements in the API-tree.
	uint32_t API_tree_size = 0;

	static SystemVariable_t *variables;
	static uint32_t variables_size;

	/// Internal variable for counting purpose.
	uint32_t elementCounter;

	/// Internal command buffer. The command data
	/// has to be copied to this buffer. It is necessary
	/// because the execute function has to modify the
	/// content of the command.
	char tempBuff[ COMMANDER_MAX_COMMAND_SIZE ];

	bool formatting = false;

	#ifdef __AVR__

	/// With the PROGMEM implementation we need to copy the
	/// data from the PROGMEM area to a buffer for compersation.
	char progmemBuffer[ COMMANDER_MAX_COMMAND_SIZE ];

	/// Compare two API-tree element's name.
	///
	/// It compares two API-tree element's name like a regular strcmp.
	/// It compares the names stored in the name_P
	/// variable. This names are stored in PROGMEM space.
	/// @param element1 Pointer to an API-tree element.
	/// @param element2 Pointer to an API-tree element.
	/// @returns Returns an int value indicating the [relationship](https://cplusplus.com/reference/cstring/strcmp/) between the strings.
	int commander_strcmp_progmem( API_t* element1, API_t* element2 );

	/// Compare an API-tree element's name with a regular string.
	///
	/// It compares an API-tree element's name with a regular string like a regular strcmp.
	/// @param element1 Pointer to an API-tree element.
	/// @param element2 Character array.
	/// @returns Returns an int value indicating the [relationship](https://cplusplus.com/reference/cstring/strcmp/) between the strings.
	int commander_strcmp_tree_ram_progmem( API_t* element1, char* element2 );

	#endif

	/// Compare two API-tree element's name.
	///
	/// It compares two API-tree element's name like a regular strcmp.
	/// variable. This names are stored in PROGMEM space.
	/// @param element1 Pointer to an API-tree element.
	/// @param element2 Pointer to an API-tree element.
	/// @returns Returns an int value indicating the [relationship](https://cplusplus.com/reference/cstring/strcmp/) between the strings.
	int commander_strcmp_regular( API_t* element1, API_t* element2 );

	/// Compare an API-tree element's name with a regular string.
	///
	/// It compares an API-tree element's name with a regular string like a regular strcmp.
	/// @param element1 Pointer to an API-tree element.
	/// @param element2 Character array.
	/// @returns Returns an int value indicating the [relationship](https://cplusplus.com/reference/cstring/strcmp/) between the strings.
	int commander_strcmp_tree_ram_regular( API_t* element1, char* element2 );

	/// Function pointer to an internal strcmp like function.
	/// It uses the regular version by default.
	int( Commander::*commander_strcmp )( API_t* element1, API_t* element2 );

	/// Function pointer to an internal strcmp like function.
	/// It uses the regular version by default.
	int( Commander::*commander_strcmp_tree_ram )( API_t* element1, char* element2 );

	/// Default response handler class.
	commandResponse defaultResponse;

	/// Pointer to response class. By default it
	/// points to the default response handler.
	Stream *response = &defaultResponse;

	/// Flag to enable or disable debug messages.
	bool debugEnabled = false;

	/// Default response handler for debug messages.
	commandResponse defaultDebugResponse;

	/// Pointer to response class. By default it
	/// points to the default debug response handler.
	Stream *dbgResponse = &defaultDebugResponse;

	/// Swap two API elements in the tree.
	void swap_api_elements( uint16_t index, uint16_t place );

	/// Optimizes the tree to make it balanced.
	void optimize_api_tree();

	/// Recursive function optimize a section in the tree.
	///
	/// It is used by optimize_api_tree function. The elementCounter
	/// has to be 0 before using this function. This function just
	/// creates an order for the balanced tree, but does not create
	/// the links between the elements.
	void recursive_optimizer( int32_t start_index, int32_t stop_index );

	/// Command execution.
	///
	/// This function executes a command. Before calling this
	/// function, the response pointer and it's channel has to
	/// be configured correctly.
	void executeCommand( char *cmd, void* parent = NULL );

	/// Search for a character in a string.
	/// @param str Pointer to a character array where the search will be.
	/// @param c This character will be searched in the string.
	/// @returns If the character found in the string, the poisition of the first occurance will be returned.
	int32_t hasChar( char* str, char c );

	#ifdef COMMANDER_ENABLE_PIPE_MODULE

	/// Channel for the internal piping.
	commanderPipeChannel pipeChannel;

	/// If piping happenes the output of the first command will be copied to this buffer.
	/// This way it can be passed to the second command and so on.
	char pipeArgBuffer[ COMMANDER_MAX_COMMAND_SIZE ];

	#endif

};



#endif /* COMMANDER_API_SRC_COMMANDER_HPP_ */
