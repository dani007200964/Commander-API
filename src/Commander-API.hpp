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

/// Version string
#define COMMANDER_API_VERSION (const char*)"3.0.0"

#include "stdint.h"
#include "string.h"

#include "Commander-Settings.hpp"
#include "Commander-IO.hpp"

#include "Stream.h"

/// Arduino detection
#ifdef ARDUINO
#include "Arduino.h"
#endif

// Clever solution to handle constant string data.
// THank you ondras12345!
#if defined(ARDUINO) && defined(__AVR__)
    #define __CONST_TXT__(s) F(s)
#else
    #define __CONST_TXT__(s) (const char*)(s)
#endif

#ifdef ESP8266
#include <ESP8266WiFi.h>
#endif

#ifdef ESP32
#include <WiFi.h>
#endif

#ifdef __AVR__
#include <avr/pgmspace.h>
#endif

/// This macro simplifies the API element creation.
///
/// With this macro you can fill the API tree structure easily.
/// @param name The name of the command. The best practice is to use a const char array.
/// @param desc The description of the command. The best practice is to use a const char array.
/// @param func This function will be called, when this command gets executed.
#define apiElement( name, desc, func ) { 0, NULL, NULL, (const char*)name, (const char*)desc, func }

#ifdef __AVR__

/// This macro simplifies the API element creation for PROGMEM implementation.
///
/// With this macro you can fill the API tree structure easily.
/// It is used for PROGMEM implementation.
/// @param element One element in the API tree.
/// @param name The name of the command. The best practice is to use a const char array.
/// @param desc The description of the command. The best practice is to use a const char array.
/// @param func_arg This function will be called, when this command gets executed.
#define apiElement_P( element, name, desc, func_arg ) { element.name_P = __CONST_TXT__( name ); element.desc_P = __CONST_TXT__( desc ); element.func = func_arg; }

#endif

/// This macro simplifies the attachment of the API-tree.
///
/// With this macro you can attach the API-tree to the
/// class easier and faster than with attachTreeFunction.
/// @note Please use this macro instead of attachTreeFunction, because it is safer. It always calculates the correct size for the tree.
#define attachTree( name ) attachTreeFunction( name, sizeof( name ) / sizeof( name[ 0 ] ) )

/// This macro simplifies the float type system variable creation.
///
/// With this macro you can fill the system variable table easily.
/// @param name The name of the float variable.
/// @note Do not use & operator before the name. Just use the name, the macro will handle the rest.
#define systemVariableFloat( name ) { #name, &name, NULL, NULL }

/// This macro simplifies the int type system variable creation.
///
/// With this macro you can fill the system variable table easily.
/// @param name The name of the int variable.
/// @note Do not use & operator before the name. Just use the name, the macro will handle the rest.
#define systemVariableInt( name ) { #name, NULL, &name, NULL }

/// This macro simplifies the char* or const char* type system variable creation.
///
/// With this macro you can fill the system variable table easily.
/// @param name The name of the char* or const char* variable.
/// @note Do not use & operator before the name. Just use the name, the macro will handle the rest. Also, no const casting is needed.
#define systemVariableString( name ) { #name, NULL, NULL, (char*)name }

#ifdef __AVR__

/// This macro simplifies the float type system variable creation for PROGMEM implementation.
///
/// With this macro you can fill the system variable table easily.
/// @param element One element in the system variables table.
/// @param name The name of the float variable.
/// @note Do not use & operator before the name. Just use the name, the macro will handle the rest.
#define systemVariableFloat_P( element, name ) { element.name_P = __CONST_TXT__( name ); element.floatData = &name; element.intData = NULL; element.strData = NULL; element.name = NULL; }

/// This macro simplifies the int type system variable creation for PROGMEM implementation.
///
/// With this macro you can fill the system variable table easily.
/// @param element One element in the system variables table.
/// @param name The name of the char* or const char* variable.
/// @note Do not use & operator before the name. Just use the name, the macro will handle the rest. Also, no const casting is needed.
#define systemVariableInt_P( element, name ) { element.name_P = __CONST_TXT__( name ); element.floatData = NULL; element.intData = &name; element.strData = NULL; element.name = NULL; }

/// This macro simplifies the char* or const char* type system variable creation for PROGMEM implementation.
///
/// With this macro you can fill the system variable table easily.
/// @param element One element in the system variables table.
/// @param name The name of the int variable.
/// @note Do not use & operator before the name. Just use the name, the macro will handle the rest.
#define systemVariableInt_P( element, name ) { element.name_P = __CONST_TXT__( name ); element.floatData = NULL; element.intData = NULL; element.strData = (char*)name; element.name = NULL; }

#endif

/// This macro simplifies the attachment of the system variable table.
///
/// With this macro you can attach the system variable table
/// to the class easier and faster than with attachVariablesFunction.
/// @note Please use this macro instead of attachVariablesFunction, because it is safer. It always calculates the correct size for the table.
#define attachVariables( name ) attachVariablesFunction( name, sizeof( name ) / sizeof( name[ 0 ] ) )

