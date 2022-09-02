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

#define COMMANDER_API_VERSION (const char*)"2.0.1"

#include "stdint.h"
#include "string.h"

#include "Commander-Settings.hpp"
#include "Commander-IO.hpp"

/// Like STM32 Class Factory
#ifdef COMMANDER_USE_SERIAL_RESPONSE
#include "Serial.hpp"
#endif

/// Arduino detection
#ifdef ARDUINO
#include "Arduino.h"
#endif

#ifdef COMMANDER_USE_WIFI_CLIENT_RESPONSE
	#ifdef ESP8266
	#include <ESP8266WiFi.h>
	#endif

	#ifdef ESP32
	#include <WiFi.h>
	#endif
#endif

/// This macro simplifies the API element creation.
///
/// With this macro you can fill the API tree structure
/// faster than the traditional {}-way.
#define apiElement( name, desc, func ) { 0, NULL, NULL, (const char*)name, (const char*)desc, func }

/// This macro simplifies the attachment of the API-tree.
///
/// With this macro you can attach the API-tree to the
/// class easier and faster than with attachTreeFunction.
#define attachTree( name ) attachTreeFunction( name, sizeof( name ) / sizeof( name[ 0 ] ) )

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
	  void(*func)( char*, commandResponse *response );  //  Function pointer to the command function

	}API_t;

	/// Attach API-tree to the object.
	///
	/// With this function you can attach the API-tree
	/// structure array to the object. This array contains
	/// the data for each command.
	/// @note There is a macro( attachTree ) to simplify this process.
	void attachTreeFunction(  API_t *API_tree_p, uint32_t API_tree_size_p );

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

	#ifdef COMMANDER_USE_SERIAL_RESPONSE
	/// Execution function for Serial response.
	///
	/// This function tries to execute a command.
	/// It uses the Serial response channel, so
	/// the messages from the command handler
	/// will be passed to the selected Serial
	/// object.
	void execute( char *cmd, Serial *resp );

	/// Execution function for Serial response.
	///
	/// This function tries to execute a command.
	/// It uses the Serial response channel, so
	/// the messages from the command handler
	/// will be passed to the selected Serial
	/// object.
	void execute( const char *cmd, Serial *resp );

	/// Debug channel for Serial.
	///
	/// This function attaches a Serial channel
	/// for debug messages. It also enables
	/// the debug functionality.
	void attachDebugChannel( Serial *resp );
	#endif

	#ifdef COMMANDER_USE_ARDUINO_SERIAL_RESPONSE
	/// Execution function for Arduino Serial response.
	///
	/// This function tries to execute a command.
	/// It uses the HardwareSerial response channel, so
	/// the messages from the command handler
	/// will be passed to the selected Serial
	/// object.
	void execute( char *cmd, HardwareSerial *resp );

	/// Execution function for Arduino Serial response.
	///
	/// This function tries to execute a command.
	/// It uses the HardwareSerial response channel, so
	/// the messages from the command handler
	/// will be passed to the selected Serial
	/// object.
	void execute( const char *cmd, HardwareSerial *resp );

	/// Debug channel for Arduino Serial.
	///
	/// This function attaches a HardwareSerial channel
	/// for debug messages. It also enables
	/// the debug functionality.
	void attachDebugChannel( HardwareSerial *resp );
	#endif

	#ifdef COMMANDER_USE_ARDUINO_32U4_SERIAL_RESPONSE
	/// Execution function for Arduino Serial response.
	///
	/// This function tries to execute a command.
	/// It uses the HardwareSerial response channel, so
	/// the messages from the command handler
	/// will be passed to the selected Serial
	/// object.
	void execute( char *cmd, Serial_ *resp );

	/// Execution function for Arduino Serial response.
	///
	/// This function tries to execute a command.
	/// It uses the HardwareSerial response channel, so
	/// the messages from the command handler
	/// will be passed to the selected Serial
	/// object.
	void execute( const char *cmd, Serial_ *resp );

	/// Debug channel for Arduino Serial.
	///
	/// This function attaches a HardwareSerial channel
	/// for debug messages. It also enables
	/// the debug functionality.
	void attachDebugChannel( Serial_ *resp );
	#endif

	#ifdef COMMANDER_USE_WIFI_CLIENT_RESPONSE
	/// Execution function for WiFi Client response.
	///
	/// This function tries to execute a command.
	/// It uses the WiFi Client response channel, so
	/// the messages from the command handler
	/// will be passed to the selected Serial
	/// object.

	void execute( char *cmd, WiFiClient *resp );
	/// Execution function for WiFi Client response.
	///
	/// This function tries to execute a command.
	/// It uses the WiFi Client response channel, so
	/// the messages from the command handler
	/// will be passed to the selected Serial
	/// object.
	void execute( const char *cmd, WiFiClient *resp );

	/// Debug channel for WiFiClient.
	///
	/// This function attaches a WiFiClient channel
	/// for debug messages. It also enables
	/// the debug functionality.
	void attachDebugChannel( WiFiClient *resp );
	#endif

	/// Enables debug messages.
	void enableDebug();

	/// Disables debug messages.
	void disableDebug();

