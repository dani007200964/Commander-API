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
/// Database class
///
/// This class is designed to create a database for any type of data.
/// Every element has to have a unique name, which is case sensitive.
/// The elements can be accessed by their names.
class CommanderDatabase{

public:

    /// Debug level definitions.
    typedef enum{
        DEBUG_OFF       = 0,    ///< All debug messages will be turned off.
        DEBUG_ERROR     = 1,    ///< Only error messages will be printed.
        DEBUG_DEBUG     = 2,    ///< Some debug data and the error messages will be printed.
        DEBUG_VERBOSE   = 3     ///< All debug messages will be turned on.
    }debugLevel_t;

	/// Data record element.
	struct dataRecord_t{

	  	uint16_t place;                     ///<  This will store the alphabetical place of the element in the tree
	  	dataRecord_t *left;                 ///<  Left element in the binary tree branch
	  	dataRecord_t *right;                ///<  Right element in the binary tree branch
	  	const char *name;                   ///<  Name of the element

        T data;                             ///< Stored data. It comes from the template, so it can be any type of data.

		#ifdef __AVR__
		__FlashStringHelper *name_P;        ///< Name of the element( stored in PROGMEM )
		#endif

	};

    /// Empty constructor.
    CommanderDatabase();

    /// Constructor.
    ///
    /// To construct a working object, this must be used.
    /// @param dataTree_p Pointer to the data array. The element type must be
    ///                   a configured dataRecord_t. For example:
    ///                   `CommanderDatabase<int>::dataRecord_t testData[ 10 ]`
    ///                   will create a data array for integer type with 10 elements.
    /// @param dataTreeSize_p The size of the data array in elements.
    CommanderDatabase( dataRecord_t* dataTree_p, uint16_t dataTreeSize_p );
    
    /// Redirect debug messages.
    ///
    /// You can specify an output stream, where the debug
    /// messages will be printed. By default it is not
    /// specified and no debug messages will be printed.
    /// @param debugChannel_p Pointer to a stream, where the debug messages will be printed.
    /// @note You have to call this function before init, if you need any debug data.
    void attachDebugChannel( Stream* debugChannel_p );

    /// Set the debug level.
    ///
    /// You can set, how detailed debug is needed.
    /// @param debugLevel_p Please check @ref debugLevel_t for more information.
    /// @note You have to specify a Stream for the debug messages with
    ///       @ref attachDebugChannel.
    void setDebugLevel( debugLevel_t debugLevel_p );

    /// Init function.
    ///
    /// This function must be called in the init section of your system.
    /// It will generate a balanced binary tree structure from the data tree.
    /// @returns If anything goes well, it will return true. If something wrong
    ///          happens during the tree generation, it will return false.
    bool init();

    /// Overload for indexing operator
    ///
    /// The indexing operator is overloaded and it can be used
    /// with an integer to get a pointer to the data tree element.
    /// The indexing is protected against wrong addressing.
    /// @param i Index of the element in the tree. If the index is
    ///          incorrect, the returned value will be NULL.
    /// @returns The address of the indexed element.
	dataRecord_t* operator [] ( int i );

    /// Overload for indexing operator
    ///
    /// The indexing operator is overloaded and it can be used
    /// with a string to get a pointer to an element by its
    /// name parameter. If it is not found, NULL will be returned.
    /// @param name The name of the searched element.
    /// @returns The address of the element which has the
    ///          same name as the name parameter.
	dataRecord_t* operator [] ( const char* name );

    /// Find array index by element place.
    ///
    /// This function returns the array index( from 1 to tree size )
    /// of an element by its place variable. It can be handy because the
    /// actual place not represents the real index in the binary tree.
    /// @param place Place of the searched element.
    /// @returns The array index of the element if the place is found.
    ///          If the place is invalid or not found, the returned value
    ///          will be 0 to avoid bad addressing.
    uint16_t findIndexByPlace( uint16_t place );

