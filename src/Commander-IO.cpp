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

// Todo: This implementation is horrible, we need a circular buffer!

#include "Commander-IO.hpp"

int commanderPipeChannel::available(){

	if( writePointer == readPointer ){
		return 0;
	}

    return writePointer - readPointer;

}

int commanderPipeChannel::read(){

	int ret;

	if( writePointer == readPointer ){
		return -1;
	}

	else{
		if( readPointer >= COMMANDER_MAX_COMMAND_SIZE ){
			return -1;
		}

		ret = (uint8_t)buffer[ readPointer ];
		readPointer++;

	}

	return ret;

}

/// Flush the channel.
void commanderPipeChannel::flush(){
	// Honestly I don't know what to do.
	// Arduino flush methods are weird.
}

int commanderPipeChannel::peek(){

	if( writePointer == readPointer ){
		return -1;
	}

    return (uint8_t)buffer[ readPointer ];

}

size_t commanderPipeChannel::write( uint8_t data ){

    if( writePointer >= COMMANDER_MAX_COMMAND_SIZE ){
        return 0;
    }

    buffer[ writePointer ] = data;
    writePointer++;

    return 1;

}

size_t commanderPipeChannel::write( const uint8_t *data, size_t size ){

    uint32_t i;

    for( i = 0; i < size; i++ ){

        if( writePointer >= COMMANDER_MAX_COMMAND_SIZE ){
            return i;
        }

        buffer[ writePointer ] = data[ i ];
        writePointer++;

    }

    return size;

}
