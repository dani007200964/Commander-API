/*
 * Created on June 25 2022
 *
 * Copyright (c) 2020 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2022.06.25
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

#include "Commander-Utils.hpp"

void apiTreeDumpFunction( Commander::API_t* tree, int treeSize, Stream* out ){

	int i;
	int j;

	if( out == NULL ){

		return;

	}

    if( treeSize < 0 ){

		out -> println( "Invalid API-tree size!" );
		return;

    }

	if( tree == NULL ){

		out -> println( "Invalid API-tree address!" );
		return;

	}

	for( i = 0; i < treeSize; i++ ){

		out -> print( i );
		out->println( " -> element:" );
		out->print( "\tname: " );
		out->println( tree[ i ].name );
		out->print( "\tdesc: " );
		out->println( tree[ i ].desc );
		out->print( "\tplace: " );
		out->println( tree[ i ].place );
		out->print( "\tleft: " );

		if( tree[ i ].left == NULL ){
			
			out->println( "NULL" );

		}

		else{

			for( j = 0; j < treeSize; j++ ){

				if( &tree[ j ] == tree[ i ].left ){

					out->println( tree[ j ].name );
					break;

				}

			}

		}

		out->print( "\tright: " );

		if( tree[ i ].right == NULL ){
			
			out -> println( "NULL" );

		}

		else{

			for( j = 0; j < treeSize; j++ ){

				if( &tree[ j ] == tree[ i ].right ){

					out -> println( tree[ j ].name );
					break;

				}

			}

		}
		out -> println();

	}

}
