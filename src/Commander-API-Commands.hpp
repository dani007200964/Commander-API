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
#define SYSTEM_COMMAND_REBOOT_NAME		    "reboot"

#define SYSTEM_COMMAND_REBOOT_DESCRIPTION	"Reboots the device.\r\n\r\n"	\
                                          	"usage: reboot\r\n"				\

#define SYSTEM_COMMAND_REBOOT systemCommand( SYSTEM_COMMAND_REBOOT_NAME, SYSTEM_COMMAND_REBOOT_DESCRIPTION, commander_reboot_func )
#ifdef __AVR__
    #define SYSTEM_COMMAND_P_REBOOT( element ) systemCommand_P( element, SYSTEM_COMMAND_REBOOT_NAME, SYSTEM_COMMAND_REBOOT_DESCRIPTION, commander_reboot_func )
#endif
/// Premade function for reboot command. It reboots the core.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
bool commander_reboot_func( char *args, Stream *response, void* parent );

//---- echo function ----//
#define SYSTEM_COMMAND_ECHO_NAME			"echo"

#define SYSTEM_COMMAND_ECHO_DESCRIPTION     "Echoes back the input data. The input data can be a system variable.\r\n\r\n"  \
                                    	    "usage: echo [input data or system variable]"

#define SYSTEM_COMMAND_ECHO systemCommand( SYSTEM_COMMAND_ECHO_NAME, SYSTEM_COMMAND_ECHO_DESCRIPTION, commander_echo_func )
#ifdef __AVR__
    #define SYSTEM_COMMAND_P_ECHO( element ) systemCommand_P( element, SYSTEM_COMMAND_ECHO_NAME, SYSTEM_COMMAND_ECHO_DESCRIPTION, commander_echo_func )
#endif
/// Premade function for echo command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
bool commander_echo_func( char *args, Stream *response, void* parent );

//---- env function ----//
#define SYSTEM_COMMAND_ENV_NAME			"env"

#define SYSTEM_COMMAND_ENV_DESCRIPTION		"Lists all hte system variables.\r\n\r\n"   \
                                    	"usage: env\r\n"							\

#define SYSTEM_COMMAND_ENV systemCommand( SYSTEM_COMMAND_ENV_NAME, SYSTEM_COMMAND_ENV_DESCRIPTION, commander_env_func )
#ifdef __AVR__
  #define SYSTEM_COMMAND_P_ENV( element ) systemCommand_P( element, SYSTEM_COMMAND_ENV_NAME, SYSTEM_COMMAND_ENV_DESCRIPTION, commander_env_func )
#endif
/// Premade function for echo command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
bool commander_env_func( char *args, Stream *response, void* parent );

//-------- micros functions --------//
#define SYSTEM_COMMAND_MICROS_NAME			"micros"

#define SYSTEM_COMMAND_MICROS_DESCRIPTION	"Returns the number of microseconds passed since the program started.\r\n\r\n"	\
                                    	"usage: micros\r\n"																\

#define SYSTEM_COMMAND_MICROS systemCommand( SYSTEM_COMMAND_MICROS_NAME, SYSTEM_COMMAND_MICROS_DESCRIPTION, commander_micros_func )
#ifdef __AVR__
  #define SYSTEM_COMMAND_P_MICROS( element ) systemCommand_P( element, SYSTEM_COMMAND_MICROS_NAME, SYSTEM_COMMAND_MICROS_DESCRIPTION, commander_micros_func )
#endif
/// Premade function for micros command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
bool commander_micros_func( char *args, Stream *response, void* parent );

//-------- millis functions --------//
#define SYSTEM_COMMAND_MILLIS_NAME			"millis"

#define SYSTEM_COMMAND_MILLIS_DESCRIPTION	"Returns the number of milliseconds passed since the program started.\r\n\r\n"	\
                                    	"usage: millis\r\n"																\

