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

#include "Commander-API-Commands.hpp"

#if defined(ARDUINO) && defined(__AVR__)
#define FF(s) F(s)
#else
#define FF(s) (s)
#endif


void commander_millis_func( char *args, Stream *response ){

  char buff[ 20 ];

  sprintf( buff, "%lu", millis() );

  response -> print( buff );

}

void commander_micros_func( char *args, Stream *response ){

  char buff[ 20 ];

  sprintf( buff, "%lu", micros() );

  response -> print( buff );

}

void commander_uptime_func( char *args, Stream *response ){

  char buff[ 20 ];

  int day;
  int hour;
  int minute;
  unsigned long second;

  second = millis() / 1000;

  day = ( second / 24 ) / 3600;
  second %= (unsigned long)24 * 3600;

  hour = second / 3600;
  second %= 3600;

  minute = second / 60;
  second %= 60;

  snprintf( buff, sizeof( buff ), "%d days, %d:%02d:%02lu", day, hour, minute, second );

  response -> print( buff );

}




void commander_pinMode_func( char *args, Stream *response ){

  int pin;
  int direction;

  int argResult;

  argResult = sscanf( args, "%d %d", &pin, &direction );

  if( argResult != 2 ){
    response -> print( FF( "Argument error!" ) );
    return;
  }

  if( pin < 0 || direction < 0 ){
    response -> print( FF( "Argument error!" ) );
    return;
  }

  if( direction == 0 ){

    pinMode( pin, INPUT );

  }

  else if( direction == 1 ){

    pinMode( pin, OUTPUT );

  }

  else{
    response -> print( FF( "Argument error! Second argument has to be 1 or 0!" ) );
  }

}

void commander_digitalWrite_func( char *args, Stream *response ){

  int pin;
  int state;

  int argResult;

  argResult = sscanf( args, "%d %d", &pin, &state );

  if( argResult != 2 ){

    response -> print( FF( "Argument error!" ) );
    return;

  }

  if( pin < 0 || state < 0 ){

    response -> print( FF( "Argument error!" ) );
    return;

  }

  if( state == 0 ){

    digitalWrite( pin, LOW );

  }

  else if( state == 1 ){

    digitalWrite( pin, HIGH );

  }

  else{
    response -> print( FF( "Argument error! Second argument has to be 1 or 0!" ) );
  }

}

void commander_digitalRead_func( char *args, Stream *response ){

  int pin;

  int argResult;

  argResult = sscanf( args, "%d", &pin );

  if( argResult != 1 ){
    response -> print( FF( "Argument error!" ) );
    return;
  }

  if( pin < 0 ){
    response -> print( FF( "Argument error!" ) );
    return;
  }

  response -> print( digitalRead( pin ) );

}

#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_LEONARDO) || defined( ESP32 ) || ( ESP8266 )

void commander_analogRead_func( char *args, Stream *response ){

  int pin;

  int argResult;

  argResult = sscanf( args, "%d", &pin );

  if( argResult != 1 ){

    response -> print( FF( "Argument error!" ) );
    return;

  }

  #if defined( ESP32 ) || ( ESP8266 )

  if( pin < 0 ){

    response -> print( FF( "Argument error!" ) );
    return;

  }

  #else

  switch( pin ){

    case 0:
      pin = A0;
      break;

    case 1:
      pin = A1;
      break;

    case 2:
      pin = A2;
      break;

    case 3:
      pin = A3;
      break;

    case 4:
      pin = A5;
      break;

    case 5:
      pin = A5;
      break;

    #ifdef ARDUINO_AVR_LEONARDO
    case 6:
      pin = A6;
      break;

    case 7:
      pin = A7;
      break;

    case 8:
      pin = A8;
      break;

    case 9:
      pin = A9;
      break;

    case 10:
      pin = A10;
      break;

    case 11:
      pin = A11;
      break;
    #endif  // ARDUINO_AVR_LEONARDO

    default:
      response -> print( FF( "Argument error!" ) );
      return;

  }
  #endif

  response -> print( analogRead( pin ) );

}

#endif

#if defined( ESP32 ) || ( ESP8266 )

void commander_ipconfig_func( char *args, Stream *response ){

  response -> println( "Wi-Fi:\r\n" );

  response -> print( "\tIP Address  . . : " );
  response -> println( WiFi.localIP() );

  response -> print( "\tSubnet Mask . . : " );
  response -> println( WiFi.subnetMask() );

  response -> print( "\tDefault Gateway : " );
  response -> println( WiFi.gatewayIP() );

}