#define enablePipeModule( pipeBuffer, pipeChannel ) enablePipeModuleFunc( pipeBuffer, sizeof( pipeBuffer ) / sizeof( pipeBuffer[ 0 ] ), pipeChannel )

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

	/// Structure for command data.
	///
	/// Every command will get a structure like this.
	/// This structure is used to store your commands
	/// in a balanced binary tree.
	typedef struct API_t{

	  	uint16_t place;                                         ///<  This will store the alphabetical place of the command in the tree
	  	struct API_t *left;                                     ///<  Left element on a binary tree branch
	  	struct API_t *right;                                    ///<  Right element on a binary tree branch
	  	const char *name;                                       ///<  Name of the command
	  	const char *desc;                                       ///<  Description of the command

	  	bool(*func)( char*, Stream *response, void* parent );   ///<  Function pointer to the command function

		#ifdef __AVR__
		__FlashStringHelper *name_P;							///< Name of the command( stored in PROGMEM )
		__FlashStringHelper *desc_P;							///< Description of the command( stored in PROGMEM )
		#endif

	}API_t;

    /// Enum for system variable type.
	enum variableType_t{
		VARIABLE_FLOAT,     ///< Used for float data.
		VARIABLE_INT,       ///< Used for int data.
		VARIABLES_STRING    ///< Used for string data.
	};

	/// Structure for system variable data.
    ///
    /// Every system variable get a structure like this.
    /// The structure stores the name of the variable along
    /// with a pointer to its source and the type.
	typedef struct{

	  	const char *name;               ///<  Name of the variable.

		float* floatData;               ///< In case of float type, it will store the address of the actual variable. Otherwise it has to be NULL!
		int* intData;                   ///< In case of int type, it will store the address of the actual variable. Otherwise it has to be NULL!
		char* strData;                  ///< In case of char* type, it will store the address of the actual variable. Otherwise it has to be NULL!

		#ifdef __AVR__
		__FlashStringHelper *name_P;    ///< Name of the variable( stored in PROGMEM )
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
	/// @note There is a macro to simplify this process. Please use the attachTree macro because it is safer!
	void attachTreeFunction( API_t *API_tree_p, uint32_t API_tree_size_p );

	/// Attach system variables list to the object.
	///
	/// With this function you can attach the system
    /// variables list to the object. This array contains
	/// the data for each variable.
	/// @note There is a macro to simplify this process. Please use the attachVariables macro because it is safer!
	static void attachVariablesFunction( SystemVariable_t* variables_p, uint32_t variables_size_p );

    /// Get the instance if a system variable by its name.
    ///
    /// With this function you can get the address of a system variable
    /// structure element by the name if the system variable.
    /// @param name The name of the system variable.
    /// @returns If the variable is found, it will return the address of the control structure. Otherwise it will return NULL.
	static SystemVariable_t* getSystemVariable( const char* name );

    /// Print the value of a system variable.
    ///
    /// This function will print the value of a system variable to a specified Stream.
    /// The variable is accessed by its name.
    /// @param channel_p Pointer to a Stream object. The data will be printed to this Stream.
    /// @param name The name of the system variable.
    /// @param decimalPlaces Optionally, you can specify how many how many decimal places will be needed in case of float data.
	static void printSystemVariable( Stream* channel_p, const char* name, int decimalPlaces = 2 );

    /// Print all the available system variables.
    ///
    /// This function will print all the available system variables to a specified Stream.
    /// The variable name and its value will be printed.
    /// @param channel_p Pointer to a Stream object. The data will be printed to this Stream.
	static void printSystemVariables( Stream* channel_p );

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
    /// @param i Index of an element in the API-tree.
    /// @returns In case of valid index, it will return the address of the element. Otherwise NULL is returned.
	API_t* operator [] ( int i );

	/// Array index operator overload for const char array( string ).
	///
	/// With this function you can get a pointer to an element
	/// from the API-tree by it's name. If the name is not found
	/// the return value will be NULL.
    /// @param name Name of an element in the API-tree.
    /// @returns In case of valid name, it will return the address of the element. Otherwise NULL is returned.
	API_t* operator [] ( const char* name );

	/// Default execution function.
	///
	/// This function tries to execute a command.
	/// It uses the default response channel, so
	/// the messages from the command handler won't
	/// be visible.
    /// @param cmd This is a command string and it will be executed.
	bool execute( const char *cmd );

	/// Execution function for Stream response.
	///
	/// This function tries to execute a command.
	/// It uses the Stream response channel, so
	/// the messages from the command handler
	/// will be passed to the selected Stream
	/// object.
    /// @param cmd This is a command string and it will be executed.
    /// @param resp Pointer to a Stream object. The output data will be printed to this Stream.
    ///             This pointer will be accessible from the function that is assigned to the command.
    /// @param parent This can be a pointer to anything. The reason why it is implemented, is because
    ///               the Shellminator project needed a simple way to communicate with the caller
    ///               terminal from the called command function. It is optional, the default value for it is NULL.
	bool execute( const char *cmd, Stream *resp, void* parent = NULL );

	/// Attach a debug channel to the object.
	///
	/// This function attaches a Serial channel
	/// for debug messages. It also enables
	/// the debug functionality. It can be useful
    /// during the init phase.
    /// @param resp Pointer to a Stream object. The output data will be printed to this Stream.
    /// @note If you call this function the debug messages will be enabled automatically.
	void attachDebugChannel( Stream *resp );

	/// Enables debug messages.
	void enableDebug();

	/// Disables debug messages.
	void disableDebug();

	/// Find an API element in the tree by alphabetical place.
    ///
    /// With this function you can find an element in the API-tree by
    /// its alphabetical place in the tree.
    /// @param place The place of the searched element.
    /// @returns It will return the index of the element if it is found. If the element is not found it will return 0.
    /// @warning It can be only used after the init function finished its job!
	int find_api_index_by_place( int place );

	/// Print the help text to a specified Stream.
	///
	/// It prints all the available commands in
	/// alphabetical order. If the description
	/// argument is set to true, it also prints
	/// the description data for all commands.
	/// @param out Pointer to a Stream object. The output data will be printed to this Stream.
    /// @param description If this flag is set to true, the description data will be printed as well.
    /// @param style If this flag is set to true, the output text will be colorized. It will use VT100
    ///              escape sequences, and because of it, the output data only will be pretty on VT100
    ///              compatible frontends.
	void printHelp( Stream* out, bool description, bool style = false );

	bool enablePipeModuleFunc( char* buffer, int bufferSize, commanderPipeChannel* pipeChannel_p );

	void enableFormatting();
	void disableFormatting();

	/// Print 'Argument error!' to a specified Serial channel.
	///
	/// This is a relatively common message, when arguments are used in a command.
	/// To avoid duplication and save som precious memory, this function is dedicated
	/// to print this message.
	/// @param channel_p Pointer to the Stream object where the message will be printed.
	static void printArgumentError( Stream* channel_p );

    static bool inString( const char* source, int index );

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
	char tempBuff[ COMMANDER_MAX_COMMAND_SIZE + 1 ];

    /// This variable will store the address of the input data.
    /// It is required to track back the original command in case
    /// of an error.
    const char* originalCommandData;

	bool formatting = false;

	#ifdef __AVR__

	/// With the PROGMEM implementation we need to copy the
	/// data from the PROGMEM area to a buffer for compersation.
	char progmemBuffer[ COMMANDER_MAX_COMMAND_SIZE + 1 ];

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
	int commander_strcmp_tree_ram_progmem( API_t* element1, const char* element2 );

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
	int commander_strcmp_tree_ram_regular( API_t* element1, const char* element2 );

	/// Function pointer to an internal strcmp like function.
	/// It uses the regular version by default.
	int( Commander::*commander_strcmp )( API_t* element1, API_t* element2 );

	/// Function pointer to an internal strcmp like function.
	/// It uses the regular version by default.
	int( Commander::*commander_strcmp_tree_ram )( API_t* element1, const char* element2 );

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
	bool executeCommand( const char *cmd, void* parent = NULL );

	/// Search for a character in a string.
	/// @param str Pointer to a character array where the search will be.
	/// @param c This character will be searched in the string.
    /// @param ignoreString If this flag is set to true, the searched character within a string will be ignored.
    ///                     For example if the searched character is 'A' and the input str is 'dog "Apple" Arduino'
    ///                     12 will be returned, which is the start of the Arduino word.
	/// @returns If the character found in the string, the position of the first occurrence will be returned.
    ///          If it can not be found, a negative number will be returned.
	int hasChar( const char* str, char c, bool ignoreString = true );

	/// Search for a character in a string.
	/// @param str Pointer to a character array where the search will be.
	/// @param c This character will be searched in the string.
	/// @param number Which occurrence of c is searched.
    /// @param ignoreString If this flag is set to true, the searched character within a string will be ignored.
    ///                     For example if the searched character is 'A' and the input str is 'dog "Apple" Arduino'
    ///                     12 will be returned, which is the start of the Arduino word.
	/// @returns If the character found in the string in the number'th place, the position of the first occurrence
    ///          will be returned. If it can not be found, a negative number will be returned.
	int hasChar( const char* str, char c, int number, bool ignoreString = true );

	/// Channel for the internal piping.
	commanderPipeChannel* pipeChannel = NULL;

	/// If piping happens the output of the first command will be copied to this buffer.
	/// This way it can be passed to the second command and so on.
    /// @note If this variable points to a valid address, the piping module will be enabled in the executeCommand function.
	char* pipeArgBuffer = NULL;

    int pipeCounter;

};



#endif /* COMMANDER_API_SRC_COMMANDER_HPP_ */
