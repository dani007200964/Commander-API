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

#include "../Commander-API-Commands.hpp"

void printCommandNotImplemented( Stream* channel_p ){

	// Check and handle invalid channel pointer.
	if( channel_p == NULL ){
		return;
	}

  channel_p -> print( __CONST_TXT__( "Command not implemented!" ) );

}

#if defined( ESP32 ) || ( ESP8266 )

void commander_ipconfig_func( char *args, Stream *response, void* parent ){

  response -> println( "Wi-Fi:\r\n" );

  response -> print( "\tIP Address  . . : " );
  response -> println( WiFi.localIP() );

  response -> print( "\tSubnet Mask . . : " );
  response -> println( WiFi.subnetMask() );

  response -> print( "\tDefault Gateway : " );
  response -> println( WiFi.gatewayIP() );

}

void commander_wifiStat_func( char *args, Stream *response, void* parent ){

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

void commander_wifiScan_func( char *args, Stream *response, void* parent ){

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

void commander_configTime_func( char *args, Stream *response, void* parent ){

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

    Commander::printArgumentError( response );
    return;

  }

}

void commander_dateTime_func( char *args, Stream *response, void* parent ){

  struct tm timeInfo;

  if( !getLocalTime( &timeInfo ) ){

    response -> print( "Failed to obtain time!" );
    return;

  }

  response -> print( &timeInfo, "%A, %B %d %Y %H:%M:%S" );

}

#endif