private:

	/// Starting address of the API-tree.
	API_t *API_tree = NULL;

	/// Number of elements in the API-tree.
	uint32_t API_tree_size = 0;

	/// Internal variable for counting purpose.
	uint32_t elementCounter;

	/// Internal command buffer. The command data
	/// has to be copied to this buffer. It is necessary
	/// because the execute function has to modify the
	/// content of the command.
	char tempBuff[ COMMANDER_MAX_COMMAND_SIZE ];

	/// Default response handler class.
	commandResponse defaultResponse;

	#ifdef COMMANDER_USE_SERIAL_RESPONSE
	/// Serial response handler class.
	commandResponseSerial serialResponse;
	#endif

	#ifdef COMMANDER_USE_ARDUINO_SERIAL_RESPONSE
	/// Serial response handler class.
	commandResponseArduinoSerial arduinoSerialResponse;
	#endif

	#ifdef COMMANDER_USE_ARDUINO_32U4_SERIAL_RESPONSE
	/// Serial response handler class.
	commandResponseArduino32U4Serial arduino32U4SerialResponse;
	#endif

	#ifdef COMMANDER_USE_WIFI_CLIENT_RESPONSE
	/// WiFi Client response handler class.
	commandResponseWiFiClient WiFiClientResponse;
	#endif

	/// Pointer to response class. By default it
	/// points to the default response handler.
	commandResponse *response = &defaultResponse;

	/// Flag to enable or disable debug messages.
	bool debugEnabled = false;

	/// Default response handler for debug messages.
	commandResponse defaultDebugResponse;

	#ifdef COMMANDER_USE_SERIAL_RESPONSE
	/// Serial response handler class.
	commandResponseSerial serialDebugResponse;
	#endif

	#ifdef COMMANDER_USE_ARDUINO_SERIAL_RESPONSE
	/// Serial response handler class.
	commandResponseArduinoSerial arduinoSerialDebugResponse;
	#endif

	#ifdef COMMANDER_USE_WIFI_CLIENT_RESPONSE
	/// WiFi Client response handler class.
	commandResponseWiFiClient WiFiClientDebugResponse;
	#endif

	/// Pointer to response class. By default it
	/// points to the default debug response handler.
	commandResponse *dbgResponse = &defaultDebugResponse;

	/// Find an API element in the tree by alphabetical place.
	uint16_t find_api_index_by_place( uint16_t place );

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
	void executeCommand( char *cmd );

	/// Help function
	///
	/// It prints all the available commands in
	/// alphabetical order. If the description
	/// argument is set to true, it also prints
	/// the description data for all commands.
	void helpFunction( bool description = false );

};



#endif /* COMMANDER_API_SRC_COMMANDER_HPP_ */
