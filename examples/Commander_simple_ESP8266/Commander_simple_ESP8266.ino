/*
 * Created on April 24 2022
 *
 * Copyright (c) 2022 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2022.04.24
 *
 * This is a simple example sketch that shows how
 * to use Commander-API library.
*/

// Necessary includes
#include <ESP8266WiFi.h>
#include "Commander-API.hpp"
#include "Commander-IO.hpp"

// This example assumes that there is a LED on GPIO-2,
// like on ESP32 NodeMCU boards.
#define LED_PIN 2

// We have to create an object from Commander class.
Commander commander;

// We have to create the prototypes functions for our commands.
// The arguments has to be the same for all command functions.
void cat_func( char *args, commandResponse *response );
void dog_func( char *args, commandResponse *response );
void sum_func( char *args, commandResponse *response );
void led_func( char *args, commandResponse *response );

// To tell Commander how many commands we have, it is necessary
// to create an array, that holds soma data that represents our
// commands. The type of this array must be Commander::API_t.
// To simplify the command registration, there is a macro called
// apiElement. This macro helps to add command data to this array.
// -The first argument is the name of the command. Commander will
//  search the commands by it's name.
// -The second argument is the description for the command.
//  If you use the help command, or '?' character after the command
//  name, Commander will response with it's description.
// -The third argument is the wrapper function, that has been defined
//  in the previous step.
Commander::API_t API_tree[] = {
    apiElement( "cat", "Description for cat command.", cat_func ),
    apiElement( "dog", "Description for dog command.", dog_func ),
    apiElement( "led", "Toggle the buit-in LED.", led_func ),
    apiElement( "sum", "This function sums two number from the argument list.", sum_func )
};

// WiFi credentials.
const char* ssid     = "your-wifi-ssid";
const char* password = "your-wifi-pass";

#define SERVER_PORT 11000

// Create an instance of the server.
// It will be available on port 10001.
WiFiServer server( SERVER_PORT );


void setup() {

  // Set the LED pin to output, and turn it off.
  pinMode( LED_PIN, OUTPUT );
  digitalWrite( LED_PIN, 0 );

  // In this example we will use the Serial for communication,
  // so we have to initialize it.
  Serial.begin( 115200 );

  // Step 1.
  Serial.println( "Step 1." );

  // There is an option to attach a debug channel to Commander.
  // It can be handy to find any problems during the initialization
  // phase. In this example we will use Serial for this.
  commander.attachDebugChannel( &Serial );

  // At start Commander des not know anything about our commands.
  // We have to attach the API_tree array from the previus steps
  // to Commander to work properly.
  commander.attachTree( API_tree );

  // Step 2.
  Serial.println();
  Serial.println( "Step 2." );

  // After we attached the API_tree, Commander has to initialise
  // itself for the fastes runtime possible. It creates a balanced
  // binary tree from the API_tree to boost the search speed.
  // This part uses some recursion, to make the code space small.
  // But recursion is a bit stack hungry, so please initialise
  // Commander at the beginning of your code to prevent stack-overlow.
  commander.init();


  // Example 1.
  Serial.println();
  Serial.println( "Example 1." );

  // At this point Commander is initialised and functional, so lets try it.
  // To execute a command we have to use the execute command. Let's try
  // the led command. This command just toggles the built-in LED.
  commander.execute( "led" );

  // Example 2.
  Serial.println();
  Serial.println( "Example 2." );

  // The most helpful command is help. It prints out all of the available
  // commands.
  commander.execute( "help" );

  // Example 3.
  Serial.println();
  Serial.println( "Example 3." );

  // After the previous step we can see, that we did not see anything.
  // This is because we did not gave any response channel to the execute
  // function. Let's set Serial as response channel.
  commander.execute( "help", &Serial );

  // Example 4.
  Serial.println();
  Serial.println( "Example 4." );

  // To print the description data as well, we have to pass '-d' as argument
  // after the help command.
  commander.execute( "help -d", &Serial );

  // Example 5.
  Serial.println();
  Serial.println( "Example 5." );
  // If we want to print out the description for only one command, we can
  // use the '?' operator after the command name.
  commander.execute( "led?", &Serial );

  // Example 6.
  Serial.println();
  Serial.println( "Example 6." );
  // Now lets try the remaining functions.
  commander.execute( "cat", &Serial );
  commander.execute( "dog", &Serial );
  commander.execute( "sum", &Serial );

  // Example 7.
  Serial.println();
  Serial.println( "Example 7." );
  // As we can see the cat and dog functions worked as expected,
  // but the sum function gave argument error. This happened
  // because we did not gave any arguments to that function.
  // Giving arguments to a command is very simple. You just have
  // to give an argument string after the command, separated by
  // a blank space. Commander will transfer the argument string
  // to the command's function. Lets try to sum 10 and 15.
  commander.execute( "sum 10 15", &Serial );

  // Example 8.
  Serial.println();
  Serial.println( "Example 8." );
  // Now lets try to execute a command that does not exist,
  // and see what happens.
  commander.execute( "reboot", &Serial );

  Serial.println();
  Serial.println( "Eaxmple session finished." );

  // Configuring WiFi for connection.
  Serial.println();
  Serial.print( "Connecting to: " );
  Serial.println( ssid );

  WiFi.mode( WIFI_STA );
  WiFi.begin( ssid, password );

  while( WiFi.status() != WL_CONNECTED ){
    delay( 500 );
    Serial.print( "." );
  }

  Serial.println();
  Serial.println( "Connected!" );
  Serial.println( "Starting server..." );
  Serial.print( "Device IP: " );
  Serial.print( WiFi.localIP() );
  Serial.print( " at port: " );
  Serial.println( SERVER_PORT );
  Serial.println( "Now you can play with commander with serial port or with socket." );
  Serial.println( "To try socket communication I suggest PuTTY." );


  server.begin();

}

