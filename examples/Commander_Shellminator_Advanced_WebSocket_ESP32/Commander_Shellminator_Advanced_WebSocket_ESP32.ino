/*
 * Created on Oct. 2 2020
 *
 * Copyright (c) 2020 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Shellminator project.
 * Modified 2022.10.02
 *
*/

#include <WebSocketsServer.h> // <- https://github.com/Links2004/arduinoWebSockets
#include <WiFi.h>
#include <WebServer.h>
#include <WiFiClient.h>
#include "esp_wifi.h"

#include "Shellminator.hpp"
#include "Shellminator-IO.hpp"
#include "Shellminator-Browser-Response.hpp" // <- It contains the webpage data

#include "Commander-API.hpp"
#include "Commander-IO.hpp"
#include "Commander-API-Commands.hpp"

// Websocket port for Shellminator.
#define WEBSOCKET_PORT 81

// Webserver port for webpage and contents.
#define WEBSERVER_PORT 80

// WiFi credentials.
const char* ssid     = "your-wifi-ssid";
const char* password = "your-wifi-pass";

// Create websocket object.
WebSocketsServer webSocket = WebSocketsServer( WEBSOCKET_PORT );

// Create webserver object.
WebServer server( WEBSERVER_PORT );

// Create a Shellminator object, and initialize it to use WiFiServer
Shellminator shell( &webSocket );

const char logo[] =

"   _____ __         ____          _             __            \r\n"
"  / ___// /_  ___  / / /___ ___  (_)___  ____ _/ /_____  _____\r\n"
"  \\__ \\/ __ \\/ _ \\/ / / __ `__ \\/ / __ \\/ __ `/ __/ __ \\/ ___/\r\n"
" ___/ / / / /  __/ / / / / / / / / / / / /_/ / /_/ /_/ / /    \r\n"
"/____/_/ /_/\\___/_/_/_/ /_/ /_/_/_/ /_/\\__,_/\\__/\\____/_/     \r\n"
"                                                              \r\n"
;

// We have to create an object from Commander class.
Commander commander;

void handleIndex();
void handleXtermJs();
void handleXtermCss();
void handleXtermAddonWebLinks();
void handleNotFound();
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);

// We have to create the prototype functions for our commands.
// The arguments has to be the same for all command functions.
void cat_func( char *args, Stream *response );
void dog_func( char *args, Stream *response );
void sum_func( char *args, Stream *response );
void led_func( char *args, Stream *response );
void ledPWM_func( char *args, Stream *response );
void random_func( char *args, Stream *response );

// Commander API-tree
Commander::API_t API_tree[] = {
    apiElement( "cat", "Description for cat command.", cat_func ),
    apiElement( "dog", "Description for dog command.", dog_func ),
    apiElement( "led", "Toggle the buit-in LED.", led_func ),
    apiElement( "sum", "This function sums two number from the argument list.", sum_func ),
    apiElement( "ledPWM", "Set the brightness of the LED", ledPWM_func ),
    API_ELEMENT_MILLIS,
    API_ELEMENT_MICROS,
    API_ELEMENT_UPTIME,
    API_ELEMENT_PINMODE,
    API_ELEMENT_DIGITALWRITE,
    API_ELEMENT_DIGITALREAD,
    API_ELEMENT_ANALOGREAD,
    API_ELEMENT_IPCONFIG,
    API_ELEMENT_WIFISTAT,
    API_ELEMENT_WIFISCAN,
    API_ELEMENT_CONFIGTIME,
    API_ELEMENT_DATETIME,
    API_ELEMENT_NEOFETCH,
    API_ELEMENT_SIN,
    API_ELEMENT_COS,
    API_ELEMENT_ABS,
    API_ELEMENT_RANDOM,
    API_ELEMENT_NOT
};

void setup() {

  // Initialize Serial with 115200 baudrate.
  Serial.begin( 115200 );

  // If you using Atmega32U4, the code will wait, until
  // you open the serial port.
  while( !Serial );

  // Clear the terminal
  shell.clear();

  // Attach the logo.
  shell.attachLogo( logo );

  // Print start message
  Serial.println( "Program begin..." );

  // WiFi configuration section
  Serial.print( "Connect to  WiFi: " );
  Serial.print( ssid );

  WiFi.mode( WIFI_STA );
  WiFi.setSleep(WIFI_PS_NONE);
  WiFi.begin( ssid, password );

  while( WiFi.status() != WL_CONNECTED ){

    delay( 1000 );
    Serial.print( "." );

  }

  shell.beginServer();

  Serial.println( " [ OK ]" );

  Serial.println( "Connected!" );
  Serial.print( "Device IP: " );
  Serial.println( WiFi.localIP() );


  // There is an option to attach a debug channel to Commander.
  // It can be handy to find any problems during the initialization
  // phase. In this example we will use Serial for this.
  commander.attachDebugChannel( &Serial );

  // At start, Commander does not know anything about our commands.
  // We have to attach the API_tree array from the previous steps
  // to Commander to work properly.
  commander.attachTree( API_tree );

  // Initialize Commander.
  commander.init();

  shell.attachCommander( &commander );

  // initialize shell object.
  shell.begin( "arnold" );

  // Attach page handlers.
  server.on("/", handleIndex);
  server.on("/xterm.js", handleXtermJs);
  server.on("/xterm.css", handleXtermCss);
  server.on("/xterm-addon-web-links.js", handleXtermAddonWebLinks);
  server.onNotFound(handleNotFound);

  // Start webserver.
  server.begin();

  // Start websocket server.
  webSocket.begin();

  // Attach the webSocketEvent function to the websocket server.
  webSocket.onEvent(webSocketEvent);

}

