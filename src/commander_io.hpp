/*
 * commander_io.hpp
 *
 *  Created on: 2022. febr. 5.
 *      Author: dani0
 */

#ifndef COMMANDER_API_SRC_COMMANDER_IO_HPP_
#define COMMANDER_API_SRC_COMMANDER_IO_HPP_

#include "Serial.hpp"

#define COMMAND_PRINTF_BUFF_LEN 100

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



#endif /* COMMANDER_API_SRC_COMMANDER_IO_HPP_ */