// Continous example.
// In the loop function there is a simple example to
// read commands from Serial in runtime. You can use
// the Serial monitor to try it. Set the line ending
// to new-line and play with the commands.

// This is a buffer to hold the incoming command.
char commandFromSerial[ 20 ];

// This variable tracks the location of the next free
// space in the commandFromSerial buffer.
uint8_t commandIndex = 0;

void loop() {

  char c;

  WiFiClient client = server.available();

  if( client ){

    while( client.connected() ){

      while( client.available() ){

        // Read the next incoming character.
        c = client.read();

        // Every command from Serial is terminated with a new-line
        // character. If a new-line character arrives we have to
        // terminate the string in the commandFromSerial buffer,
        // and execute it. After execution we have to reset the
        // commandIndex counter to zero.
        if( c == '\n' ){

          commandFromSerial[ commandIndex ] = '\0';
          commander.execute( commandFromSerial, &client );
          commandIndex = 0;

        }

        // If we have a carriage-return character we simply
        // ignore it.
        else if( c == '\r' ){
          continue;
        }

        // Every other case we just put the data to the next
        // free space in the commandFromSerial buffer, increment
        // the commandIndex, and check if it want's to overflow.
        else{

          commandFromSerial[ commandIndex ] = c;
          commandIndex++;
          if( commandIndex >= 20 ){
            commandIndex = 19;
          }

        }

      }

      delay( 10 );

    }

  }

  // Check if there is any data incoming.
  while( Serial.available() ){

    // Read the next incoming character.
    c = Serial.read();

    // Every command from Serial is terminated with a new-line
    // character. If a new-line character arrives we have to
    // terminate the string in the commandFromSerial buffer,
    // and execute it. After execution we have to reset the
    // commandIndex counter to zero.
    if( c == '\n' ){

      commandFromSerial[ commandIndex ] = '\0';
      commander.execute( commandFromSerial, &Serial );
      commandIndex = 0;

    }

    // If we have a carriage-return character we simply
    // ignore it.
    else if( c == '\r' ){
      continue;
    }

    // Every other case we just put the data to the next
    // free space in the commandFromSerial buffer, increment
    // the commandIndex, and check if it want's to overflow.
    else{

      commandFromSerial[ commandIndex ] = c;
      commandIndex++;
      if( commandIndex >= 20 ){
        commandIndex = 19;
      }

    }

  }

}


/// This is an example function for the cat command
void cat_func(char *args, commandResponse *response )
{

  response -> print("Hello from cat function!\r\n");

}

/// This is an example function for the dog command
void dog_func(char *args, commandResponse *response )
{

  response -> print("Hello from dog function!\r\n");

}

/// This is an example function for the led command
void led_func(char *args, commandResponse *response )
{

  digitalWrite( LED_PIN, !digitalRead( LED_PIN ) );

}

/// This is an example function for the sum command
void sum_func(char *args, commandResponse *response )
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

  // We have to check that we parsed succesfully the two
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
  response -> printf( "%d + %d = %d\r\n", a, b, sum );

}
