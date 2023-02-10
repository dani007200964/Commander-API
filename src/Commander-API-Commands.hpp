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

/// Arduino detection
#ifdef ARDUINO
#include "Arduino.h"
#include "Wire.h"
#endif

#include <math.h>

#ifdef __AVR__
  #include <avr/wdt.h>
#endif

#ifdef ESP32

  #include "time.h"

#endif

#include "Commander-API.hpp"

//-------- System functions --------//

#define API_ELEMENT_REBOOT apiElement( "reboot", "Reboots the device.", commander_reboot_func )
#ifdef __AVR__
  #define API_ELEMENT_P_REBOOT( element ) apiElement_P( element, "reboot", "Reboots the device.", commander_reboot_func )
#endif
/// Premade function for reboot command. It reboots the core.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_reboot_func( char *args, Stream *response );

//-------- Timing functions --------//

#define API_ELEMENT_MICROS apiElement( "micros", "Returns the number of microseconds passed since the program started.", commander_micros_func )
#ifdef __AVR__
  #define API_ELEMENT_P_MICROS( element ) apiElement_P( element, "micros", "Returns the number of microseconds passed since the program started.", commander_micros_func )
#endif
/// Premade function for micros command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_micros_func( char *args, Stream *response );

#define API_ELEMENT_MILLIS apiElement( "millis", "Returns the number of milliseconds passed since the program started.", commander_millis_func )
#ifdef __AVR__
  #define API_ELEMENT_P_MILLIS( element ) apiElement_P( element, "millis", "Returns the number of milliseconds passed since the program started.", commander_millis_func )
#endif
/// Premade function for millis command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_millis_func( char *args, Stream *response );

#define API_ELEMENT_UPTIME apiElement( "uptime", "Returns the time passed since the program started.", commander_uptime_func )
#ifdef __AVR__
  #define API_ELEMENT_P_UPTIME( element ) apiElement_P( element, "uptime", "Returns the time passed since the program started.", commander_uptime_func )
#endif
/// Premade function for uptime command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_uptime_func( char *args, Stream *response );

//-------- Pure awesomeness --------//

#define API_ELEMENT_NEOFETCH apiElement( "neofetch", "Nice looking system information.", commander_neofetch_func )
#ifdef __AVR__
  #define API_ELEMENT_P_NEOFETCH( element ) apiElement_P( element, "neofetch", "Nice looking system information.", commander_neofetch_func )
#endif
/// Premade function for neofetch command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_neofetch_func( char *args, Stream *response );



//-------- Digital I-O functions --------//

#define API_ELEMENT_PINMODE apiElement( "pinMode", "Set the direction of a pin.\r\n\tExample: pinMode [ Pin Number ] [ Direction ]\r\n\t[ Pin Number ] - The number ofthe pin. Typically printed on the board.\r\n\t[ Direction ] - 0 means input, 1 means output.", commander_pinMode_func )
#ifdef __AVR__
  #define API_ELEMENT_P_PINMODE( element ) apiElement_P( element, "pinMode", "Set the direction of a pin.\r\n\tExample: pinMode [ Pin Number ] [ Direction ]\r\n\t[ Pin Number ] - The number ofthe pin. Typically printed on the board.\r\n\t[ Direction ] - 0 means input, 1 means output.", commander_pinMode_func )
#endif
/// Premade function for pinMode command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_pinMode_func( char *args, Stream *response );

#define API_ELEMENT_DIGITALWRITE apiElement( "digitalWrite", "Set the state of an output pin.\r\n\tExample: digitalWrite [ Pin Number ] [ State ]\r\n\t[ Pin Number ] - The number ofthe pin. Typically printed on the board.\r\n\t[ State ] - 0 means low, 1 means high.", commander_digitalWrite_func )
#ifdef __AVR__
  #define API_ELEMENT_P_DIGITALWRITE( element ) apiElement_P( element, "digitalWrite", "Set the state of an output pin.\r\n\tExample: digitalWrite [ Pin Number ] [ State ]\r\n\t[ Pin Number ] - The number ofthe pin. Typically printed on the board.\r\n\t[ State ] - 0 means low, 1 means high.", commander_digitalWrite_func )
#endif
/// Premade function for digitalWrite command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_digitalWrite_func( char *args, Stream *response );

#define API_ELEMENT_DIGITALREAD apiElement( "digitalRead", "Read the state of a pin.\r\n\tExample: digitalRead [ Pin Number ]\r\n\t[ Pin Number ] - The number ofthe pin. Typically printed on the board.\r\n\t[ Returns ] - 0 means low, 1 means high.", commander_digitalRead_func )
#ifdef __AVR__
  #define API_ELEMENT_P_DIGITALREAD( element ) apiElement_P( element, "digitalRead", "Read the state of a pin.\r\n\tExample: digitalRead [ Pin Number ]\r\n\t[ Pin Number ] - The number ofthe pin. Typically printed on the board.\r\n\t[ Returns ] - 0 means low, 1 means high.", commander_digitalRead_func )
#endif
/// Premade function for digitalRead command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_digitalRead_func( char *args, Stream *response );

//-------- Analog I-O functions --------//

