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


#ifndef COMMANDER_API_SRC_COMMANDER_IO_HPP_
#define COMMANDER_API_SRC_COMMANDER_IO_HPP_

#include <stdint.h>
#include <stddef.h>

#include "Commander-Settings.hpp"

#include "Stream.h"

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

/// Default response class.
///
/// This base class is responsible to create a communication
/// channel between the function associated with a command
/// and the sender entity. This entity can be anything like
/// Serial, Client...
/// Because every function in this class is virtual, it means
/// that they can be overridden with subclasses. It is useful,
/// because if we make a subclass for every entity that can
/// communicate with Commander, we can automatically pair the
/// right function for that entity. The base class doesn't do
/// much. To make it any use, we have to create a subclass
/// for it like below.
class commandResponse : public Stream{

public:

	/// Available bytes in the channel.
  ///
  /// @returns The available bytes in the channel. Because it is the base class, it returns 0.
  int    available()                               	{ return 0;  }

  /// Read one byte form the channel.
  ///
  /// @returns Read and return one byte form the channel. The byte will be removed from the channel. Because it is the base class, it returns -1.
  int    read()                                    	{ return -1; }

  /// Peek the firtst byte from the channel.
  ///
  /// @returns Read and return one byte form the channel. The byte will NOT be removed from the channel. Because it is the base class, it returns 0.
  int    peek()                                    	{ return 0;  }

  /// Flush the channel.
  void   flush()                                   	{ return;    }

  /// Write one byte to the channel.
  ///
  /// @param b The value that has to be written to the channel.
  /// @returns The number of bytes that has been sucessfully written to the channel. Because it is the base class, it returns 0.
  size_t write( uint8_t b )                        	{ return 0;  }

};

class commanderPipeChannel : public Stream{

public:

  /// Available bytes in the channel.
  ///
  /// @returns The available bytes in the channel.
  int    available() override;

  /// Read one byte form the channel.
  ///
  /// @returns Read and return one byte form the channel. The byte will be removed from the channel.
	int    read() override;

  /// Peek the firtst byte from the channel.
  ///
  /// @returns Read and return one byte form the channel. The byte will NOT be removed from the channel.
	int    peek() override;

  /// Flush the channel.
	void   flush() override;

  /// Write one byte to the channel.
  ///
  /// @param b The value that has to be written to the channel.
  /// @returns The number of bytes that has been sucessfully written to the channel. Because it is the base class, it returns 0.
	size_t write( uint8_t b ) override;

	size_t write( const uint8_t *buffer, size_t size ) override;

private:
	uint8_t buffer[ COMMANDER_MAX_COMMAND_SIZE ];
	uint32_t readPointer = 0;
	uint32_t writePointer = 0;

};


#endif /* COMMANDER_API_SRC_COMMANDER_IO_HPP_ */
