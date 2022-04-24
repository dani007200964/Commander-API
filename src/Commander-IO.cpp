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


#include "Commander-IO.hpp"

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

//---- print section ----//
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

size_t commandResponseSerial::print( int8_t b ){

	if( serialPort ) return serialPort -> print( b );
	return 0;

}

size_t commandResponseSerial::print( uint8_t b ){

	if( serialPort ) return serialPort -> print( b );
	return 0;

}

size_t commandResponseSerial::print( int16_t b ){

	if( serialPort ) return serialPort -> print( b );
	return 0;

}

size_t commandResponseSerial::print( uint16_t b ){

	if( serialPort ) return serialPort -> print( b );
	return 0;

}

size_t commandResponseSerial::commandResponseArduinoSerial::print( int32_t b ){

	if( serialPort ) return serialPort -> print( b );
	return 0;

}

size_t commandResponseSerial::print( uint32_t b ){

	if( serialPort ) return serialPort -> print( b );
	return 0;

}

size_t commandResponseSerial::print( float f ){

	if( serialPort ) return serialPort -> print( f );
	return 0;

}

size_t commandResponseSerial::print( double f ){

	if( serialPort ) return serialPort -> print( f );
	return 0;

}

//---- println section ----//

size_t commandResponseSerial::println(){

	if( serialPort ) return serialPort -> println();
	return 0;

}

size_t commandResponseSerial::println( char c ){

	if( serialPort ) return serialPort -> println( c );
	return 0;

}

size_t commandResponseSerial::println( char *str ){

	if( serialPort ) return serialPort -> println( str );
	return 0;

}

size_t commandResponseSerial::println( const char *str ){

	if( serialPort ) return serialPort -> println( str );
	return 0;

}

size_t commandResponseSerial::println( int8_t b ){

	if( serialPort ) return serialPort -> println( b );
	return 0;

}

size_t commandResponseSerial::println( uint8_t b ){

	if( serialPort ) return serialPort -> println( b );
	return 0;

}

size_t commandResponseSerial::println( int16_t b ){

	if( serialPort ) return serialPort -> println( b );
	return 0;

}

size_t commandResponseSerial::println( uint16_t b ){

	if( serialPort ) return serialPort -> println( b );
	return 0;

}

size_t commandResponseSerial::println( int32_t b ){

	if( serialPort ) return serialPort -> print( b );
	return 0;

}

size_t commandResponseSerial::println( uint32_t b ){

	if( serialPort ) return serialPort -> print( b );
	return 0;

}

size_t commandResponseSerial::println( float f ){

	if( serialPort ) return serialPort -> print( f );
	return 0;

}