void commander_wifiStat_func( char *args, Stream *response ){

  response -> println( "Wi-Fi:\r\n" );

  response -> print( "\tMode: " );

  switch( WiFi.getMode() ){

    #ifdef ESP32

    case WIFI_MODE_STA:
      response -> println( "Station" );
      break;

    case WIFI_MODE_AP:
      response -> println( "Access Point" );
      break;

    case WIFI_MODE_APSTA:
      response -> println( "Access Point & Station" );
      break;

    #endif

    #ifdef ESP8266

    case WIFI_STA:
      response -> println( "Station" );
      break;

    case WIFI_AP:
      response -> println( "Access Point" );
      break;

    case WIFI_AP_STA:
      response -> println( "Access Point & Station" );
      break;

    #endif

    default:
      response -> println( "Unknown" );
      break;



  }

  response -> print( "\tRSSI: " );
  response -> print( WiFi.RSSI() );
  response -> println( "dBm" );

  response -> print( "\tMAC : " );
  response -> println( WiFi.macAddress() );

}

void commander_wifiScan_func( char *args, Stream *response ){

  int num;
  int i;
  bool hasLocked = false;

  response -> print( "Scanning for available networks... " );

  num = WiFi.scanNetworks();

  response -> println( "[ OK ]:" );

  for( i = 0; i < num; i++ ){

    #ifdef ESP32

    if( WiFi.encryptionType( i ) != WIFI_AUTH_OPEN ){

      response -> print( "\t* " );
      hasLocked = true;

    }

    #endif

    #ifdef ESP8266

    if( WiFi.encryptionType( i ) != ENC_TYPE_NONE ){

      response -> print( "\t* " );
      hasLocked = true;

    }

    #endif

    else{

      response -> print( "\t  " );

    }

    response -> print( WiFi.SSID( i ) );

    response -> println();

  }

  if( hasLocked ){
    response -> print( "\r\n * means closed network." );
  }

}

#endif

#ifdef ESP32

void commander_configTime_func( char *args, Stream *response ){

  int gmtOffset_sec;
  int daylightOffset_sec;
  char ntpServer[32] = "";
  int argResult;

  argResult = sscanf( args, "%d %d %s", &gmtOffset_sec, &daylightOffset_sec, ntpServer );

  if( argResult == 3 ){

    configTime( gmtOffset_sec, daylightOffset_sec, ntpServer );
    response -> print( "Time configured." );
    return;

  }

  argResult = sscanf( args, "%d %d", &gmtOffset_sec, &daylightOffset_sec );

  if( argResult == 2 ){

    configTime( gmtOffset_sec, daylightOffset_sec, "pool.ntp.org" );
    response -> print( "Time configured with default NTP server: pool.ntp.org" );
    return;

  }

  else{

    response -> print( "Argument error!" );
    return;

  }

}

void commander_dateTime_func( char *args, Stream *response ){

  struct tm timeInfo;

  if( !getLocalTime( &timeInfo ) ){

    response -> print( "Failed to obtain time!" );
    return;

  }

  response -> print( &timeInfo, "%A, %B %d %Y %H:%M:%S" );

}

#endif

