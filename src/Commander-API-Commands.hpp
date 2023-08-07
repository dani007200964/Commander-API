/*
 * Created on Oct. 01 2022
 *
 * Copyright (c) 2020 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2022.10.04
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

#ifndef COMMANDER_API_COMMANDS_HPP__
#define COMMANDER_API_COMMANDS_HPP__

/// Arduino detection
#ifdef ARDUINO
#include "Arduino.h"
#include "Wire.h"
#else
#include "System.h"
#endif

#include <math.h>

#ifdef __AVR__
  #include <avr/wdt.h>
#endif

#ifdef ESP32

  #include "time.h"

#endif

#include "Commander-API.hpp"
#include "Commander-Arguments.hpp"

void printCommandNotImplemented( Stream* channel_p );

//**** System functions ****//

//-------- reboot function --------//
#define API_ELEMENT_REBOOT_NAME		"reboot"

#define API_ELEMENT_REBOOT_DESCRIPTION	"Reboots the device.\r\n\r\n"	\
                                      	"usage: reboot\r\n"				\

#define API_ELEMENT_REBOOT apiElement( API_ELEMENT_REBOOT_NAME, API_ELEMENT_REBOOT_DESCRIPTION, commander_reboot_func )
#ifdef __AVR__
  #define API_ELEMENT_P_REBOOT( element ) apiElement_P( element, API_ELEMENT_REBOOT_NAME, API_ELEMENT_REBOOT_DESCRIPTION, commander_reboot_func )
#endif
/// Premade function for reboot command. It reboots the core.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_reboot_func( char *args, Stream *response, void* parent );

//---- echo function ----//
#define API_ELEMENT_ECHO_NAME			"echo"

#define API_ELEMENT_ECHO_DESCRIPTION	"Echoes back the input data. The input data can be a system variable.\r\n\r\n"	\
                                    	"usage: echo [input data or system variable]\r\n"								\

#define API_ELEMENT_ECHO apiElement( API_ELEMENT_ECHO_NAME, API_ELEMENT_ECHO_DESCRIPTION, commander_echo_func )
#ifdef __AVR__
  #define API_ELEMENT_P_ECHO( element ) apiElement_P( element, API_ELEMENT_ECHO_NAME, API_ELEMENT_ECHO_DESCRIPTION, commander_echo_func )
#endif
/// Premade function for echo command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_echo_func( char *args, Stream *response, void* parent );

//---- env function ----//
#define API_ELEMENT_ENV_NAME			"env"

#define API_ELEMENT_ENV_DESCRIPTION		"Lists all hte system variables.\r\n\r\n"   \
                                    	"usage: env\r\n"							\

#define API_ELEMENT_ENV apiElement( API_ELEMENT_ENV_NAME, API_ELEMENT_ENV_DESCRIPTION, commander_env_func )
#ifdef __AVR__
  #define API_ELEMENT_P_ENV( element ) apiElement_P( element, API_ELEMENT_ENV_NAME, API_ELEMENT_ENV_DESCRIPTION, commander_env_func )
#endif
/// Premade function for echo command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_env_func( char *args, Stream *response, void* parent );

//-------- micros functions --------//
#define API_ELEMENT_MICROS_NAME			"micros"

#define API_ELEMENT_MICROS_DESCRIPTION	"Returns the number of microseconds passed since the program started.\r\n\r\n"	\
                                    	"usage: micros\r\n"																\

#define API_ELEMENT_MICROS apiElement( API_ELEMENT_MICROS_NAME, API_ELEMENT_MICROS_DESCRIPTION, commander_micros_func )
#ifdef __AVR__
  #define API_ELEMENT_P_MICROS( element ) apiElement_P( element, API_ELEMENT_MICROS_NAME, API_ELEMENT_MICROS_DESCRIPTION, commander_micros_func )
#endif
/// Premade function for micros command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_micros_func( char *args, Stream *response, void* parent );

//-------- millis functions --------//
#define API_ELEMENT_MILLIS_NAME			"millis"