size_t commandResponseSerial::println( double f ){

	if( serialPort ) return serialPort -> print( f );
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

//---- print section ----//
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

size_t commandResponseArduinoSerial::print( int8_t b ){

	if( serialPort ) return serialPort -> print( b );
	return 0;

}

size_t commandResponseArduinoSerial::print( uint8_t b ){

	if( serialPort ) return serialPort -> print( b );
	return 0;

}

size_t commandResponseArduinoSerial::print( int16_t b ){

	if( serialPort ) return serialPort -> print( b );
	return 0;

}

size_t commandResponseArduinoSerial::print( uint16_t b ){

	if( serialPort ) return serialPort -> print( b );
	return 0;

}

size_t commandResponseArduinoSerial::print( int32_t b ){

	if( serialPort ) return serialPort -> print( b );
	return 0;

}

size_t commandResponseArduinoSerial::print( uint32_t b ){

	if( serialPort ) return serialPort -> print( b );
	return 0;

}

size_t commandResponseArduinoSerial::print( float f ){

	if( serialPort ) return serialPort -> print( f );
	return 0;

}

size_t commandResponseArduinoSerial::print( double f ){

	if( serialPort ) return serialPort -> print( f );
	return 0;

}

//---- println section ----//

size_t commandResponseArduinoSerial::println(){

	if( serialPort ) return serialPort -> println();
	return 0;

}

size_t commandResponseArduinoSerial::println( char c ){

	if( serialPort ) return serialPort -> println( c );
	return 0;

}

size_t commandResponseArduinoSerial::println( char *str ){

	if( serialPort ) return serialPort -> println( str );
	return 0;

}

size_t commandResponseArduinoSerial::println( const char *str ){

	if( serialPort ) return serialPort -> println( str );
	return 0;

}

size_t commandResponseArduinoSerial::println( int8_t b ){

	if( serialPort ) return serialPort -> println( b );
	return 0;

}

size_t commandResponseArduinoSerial::println( uint8_t b ){

	if( serialPort ) return serialPort -> println( b );
	return 0;

}

size_t commandResponseArduinoSerial::println( int16_t b ){

	if( serialPort ) return serialPort -> println( b );
	return 0;

}

size_t commandResponseArduinoSerial::println( uint16_t b ){

	if( serialPort ) return serialPort -> println( b );
	return 0;

}

size_t commandResponseArduinoSerial::println( int32_t b ){

	if( serialPort ) return serialPort -> print( b );
	return 0;

}

size_t commandResponseArduinoSerial::println( uint32_t b ){

	if( serialPort ) return serialPort -> print( b );
	return 0;

}

size_t commandResponseArduinoSerial::println( float f ){

	if( serialPort ) return serialPort -> print( f );
	return 0;

}

size_t commandResponseArduinoSerial::println( double f ){

	if( serialPort ) return serialPort -> print( f );
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

//---- print section ----//

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

size_t commandResponseWiFiClient::print( int8_t b ){

	if( serialPort ) return serialPort -> print( b );
	return 0;

}

size_t commandResponseWiFiClient::print( uint8_t b ){

	if( serialPort ) return serialPort -> print( b );
	return 0;

}

size_t commandResponseWiFiClient::print( int16_t b ){

	if( serialPort ) return serialPort -> print( b );
	return 0;

}

size_t commandResponseWiFiClient::print( uint16_t b ){

	if( serialPort ) return serialPort -> print( b );
	return 0;

}

size_t commandResponseWiFiClient::print( int32_t b ){

	if( serialPort ) return serialPort -> print( b );
	return 0;

}

size_t commandResponseWiFiClient::print( uint32_t b ){

	if( serialPort ) return serialPort -> print( b );
	return 0;

}

size_t commandResponseWiFiClient::print( float f ){

	if( serialPort ) return serialPort -> print( f );
	return 0;

}

size_t commandResponseWiFiClient::print( double f ){

	if( serialPort ) return serialPort -> print( f );
	return 0;

}

//---- println section ----//

size_t commandResponseWiFiClient::println(){

	if( serialPort ) return serialPort -> println();
	return 0;

}

size_t commandResponseWiFiClient::println( char c ){

	if( serialPort ) return serialPort -> println( c );
	return 0;

}

size_t commandResponseWiFiClient::println( char *str ){

	if( serialPort ) return serialPort -> println( str );
	return 0;

}

size_t commandResponseWiFiClient::println( const char *str ){

	if( serialPort ) return serialPort -> println( str );
	return 0;

}

size_t commandResponseWiFiClient::println( int8_t b ){

	if( serialPort ) return serialPort -> println( b );
	return 0;

}

size_t commandResponseWiFiClient::println( uint8_t b ){

	if( serialPort ) return serialPort -> println( b );
	return 0;

}

size_t commandResponseWiFiClient::println( int16_t b ){

	if( serialPort ) return serialPort -> println( b );
	return 0;

}

size_t commandResponseWiFiClient::println( uint16_t b ){

	if( serialPort ) return serialPort -> println( b );
	return 0;

}

size_t commandResponseWiFiClient::println( int32_t b ){

	if( serialPort ) return serialPort -> print( b );
	return 0;

}

size_t commandResponseWiFiClient::println( uint32_t b ){

	if( serialPort ) return serialPort -> print( b );
	return 0;

}

size_t commandResponseWiFiClient::println( float f ){

	if( serialPort ) return serialPort -> print( f );
	return 0;

}

size_t commandResponseWiFiClient::println( double f ){

	if( serialPort ) return serialPort -> print( f );
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