#define SYSTEM_COMMAND_MILLIS systemCommand( SYSTEM_COMMAND_MILLIS_NAME, SYSTEM_COMMAND_MILLIS_DESCRIPTION, commander_millis_func )
#ifdef __AVR__
  #define SYSTEM_COMMAND_P_MILLIS( element ) systemCommand_P( element, SYSTEM_COMMAND_MILLIS_NAME, SYSTEM_COMMAND_MILLIS_DESCRIPTION, commander_millis_func )
#endif
/// Premade function for millis command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
bool commander_millis_func( char *args, Stream *response, void* parent );

//-------- uptime functions --------//
#define SYSTEM_COMMAND_UPTIME_NAME			"uptime"

#define SYSTEM_COMMAND_UPTIME_DESCRIPTION	"Returns the time passed since the program started.\r\n\r\n"	\
                                    	"usage: uptime\r\n"																\

#define SYSTEM_COMMAND_UPTIME systemCommand( SYSTEM_COMMAND_UPTIME_NAME, SYSTEM_COMMAND_UPTIME_DESCRIPTION, commander_uptime_func )
#ifdef __AVR__
  #define SYSTEM_COMMAND_P_UPTIME( element ) systemCommand_P( element, SYSTEM_COMMAND_UPTIME_NAME, SYSTEM_COMMAND_UPTIME_DESCRIPTION, commander_uptime_func )
#endif
/// Premade function for uptime command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
bool commander_uptime_func( char *args, Stream *response, void* parent );

//-------- neofetch function --------//
#define SYSTEM_COMMAND_NEOFETCH_NAME			"neofetch"

#define SYSTEM_COMMAND_NEOFETCH_DESCRIPTION	"Nice looking system information.\r\n\r\n"	\
                                    		"usage: neofetch\r\n"																\


#define SYSTEM_COMMAND_NEOFETCH systemCommand( SYSTEM_COMMAND_NEOFETCH_NAME, SYSTEM_COMMAND_NEOFETCH_DESCRIPTION, commander_neofetch_func )
#ifdef __AVR__
  #define SYSTEM_COMMAND_P_NEOFETCH( element ) systemCommand_P( element, SYSTEM_COMMAND_NEOFETCH_NAME, SYSTEM_COMMAND_NEOFETCH_DESCRIPTION, commander_neofetch_func )
#endif
/// Premade function for neofetch command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
bool commander_neofetch_func( char *args, Stream *response, void* parent );

//-------- Digital I-O functions --------//
#define SYSTEM_COMMAND_PINMODE_NAME		"pinMode"

#define SYSTEM_COMMAND_PINMODE_DESCRIPTION	"Set the direction of a pin.\r\n\r\n"		\
                                        "usage: pinMode [options]\r\n"				\
                                        "Options:\r\n"								\
                                        "  -p, --pin\t[int] Pin identifier.\r\n"	\
                                        "  -o, --output\tSet mode to output.\r\n"	\
                                        "  -i, --input\tSet mode to input.\r\n"

#define SYSTEM_COMMAND_PINMODE systemCommand( SYSTEM_COMMAND_PINMODE_NAME, SYSTEM_COMMAND_PINMODE_DESCRIPTION, commander_pinMode_func )
#ifdef __AVR__
  #define SYSTEM_COMMAND_P_PINMODE( element ) systemCommand_P( element, SYSTEM_COMMAND_PINMODE_NAME, SYSTEM_COMMAND_PINMODE_DESCRIPTION, commander_pinMode_func )
#endif
/// Premade function for pinMode command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
bool commander_pinMode_func( char *args, Stream *response, void* parent );

#define SYSTEM_COMMAND_DIGITALWRITE_NAME			"digitalWrite"

#define SYSTEM_COMMAND_DIGITALWRITE_DESCRIPTION	"Set the state of an output pin.\r\n\r\n"			\
                                        		"usage: digitalWrite [options]\r\n"					\
                                        		"Options:\r\n"										\
                                        		"  -p, --pin\t[int] Pin identifier.\r\n"			\
                                        		"  -h, --high\tSet output mode to logic high.\r\n"	\
                                        		"  -l, --low\tSet output mode to logic high.\r\n"

