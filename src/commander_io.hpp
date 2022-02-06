/*
 * Created on June 18 2020
 *
 * Copyright (c) 2020 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2022.02.06
*/

#ifndef COMMANDER_API_SRC_COMMANDER_IO_HPP_
#define COMMANDER_API_SRC_COMMANDER_IO_HPP_

#include <stdint.h>
#include <stddef.h>

#include "commander_settings.hpp"

#ifdef COMMANDER_USE_SERIAL_RESPONSE
#include "Serial.hpp"
#endif

#ifdef ARDUINO
#include "Arduino.h"
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
	virtual int    available()                               { return 0; }
	virtual int    read()                                    { return -1; }
	virtual int    peek()                                    { return 0; }
	virtual size_t readBytes( uint8_t *buff, uint32_t size ) { return 0; }
	virtual void   flush()                                   { return;   }
	virtual size_t write( uint8_t b )                        { return 0; }
	virtual size_t print( char c )                           { return 0; }
	virtual size_t print( char *str )                        { return 0; }
	virtual size_t print( const char *str )                  { return 0; }

	virtual int    printf( const char *fmt, ... )            { return 0; }

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

	int    printf( const char *fmt, ... ) override;

private:
	HardwareSerial *serialPort = NULL;

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

	int    printf( const char *fmt, ... ) override;

private:
	WiFiClient *client = NULL;

};

#endif





#endif /* COMMANDER_API_SRC_COMMANDER_IO_HPP_ */