#define API_ELEMENT_ANALOGREAD apiElement( "analogRead", "Generate an ADC measurement on a pin.\r\n\tExample: analogRead [ Pin Number ]\r\n\t[ Pin Number ] - The number ofthe pin. Typically printed on the board.\r\n\t[ Returns ] - The raw ADC sample.", commander_analogRead_func )
#ifdef __AVR__
  #define API_ELEMENT_P_ANALOGREAD( element ) apiElement_P( element, "analogRead", "Generate an ADC measurement on a pin.\r\n\tExample: analogRead [ Pin Number ]\r\n\t[ Pin Number ] - The number ofthe pin. Typically printed on the board.\r\n\t[ Returns ] - The raw ADC sample.", commander_analogRead_func )
#endif
/// Premade function for analogRead command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_analogRead_func( char *args, Stream *response );

//-------- WiFi functions --------//

#if defined( ESP32 ) || ( ESP8266 )

#define API_ELEMENT_IPCONFIG apiElement( "ipconfig", "Print network information.", commander_ipconfig_func )
/// Premade function for ipconfig command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_ipconfig_func( char *args, Stream *response );

#define API_ELEMENT_WIFISTAT apiElement( "wifiStat", "Print WiFi information.", commander_wifiStat_func )
/// Premade function for wifiStat command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_wifiStat_func( char *args, Stream *response );

#define API_ELEMENT_WIFISCAN apiElement( "wifiScan", "Search for available networks around.", commander_wifiScan_func )
/// Premade function for wifiScan command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_wifiScan_func( char *args, Stream *response );

#endif

#ifdef ESP32

#define API_ELEMENT_CONFIGTIME apiElement( "configTime", "Configure NTP time settings.\r\n\tExample: configTime [ GMT Offset Sec ] [ DL Offset Sec ] [ Server ]\r\n\t[ GMT Offset Sec ] - UTC offset for your timezone in seconds.\r\n\t[ GMT Offset Sec ] - Daylight offset in sec.\r\n\t[ Server ] - NTP Server Address( optional, default: pool.ntp.org )", commander_configTime_func )
/// Premade function for wifiScan command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_configTime_func( char *args, Stream *response );

#define API_ELEMENT_DATETIME apiElement( "dateTime", "Returns the NTP synchronised date and time.", commander_dateTime_func )
/// Premade function for wifiScan command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_dateTime_func( char *args, Stream *response );

#endif

//-------- Math functions --------//

#define API_ELEMENT_SIN apiElement( "sin", "Sine function. The input is in radians.", commander_sin_func )
#ifdef __AVR__
  #define API_ELEMENT_P_SIN( element ) apiElement_P( element, "sin", "Sine function. The input is in radians.", commander_sin_func )
#endif
/// Premade function for sin command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_sin_func( char *args, Stream *response );

#define API_ELEMENT_COS apiElement( "cos", "Cosine function. The input is in radians.", commander_cos_func )
#ifdef __AVR__
  #define API_ELEMENT_P_COS( element ) apiElement_P( element, "cos", "Cosine function. The input is in radians.", commander_cos_func )
#endif
/// Premade function for cos command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_cos_func( char *args, Stream *response );

#define API_ELEMENT_ABS apiElement( "abs", "Calculates the absolute value of a number.", commander_abs_func )
#ifdef __AVR__
  #define API_ELEMENT_P_ABS( element ) apiElement_P( element, "abs", "Calculates the absolute value of a number.", commander_abs_func )
#endif
/// Premade function for abs command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_abs_func( char *args, Stream *response );

#define API_ELEMENT_RANDOM apiElement( "random", "Generates a random number between the parameters.\r\n\tExample: random [ min ] [ max ]\r\n\t[ min ] - Lower integer bound\r\n\t[ max ] - Upper integer bound", commander_random_func )
#ifdef __AVR__
  #define API_ELEMENT_P_RANDOM( element ) apiElement_P( element, "random", "Generates a random number between the parameters.\r\n\tExample: random [ min ] [ max ]\r\n\t[ min ] - Lower integer bound\r\n\t[ max ] - Upper integer bound", commander_random_func )
#endif
/// Premade function for random command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_random_func( char *args, Stream *response );

#define API_ELEMENT_NOT apiElement( "not", "Logical not. If the input is 0 returns 1. Any other cases it returns 0.", commander_not_func )
#ifdef __AVR__
  #define API_ELEMENT_P_NOT( element ) apiElement_P( element, "not", "Logical not. If the input is 0 returns 1. Any other cases it returns 0.", commander_not_func )
#endif
/// Premade function for not command.
/// @param args Pointer to the argument string.
/// @param response Response channel for messages.
void commander_not_func( char *args, Stream *response );

/// The neofetch logo have this many lines.
#define NEOFETCH_LOGO_HEIGHT 12

// Uncomment the unnecessary fields.
// Modify the required ones to your application.
#define NEOFETCH_FW_NAME "Firmware-name"
//#define NEOFETCH_CPU_TYPE "CPU-Type"
#define NEOFETCH_CPU_TYPE_AUTO
#define NEOFETCH_COMPILER __VERSION__
#define NEOFETCH_COMPILE_DATE __DATE__
#define NEOFETCH_TERMINAL "Shellminator"
#define NEOFETCH_COMMAND_PARSER "Commander"
#define NEOFETCH_AUTHOR "Daniel Hajnal"
#define NEOFETCH_LICENSE "MIT"
