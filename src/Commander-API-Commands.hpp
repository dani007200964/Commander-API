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
#endif

#include <math.h>

#include "Commander-API.hpp"

//-------- Timing functions --------//

#define API_ELEMENT_MICROS apiElement( "micros", "Returns the number of microseconds passed since the program started.", commander_micros_func )
void commander_micros_func( char *args, Stream *response );

#define API_ELEMENT_MILLIS apiElement( "millis", "Returns the number of milliseconds passed since the program started.", commander_millis_func )
void commander_millis_func( char *args, Stream *response );

#define API_ELEMENT_UPTIME apiElement( "uptime", "Returns the time passed since the program started.", commander_uptime_func )
void commander_uptime_func( char *args, Stream *response );





//-------- Pure awesomeness --------//

#define API_ELEMENT_NEOFETCH apiElement( "neofetch", "Nice looking system information.", commander_neofetch_func )
void commander_neofetch_func( char *args, Stream *response );



//-------- Digital I-O functions --------//

#define API_ELEMENT_PINMODE apiElement( "pinMode", "Set the direction of a pin.\r\n\tExample: pinMode [ Pin Number ] [ Direction ]\r\n\t[ Pin Number ] - The number ofthe pin. Typically printed on the board.\r\n\t[ Direction ] - 0 means input, 1 means output.", commander_pinMode_func )
void commander_pinMode_func( char *args, Stream *response );

#define API_ELEMENT_DIGITALWRITE apiElement( "digitalWrite", "Set the state of an output pin.\r\n\tExample: digitalWrite [ Pin Number ] [ State ]\r\n\t[ Pin Number ] - The number ofthe pin. Typically printed on the board.\r\n\t[ State ] - 0 means low, 1 means high.", commander_digitalWrite_func )
void commander_digitalWrite_func( char *args, Stream *response );

#define API_ELEMENT_DIGITALREAD apiElement( "digitalRead", "Read the state of a pin.\r\n\tExample: digitalRead [ Pin Number ]\r\n\t[ Pin Number ] - The number ofthe pin. Typically printed on the board.\r\n\t[ Returns ] - 0 means low, 1 means high.", commander_digitalRead_func )
void commander_digitalRead_func( char *args, Stream *response );

//-------- WiFi functions --------//

#define API_ELEMENT_IPCONFIG apiElement( "ipconfig", "Print network information.", commander_ipconfig_func )
void commander_ipconfig_func( char *args, Stream *response );

#define API_ELEMENT_WIFISTAT apiElement( "wifiStat", "Print WiFi information.", commander_wifiStat_func )
void commander_wifiStat_func( char *args, Stream *response );

#define API_ELEMENT_WIFISCAN apiElement( "wifiScan", "Search for available networks around.", commander_wifiScan_func )
void commander_wifiScan_func( char *args, Stream *response );


//-------- Math functions --------//

#define API_ELEMENT_SIN apiElement( "sin", "Sine function. The input is in radians.", commander_sin_func )
void commander_sin_func( char *args, Stream *response );

#define API_ELEMENT_COS apiElement( "cos", "Cosine function. The input is in radians.", commander_cos_func )
void commander_cos_func( char *args, Stream *response );


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
