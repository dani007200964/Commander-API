/*
 * Created on June 18 2020
 *
 * Copyright (c) 2020 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
*/


#ifndef INTERPRETER_H_
#define INTERPRETER_H_


#include <stdio.h>
#include <stdint.h>
#include <string.h>

/// Version information
#define COMMANDER_API_VERSION "V0.2A"

/// Arduino environment used
///
/// If you use the Arduino environment with this library,
/// The easiest way is to uncomment this macro( uncommented by default ).
/// It creates a printf like function to you called \link arduino_printf \endlink.
/// A printf like function is necessary for this library, it is explained below why and how.
#define ARDUINO_PLATFORM

#ifdef ARDUINO_PLATFORM

/// If you use Arduino environment you have to include Arduino.h
#include "Arduino.h"

/// If you use Arduino environment you have to create a printf like function
int arduino_printf( const char *fmt, ... );

#endif

/// Definition to a buffer size
///
/// If you want to use the \link execute \endlink function with const char
/// command as argument, you must define this macro with a resonable size.
/// The importance of this is explained in the \link execute \endlink function.
/// If you wont use the \link execute \endlink function with const char
/// command parameter, you can comment this macro out.
#define INTERPRETER_BUFFER_SIZE 30

//  +----  Set the correct values  ----+
//  |                                  |
//  |     NUM_OF_API_FUNCS value has   |
//  |           to be exact!           |
//  |                                  |
//  +----------------------------------+

/// The number of API functions
///
/// You have to set an exact value to this definition about
/// how many commands have you added to the interpreter.
/// If this number is not correct, than the compiler can't
/// reserve space correctly for the API tree. To make this
/// library work you have to use at least 3 commands.
/// If you have less than 3 command just use simple strcmp.
#define NUM_OF_API_FUNCS  4

/// Debug message output
///
/// You can define a printf()-like function to send debug
/// messages from the interpreter. It can be useful to
/// validate that the API tree generation was succesfull.
///  comment out if you does not want to get debug messages
#define INTERPRETER_DBG printf

/// Arduino printf buffer size
///
/// With this definition you can define the size of the output
/// buffer size of the \link arduino_printf \endlink function.
#define ARDUINP_PRINTF_BUFF_SIZE 150

#ifdef ARDUINO_PLATFORM
#undef INTERPRETER_DBG
#define INTERPRETER_DBG arduino_printf
#endif

/// Output messages
///
/// This is the output channel of the interpreter.
/// THIS IS NOT OPTIONAL!
/// Default configuration is uses printf, but you can use
/// any printf like function.
#define INTERPRETER_PRINTF printf

#ifdef ARDUINO_PLATFORM
#undef INTERPRETER_PRINTF
#define INTERPRETER_PRINTF arduino_printf
#endif

/// Structure for command data
///
/// Every command will get a structure like this.
/// This structure is used to store your commands
/// in a balanced binary tree.
typedef struct API_t{

  uint16_t place;           //  This will store the alphabetical place of the command in the tree
  struct API_t *left;       //  Left element on a binatry tree branch
  struct API_t *right;      //  Right element on a binary tree branch
  const char **name;        //  Name of the command
  const char **desc;        //  Description of the command
  void(*func)(char*,int(*resp_fn)(const char*, ...)); //  Function pointer to the command function

}API_t;

/// This command is used to add a new command to the interpreter.
///
/// In practise you wont have to use this command, because
/// there is a macro for it called \link add_command \endlink.
/// Using this function without command creation macros is not recommended.
/// @param name pointer to a const char* that holds the name of the command
/// @param desc pointer to a const char* that holds the description of the command
/// @param func function-pointer to a function that will be called, when the command will be executed
void add_interpreter_command(const char **name, const char **desc, void(*func)(char*,int(*resp_fn)(const char*, ...)));

/// This is the initialization function
///
/// This function handles the API tree generation.
/// In this function you have to add your commands to the interpreter
/// with \link add_command \endlink macro. The init function also
/// compares \link NUM_OF_API_FUNCS \endlink with the number of added commands.
/// If there's a mismatch it sends an error to the debug port.
void init_interpreter(void);

/// Prints your commands
///
/// This function prints your commands in alphabetical order.
/// @warning It is a recursive function, so it can consume a lot of stack memory. Please don't use it after init!
/// @param head this is the head of the API tree
void print_apis_in_order(API_t *head);

/// Indexes all elements in the tree
///
/// It is used by the library to calculate and store every elements alphabetical index.
/// @warning It is a recursive function, so it can consume a lot of stack memory. Please don't use it after init!
/// Do not use it alone. The \link index_apis_in_order \endlink function
/// can be used for this purpose.
/// @param head this is the head of the API tree
void recursive_indexer(API_t *head);

/// Indexes all elements in the tree
///
/// It is used by the library to calculate and store every elements alphabetical index.
/// @note Use this function to index the commands.
/// @warning It uses a recursive function, so it can consume a lot of stack memory. Please don't use it after init!
/// @param head this is the head of the API tree
void index_apis_in_order(API_t *head);

/// Finds an element in API tree by alphabetical order
///
/// You give the alphabetical index of an element and it returns
/// the index of that elment in the binary tree.
/// @param place alphabetical order of an element
/// @returns place of that element in the API tree
uint16_t find_api_index_by_place( uint16_t place );

/// Tree optimizer
///
/// This function is used to balance the API_tree to get the highest
/// search performance.
/// @warning It uses a recursive function, so it can consume a lot of stack memory. Please don't use it after init!
/// @param head this is the head of the API tree
void optimise_api_tree(API_t *head);

/// Swap two elements in API tree
///
/// This is a tricky function. Basically it swaps two elements, but the tricky
/// part is that how to specify those two elements. The index argument is
/// refer to the index in the API tree, for example API_tree[0].
/// The place refers to an alphabetical place of a command in API tree.
/// For example, to swap a command thats alphabetical index is 3 with a command
/// that is the 0th element in the API tree you should
/// call this function like this: swap_api_elements( 0, 3 )
/// @param index the index of an element in API tree.
/// @param alphabetical place in API tree.
void swap_api_elements( uint16_t index, uint16_t place );

/// Recorsive Optinizer function
///
/// This function is used by the \link optimise_api_tree \endlink function.
/// Please do not use it alone!
/// @warning It is a recursive function, so it can consume a lot of stack memory. Please don't use it after init!
/// @param start_index start boundary of the intervall where to optimise
/// @param stop_index stop boundary of the intervall where to optimise
void recursive_optimiser( int32_t start_index, int32_t stop_index );

/// Execution function
///
/// You have to call this function when you want to execute a command.
/// The command is basically a C-like string.
/// @warning use this function after \link init_interpreter \endlink.
/// @param cmd the command that you want to execute.
/// @param resp_fn the response function for command execution.
void execute( char *cmd, int(*resp_fn)(const char*, ...) );

#endif