#define SYSTEM_COMMAND_DIGITALWRITE systemCommand( SYSTEM_COMMAND_DIGITALWRITE_NAME, SYSTEM_COMMAND_DIGITALWRITE_DESCRIPTION, commander_digitalWrite_func )
#ifdef __AVR__
  #define SYSTEM_COMMAND_P_DIGITALWRITE( element ) systemCommand_P( element, SYSTEM_COMMAND_DIGITALWRITE_NAME, SYSTEM_COMMAND_DIGITALWRITE_DESCRIPTION, commander_digitalWrite_func )
#endif
/// Premade function for digitalWrite command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
bool commander_digitalWrite_func( char *args, Stream *response, void* parent );

#define SYSTEM_COMMAND_DIGITALREAD_NAME			"digitalRead"

#define SYSTEM_COMMAND_DIGITALREAD_DESCRIPTION		"Read the state of a pin.\r\n\r\n"							\
                                        		"usage: digitalRead [options]\r\n"							\
                                        		"Options:\r\n"												\
                                        		"  -p, --pin\t[int] Pin identifier.\r\n"					\
                                        		"  -t, --text\tSet return format to text[ LOW, HIGH ].\r\n"

#define SYSTEM_COMMAND_DIGITALREAD systemCommand( SYSTEM_COMMAND_DIGITALREAD_NAME, SYSTEM_COMMAND_DIGITALREAD_DESCRIPTION, commander_digitalRead_func )
#ifdef __AVR__
  #define SYSTEM_COMMAND_P_DIGITALREAD( element ) systemCommand_P( element, SYSTEM_COMMAND_DIGITALREAD_NAME, SYSTEM_COMMAND_DIGITALREAD_DESCRIPTION, commander_digitalRead_func )
#endif
/// Premade function for digitalRead command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
bool commander_digitalRead_func( char *args, Stream *response, void* parent );

//-------- analogRead functions --------//
#define SYSTEM_COMMAND_ANALOGREAD_NAME				"analogRead"

#define SYSTEM_COMMAND_ANALOGREAD_DESCRIPTION		"Reads the value from the specified analog pin.\r\n\r\n"			\
                                        		"usage: analogRead [options]\r\n"									\
                                        		"Options:\r\n"														\
                                        		"  -p, --pin\t[int] Pin identifier( A0 -> 0, A5 -> 5... )."

#define SYSTEM_COMMAND_ANALOGREAD systemCommand( SYSTEM_COMMAND_ANALOGREAD_NAME, SYSTEM_COMMAND_ANALOGREAD_DESCRIPTION, commander_analogRead_func )
#ifdef __AVR__
  #define SYSTEM_COMMAND_P_ANALOGREAD( element ) systemCommand_P( element, SYSTEM_COMMAND_ANALOGREAD_NAME, SYSTEM_COMMAND_ANALOGREAD_DESCRIPTION, commander_analogRead_func )
#endif
/// Premade function for analogRead command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
bool commander_analogRead_func( char *args, Stream *response, void* parent );

//-------- analogWrite functions --------//
#define SYSTEM_COMMAND_ANALOGWRITE_NAME			"analogWrite"

#define SYSTEM_COMMAND_ANALOGWRITE_DESCRIPTION		"Writes an analog value (PWM wave) to a pin.\r\n\r\n"	\
                                        		"usage: analogWrite [options]\r\n"						\
                                        		"Options:\r\n"											\
                                        		"  -p, --pin\t[int] Pin identifier."					\
                                        		"  -d, --duty\t[int] Duty cycle[ 0 - 255 ]."			\
												"  -v, --value\t[int] Value in percentage[ 0 - 100 ]."

