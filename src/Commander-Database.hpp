/*
 * Created on Sept 9 2023
 *
 * Copyright (c) 2020 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2023.09.09
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


#ifndef COMMANDER_DATABASE_HPP_
#define COMMANDER_DATABASE_HPP_

#include <stdint.h>
#include "Stream.h"

// Clever solution to handle constant string data.
// Thank you ondras12345!
#ifndef __CONST_TXT__
    #if defined(ARDUINO) && defined(__AVR__)
        #define __CONST_TXT__(s) F(s)
    #else
        #define __CONST_TXT__(s) (const char*)(s)
    #endif
#endif

template< typename T >
class CommanderDatabase{

public:

    typedef enum{
        DEBUG_OFF = 0,
        DEBUG_ERROR = 1,
        DEBUG_DEBUG = 2,
        DEBUG_VERBOSE = 3
    }debugLevel_t;

	struct dataRecord_t{

	  	uint16_t place;                                         ///<  This will store the alphabetical place of the command in the tree
	  	dataRecord_t *left;                              ///<  Left element on a binary tree branch
	  	dataRecord_t *right;                             ///<  Right element on a binary tree branch
	  	const char *name;                                       ///<  Name of the command

        T data;

		#ifdef __AVR__
		__FlashStringHelper *name_P;							///< Name of the command( stored in PROGMEM )
		#endif

	};

    CommanderDatabase();
    CommanderDatabase( dataRecord_t* dataTree_p, uint16_t dataTreeSize_p );
    void attachDebugChannel( Stream* debugChannel_p );
    void setDebugLevel( debugLevel_t debugLevel_p );

    bool init();

	dataRecord_t* operator [] ( int i );

	dataRecord_t* operator [] ( const char* name );

    int findIndexByPlace( int place );

    uint16_t getSize();

private:
	/// Starting address of the API-tree.
	dataRecord_t* dataTree = NULL;

	/// Number of elements in the API-tree.
	uint16_t dataTreeSize = 0;

    Stream* debugChannel = NULL;

    debugLevel_t debugLevel = DEBUG_OFF;

	/// Function pointer to an internal strcmp like function.
	/// It uses the regular version by default.
	int( CommanderDatabase::*strcmpElementElement )( dataRecord_t* element1, dataRecord_t* element2 );

	/// Function pointer to an internal strcmp like function.
	/// It uses the regular version by default.
	int( CommanderDatabase::*strcmpElementCharArray )( dataRecord_t* element1, const char* element2 );

	int strcmpElementElementRegular( dataRecord_t* element1, dataRecord_t* element2 );

	int strcmpElementCharArrayRegular( dataRecord_t* element1, const char* element2 );

    void swapElements( uint16_t index, uint16_t place );

    bool optimizeDataTree();

};

template< typename T >
CommanderDatabase< T >::CommanderDatabase(){

    dataTree = NULL;
    dataTreeSize = 0;
    debugChannel = NULL;
    debugLevel = DEBUG_OFF;

}

template< typename T >
CommanderDatabase< T >::CommanderDatabase( struct dataRecord_t* dataTree_p, uint16_t dataTreeSize_p ){

    dataTree = dataTree_p;
    dataTreeSize = dataTreeSize_p;
    debugChannel = NULL;
    debugLevel = DEBUG_OFF;

}

template< typename T >
void CommanderDatabase< T >::attachDebugChannel( Stream* debugChannel_p ){
    debugChannel = debugChannel_p;
}

template< typename T >
void CommanderDatabase< T >::setDebugLevel( debugLevel_t debugLevel_p ){
    debugLevel = debugLevel_p;
}

template< typename T >
int CommanderDatabase< T >::strcmpElementElementRegular( dataRecord_t* element1, dataRecord_t* element2 ){
	return strcmp( element1 -> name, element2 -> name );
}

template< typename T >
int CommanderDatabase< T >::strcmpElementCharArrayRegular( dataRecord_t* element1, const char* element2 ){
	return strcmp( element1 -> name, element2 );
}

template< typename T >
int CommanderDatabase< T >::findIndexByPlace( int place ){

	// Generic counter variable
	uint16_t i;

	if( place < 0 ){

		return 0;

	}

	// Go through all commands
	for( i = 0; i < dataTreeSize; i++ ){

		// Check that if we found the desired command
		if( dataTree[ i ].place == place ){

			// If we found it, return the index of it.
			return i;

		}

	}

	return 0;

}


template< typename T >
void CommanderDatabase< T >::swapElements( uint16_t index, uint16_t place ){

    // Buffer that will temporary hold an element.
    // This is required for a swap.
    dataRecord_t buffer;

    // This variable will store the address of the element defined by the second argument( place ).
    uint16_t current_index;

    // Find the index in the array by place of the 'i'-th element
    current_index = findIndexByPlace( place );

    // save the context of the 'i'-th element to the buffer
    buffer = dataTree[ index ];

    // write the 'current_index'-th element to the 'i'-th element
    dataTree[ index ] = dataTree[ current_index ];

    // write the buffer to the 'current_index'-th element
    dataTree[ current_index ] = buffer;

}

template< typename T >
bool CommanderDatabase< T >::optimizeDataTree(){

    // Generic counter.
	uint16_t i;

    // Generic counter.
    uint16_t j;

    // This variable will be used to find the
    // depth of the required binary tree.
    uint16_t levelMask;

    // This variable will store how many bits needs
    // to be shifted for the specific levels in the tree.
    uint8_t shiftIndex;

    // This variable will track how many possible leafs are
    // in the current level.
    uint16_t levelElements;

    // The index of the actual element( leaf ) will be calculated
    // to this variable.
    uint16_t elementIndex;

    // This variable tracks how many elements are processed.
    uint16_t elementCounter;

	// Stores the next elements address in the tree
	dataRecord_t *next;

	// Stores the previous elements address in the tree
	dataRecord_t *prev;

	// It will store string comparison result
	int comp_res;

    // Create a mask for the MSB only( in 16-bit domain ).
    levelMask = 0x8000;
    for( i = 0; i < 32; i++ ){

        // Check if we found the firs bit, that is not zero.
        if( ( dataTreeSize & levelMask ) != 0 ){
            break;
        }

        // Shift to right one bit.
        levelMask >>= 1;

    }

    // Set the siftIndex to 1 by default.
    shiftIndex = 1;

    // Find how many bits are used for the tree and
    // store the MSB index to the shiftIndex variable.
    for( i = 0; i < 32; i++ ){

        // Check if we found the firs bit, that is not zero.
        if( ( levelMask & ( (uint16_t)1 << i ) ) != 0 ){
            break;
        }

        shiftIndex++;

    }

    levelElements = 1;
    elementCounter = 0;

    for( i = levelMask; i != 0; i >>= 1 ){

        // i variable will be the actual start index for the current level.
        for( j = 0; j < levelElements; j++ ){

            elementIndex = i | ( j << shiftIndex );
    
            if( ( debugChannel != NULL ) && ( debugLevel == DEBUG_VERBOSE ) ){
                debugChannel -> print( __CONST_TXT__( "  level: " ) );
                debugChannel -> print( i, BIN );
                debugChannel -> print( __CONST_TXT__( " elementIndex: " ) );
                debugChannel -> print( elementIndex );
            }

            if( elementIndex > dataTreeSize ){
                if( ( debugChannel != NULL ) && ( debugLevel == DEBUG_VERBOSE ) ){
                	debugChannel -> println( __CONST_TXT__( " skip" ) );
                }
                continue;
            }

            swapElements( elementCounter, elementIndex );

            // Create the connection for the parent leaf.
            if( elementCounter > 0 ){

                prev = &dataTree[ 0 ];

                comp_res = ( this ->* strcmpElementElement )( prev, &dataTree[ elementCounter ] );

                (comp_res > 0) ? (next = (prev->left)) : ( next = (prev->right));

                while( next != NULL ){

                    prev = next;
                    comp_res = ( this ->* strcmpElementElement )( prev, &dataTree[ elementCounter ] );
                    (comp_res > 0) ? (next = (prev->left)) : ( next = (prev->right));

                }

                if( comp_res > 0 ){
                    prev -> left = &dataTree[ elementCounter ];
                }

                else{
                    prev -> right = &dataTree[ elementCounter ];
                }
                if( ( debugChannel != NULL ) && ( debugLevel == DEBUG_VERBOSE ) ){
                    debugChannel -> print( __CONST_TXT__( " parent: " ) );
                    debugChannel -> println( prev -> place );
                }

                //( comp_res > 0 ) ? ( ( prev->left ) = &API_tree[ elementCounter ] ) : ( ( prev->right ) = &API_tree[ elementCounter ] );

            }

            else if( ( debugChannel != NULL ) && ( debugLevel == DEBUG_VERBOSE ) ){
                debugChannel -> println( __CONST_TXT__(" ROOT") );
            }

            elementCounter++;

        }

        levelElements <<= 1;
        shiftIndex--;

    }

    return true;

}

template< typename T >
bool CommanderDatabase< T >::init(){

	// Generic counter variables.
	uint32_t i;
	uint32_t j;

	// Temporary variable, used to flip elements.
	dataRecord_t temp;

	strcmpElementElement = &CommanderDatabase::strcmpElementElementRegular;
	strcmpElementCharArray = &CommanderDatabase::strcmpElementCharArrayRegular;

    if( ( debugChannel != NULL ) && ( debugLevel >= DEBUG_DEBUG ) ){
        debugChannel -> println( __CONST_TXT__( "Database init start" ) );
        debugChannel -> println( __CONST_TXT__( "Creating alphabetical order..." ) );
    }

	// Simple bubble sort.
    // We need to sort the elements into an alphabetical order.
	for( i = 0; i < dataTreeSize; i++ ){

		for( j = i + 1; j < dataTreeSize; j++ ){

			if( ( this ->* strcmpElementElement )( &dataTree[ i ], &dataTree[ j ] ) > 0 ){

				temp = dataTree[ i ];
				dataTree[ i ] = dataTree[ j ];
				dataTree[ j ] = temp;

			}

		}

	}

	// Fill the place variable in the elements with
	// correct alphabetical place. The place has to
    // be started from index of 1!
	for( i = 0; i < dataTreeSize; i++ ){

		dataTree[ i ].place = i + 1;
        if( ( debugChannel != NULL ) && ( debugLevel == DEBUG_VERBOSE ) ){
            debugChannel -> print( __CONST_TXT__( "  " ) );
            debugChannel -> print( i );
            debugChannel -> print( __CONST_TXT__( ".\tname: " ) );
            // todo AVR support!
            debugChannel -> println( dataTree[ i ].name );
        }

	}

    // Optimize the tree to make it balanced.
	// It is necessary to speed up the command
	// search phase.
    if( ( debugChannel != NULL ) && ( debugLevel >= DEBUG_DEBUG ) ){
        debugChannel -> println( __CONST_TXT__( "Create balanced binary structure... " ) );
    }

	optimizeDataTree();

    return true;
}


template< typename T >
typename CommanderDatabase< T >::dataRecord_t* CommanderDatabase< T >::operator [] ( int i ){

	// Detect wrong addressing.
	if( ( i < 0 ) || ( i >= (int)dataTreeSize ) ){

		return NULL;

	}

	return &dataTree[ i ];

}

template< typename T >
typename CommanderDatabase< T >::dataRecord_t* CommanderDatabase< T >::operator [] ( const char* name ){

	// Stores the next elements address in the tree
	dataRecord_t *next;

	// Stores the previous elements address in the tree
	dataRecord_t *prev;

	// It will store string compersation result
	int comp_res;

	prev = &dataTree[ 0 ];

	comp_res = ( this ->* strcmpElementCharArray )( prev, name );
	
	(comp_res > 0) ? (next = (prev->left)) : ( next = (prev->right));

	// Go through the binary tree until you find a match, or until you find the
	// end of the tree.
	while( ( comp_res !=0 ) && ( next != NULL ) ){

		prev = next;
		comp_res = ( this ->* strcmpElementCharArray )( prev, name );
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
template< typename T >
uint16_t CommanderDatabase< T >::getSize(){
    return dataTreeSize;
}


#endif