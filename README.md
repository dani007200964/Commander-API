# Commander API
**Version V0.2A**

Commander-API is a simple to use interpreter library and you can easily use it to process character based commands and link them to a specified function. It is designed mainly to work with low memory capacity devices, for example, __small ARM or AVR devices or some embedded stuff__. The library shows an Arduino implementation and it can be found in the Arduino folder in the repository. The source files are located in the src folder.

# Doxygen documentation

The project has a Doxygen generated documentation. It can be found in Doc/html/index.html.
The theme that used with the documentation can be found [here](https://jothepro.github.io/doxygen-awesome-css/)

# Arduino installation

__1.__

Download this library as a .zip, or clone it.

__2.__

Create a new sketch in Arduino IDE and open its folder.

__3.__

![](https://github.com/dani007200964/Commander-API/blob/master/Doc/images/arduino_install_lib_install.png)
Now copy interpreter.c and interpreter.h files from src folder in this repository, to your sketch folder.

__4.__

Because Arduino uses C++ not C, you have to rename the interpreter.c file to interpreter.cpp,
and the interpreter.h file to interpreter.hpp. My recommendation is to use a text editor for
this step like [Atom](https://atom.io/) or [Notepad++](https://notepad-plus-plus.org/downloads/).

__5.__

If Arduino IDE is opened __save all your work,__ then restart Arduino IDE.

__6.__

![](https://github.com/dani007200964/Commander-API/blob/master/Doc/images/arduino_install_success.png)
Now you should see the interpreter.cpp and interpreter.hpp files on the top bar.
Than you just include interpreter.hpp as usual.

Congratulations you successfully added the library to your sketch.

# Usage with Arduino

**Basic example**

__1.__

The first thing you have to do is to add the library files to your project.
It is discussed in the Arduino installation page how to do.

__2.__

The next thing you have to do is to include the library at the beginning of your program.

Code:
```
#include "interpreter.hpp"
```

__3.__

Now, you have to create at leas 3 commands, and add them to the interpreter. To do that, first you have to open
the interpreter.cpp file. Locate the next comment:

```
//  +----  Create instruction data for the API  ----+
//  |                                               |
//  |       This is where you have to add           |
//  |               your commands!                  |
//  |                                               |
//  +-----------------------------------------------+
```

By default in the code, there are 4 commands created as an example, below this comment.

```
create_command_data(stop, "This command can be used to stop something.\r\nargs:\td - generic number\r\n\tc - someting else");
create_command_data(start, "This command can be used to start something.\r\nargs:\td - generic number\r\n\tc - someting else");
create_command_data(left, "This command can be used to make someting turn left.\r\nargs:\td - generic number\r\n\tc - someting else");
create_command_data(right, "This command can be used to make someting turn right.\r\nargs:\td - generic number\r\n\tc - someting else");
```

You can modify these of course. How you can create a new one is shown in the next step.

__4.__

If you want to create a new command, firstly you have to create its data. To do that you have to use create_command_data macro.
The syntax is:

```
create_command_data( name_of_the_command, description_of_this_command );
```

Example:
```
create_command_data( reset, "description of reset command" );
```

__Note that the name of the command should not have " characters before and after like a regular string!__
The name also can't start with a number, and you can't use any special characters in it like: ?!,:-...etc..

__5.__

In step 3, and 4 you only created the data for the commands. In this step you have to add these data to the interpreter.
To do that you have to find the following text int the implementation of init_interpreter function:

```
//  +----  Match instruction to it's function   ----+
//  |                                               |
//  |       This is where you have to match         |
//  |       every instruction name to it's          |
//  |                   function.                   |
//  |                                               |
//  +-----------------------------------------------+
```

By default in the code, there are 4 commands added as an example, below this comment.

```
add_command(stop, stop_func);
add_command(start, start_func);
add_command(left, left_func);
add_command(right, right_func);
```

You can modify these of course. How you can create a new one is shown in the next step.

__6.__

To add the created data to the interpreter you have to use add_command macro.
The syntax is:
```
add_command( name_of_the_command, function_for_this_command );
```

Example:
```
add_command( reset, reset_func );
```

__Not that the name of the command has to match exactly with the name in step 3 and 4!__

__7.__

Now you have to create the function that will be executed when the command arrives to the interpreter.
The name of this function has to be exactly the same as the function name( 2nd argument ) in step 5, and 6.

Example:
```
// This is an example function for the reset command
void reset_func(char *args, int(*resp_fn)(const char*, ...))
{

  int test_arg1;
  int test_arg2;
  int arg_read_result;

  Serial.println( "Reset function called" );

  // Do the actual code somewhere here.

  // If you want to use the response channel,
  // This is how to do it correctly.
  // Always check the response function channel!
  // If it's a NULL pointer you can't use it,
  // because it will crash your porgram!
  if( resp_fn != NULL ){

    resp_fn( "Wow! Magic!!!!\r\n" );

  }

  // If you have arguments you have to process it like a sscanf
  arg_read_result = sscanf( args, "%d %d", test_arg1, test_arg2 );

  // You should check that if the argument read was successfully
  // sscanf should return exactly the same number as how many arguments
  // you have added.
  if( arg_read_result == 2 ){

    // Arguments processed, no error.

  }

  else{

    // Some of the arguments has an error.
    // Maybe a Type-O.

  }

}
```

The example above is quite complex, but it shows all of the futures that a command function has.
You don't have to use all of it if you doesn't need that specific function.
The only restriction is that the function type has to be the same.

You can write these functions driectly in interpreter.cpp file, or you can create a header and
an implementation file for your command functions and include that in interpreter.hpp.

Example:
```
void name_of_the_function(char *args, int(*resp_fn)(const char*, ...));
```

I know that it is not pretty, but in practice you just copy and rename it.

__8.__

The next thing is to count how many commands you have. __This number has to be exact!__
You have to open interpreter.hpp file, then search for the NUM_OF_API_FUNCS definition.
Give this macro the correct number of commands.

__9.__

The library has an option called ARDUINO_PLATFORM in interpreter.hpp. If you use
Arduino IDE you have to uncomment this define.

__10.__

Now the basic configuration of the library is finished, so you just have to use it in your code.
The interpreter has to be initialized. To initialise the interpreter the safest practise is,
to initialise it as soon as possible. The reason for this is because the library uses some recursive
functions to build a binary tree from the commands. It needs a relatively high amount of stack
compared a simple initialisation function. After the initialisation this stack memory will be
freed up. In Arduino environment basically you have to init Serial first, then,
init the interpreter in the beginning of the setup function.

Code:
```
init_interpreter();
```

__10.__

Now you just have to use the execute function every time you want to execute a command.
The 3 examples in the Arduino folder in the repository shows 3 detailed example to use
and understand this library.

__Congratulations, you have made your first project with Commander API :)__

**The importance of response function**

![](https://github.com/dani007200964/Commander-API/blob/master/Doc/images/images/response_function_explained_01.png)
Imagine a system that has a various number of channels to communicate with.
For example a Linux system, which has its shell redirected to SSH, Serial, GUI...
If a command arrives in one of the supported channels, you want to generate
the response to that channel. For example if a command arrives from Serial,
you want to generate the answer and the messages from the command to Serial as well,
not to any other channels. This is why response function is used.
The Commander API handles everything you just have to create a valid response
function to it. The advanced demo shows how to add a response function correctly.
If you don't use a response function, please use NULL as argument. In this case the
error messages will be redirected to INTERPRETER_PRINTF definition.

**Print the description**

![](https://github.com/dani007200964/Commander-API/blob/master/Doc/images/images/description_example.png)
To print the description you just have to add a question mark to the end of the command.

**When and how to use a buffer?**

Commander API designed to work mainly on embedded devices. In these devices usually you work
from RAM. If you work from RAM you have an option to modify the contant of the command that
has given to the execute function. There are two cases when you __MUST__ have to use a buffer:

__1.__ When you want to use the execute function with constant data. In this case the Commander
API will try to overwrite this data, while executing the command. Why is it work like this is
explained in the source file. In this case it will cause Hard Fault, because the software will
try to modify the content of the FLASH( or program ) memory. This is restricted.

__2.__ When you don't want to modify the data. In my opinion it is very rare. In most cases
you just collect the command string until a terminator character and pass it to the interpreter.
If you need the command string after the execute function use a buffer.

How to setup buffered mode:

__1.__

Open interpreter.hpp and find INTERPRETER_BUFFER_SIZE definition.

__2.__

If it is commented, uncomment it.
You have to decide how large buffer you need. If it is too large than you will waste RAM.
If it is too short, than you can't interpret large commands correctly.

If you __does not need a buffer__, than you __MUST uncomment__ INTERPRETER_BUFFER_SIZE!

**Arduino printf function**

The arduino_printf function is implemented by compatibility reasons. Commander API requires
a printf like function as a communication channel. This function acts like a printf function,
but it is redirected to serial. If you need more channels like TCP
or bluetooth you have to implement a printf like functions for those channels as well.


## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## Donation
If this project help you reduce time to develop, you can give me a cup of coffee :)

[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/donate?hosted_button_id=YFGZD78H6K2CS)

## License & copyright
© Daniel Hajnal
Licensed under the MIT License