#define SYSTEM_COMMAND_ANALOGWRITE systemCommand( SYSTEM_COMMAND_ANALOGWRITE_NAME, SYSTEM_COMMAND_ANALOGWRITE_DESCRIPTION, commander_analogWrite_func )
#ifdef __AVR__
  #define SYSTEM_COMMAND_P_ANALOGWRITE( element ) systemCommand_P( element, SYSTEM_COMMAND_ANALOGWRITE_NAME, SYSTEM_COMMAND_ANALOGWRITE_DESCRIPTION, commander_analogWrite_func )
#endif
/// Premade function for analogRead command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
bool commander_analogWrite_func( char *args, Stream *response, void* parent );

//-------- WiFi functions --------//

#if defined( ESP32 ) || ( ESP8266 )

#define SYSTEM_COMMAND_IPCONFIG systemCommand( "ipconfig", "Print network information.", commander_ipconfig_func )
/// Premade function for ipconfig command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_ipconfig_func( char *args, Stream *response, void* parent );

#define SYSTEM_COMMAND_WIFISTAT systemCommand( "wifiStat", "Print WiFi information.", commander_wifiStat_func )
/// Premade function for wifiStat command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_wifiStat_func( char *args, Stream *response, void* parent );

#define SYSTEM_COMMAND_WIFISCAN systemCommand( "wifiScan", "Search for available networks around.", commander_wifiScan_func )
/// Premade function for wifiScan command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_wifiScan_func( char *args, Stream *response, void* parent );

#endif

#ifdef ESP32

#define SYSTEM_COMMAND_CONFIGTIME systemCommand( "configTime", "Configure NTP time settings.\r\n\tExample: configTime [ GMT Offset Sec ] [ DL Offset Sec ] [ Server ]\r\n\t[ GMT Offset Sec ] - UTC offset for your timezone in seconds.\r\n\t[ GMT Offset Sec ] - Daylight offset in sec.\r\n\t[ Server ] - NTP Server Address( optional, default: pool.ntp.org )", commander_configTime_func )
/// Premade function for wifiScan command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_configTime_func( char *args, Stream *response, void* parent );

#define SYSTEM_COMMAND_DATETIME systemCommand( "dateTime", "Returns the NTP synchronised date and time.", commander_dateTime_func )
/// Premade function for wifiScan command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_dateTime_func( char *args, Stream *response, void* parent );

#endif

//-------- sin function --------//
#define SYSTEM_COMMAND_SIN_NAME			"sin"

#define SYSTEM_COMMAND_SIN_DESCRIPTION		"Sine function.\r\n\r\n"	                                            \
                                        "usage: sin [options]\r\n"						                        \
                                        "Options:\r\n"									                        \
                                        "  -d, --deg\t[float] Input angle in degrees.\r\n"                      \
										"  -r, --rad\t[float] Input angle in radians.\r\n"                      \
										"  -p, --places\t[int] The number of decimal places can be defined\r\n" \
                                        "\t\t[ optional, 2 digits by default. ]."
                                        

#define SYSTEM_COMMAND_SIN systemCommand( SYSTEM_COMMAND_SIN_NAME, SYSTEM_COMMAND_SIN_DESCRIPTION, commander_sin_func )
#ifdef __AVR__
  #define SYSTEM_COMMAND_P_SIN( element ) systemCommand_P( element, SYSTEM_COMMAND_SIN_NAME, SYSTEM_COMMAND_SIN_DESCRIPTION, commander_sin_func )
#endif
/// Premade function for sin command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
bool commander_sin_func( char *args, Stream *response, void* parent );

//-------- sin function --------//
#define SYSTEM_COMMAND_COS_NAME			"cos"

#define SYSTEM_COMMAND_COS_DESCRIPTION		"Cosine function.\r\n\r\n"	                                            \
                                        "usage: cos [options]\r\n"						                        \
                                        "Options:\r\n"									                        \
                                        "  -d, --deg\t[float] Input angle in degrees.\r\n"                      \
										"  -r, --rad\t[float] Input angle in radians.\r\n"                      \
										"  -p, --places\t[int] The number of decimal places can be defined\r\n" \
                                        "\t\t[ optional, 2 digits by default. ]."
                                        

