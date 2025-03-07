@mainpage Introduction

## A Lightweight Command Interpreter for Microcontrollers

Commander-API is a command interpreter designed for microcontrollers with limited resources. It runs on almost any microcontroller, whether old or new.  

### So, what’s it good for?  
Essentially, it gives you a functionality similar to a command-line interface on a desktop computer. You can create commands and easily link them to specific functions in your code. The main motivation behind this project was to eliminate the need to constantly recompile and upload your code during development. Instead, you can define diagnostic and testing commands that are dynamically available at runtime.  

But that’s not all! Commander-API also supports arguments, allowing you to create parameterized commands. This makes your development workflow much more flexible and powerful.

In addition to handling commands and arguments, Commander-API can also manage environment variables. This lets you store and retrieve settings dynamically, making your system even more flexible and adaptable.

## Just a few lines of code and it is done!

```cpp
#include "Commander-API.hpp"

#define COMMAND_SIZE 30

// We have to create an object from Commander class.
Commander commander;

// Command callbacks
bool cat_func( char *args, CommandCaller* caller );
bool dog_func( char *args, CommandCaller* caller );

// Command tree
Commander::systemCommand_t API_tree[] = {
    systemCommand( "cat", "Description for cat command.", cat_func ),
    systemCommand( "dog", "Description for dog command.", dog_func )
};

// This buffer is used to store command from Serial port.
char commandBuffer[ COMMAND_SIZE ];

// System init section.
void setup(){
    Serial.begin(115200);

    commander.attachTree( API_tree );
    commander.init();

    Serial.println();
    Serial.println( "---- Init Finished ----" );
    Serial.println();

    Serial.println( "Type something" );
    Serial.print( "$: " );
}

// Infinite loop.
void loop(){
    commander.update( commandBuffer, COMMAND_SIZE, &Serial );
}

/// This is an example function for the cat command
bool cat_func(char *args, CommandCaller* caller ){
    caller -> print( "Hello from cat function!\r\n" );
    return true;
}

/// This is an example function for the dog command
bool dog_func(char *args, CommandCaller* caller ){
    caller -> print( "Hello from dog function!\r\n" );
    return true;
}
```

Right? It doesn't seem that complicated, does it? It was very important to us to keep things simple.
We really wanted beginner programmer padawans to be able to create amazing things easily with Commander.
That's why we made sure the API is as simple and straightforward as possible.


<div class="section_buttons">
 
| Previous          |                         Next |
|:------------------|-----------------------------:|
|                   | [Install](@ref installation_page) |
 
</div>