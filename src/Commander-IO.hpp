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

#ifdef COMMANDER_USE_SERIAL_RESPONSE
#include "Serial.hpp"
#endif

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
class commandResponse{

public:
	virtual int    available()                               	{ return 0;  }
	virtual int    read()                                    	{ return -1; }
	virtual int    peek()                                    	{ return 0;  }
	virtual size_t readBytes( uint8_t *buff, uint32_t size ) 	{ return 0;  }
	virtual void   flush()                                   	{ return;    }
	virtual size_t write( uint8_t b )                        	{ return 0;  }

	virtual size_t print( char c )                           	{ return 0;  }
	virtual size_t print( char *str )                        	{ return 0;  }
	virtual size_t print( const char *str )                  	{ return 0;  }

	virtual size_t print( int8_t b )							{ return 0;  }
	virtual size_t print( uint8_t b )							{ return 0;  }
	virtual size_t print( int16_t b )							{ return 0;  }
	virtual size_t print( uint16_t b )							{ return 0;  }
	virtual size_t print( int32_t b )							{ return 0;  }
	virtual size_t print( uint32_t b )							{ return 0;  }
	virtual size_t print( float f )								{ return 0;  }
	virtual size_t print( double f )							{ return 0;  }

	virtual size_t println()                           			{ return 0;  }
	virtual size_t println( char c )                           	{ return 0;  }
	virtual size_t println( char *str )                        	{ return 0;  }
	virtual size_t println( const char *str )                  	{ return 0;  }

	virtual size_t println( int8_t b )							{ return 0;  }
	virtual size_t println( uint8_t b )							{ return 0;  }
	virtual size_t println( int16_t b )							{ return 0;  }
	virtual size_t println( uint16_t b )						{ return 0;  }
	virtual size_t println( int32_t b )							{ return 0;  }
	virtual size_t println( uint32_t b )						{ return 0;  }
	virtual size_t println( float f )							{ return 0;  }
	virtual size_t println( double f )							{ return 0;  }

	virtual int    printf( const char *fmt, ... )            	{ return 0; }

};

#ifdef COMMANDER_USE_SERIAL_RESPONSE

/// Serial response subclass.
///
/// This subclass is overrides the communication functions in
/// the commandResponse class to make it work with a Serial
/// like class in STM32 Class Factory.
class commandResponseSerial : public commandResponse{

public:

	void select( Serial *serialPort_p );

	int    available() override;
	int    read() override;
	int    peek() override;
	size_t readBytes( uint8_t *buff, uint32_t size ) override;
	void   flush() override;
	size_t write( uint8_t b ) override;

	size_t print( char c ) override;
	size_t print( char *str ) override;
	size_t print( const char *str ) override;

	size_t print( int8_t b ) override;
	size_t print( uint8_t b ) override;
	size_t print( int16_t b ) override;
	size_t print( uint16_t b ) override;
	size_t print( int32_t b ) override;
	size_t print( uint32_t b ) override;
	size_t print( float f ) override;
	size_t print( double f ) override;

	size_t println() override;
	size_t println( char c ) override;
	size_t println( char *str ) override;
	size_t println( const char *str ) override;

	size_t println( int8_t b ) override;
	size_t println( uint8_t b ) override;
	size_t println( int16_t b ) override;
	size_t println( uint16_t b ) override;
	size_t println( int32_t b ) override;
	size_t println( uint32_t b ) override;
	size_t println( float f ) override;
	size_t println( double f ) override;

	int    printf( const char *fmt, ... ) override;

private:
	Serial *serialPort = NULL;

};

#endif

#ifdef COMMANDER_USE_ARDUINO_SERIAL_RESPONSE

/// Arduino Hardware serial response subclass.
///
/// This subclass is overrides the communication functions in
/// the commandResponse class to make it work with a HardwareSerial
/// like class in Arduino environment.
class commandResponseArduinoSerial : public commandResponse{

public:

	void select( HardwareSerial *serialPort_p );

	int    available() override;
	int    read() override;
	int    peek() override;
	size_t readBytes( uint8_t *buff, uint32_t size ) override;
	void   flush() override;
	size_t write( uint8_t b ) override;
	size_t print( char c ) override;
	size_t print( char *str ) override;
	size_t print( const char *str ) override;

	size_t print( int8_t b ) override;
	size_t print( uint8_t b ) override;
	size_t print( int16_t b ) override;
	size_t print( uint16_t b ) override;
	size_t print( int32_t b ) override;
	size_t print( uint32_t b ) override;
	size_t print( float f ) override;
	size_t print( double f ) override;

	size_t println() override;
	size_t println( char c ) override;
	size_t println( char *str ) override;
	size_t println( const char *str ) override;

	size_t println( int8_t b ) override;
	size_t println( uint8_t b ) override;
	size_t println( int16_t b ) override;
	size_t println( uint16_t b ) override;
	size_t println( int32_t b ) override;
	size_t println( uint32_t b ) override;
	size_t println( float f ) override;
	size_t println( double f ) override;