#define SYSTEM_COMMAND_COS systemCommand( SYSTEM_COMMAND_COS_NAME, SYSTEM_COMMAND_COS_DESCRIPTION, commander_cos_func )
#ifdef __AVR__
  #define SYSTEM_COMMAND_P_COS( element ) systemCommand_P( element, SYSTEM_COMMAND_COS_NAME, SYSTEM_COMMAND_COS_DESCRIPTION, commander_cos_func )
#endif
/// Premade function for cos command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
bool commander_cos_func( char *args, Stream *response, void* parent );

//-------- abs function --------//
#define SYSTEM_COMMAND_ABS_NAME			"abs"

#define SYSTEM_COMMAND_ABS_DESCRIPTION		"Calculates the absolute value of a number.\r\n\r\n"                    \
                                        "usage: abs [float][options]\r\n"                                       \
                                        "Options:\r\n"									                        \
										"  -p, --places\t[int] The number of decimal places can be defined\r\n" \
                                        "\t\t[ optional, 2 digits by default. ]."

#define SYSTEM_COMMAND_ABS systemCommand( SYSTEM_COMMAND_ABS_NAME, SYSTEM_COMMAND_ABS_DESCRIPTION, commander_abs_func )
#ifdef __AVR__
  #define SYSTEM_COMMAND_P_ABS( element ) systemCommand_P( element, SYSTEM_COMMAND_ABS_NAME, SYSTEM_COMMAND_ABS_DESCRIPTION, commander_abs_func )
#endif
/// Premade function for abs command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
bool commander_abs_func( char *args, Stream *response, void* parent );

//-------- random function --------//
#define SYSTEM_COMMAND_RANDOM_NAME         "random"

#define SYSTEM_COMMAND_RANDOM_DESCRIPTION  "Generates a random number.\r\n\r\n"                       \
                                        "usage: random [options]\r\n"                              \
                                        "Options:\r\n"									           \
										"  -u, --upper\t[int] Upper bound of the random value\r\n" \
										"  -l, --lower\t[int] Lower bound of the random value\r\n" \
                                        "\t\t[ optional, 0 default. ]."

#define SYSTEM_COMMAND_RANDOM systemCommand( SYSTEM_COMMAND_RANDOM_NAME, SYSTEM_COMMAND_RANDOM_DESCRIPTION, commander_random_func )
#ifdef __AVR__
  #define SYSTEM_COMMAND_P_RANDOM( element ) systemCommand_P( element, SYSTEM_COMMAND_RANDOM_NAME, SYSTEM_COMMAND_RANDOM_DESCRIPTION, commander_random_func )
#endif
/// Premade function for random command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
bool commander_random_func( char *args, Stream *response, void* parent );

//-------- not function --------//
#define SYSTEM_COMMAND_NOT_NAME            "not"

#define SYSTEM_COMMAND_NOT_DESCRIPTION     "If the input is 0, it will return 1. Any other cases, it will return 0.\r\n\r\n"   \
                                        "usage: not [int]"

#define SYSTEM_COMMAND_NOT systemCommand( SYSTEM_COMMAND_NOT_NAME, SYSTEM_COMMAND_NOT_DESCRIPTION, commander_not_func )
#ifdef __AVR__
  #define SYSTEM_COMMAND_P_NOT( element ) systemCommand_P( element, SYSTEM_COMMAND_NOT_NAME, SYSTEM_COMMAND_NOT_DESCRIPTION, commander_not_func )
#endif
/// Premade function for not command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
bool commander_not_func( char *args, Stream *response, void* parent );



//-------- exportTarget function --------//
#define SYSTEM_COMMAND_EXPORT_TARGET_NAME          "exportTarget"

#define SYSTEM_COMMAND_EXPORT_TARGET_DESCRIPTION   "You can get or set the target of the export command.\r\n\r\n"                          \
                                                "usage: selectExport [target]\r\n\r\n"                                                  \
                                                "target: The target has to be an integer, or a float system variable.\r\n"              \
                                                "\t If target is not defined, the command will print the name of the current target."