void loop() {

  // Process everything.
  shell.update();
  server.handleClient();
  webSocket.loop();

  // Give some time to the other tasks.
  delay( 20 );

}

/// This is an example function for the cat command
void cat_func(char *args, Stream *response )
{

  response -> print("Hello from cat function!\r\n");

}

/// This is an example function for the dog command
void dog_func(char *args, Stream *response )
{

  response -> print("Hello from dog function!\r\n");

}

/// This is an example function for the led command
void led_func(char *args, Stream *response )
{

  // Toggle your LED pin here, if you have on your board
  // digitalWrite( LED_PIN, !digitalRead( LED_PIN ) );
  response -> print("LED toggle!\r\n");

}

/// This is an example function for the sum command
void sum_func(char *args, Stream *response )
{

  // These variables will hold the value of the
  // two numbers, that has to be summed.
  int a = 0;
  int b = 0;

  // This variable will hold the result of the
  // argument parser.
  int argResult;

  // This variable will hold the sum result.
  int sum = 0;

  argResult = sscanf( args, "%d %d", &a, &b );

  // We have to check that we parsed successfully  the two
  // numbers from the argument string.
  if( argResult != 2 ){

    // If we could not parse two numbers, we have an argument problem.
    // We print out the problem to the response channel.
    response -> print( "Argument error! Two numbers required, separated with a blank space.\r\n" );

    // Sadly we have to stop the command execution and return.
    return;

  }

  // Calculate the sum.
  sum = a + b;

  // Print out the result.
  response -> print( a );
  response -> print( " + " );
  response -> print( b );
  response -> print( " = " );
  response -> println( sum );

}

void ledPWM_func(char *args, Stream *response ){

  int pwm = 0;

  int argResult;

  argResult = sscanf( args, "%d", &pwm );

  if( argResult != 1 ){

    response -> print( "Argument error!" );

    // Sadly we have to stop the command execution and return.
    return;

  }

  if( pwm > 100 ){
    pwm = 100;
  }

  if( pwm < 0 ){
    pwm = 0;
  }

  response -> print( "New PWM value: " );
  response -> print( pwm );

}

// This function generates a response for the index page.
void handleIndex(){
  server.send_P(200, "text/html", shellminator_html_response, shellminator_html_response_len );
}

// This function generates a response for /xterm.js
void handleXtermJs(){
  server.send_P(200, "application/javascript", shellminator_xterm_js_response, shellminator_xterm_js_response_len );
}

// This function generates a response for /xterm.css
void handleXtermCss(){
  server.send_P(200, "text/css", shellminator_xterm_css_response, shellminator_xterm_css_response_len );
}

// This function generates a response for xterm-addon-web-links.js
void handleXtermAddonWebLinks(){
  server.send_P(200, "application/javascript", shellminator_xterm_addon_web_links_js_response, shellminator_xterm_addon_web_links_js_response_len );
}

// This function generates a response for everything else.
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

// This function will be called on websocket event.
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

  // This implementation only works woth one websocket based terminal client.
  // Every websocket client get an identifier from 0 - 255. The num argument
  // is this identifier. We have to close every other client, than 0.
  if( num > 0 ){

    // Send the problem to the client, than close it.
    webSocket.sendTXT( num, "\r\nNo more connections allowed!\r\n" );
    webSocket.disconnect( num );
    return;

  }

  // Depending on the event, we have to decide the next action.
  switch( type ){

    // The client disconnected.
    case WStype_DISCONNECTED:

      // Currently, just print out the event.
      Serial.printf("[%u] Disconnected!\n", num);
      break;

    // New connection.
    case WStype_CONNECTED:

      // Clear the screen and print the logo with the banner.
      shell.clear();
      shell.drawLogo();
      shell.printBanner();
      break;

    // Text data incoming
    case WStype_TEXT:

      // Print to serial, just for debug.
      Serial.printf("[%u] get Text: %s\n", num, payload);

      // In the Shellminator-IO files, the websocket channel
      // is implemented as a circular buffer. The incoming data
      // from the clients has to be pushed to this circular buffer
      // in the websocket event.
      shell.webSocketPush( payload, length );
      break;

  }

}