	int    printf( const char *fmt, ... ) override;

private:
	HardwareSerial *serialPort = NULL;

};

#endif

#ifdef COMMANDER_USE_ARDUINO_32U4_SERIAL_RESPONSE

/// Arduino Serial_ response subclass.
///
/// This subclass is overrides the communication functions in
/// the commandResponse class to make it work with a Serial_
/// like class in Arduino environment. The Serial_ class usually
/// used by Atmega-32U4 boards with hardware USB support.
class commandResponseArduino32U4Serial : public commandResponse{

public:

	void select( Serial_ *serialPort_p );

	int    available() override;
	int    read() override;
	int    peek() override;
	size_t readBytes( uint8_t *buff, uint32_t size ) override;
	void   flush() override;
	size_t write( uint8_t b ) override;
	size_t print( char c ) override;
	size_t print( char *str ) override;
	size_t print( const char *str ) override;

	size_t print( int8_t b ) override;
	size_t print( uint8_t b ) override;
	size_t print( int16_t b ) override;
	size_t print( uint16_t b ) override;
	size_t print( int32_t b ) override;
	size_t print( uint32_t b ) override;
	size_t print( float f ) override;
	size_t print( double f ) override;

	size_t println() override;
	size_t println( char c ) override;
	size_t println( char *str ) override;
	size_t println( const char *str ) override;

	size_t println( int8_t b ) override;
	size_t println( uint8_t b ) override;
	size_t println( int16_t b ) override;
	size_t println( uint16_t b ) override;
	size_t println( int32_t b ) override;
	size_t println( uint32_t b ) override;
	size_t println( float f ) override;
	size_t println( double f ) override;

	int    printf( const char *fmt, ... ) override;

private:
	Serial_ *serialPort = NULL;

};

#endif

#ifdef COMMANDER_USE_WIFI_CLIENT_RESPONSE

/// Arduino Hardware serial response subclass.
///
/// This subclass is overrides the communication functions in
/// the commandResponse class to make it work with a HardwareSerial
/// like class in Arduino environment.
class commandResponseWiFiClient : public commandResponse{

public:

	void select( WiFiClient *client_p );

	int    available() override;
	int    read() override;
	int    peek() override;
	size_t readBytes( uint8_t *buff, uint32_t size ) override;
	void   flush() override;
	size_t write( uint8_t b ) override;
	size_t print( char c ) override;
	size_t print( char *str ) override;
	size_t print( const char *str ) override;

	size_t print( int8_t b ) override;
	size_t print( uint8_t b ) override;
	size_t print( int16_t b ) override;
	size_t print( uint16_t b ) override;
	size_t print( int32_t b ) override;
	size_t print( uint32_t b ) override;
	size_t print( float f ) override;
	size_t print( double f ) override;

	size_t println() override;
	size_t println( char c ) override;
	size_t println( char *str ) override;
	size_t println( const char *str ) override;

	size_t println( int8_t b ) override;
	size_t println( uint8_t b ) override;
	size_t println( int16_t b ) override;
	size_t println( uint16_t b ) override;
	size_t println( int32_t b ) override;
	size_t println( uint32_t b ) override;
	size_t println( float f ) override;
	size_t println( double f ) override;

	int    printf( const char *fmt, ... ) override;

private:
	WiFiClient *client = NULL;

};

#endif





















class commandResponsePipe : public commandResponse{

public:

	int    available() override;
	int    read() override;
	int    peek() override;
	size_t readBytes( uint8_t *buff, uint32_t size ) override;
	void   flush() override;
	size_t write( uint8_t b ) override;
	size_t print( char c ) override;
	size_t print( char *str ) override;
	size_t print( const char *str ) override;

	size_t print( int8_t b ) override;
	size_t print( uint8_t b ) override;
	size_t print( int16_t b ) override;
	size_t print( uint16_t b ) override;
	size_t print( int32_t b ) override;
	size_t print( uint32_t b ) override;
	size_t print( float f ) override;
	size_t print( double f ) override;

	size_t println() override;
	size_t println( char c ) override;
	size_t println( char *str ) override;
	size_t println( const char *str ) override;

	size_t println( int8_t b ) override;
	size_t println( uint8_t b ) override;
	size_t println( int16_t b ) override;
	size_t println( uint16_t b ) override;
	size_t println( int32_t b ) override;
	size_t println( uint32_t b ) override;
	size_t println( float f ) override;
	size_t println( double f ) override;

	int    printf( const char *fmt, ... ) override;

	char* getData();

private:
	char* buffer[ PIPE_BUFFER_LEN ];
	uint32_t buffer_cntr = 0;

};






#endif /* COMMANDER_API_SRC_COMMANDER_IO_HPP_ */