#define API_ELEMENT_MILLIS_DESCRIPTION	"Returns the number of milliseconds passed since the program started.\r\n\r\n"	\
                                    	"usage: millis\r\n"																\

#define API_ELEMENT_MILLIS apiElement( API_ELEMENT_MILLIS_NAME, API_ELEMENT_MILLIS_DESCRIPTION, commander_millis_func )
#ifdef __AVR__
  #define API_ELEMENT_P_MILLIS( element ) apiElement_P( element, API_ELEMENT_MILLIS_NAME, API_ELEMENT_MILLIS_DESCRIPTION, commander_millis_func )
#endif
/// Premade function for millis command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_millis_func( char *args, Stream *response, void* parent );

//-------- uptime functions --------//
#define API_ELEMENT_UPTIME_NAME			"uptime"

#define API_ELEMENT_UPTIME_DESCRIPTION	"Returns the time passed since the program started.\r\n\r\n"	\
                                    	"usage: uptime\r\n"																\

#define API_ELEMENT_UPTIME apiElement( API_ELEMENT_UPTIME_NAME, API_ELEMENT_UPTIME_DESCRIPTION, commander_uptime_func )
#ifdef __AVR__
  #define API_ELEMENT_P_UPTIME( element ) apiElement_P( element, API_ELEMENT_UPTIME_NAME, API_ELEMENT_UPTIME_DESCRIPTION, commander_uptime_func )
#endif
/// Premade function for uptime command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_uptime_func( char *args, Stream *response, void* parent );

//-------- neofetch function --------//
#define API_ELEMENT_NEOFETCH_NAME			"neofetch"

#define API_ELEMENT_NEOFETCH_DESCRIPTION	"Nice looking system information.\r\n\r\n"	\
                                    		"usage: neofetch\r\n"																\


#define API_ELEMENT_NEOFETCH apiElement( API_ELEMENT_NEOFETCH_NAME, API_ELEMENT_NEOFETCH_DESCRIPTION, commander_neofetch_func )
#ifdef __AVR__
  #define API_ELEMENT_P_NEOFETCH( element ) apiElement_P( element, API_ELEMENT_NEOFETCH_NAME, API_ELEMENT_NEOFETCH_DESCRIPTION, commander_neofetch_func )
#endif
/// Premade function for neofetch command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_neofetch_func( char *args, Stream *response, void* parent );

//-------- Digital I-O functions --------//
#define API_ELEMENT_PINMODE_NAME		"pinMode"

#define API_ELEMENT_PINMODE_DESCRIPTION	"Set the direction of a pin.\r\n\r\n"		\
                                        "usage: pinMode [options]\r\n"				\
                                        "Options:\r\n"								\
                                        "  -p, --pin\t[int] Pin identifier.\r\n"	\
                                        "  -o, --output\tSet mode to output.\r\n"	\
                                        "  -i, --input\tSet mode to input.\r\n"

#define API_ELEMENT_PINMODE apiElement( API_ELEMENT_PINMODE_NAME, API_ELEMENT_PINMODE_DESCRIPTION, commander_pinMode_func )
#ifdef __AVR__
  #define API_ELEMENT_P_PINMODE( element ) apiElement_P( element, API_ELEMENT_PINMODE_NAME, API_ELEMENT_PINMODE_DESCRIPTION, commander_pinMode_func )
#endif
/// Premade function for pinMode command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_pinMode_func( char *args, Stream *response, void* parent );

#define API_ELEMENT_DIGITALWRITE_NAME			"digitalWrite"

#define API_ELEMENT_DIGITALWRITE_DESCRIPTION	"Set the state of an output pin.\r\n\r\n"			\
                                        		"usage: digitalWrite [options]\r\n"					\
                                        		"Options:\r\n"										\
                                        		"  -p, --pin\t[int] Pin identifier.\r\n"			\
                                        		"  -h, --high\tSet output mode to logic high.\r\n"	\
                                        		"  -l, --low\tSet output mode to logic high.\r\n"