void commander_neofetch_func( char *args, Stream *response ){

  uint32_t rowCounter = 0;

  response -> print( FF(
      "\r\n\033[1;36m"
      "      :=*%@@@@%#+-             :=*%@@@@%#+-       \r\n"
      "    +%@@@@@@@@@@@@@#-       :*@@@@@@@@@@@@@@*:    \r\n"
      "  =@@@@@*=-:::-+#@@@@@=   :#@@@@%*=::::-+%@@@@#.  \r\n"
      " *@@@@-          .=@@@@%:*@@@@*:          .#@@@@. \r\n"
      "+@@@%               +@@@@@@@%:     .##      +@@@% \r\n"
      "@@@@-   .+++++++     -@@@@@*     -+*@@++-    @@@@:\r\n"
      "@@@@-   .+++++++     .%@@@@+     =+*@@*+-    %@@@:\r\n"
      "*@@@#               =@@@@@@@#.     .##      -@@@@ \r\n"
      " #@@@%:           -%@@@@=#@@@@+.           +@@@@: \r\n"
      "  *@@@@%=:.   :-*@@@@@*   -%@@@@#=:.  .:-*@@@@%:  \r\n"
      "   :*@@@@@@@@@@@@@@@+.      -#@@@@@@@@@@@@@@%=    \r\n"
      "      -+#@@@@@@%*=:            -+#@@@@@@%*=.      \r\n"
      "\033[0;37m" ) );

  response -> print( FF( "\033[" ) );
  response -> print( NEOFETCH_LOGO_HEIGHT );
  response -> print( FF( "A\033[51C" ) );

  #ifdef NEOFETCH_FW_NAME
  response -> print( FF( "\033[1;31mFW\033[0;37m: " ) );
  response -> print( FF( NEOFETCH_FW_NAME ) );
  response -> print( FF( "\r\n\033[51C" ) );
  rowCounter++;
  #endif

  #ifdef NEOFETCH_CPU_TYPE
  response -> print( FF( "\033[1;31mCPU\033[0;37m: " ) );
  response -> print( FF( NEOFETCH_CPU_TYPE ) );
  response -> print( FF( "\r\n\033[51C" ) );
  rowCounter++;
  #endif

  #ifdef NEOFETCH_CPU_TYPE_AUTO
  response -> print( FF( "\033[1;31mCPU\033[0;37m: " ) );

  #ifdef ARDUINO_AVR_UNO
  response -> print( FF( "AVR - Arduino UNO" ) );
  #elif ARDUINO_AVR_LEONARDO
  response -> print( FF( "AVR - Arduino Leonardo" ) );
  #elif ESP32
  response -> print( FF( "ESP32" ) );
  #elif ESP8266
  response -> print( FF( "ESP8266" ) );
  #else
  response -> print( FF( "Unknown" ) );
  #endif

  response -> print( FF( "\r\n\033[51C" ) );
  rowCounter++;
  #endif

  #ifdef NEOFETCH_COMPILER
  response -> print( FF( "\033[1;31mCompiler\033[0;37m: GCC " ) );
  response -> print( FF( NEOFETCH_COMPILER ) );
  response -> print( FF( "\r\n\033[51C" ) );
  rowCounter++;
  #endif

  #ifdef NEOFETCH_COMPILE_DATE
  response -> print( FF( "\033[1;31mCompile Date\033[0;37m: " ) );
  response -> print( FF( NEOFETCH_COMPILE_DATE ) );
  response -> print( FF( "\r\n\033[51C" ) );
  rowCounter++;
  #endif

  #ifdef NEOFETCH_TERMINAL
  response -> print( FF( "\033[1;31mTerminal\033[0;37m: " ) );
  response -> print( FF( NEOFETCH_TERMINAL ) );
  response -> print( FF( "\r\n\033[51C" ) );
  rowCounter++;
  #endif

  #ifdef NEOFETCH_COMMAND_PARSER
  response -> print( FF( "\033[1;31mCMD Parser\033[0;37m: " ) );
  response -> print( FF( NEOFETCH_COMMAND_PARSER ) );
  response -> print( FF( "\r\n\033[51C" ) );
  rowCounter++;
  #endif

  #ifdef NEOFETCH_AUTHOR
  response -> print( FF( "\033[1;31mAuthor\033[0;37m: " ) );
  response -> print( FF( NEOFETCH_AUTHOR ) );
  response -> print( FF( "\r\n\033[51C" ) );
  rowCounter++;
  #endif

  #ifdef NEOFETCH_LICENSE
  response -> print( FF( "\033[1;31mLicense\033[0;37m: " ) );
  response -> print( FF( NEOFETCH_LICENSE ) );
  response -> print( FF( "\r\n\033[51C" ) );
  rowCounter++;
  #endif

  response -> print( FF( "\033[" ) );
  response -> print( NEOFETCH_LOGO_HEIGHT - rowCounter );
  response -> print( 'B' );

}


void commander_reboot_func( char *args, Stream *response ){

  response -> println( FF( "Rebooting..." ) );

  #if defined( ESP32 ) || ( ESP8266 )

  ESP.restart();

  #elif __AVR__

  wdt_enable( WDTO_15MS );
  while( 1 );

  #endif

}


void commander_sin_func( char *args, Stream *response ){

  float f = atof( args );

  response -> print( sin( f ), 6 );

}

void commander_cos_func( char *args, Stream *response ){

  float f = atof( args );

  response -> print( cos( f ), 6 );

}

void commander_not_func( char *args, Stream *response ){

  int num;
  int argResult;

  argResult = sscanf( args, "%d", &num );

  if( argResult != 1 ){

    response -> print( FF( "Argument error!" ) );
    return;

  }

  response -> print( !num );

}

void commander_random_func( char *args, Stream *response ){

  int min;
  int max;
  int argResult;

  argResult = sscanf( args, "%d %d", &min, &max );

  if( argResult != 2 ){

    response -> print( FF( "Argument error!" ) );

    return;

  }

  if( min >= max ){

    response -> print( FF( "Argument error! First argument is min, second is max!" ) );

    return;

  }

  response -> print( random( min, max ) );

}

void commander_abs_func( char *args, Stream *response ){

  float f = atof( args );

  response -> print( abs( f ) );

}
