/*
 * Created on June 18 2020
 *
 * Copyright (c) 2020 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2022.02.06
*/

#include "commander_io.hpp"

#ifdef COMMANDER_USE_SERIAL_RESPONSE

//----- Response for Serial Class -----//

void commandResponseSerial::select( Serial *serialPort_p ){

	serialPort = serialPort_p;

}

int commandResponseSerial::available(){

	if( serialPort ) return serialPort -> available();
	return 0;

}

int commandResponseSerial::read(){

	if( serialPort ) return serialPort -> read();
	return -1;

}

int commandResponseSerial::peek(){

	if( serialPort ) return serialPort -> peek();
	return -1;

}

size_t commandResponseSerial::readBytes( uint8_t *buff, uint32_t size ){

	if( serialPort ) return serialPort -> readBytes( buff, size );
	return 0;

}

void commandResponseSerial::flush(){

	if( serialPort ) return serialPort -> flush();

}

size_t commandResponseSerial::write( uint8_t b ){

	if( serialPort ) return serialPort -> write( b );
	return 0;

}

size_t commandResponseSerial::print( char c ){

	if( serialPort ) return serialPort -> print( c );
	return 0;

}

size_t commandResponseSerial::print( char *str ){

	if( serialPort ) return serialPort -> print( str );
	return 0;

}

size_t commandResponseSerial::print( const char *str ){

	if( serialPort ) return serialPort -> print( str );
	return 0;

}

int commandResponseSerial::printf( const char *fmt, ... ){

	char out_buff[ COMMAND_PRINTF_BUFF_LEN ];

	va_list args;

	va_start( args, fmt );

	vsnprintf( out_buff, COMMAND_PRINTF_BUFF_LEN, fmt, args );

	va_end( args );

	if( serialPort ){

		return serialPort -> print( out_buff );

	}

	else{

		return -1;

	}

}

#endif

#ifdef COMMANDER_USE_ARDUINO_SERIAL_RESPONSE

//----- Response for Arduino Serial Class -----//

void commandResponseArduinoSerial::select( HardwareSerial *serialPort_p ){

	serialPort = serialPort_p;

}

int commandResponseArduinoSerial::available(){

	if( serialPort ) return serialPort -> available();
	return 0;

}

int commandResponseArduinoSerial::read(){

	if( serialPort ) return serialPort -> read();
	return -1;

}

int commandResponseArduinoSerial::peek(){

	if( serialPort ) return serialPort -> peek();
	return -1;

}

size_t commandResponseArduinoSerial::readBytes( uint8_t *buff, uint32_t size ){

	if( serialPort ) return serialPort -> readBytes( buff, size );
	return 0;

}

void commandResponseArduinoSerial::flush(){

	if( serialPort ) return serialPort -> flush();

}

size_t commandResponseArduinoSerial::write( uint8_t b ){

	if( serialPort ) return serialPort -> write( b );
	return 0;

}

size_t commandResponseArduinoSerial::print( char c ){

	if( serialPort ) return serialPort -> print( c );
	return 0;

}

size_t commandResponseArduinoSerial::print( char *str ){

	if( serialPort ) return serialPort -> print( str );
	return 0;

}

size_t commandResponseArduinoSerial::print( const char *str ){

	if( serialPort ) return serialPort -> print( str );
	return 0;

}

int commandResponseArduinoSerial::printf( const char *fmt, ... ){

	char out_buff[ COMMAND_PRINTF_BUFF_LEN ];

	va_list args;

	va_start( args, fmt );

	vsnprintf( out_buff, COMMAND_PRINTF_BUFF_LEN, fmt, args );

	va_end( args );

	if( serialPort ){

		return serialPort -> print( out_buff );

	}

	else{

		return -1;

	}

}

#endif

#ifdef COMMANDER_USE_WIFI_CLIENT_RESPONSE

//----- Response for WiFi Client Class -----//

void commandResponseWiFiClient::select( WiFiClient *client_p ){

	client = client_p;

}

int commandResponseWiFiClient::available(){

	if( client ) return client -> available();
	return 0;

}

int commandResponseWiFiClient::read(){

	if( client ) return client -> read();
	return -1;

}

int commandResponseWiFiClient::peek(){

	if( client ) return client -> peek();
	return -1;

}

size_t commandResponseWiFiClient::readBytes( uint8_t *buff, uint32_t size ){

	if( client ) return client -> readBytes( buff, size );
	return 0;

}

void commandResponseWiFiClient::flush(){

	if( client ) return client -> flush();

}

size_t commandResponseWiFiClient::write( uint8_t b ){

	if( client ) return client -> write( b );
	return 0;

}

size_t commandResponseWiFiClient::print( char c ){

	if( client ) return client -> print( c );
	return 0;

}

size_t commandResponseWiFiClient::print( char *str ){

	if( client ) return client -> print( str );
	return 0;

}

size_t commandResponseWiFiClient::print( const char *str ){

	if( client ) return client -> print( str );
	return 0;

}

int commandResponseWiFiClient::printf( const char *fmt, ... ){

	char out_buff[ COMMAND_PRINTF_BUFF_LEN ];

	va_list args;

	va_start( args, fmt );

	vsnprintf( out_buff, COMMAND_PRINTF_BUFF_LEN, fmt, args );

	va_end( args );

	if( client ){

		return client -> print( out_buff );

	}

	else{

		return -1;

	}

}

#endif