#define API_ELEMENT_DIGITALWRITE apiElement( API_ELEMENT_DIGITALWRITE_NAME, API_ELEMENT_DIGITALWRITE_DESCRIPTION, commander_digitalWrite_func )
#ifdef __AVR__
  #define API_ELEMENT_P_DIGITALWRITE( element ) apiElement_P( element, API_ELEMENT_DIGITALWRITE_NAME, API_ELEMENT_DIGITALWRITE_DESCRIPTION, commander_digitalWrite_func )
#endif
/// Premade function for digitalWrite command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_digitalWrite_func( char *args, Stream *response, void* parent );

#define API_ELEMENT_DIGITALREAD_NAME			"digitalRead"

#define API_ELEMENT_DIGITALREAD_DESCRIPTION		"Read the state of a pin.\r\n\r\n"							\
                                        		"usage: digitalRead [options]\r\n"							\
                                        		"Options:\r\n"												\
                                        		"  -p, --pin\t[int] Pin identifier.\r\n"					\
                                        		"  -t, --text\tSet return format to text[ LOW, HIGH ].\r\n"

#define API_ELEMENT_DIGITALREAD apiElement( API_ELEMENT_DIGITALREAD_NAME, API_ELEMENT_DIGITALREAD_DESCRIPTION, commander_digitalRead_func )
#ifdef __AVR__
  #define API_ELEMENT_P_DIGITALREAD( element ) apiElement_P( element, API_ELEMENT_DIGITALREAD_NAME, API_ELEMENT_DIGITALREAD_DESCRIPTION, commander_digitalRead_func )
#endif
/// Premade function for digitalRead command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_digitalRead_func( char *args, Stream *response, void* parent );

//-------- analogRead functions --------//
#define API_ELEMENT_ANALOGREAD_NAME				"analogRead"

#define API_ELEMENT_ANALOGREAD_DESCRIPTION		"Reads the value from the specified analog pin.\r\n\r\n"			\
                                        		"usage: analogRead [options]\r\n"									\
                                        		"Options:\r\n"														\
                                        		"  -p, --pin\t[int] Pin identifier( A0 -> 0, A5 -> 5... )."

#define API_ELEMENT_ANALOGREAD apiElement( API_ELEMENT_ANALOGREAD_NAME, API_ELEMENT_ANALOGREAD_DESCRIPTION, commander_analogRead_func )
#ifdef __AVR__
  #define API_ELEMENT_P_ANALOGREAD( element ) apiElement_P( element, API_ELEMENT_ANALOGREAD_NAME, API_ELEMENT_ANALOGREAD_DESCRIPTION, commander_analogRead_func )
#endif
/// Premade function for analogRead command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_analogRead_func( char *args, Stream *response, void* parent );

//-------- analogWrite functions --------//
#define API_ELEMENT_ANALOGWRITE_NAME			"analogWrite"

#define API_ELEMENT_ANALOGWRITE_DESCRIPTION		"Writes an analog value (PWM wave) to a pin.\r\n\r\n"	\
                                        		"usage: analogWrite [options]\r\n"						\
                                        		"Options:\r\n"											\
                                        		"  -p, --pin\t[int] Pin identifier."					\
                                        		"  -d, --duty\t[int] Duty cycle[ 0 - 255 ]."			\
												"  -v, --value\t[int] Value in percentage[ 0 - 100 ]."

#define API_ELEMENT_ANALOGWRITE apiElement( API_ELEMENT_ANALOGWRITE_NAME, API_ELEMENT_ANALOGWRITE_DESCRIPTION, commander_analogWrite_func )
#ifdef __AVR__
  #define API_ELEMENT_P_ANALOGWRITE( element ) apiElement_P( element, API_ELEMENT_ANALOGWRITE_NAME, API_ELEMENT_ANALOGWRITE_DESCRIPTION, commander_analogWrite_func )
#endif
/// Premade function for analogRead command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_analogWrite_func( char *args, Stream *response, void* parent );