#define SYSTEM_COMMAND_EXPORT_TARGET systemCommand( SYSTEM_COMMAND_EXPORT_TARGET_NAME, SYSTEM_COMMAND_EXPORT_TARGET_DESCRIPTION, commander_exportTarget_func )
#ifdef __AVR__
  #define SYSTEM_COMMAND_P_EXPORT_TARGET( element ) systemCommand_P( element, SYSTEM_COMMAND_EXPORT_TARGET_NAME, SYSTEM_COMMAND_EXPORT_TARGET_DESCRIPTION, commander_exportTarget_func )
#endif
/// Premade function for not command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
bool commander_exportTarget_func( char *args, Stream *response, void* parent );

//-------- export function --------//
#define SYSTEM_COMMAND_EXPORT_NAME         "export"

#define SYSTEM_COMMAND_EXPORT_DESCRIPTION  "It will write the given value to the selected export target.\r\n\r\n"  \
                                        "usage: export [value]\r\n\r\n"                                         \
                                        "value: The value has to be an integer, or a float."

#define SYSTEM_COMMAND_EXPORT systemCommand( SYSTEM_COMMAND_EXPORT_NAME, SYSTEM_COMMAND_EXPORT_DESCRIPTION, commander_export_func )
#ifdef __AVR__
  #define SYSTEM_COMMAND_P_EXPORT( element ) systemCommand_P( element, SYSTEM_COMMAND_EXPORT_NAME, SYSTEM_COMMAND_EXPORT_DESCRIPTION, commander_export_func )
#endif
/// Premade function for not command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
bool commander_export_func( char *args, Stream *response, void* parent );

//-------- export function --------//
#define SYSTEM_COMMAND_MEMDUMP_NAME         "memDump"

#define SYSTEM_COMMAND_MEMDUMP_DESCRIPTION     "It is a tool to check data in the memory.\r\n\r\n"                     \
                                            "usage: memDump [base address][type][options]\r\n\r\n"                  \
                                            "base address: This is the start address of the memory region.\r\n"     \
                                            "type: Type of the data in the specified address. Valid options:\r\n"   \
                                            "  u8\r\n"                                                              \
                                            "  s8\r\n"                                                              \
                                            "  u16\r\n"                                                             \
                                            "  s16\r\n"                                                             \
                                            "  u32\r\n"                                                             \
                                            "  s32\r\n"                                                             \
                                            "Options:\r\n"                                                          \
										    "  -h, --hex\tSet the output format to hex.\r\n"                        \
										    "  -d, --dex\tSet the output format to decimal[ default ].\r\n"         \
										    "  -b, --bin\tSet the output format to binary.\r\n"                     \
										    "  -n, --number\t[int] Set the number of elements to be printed.\r\n"         \
										    "  -e, --end\tAddress of the last element to be printed.\r\n\r\n"       \
                                            "Example, print 10 bytes of data from address 0x00FF:\r\n"              \
										    "  memDump 0x00FF u8 -h -n 10"

#define SYSTEM_COMMAND_MEMDUMP    systemCommand( SYSTEM_COMMAND_MEMDUMP_NAME, SYSTEM_COMMAND_MEMDUMP_DESCRIPTION, commander_memDump_func )
#define SYSTEM_COMMAND_MEMDUMP_ND systemCommand( SYSTEM_COMMAND_MEMDUMP_NAME, "", commander_memDump_func )
#ifdef __AVR__
  #define SYSTEM_COMMAND_P_MEMDUMP( element ) systemCommand_P( element, SYSTEM_COMMAND_MEMDUMP_NAME, SYSTEM_COMMAND_MEMDUMP_DESCRIPTION, commander_memDump_func )
#endif
/// Premade function for not command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
bool commander_memDump_func( char *args, Stream *response, void* parent );
extern uint32_t memDumpAddressRanges[][ 2 ];

#endif