    /// Get tree size
    ///
    /// You can get the size of the tree wit this function.
    /// @returns The size of the tree in elements.
    uint16_t getSize();

    int completeFragment( const char* fragment, char* buffer, int buffer_size );

private:
	/// Starting address of the API-tree.
	dataRecord_t* dataTree = NULL;

	/// Number of elements in the API-tree.
	uint16_t dataTreeSize = 0;

    /// Pointer to a Stream object, which will be used as debug output.
    Stream* debugChannel = NULL;

    /// Debug level.
    debugLevel_t debugLevel = DEBUG_OFF;

    /// If initialised correctly, it will be true.
    bool initFlag = false;

	/// Function pointer to an internal strcmp like function.
	/// It uses the regular version by default.
	int( CommanderDatabase::*strcmpElementElement )( dataRecord_t* element1, dataRecord_t* element2 );

	/// Function pointer to an internal strcmp like function.
	/// It uses the regular version by default.
	int( CommanderDatabase::*strcmpElementCharArray )( dataRecord_t* element1, const char* element2 );

	/// Function pointer to an internal strcmp like function.
	/// It uses the regular version by default.
	int( CommanderDatabase::*strncmpElementElement )( dataRecord_t* element1, dataRecord_t* element2, size_t num  );

	/// Function pointer to an internal strncmp like function.
	/// It uses the regular version by default.
	int( CommanderDatabase::*strncmpElementCharArray )( dataRecord_t* element1, const char* element2, size_t num );

	int strcmpElementElementRegular( dataRecord_t* element1, dataRecord_t* element2 );

	int strcmpElementCharArrayRegular( dataRecord_t* element1, const char* element2 );

	int strncmpElementElementRegular( dataRecord_t* element1, dataRecord_t* element2, size_t num );

	int strncmpElementCharArrayRegular( dataRecord_t* element1, const char* element2, size_t num );

    void swapElements( uint16_t a, uint16_t b );

    bool optimizeDataTree();

    /// Custom strcmp function.
    ///
    /// It works like the original strcmp, but it terminates
    /// to space character as well.
    int strcmpDB( const char *p1, const char* p2 );

    int strncmpDB( const char *p1, const char* p2, size_t num );

    friend class CommanderDatabaseUT;

};

template< typename T >
CommanderDatabase< T >::CommanderDatabase(){

    dataTree = NULL;
    dataTreeSize = 0;
    debugChannel = NULL;
    debugLevel = DEBUG_OFF;
    initFlag = false;

}

template< typename T >
CommanderDatabase< T >::CommanderDatabase( struct dataRecord_t* dataTree_p, uint16_t dataTreeSize_p ){

    dataTree = dataTree_p;
    dataTreeSize = dataTreeSize_p;
    debugChannel = NULL;
    debugLevel = DEBUG_OFF;
    initFlag = false;

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
	return strcmpDB( element1 -> name, element2 -> name );
}

template< typename T >
int CommanderDatabase< T >::strcmpElementCharArrayRegular( dataRecord_t* element1, const char* element2 ){
	return strcmpDB( element1 -> name, element2 );
}

template< typename T >
int CommanderDatabase< T >::strncmpElementElementRegular( dataRecord_t* element1, dataRecord_t* element2, size_t num ){
	return strncmpDB( element1 -> name, element2 -> name, num );
}

template< typename T >
int CommanderDatabase< T >::strncmpElementCharArrayRegular( dataRecord_t* element1, const char* element2, size_t num ){
	return strncmpDB( element1 -> name, element2, num );
}