//-------- WiFi functions --------//

#if defined( ESP32 ) || ( ESP8266 )

#define API_ELEMENT_IPCONFIG apiElement( "ipconfig", "Print network information.", commander_ipconfig_func )
/// Premade function for ipconfig command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_ipconfig_func( char *args, Stream *response, void* parent );

#define API_ELEMENT_WIFISTAT apiElement( "wifiStat", "Print WiFi information.", commander_wifiStat_func )
/// Premade function for wifiStat command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_wifiStat_func( char *args, Stream *response, void* parent );

#define API_ELEMENT_WIFISCAN apiElement( "wifiScan", "Search for available networks around.", commander_wifiScan_func )
/// Premade function for wifiScan command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_wifiScan_func( char *args, Stream *response, void* parent );

#endif

#ifdef ESP32

#define API_ELEMENT_CONFIGTIME apiElement( "configTime", "Configure NTP time settings.\r\n\tExample: configTime [ GMT Offset Sec ] [ DL Offset Sec ] [ Server ]\r\n\t[ GMT Offset Sec ] - UTC offset for your timezone in seconds.\r\n\t[ GMT Offset Sec ] - Daylight offset in sec.\r\n\t[ Server ] - NTP Server Address( optional, default: pool.ntp.org )", commander_configTime_func )
/// Premade function for wifiScan command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_configTime_func( char *args, Stream *response, void* parent );

#define API_ELEMENT_DATETIME apiElement( "dateTime", "Returns the NTP synchronised date and time.", commander_dateTime_func )
/// Premade function for wifiScan command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_dateTime_func( char *args, Stream *response, void* parent );

#endif

//-------- Math functions --------//

#define API_ELEMENT_SIN apiElement( "sin", "Sine function. The input is in radians.", commander_sin_func )
#ifdef __AVR__
  #define API_ELEMENT_P_SIN( element ) apiElement_P( element, "sin", "Sine function. The input is in radians.", commander_sin_func )
#endif
/// Premade function for sin command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_sin_func( char *args, Stream *response, void* parent );

#define API_ELEMENT_COS apiElement( "cos", "Cosine function. The input is in radians.", commander_cos_func )
#ifdef __AVR__
  #define API_ELEMENT_P_COS( element ) apiElement_P( element, "cos", "Cosine function. The input is in radians.", commander_cos_func )
#endif
/// Premade function for cos command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_cos_func( char *args, Stream *response, void* parent );

#define API_ELEMENT_ABS apiElement( "abs", "Calculates the absolute value of a number.", commander_abs_func )
#ifdef __AVR__
  #define API_ELEMENT_P_ABS( element ) apiElement_P( element, "abs", "Calculates the absolute value of a number.", commander_abs_func )
#endif
/// Premade function for abs command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_abs_func( char *args, Stream *response, void* parent );

#define API_ELEMENT_RANDOM apiElement( "random", "Generates a random number between the parameters.\r\n\tExample: random [ min ] [ max ]\r\n\t[ min ] - Lower integer bound\r\n\t[ max ] - Upper integer bound", commander_random_func )
#ifdef __AVR__
  #define API_ELEMENT_P_RANDOM( element ) apiElement_P( element, "random", "Generates a random number between the parameters.\r\n\tExample: random [ min ] [ max ]\r\n\t[ min ] - Lower integer bound\r\n\t[ max ] - Upper integer bound", commander_random_func )
#endif
/// Premade function for random command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_random_func( char *args, Stream *response, void* parent );

#define API_ELEMENT_NOT apiElement( "not", "Logical not. If the input is 0 returns 1. Any other cases it returns 0.", commander_not_func )
#ifdef __AVR__
  #define API_ELEMENT_P_NOT( element ) apiElement_P( element, "not", "Logical not. If the input is 0 returns 1. Any other cases it returns 0.", commander_not_func )
#endif
/// Premade function for not command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_not_func( char *args, Stream *response, void* parent );

#endif