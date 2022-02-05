/*
 * commander.hpp
 *
 *  Created on: Feb 5, 2022
 *      Author: dani0
 */

#ifndef COMMANDER_API_SRC_COMMANDER_HPP_
#define COMMANDER_API_SRC_COMMANDER_HPP_

#include "stdint.h"
#include "Serial.hpp"

#include "commander_io.hpp"

#define COMMANDER_MAX_COMMAND_SIZE 30

/// This macro simplifies the API element creation.
///
/// With this macro you can fill the API tree structure
/// faster than the traditional {}-way.
#define apiElement( name, desc, func ) { 0, NULL, NULL, name, desc, func }

/// This macro simplifies the attachment of the API-tree.
///
/// With this macro you can attach the API-tree to the
/// class easier and faster than with attachTreeFunction.
#define attachTree( name ) attachTreeFunction( name, sizeof( name ) / sizeof( name[ 0 ] ) )

class Commander{

public:

	/// Structure for command data
	///
	/// Every command will get a structure like this.
	/// This structure is used to store your commands
	/// in a balanced binary tree.
	typedef struct API_t{

	  uint16_t place;           //  This will store the alphabetical place of the command in the tree
	  struct API_t *left;       //  Left element on a binatry tree branch
	  struct API_t *right;      //  Right element on a binary tree branch
	  const char *name;         //  Name of the command
	  const char *desc;         //  Description of the command
	  void(*func)( char*, commandResponse *response ); //  Function pointer to the command function

	}API_t;

	/// Attach API-tree to the object.
	///
	/// With this function you can attach the API-tree
	/// structure array to the object. This array contains
	/// the data for each command.
	/// @note There is a macro( attachTree ) to simplify this process.
	void attachTreeFunction(  API_t *API_tree_p, uint32_t API_tree_size_p );

	/// Attach debug output to the object.
	void attachDebugPort( Serial *debugPort_p );

	void init();

	void execute( char *cmd );

	void execute( char *cmd, Serial *resp );

	API_t* operator [] ( int i );

	API_t* operator [] ( char* name );

	API_t* operator [] ( const char* name );


private:

	API_t *API_tree = NULL;
	uint32_t API_tree_size = 0;

	Serial *debugPort = NULL;

	uint32_t elementCounter;

	char tempBuff[ COMMANDER_MAX_COMMAND_SIZE ];

	commandResponse defaultResponse;
	commandResponseSerial serialResponse;

	commandResponse *response = &defaultResponse;

	uint16_t find_api_index_by_place( uint16_t place );

	void swap_api_elements( uint16_t index, uint16_t place );

	void optimise_api_tree();

	void recursive_optimiser( int32_t start_index, int32_t stop_index );

	void executeCommand( char *cmd );

};


#endif /* COMMANDER_API_SRC_COMMANDER_HPP_ */