template< typename T >
uint16_t CommanderDatabase< T >::findIndexByPlace( uint16_t place ){

	// Generic counter variable
	uint16_t i;

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
void CommanderDatabase< T >::swapElements( uint16_t a, uint16_t b ){

    // Buffer that will temporary hold an element.
    // This is required for a swap.
    dataRecord_t buffer;

    // Protect against overflow.
    if( a >= dataTreeSize ){
        return;
    }

    // Protect against overflow.
    if( b >= dataTreeSize ){
        return;
    }

    buffer = dataTree[ a ];
    dataTree[ a ] = dataTree[ b ];
    dataTree[ b ] = buffer;

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
                debugChannel -> print( __CONST_TXT__( " idx: " ) );
                debugChannel -> print( elementIndex );
            }

            if( elementIndex > dataTreeSize ){
                if( ( debugChannel != NULL ) && ( debugLevel == DEBUG_VERBOSE ) ){
                	debugChannel -> println( __CONST_TXT__( " skip" ) );
                }
                continue;
            }

            swapElements( elementCounter, findIndexByPlace( elementIndex ) );

            // Create the connection for the parent leaf.
            if( elementCounter > 0 ){

                // The first element is the starting node.
                prev = &dataTree[ 0 ];

                // Compare the next leafs name with the new items name.
                comp_res = ( this ->* strcmpElementElement )( prev, &dataTree[ elementCounter ] );

                // Check if we found a match.
                if( comp_res == 0 ){
                    // This is a problem, because each element has to be unique.
                    return false;
                }

                // Otherwise check which leaf will be the next.
                (comp_res > 0) ? (next = (prev->left)) : ( next = (prev->right));

                while( next != NULL ){

                    prev = next;
    
                    // Compare the next leafs name with the new items name.
                    comp_res = ( this ->* strcmpElementElement )( prev, &dataTree[ elementCounter ] );

                    // Check if we found a match.
                    if( comp_res == 0 ){
                        // This is a problem, because each element has to be unique.
                        return false;
                    }

                    // Otherwise check which leaf will be the next.
                    (comp_res > 0) ? (next = (prev->left)) : ( next = (prev->right));

                }

                // Check which side will be used to store the new item.
                if( comp_res > 0 ){
                    prev -> left = &dataTree[ elementCounter ];
                }

                else if( comp_res < 0 ){
                    prev -> right = &dataTree[ elementCounter ];
                }

                // Check if we found a match.
                else{
                    // This is a problem, because each element has to be unique.
                    return false;
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

    bool swapped;
    int compareResult;

	strcmpElementElement = &CommanderDatabase::strcmpElementElementRegular;
	strcmpElementCharArray = &CommanderDatabase::strcmpElementCharArrayRegular;

	strncmpElementElement = &CommanderDatabase::strncmpElementElementRegular;
	strncmpElementCharArray = &CommanderDatabase::strncmpElementCharArrayRegular;

    if( ( debugChannel != NULL ) && ( debugLevel >= DEBUG_DEBUG ) ){
        debugChannel -> println( __CONST_TXT__( "Database init start" ) );
        debugChannel -> println( __CONST_TXT__( "Creating alphabetical order..." ) );
    }

	// Simple bubble sort.
    // We need to sort the elements into an alphabetical order.
	for( i = 0; i < (uint16_t)( dataTreeSize - 1 ); i++ ){
        swapped = false;
		for( j = 0; j < (uint16_t)( dataTreeSize - i - 1 ); j++ ){

            compareResult = ( this ->* strcmpElementElement )( &dataTree[ j ], &dataTree[ j + 1 ] );

            // Every element has to have an unique name.
            if( compareResult == 0 ){
                return false;
            }
            
			if( compareResult < 0 ){

				temp = dataTree[ j ];
				dataTree[ j ] = dataTree[ j + 1 ];
				dataTree[ j + 1 ] = temp;
                swapped = true;

			}

		}

        if( !swapped ){
            break;
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

    if( ( debugChannel != NULL ) && ( debugLevel >= DEBUG_DEBUG ) ){
        debugChannel -> println( __CONST_TXT__( "Prepare leaf connections..." ) );
    }

    // Prepare all leaf connections.
	for( i = 0; i < dataTreeSize; i++ ){
		dataTree[ i ].left = NULL;
		dataTree[ i ].right = NULL;
	}
    
    // Optimize the tree to make it balanced.
	// It is necessary to speed up the command
	// search phase.
    if( ( debugChannel != NULL ) && ( debugLevel >= DEBUG_DEBUG ) ){
        debugChannel -> println( __CONST_TXT__( "Create balanced binary structure... " ) );
    }

    initFlag = optimizeDataTree();

	return initFlag;

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

    if( initFlag == false ){
        return NULL;
    }

    // Thee roo node will be the first element.
	prev = &dataTree[ 0 ];

	comp_res = ( this ->* strcmpElementCharArray )( prev, name );
	
	(comp_res > 0) ? (next = (prev->left)) : ( next = (prev->right));

	// Go through the binary tree until you find a match, or until you find the
	// end of the tree.
	while( ( comp_res != 0 ) && ( next != NULL ) ){

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

template< typename T >
int CommanderDatabase< T >::strcmpDB( const char *p1, const char* p2 ){
    const unsigned char *s1 = (const unsigned char *) p1;
    const unsigned char *s2 = (const unsigned char *) p2;

    unsigned char c1;
    unsigned char c2;

    do{
        c1 = (unsigned char) *s1;
        c2 = (unsigned char) *s2;

        s1++;
        s2++;

        if( ( c1 == ' ' ) || ( c2 == ' ' ) ){
            c1 = '\0';
            c2 = '\0';
        }

        if( c1 == '\0' ){
            return c2 - c1;
        }

    } while( c1 == c2 );

    return c2 - c1;

}

template< typename T >
int CommanderDatabase< T >::strncmpDB( const char *p1, const char* p2, size_t num ){
    const unsigned char *s1 = (const unsigned char *) p1;
    const unsigned char *s2 = (const unsigned char *) p2;

    unsigned char c1;
    unsigned char c2;

    size_t counter = 0;

    do{
        c1 = (unsigned char) *s1;
        c2 = (unsigned char) *s2;

        s1++;
        s2++;

        if( ( c1 == ' ' ) || ( c2 == ' ' ) ){
            c1 = '\0';
            c2 = '\0';
        }

        if( c1 == '\0' ){
            return c2 - c1;
        }

        counter++;
        if( counter >= num ){
            return c2 - c1;
        }

    } while( c1 == c2 );

    return c2 - c1;

}

template< typename T >
int CommanderDatabase< T >::completeFragment( const char* fragment, char* buffer, int buffer_size ){

	// Stores the next elements address in the tree
	dataRecord_t *next;

	// Stores the previous elements address in the tree
	dataRecord_t *prev;

	// It will store string compersation result
	int comp_res;

    int fragment_len;

    if( initFlag == false ){
        return 0;
    }

    if( fragment[ 0 ] == '\0' ){
        return 0;
    }

    fragment_len = strlen( fragment );

    // Thee roo node will be the first element.
	prev = &dataTree[ 0 ];

	comp_res = ( this ->* strncmpElementCharArray )( prev, fragment, fragment_len );
    if( comp_res == 0 ){
        strncpy( buffer, prev -> name, buffer_size );
        return 1;
    }

	comp_res = ( this ->* strcmpElementCharArray )( prev, fragment );
	(comp_res > 0) ? (next = (prev->left)) : ( next = (prev->right));

	// Go through the binary tree until you find a match, or until you find the
	// end of the tree.
	while( ( comp_res != 0 ) && ( next != NULL ) ){

		prev = next;

		comp_res = ( this ->* strncmpElementCharArray )( prev, fragment, fragment_len );
        if( comp_res == 0 ){
            strncpy( buffer, prev -> name, buffer_size );
            return 1;
        }

    	comp_res = ( this ->* strcmpElementCharArray )( prev, fragment );
		(comp_res > 0) ? (next = (prev->left)) : ( next = (prev->right));

	}

	// If comp_res variable has a zero in it, that means in the last iteration
	// we had a match.
	if( comp_res == 0 ){

        strncpy( buffer, prev -> name, buffer_size );
		return 1;

	}

	// If we did not found the command we return NULL.
	return 0;



}



#endif