/*
 * commander_io.cpp
 *
 *  Created on: 2022. febr. 5.
 *      Author: dani0
 */

#include "commander_io.hpp"

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




