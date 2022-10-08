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

  sprintf( buff, "%d days, %d:%d:%d", day, hour, minute, second );

  response -> print( buff );

}




void commander_pinMode_func( char *args, Stream *response ){

  int pin;
  int direction;

  int argResult;

  argResult = sscanf( args, "%d %d", &pin, &direction );

  if( argResult != 2 ){

    response -> print( "Argument error!" );
    return;

  }

  if( pin < 0 || direction < 0 ){

    response -> print( "Argument error!" );
    return;

  }

  if( direction == 0 ){

    pinMode( pin, INPUT );

  }

  else if( direction == 1 ){

    pinMode( pin, OUTPUT );

  }

  else{

    response -> print( "Argument error! Second argument has to be 1 or 0!" );

  }

}

void commander_digitalWrite_func( char *args, Stream *response ){

  int pin;
  int state;

  int argResult;

  argResult = sscanf( args, "%d %d", &pin, &state );

  if( argResult != 2 ){

    response -> print( "Argument error!" );
    return;

  }

  if( pin < 0 || state < 0 ){

    response -> print( "Argument error!" );
    return;

  }

  if( state == 0 ){

    digitalWrite( pin, LOW );

  }

  else if( state == 1 ){

    digitalWrite( pin, HIGH );

  }

  else{

    response -> print( "Argument error! Second argument has to be 1 or 0!" );

  }

}

void commander_digitalRead_func( char *args, Stream *response ){

  int pin;

  int argResult;

  argResult = sscanf( args, "%d", &pin );

  if( argResult != 1 ){

    response -> print( "Argument error!" );
    return;

  }

  if( pin < 0 ){

    response -> print( "Argument error!" );
    return;

  }

  response -> print( digitalRead( pin ) );

}










void commander_ipconfig_func( char *args, Stream *response ){

  response -> println( (const char*)"Wi-Fi:\r\n" );

  response -> print( (const char*)"\tIP Address  . . : " );
  response -> println( WiFi.localIP() );

  response -> print( (const char*)"\tSubnet Mask . . : " );
  response -> println( WiFi.subnetMask() );

  response -> print( (const char*)"\tDefault Gateway : " );
  response -> println( WiFi.gatewayIP() );

}

void commander_wifiStat_func( char *args, Stream *response ){

  response -> println( (const char*)"Wi-Fi:\r\n" );

  response -> print( (const char*)"\tMode: " );

  switch( WiFi.getMode() ){

    case WIFI_MODE_STA:
      response -> println( "Station" );
      break;

    case WIFI_MODE_AP:
      response -> println( "Acces Point" );
      break;

    case WIFI_MODE_APSTA:
      response -> println( "Acces Point & Station" );
      break;

    default:
      response -> println( "Unknown" );
      break;

  }

  response -> print( (const char*)"\tRSSI: " );
  response -> print( WiFi.RSSI() );
  response -> println( "dBm" );

  response -> print( (const char*)"\tMAC : " );
  response -> println( WiFi.macAddress() );

}

void commander_wifiScan_func( char *args, Stream *response ){

  int num;
  int i;
  bool hasLocked = false;

  response -> print( (const char*)"Scanning for available networks... " );

  num = WiFi.scanNetworks();

  response -> println( (const char*)"[ OK ]:" );

  for( i = 0; i < num; i++ ){

    if( WiFi.encryptionType( i ) != WIFI_AUTH_OPEN ){

      response -> print( "\t* " );
      hasLocked = true;

    }

    else{

      response -> print( "\t  " );

    }

    response -> print( WiFi.SSID( i ) );

    response -> println();

  }

  if( hasLocked ){
    response -> print( (const char*)"\r\n * means closed network." );
  }

}

const char* neofetchLogo = {
  "\033[1;36m"
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
  "\033[0;37m"
};

void commander_neofetch_func( char *args, Stream *response ){

  uint32_t rowCounter = 0;

  response -> print( neofetchLogo );

  response -> print( "\033[" );
  response -> print( NEOFETCH_LOGO_HEIGHT );
  response -> print( "A\033[51C" );

  #ifdef NEOFETCH_FW_NAME
  response -> print( "\033[1;31mFW\033[0;37m: " );
  response -> print( NEOFETCH_FW_NAME );
  response -> print( "\r\n\033[51C" );
  rowCounter++;
  #endif

  #ifdef NEOFETCH_CPU_TYPE
  response -> print( "\033[1;31mCPU\033[0;37m: " );
  response -> print( NEOFETCH_CPU_TYPE );
  response -> print( "\r\n\033[51C" );
  rowCounter++;
  #endif

  #ifdef NEOFETCH_CPU_TYPE_AUTO
  response -> print( "\033[1;31mCPU\033[0;37m: " );

  #ifdef ESP32
  response -> print( "ESP32" );
  #elif ESP8266
  response -> print( "ESP8266" );
  #else
  response -> print( "Unknown" );
  #endif

  response -> print( "\r\n\033[51C" );
  rowCounter++;
  #endif

  #ifdef NEOFETCH_COMPILER
  response -> print( "\033[1;31mCompiler\033[0;37m: GCC " );
  response -> print( NEOFETCH_COMPILER );
  response -> print( "\r\n\033[51C" );
  rowCounter++;
  #endif

  #ifdef NEOFETCH_COMPILE_DATE
  response -> print( "\033[1;31mCompile Date\033[0;37m: " );
  response -> print( NEOFETCH_COMPILE_DATE );
  response -> print( "\r\n\033[51C" );
  rowCounter++;
  #endif

  #ifdef NEOFETCH_TERMINAL
  response -> print( "\033[1;31mTerminal\033[0;37m: " );
  response -> print( NEOFETCH_TERMINAL );
  response -> print( "\r\n\033[51C" );
  rowCounter++;
  #endif

  #ifdef NEOFETCH_COMMAND_PARSER
  response -> print( "\033[1;31mCMD Parser\033[0;37m: " );
  response -> print( NEOFETCH_COMMAND_PARSER );
  response -> print( "\r\n\033[51C" );
  rowCounter++;
  #endif

  #ifdef NEOFETCH_AUTHOR
  response -> print( "\033[1;31mAuthor\033[0;37m: " );
  response -> print( NEOFETCH_AUTHOR );
  response -> print( "\r\n\033[51C" );
  rowCounter++;
  #endif

  #ifdef NEOFETCH_LICENSE
  response -> print( "\033[1;31mLicense\033[0;37m: " );
  response -> print( NEOFETCH_LICENSE );
  response -> print( "\r\n\033[51C" );
  rowCounter++;
  #endif

  response -> print( "\033[" );
  response -> print( NEOFETCH_LOGO_HEIGHT - rowCounter );
  response -> print( "B" );

}


void commander_sin_func( char *args, Stream *response ){

  float f = atof( args );

  response -> print( sin( f ), 6 );

}

void commander_cos_func( char *args, Stream *response ){

  float f = atof( args );

  response -> print( cos( f ), 6 );

}
