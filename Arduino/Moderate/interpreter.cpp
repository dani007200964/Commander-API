/*
* Created on June 18 2020
*
* Copyright (c) 2020 - Daniel Hajnal
* hajnal.daniel96@gmail.com
* This file is part of the Commander-API project.
*/


#include "interpreter.hpp"

API_t API_tree[NUM_OF_API_FUNCS];
uint32_t API_cntr;

uint32_t API_place_cntr;

#ifdef INTERPRETER_BUFFER_SIZE
/// Interpreter  input buffer
///
/// It is only used when INTERPRETER_BUFFER_SIZE is defined.
/// In this case the interpreter will copy to this buffer the incoming data
/// before every execution.
char interpreter_buff[INTERPRETER_BUFFER_SIZE];
#endif

/// Command data creator function
///
/// This macro helps to create the command data for a new command.
/// Every command has a name and a description.
/// These data wont change so they are constant.
/// To save some RAM it is handy to store constant data in program memory( FLASH ).
/// This macro handles all of this constant variable cration.
/// @warning The name has to bee an ASCII text. It can't have special characters( !,+,?..etc ), or spaces. It can contain numbers, but the first character has ro be a character not a number!
/// @param name the name of the command without ""
/// @param desc the description of the command with ""
#define create_command_data(name, desc)            \
const char *name##_API_NAME = (const char *)#name; \
const char *name##_API_DESC = (const char *)desc;

/// Add command to the interpreter
///
/// This macro helps adding the command to the interpreter.
/// @warning Before using this macro for a specific command you have to use \link create_command_data \endlink macro first!
/// @param name the name of the command without "".
/// @func the function that will be called when this command arrives.
#define add_command(name, func) add_interpreter_command(&name##_API_NAME, &name##_API_DESC, func);


//  +----  Create instruction data for the API  ----+
//  |                                               |
//  |       This is where you have to add           |
//  |               your commands!                  |
//  |                                               |
//  +-----------------------------------------------+

create_command_data(stop, "This command can be used to stop something.\r\nargs:\td - generic number\r\n\tc - someting else");
create_command_data(start, "This command can be used to start something.\r\nargs:\td - generic number\r\n\tc - someting else");
create_command_data(left, "This command can be used to make someting turn left.\r\nargs:\td - generic number\r\n\tc - someting else");
create_command_data(right, "This command can be used to make someting turn right.\r\nargs:\td - generic number\r\n\tc - someting else");


// This is an example function for the stop command
void stop_func(char *args, int(*resp_fn)(const char*, ...))
{
  INTERPRETER_PRINTF("STOP!\r\n");
  INTERPRETER_PRINTF("Args: %s\r\n", args);

  // Always check the response function channel!
  // If it's a NULL pointer you can't use it,
  // because it will crash your porgram!
  if( resp_fn != NULL ){

    resp_fn( "Wow! Magic!!!!\r\n" );

  }
}

/// This is an example function for the start command
void start_func(char *args, int(*resp_fn)(const char*, ...))
{
  INTERPRETER_PRINTF("START!\r\n");
  INTERPRETER_PRINTF("Args: %s\r\n", args);

}

/// This is an example function for the left command
void left_func(char *args, int(*resp_fn)(const char*, ...))
{
  INTERPRETER_PRINTF("Turning left!\r\n");
  INTERPRETER_PRINTF("Args: %s\r\n", args);

}

/// This is an example function for the right command
void right_func(char *args, int(*resp_fn)(const char*, ...))
{
  INTERPRETER_PRINTF("Turning right!\r\n");
  INTERPRETER_PRINTF("Args: %s\r\n", args);

}

#ifdef ARDUINO_PLATFORM

/// printf like function for Arduino
///
/// This function acts like a printf function in c/c++.
/// The output of this function is redirected to Serial.
/// @param fmt Format string
/// @param ... arguments
/// @note You can change the buffer size in \link ARDUINP_PRINTF_BUFF_SIZE \endlink definition.
int arduino_printf( const char *fmt, ... ){

  // Create a buffer with ARDUINP_PRINTF_BUFF_SIZE size
  char buffer[ ARDUINP_PRINTF_BUFF_SIZE ];

  // This variable will store the return data
  int ret;

  // Variadic argument reading start
  va_list args;
  va_start( args, fmt );

  // Using vsnprintf we can avoid buffer overflow
  ret = vsnprintf( buffer, ARDUINP_PRINTF_BUFF_SIZE, fmt, args );

  // Variadic argument reading stop
  va_end( args );

  // Print the data using Serial
  Serial.print( buffer );

  // Return the ret data
  return ret;

}

#endif

void init_interpreter(void)
{
  // Initialise the 'API_cntr' variable as zero before adding new items
  API_cntr = 0;

  //  +----  Match instruction to it's function   ----+
  //  |                                               |
  //  |       This is where you have to match         |
  //  |       every instruction name to it's          |
  //  |                   function.                   |
  //  |                                               |
  //  +-----------------------------------------------+
  add_command(stop, stop_func);
  add_command(start, start_func);
  add_command(left, left_func);
  add_command(right, right_func);


  // Index eache element to find their place in alphabetic order
  index_apis_in_order( &API_tree[0] );

  // Optimise the API_tree to make it balanced
  optimise_api_tree( &API_tree[0] );

  // Print the API list
  INTERPRETER_DBG( "Available commands:\r\n" );
  print_apis_in_order( &API_tree[0] );
  INTERPRETER_DBG( "\r\n" );

  // Checking if there is a mismatch between the defined and the actual number
  // of commands.
  if( API_cntr != NUM_OF_API_FUNCS ){

    // If a mismatch detected it is a good idea to let the developwe know!
    #ifdef INTERPRETER_DBG
    INTERPRETER_DBG( "**ERROR**\tAPI function number mismatch!!!\r\n" );
    #endif

  }
}

void add_interpreter_command(const char **name, const char **desc, void (*func)(char *, int(*resp_fn)(const char*, ...)))
{

  // Stores the next elements address in the tree
  API_t *next;

  // Stores the previous elements address in the tree
  API_t *prev;

  // It will store string compersation result
  int32_t comp_res;

  //  if the API_cntr value is greater or equal than the defined maximum
  //  API command number, there is a problem in the code!
  if (API_cntr >= NUM_OF_API_FUNCS)
  {

    #ifdef INTERPRETER_DBG
    INTERPRETER_DBG( "**ERROR**\tToo many instruction, memory is full!\r\n" );
    #endif

    return;
  }

  //  if it is the first command we hacve to create the root of the
  //  binary tree
  if (API_cntr == 0)
  {
    API_tree[0].name = (const char**)name;  //  address of the name string( char** type )
    API_tree[0].desc = (const char**)desc;  //  address of the description string( char** type )
    API_tree[0].func = func;                //  function pointer to the actual function

    API_tree[0].left = NULL;    //  because it is the first element of the tree,
    API_tree[0].right = NULL;   //  left and right branches has to be NULL

    API_tree[0].place = 0;      //  default place = 0

  }

  // if it is ot the first command we have to find it's place in the tree
  else
  {
    prev = &API_tree[0];                                        //  get the address of the root element
    comp_res = strcmp( (char*)*(prev->name), (char*)*name );    //  compare the names and save the result to 'comp_res'

    //  compare( ABC order ) the root element name and the new element name
    (comp_res > 0) ? (next = (prev->left)) : ( next = (prev->right));

    //  find the place in the tree
    while (next != 0)
    {
      prev = next;
      comp_res = strcmp( *(prev->name), *name);
      (comp_res > 0) ? (next = (prev->left)) : (next = (prev->right));
    }

    //  link the new item on the previous branch
    ( comp_res > 0 ) ? ( ( prev->left ) = &API_tree[API_cntr] ) : ( ( prev->right ) = &API_tree[API_cntr] );

    //  Fill the new item parameters

    API_tree[API_cntr].name = (const char**)name;  //  address of the name string( char** type )
    API_tree[API_cntr].desc = (const char**)desc;  //  address of the description string( char** type )
    API_tree[API_cntr].func = func;                //  function pointer to the actual function

    API_tree[API_cntr].left = NULL;     //  close the branch
    API_tree[API_cntr].right = NULL;

    API_tree[API_cntr].place = 0;       //  default place = 0

  }

  // Increment the API_cntr variable to track the actually added commands
  API_cntr++;

}

void index_apis_in_order(API_t *head){

  // Before the recursive indexer starts we have to zero API_place_cntr variable.
  // This is important because it defines the value for the first element.
  API_place_cntr = 0;

  // Start the recursive indexer algorythm.
  recursive_indexer( head );

  // If it finished it is handy to let the developer know that
  // The indexer finished.
  #ifdef INTERPRETER_DBG
  INTERPRETER_DBG( "Indexer finished...\r\n" );
  #endif


}

void recursive_indexer(API_t *head){

  // Check end of recursive algorythm
  if( head == 0 ){

    // It means that the algorythm has finished so we can stop the recursion.
    return;

  }

  // Recursively call the left element
  // Left elmenets will be processed first!
  recursive_indexer( head -> left );

  // Store the API_place_cntr to the API tree elements place datafield.
  head -> place = API_place_cntr;

  // Increment the API_place_cntr variable to track the
  // alphabetical place for the next element.
  API_place_cntr++;

  // Recursively call the right element
  // Right elmenets will be processed last!
  recursive_indexer( head -> right );

}

void print_apis_in_order(API_t *head){

  // Check end of recursive algorythm
  if( head == 0 ){
    // It means that the algorythm has finished so we can stop the recursion.
    return;
  }

  // Recursively call the left element
  // Left elmenets will be processed first!
  print_apis_in_order( head -> left );

  // Print the command alphabetical place, name and the description
  INTERPRETER_PRINTF( "%s\r\n", *(head -> name) );
  INTERPRETER_PRINTF( "%s\r\n", *(head -> desc) );

  // Recursively call the right element
  // Right elmenets will be processed last!
  print_apis_in_order( head -> right );

}

uint16_t find_api_index_by_place( uint16_t place ){

  // Generic counter variable
  uint16_t i;

  // Go through all commands
  for( i = 0; i < NUM_OF_API_FUNCS; i++ ){

    // Check that if we found the desired command
    if( API_tree[i].place == place ){

      // If we found it, return the index of it.
      return i;

    }

  }

  // else return 0
  return 0;
}

void swap_api_elements( uint16_t index, uint16_t place ){

  // Buffer that will temporarly hold an element.
  // This is required for a swap.
  API_t buffer;

  // This variable will store the address of the element defined by the second argument( place ).
  uint16_t current_index;

  // Find the index in the array by place of the 'i'-th element
  current_index = find_api_index_by_place( place );

  // save the context of the 'i'-th element to the buffer
  buffer = API_tree[index];

  // write the 'current_index'-th element to the 'i'-th element
  API_tree[index] = API_tree[current_index];

  // write the buffer to the 'current_index'-th element
  API_tree[current_index] = buffer;

}

void optimise_api_tree(API_t *head){

  uint32_t i;
  API_t buffer;

  // recursive optimiser need to initialise 'API_cntr' to 0
  API_cntr = 0;

  // recursively finds the order which is optimal for a balanced tree
  recursive_optimiser( 0, NUM_OF_API_FUNCS - 1 );


  // The order is good, but the connection between the branches broken,
  // because we swapped the API_tree array elements.
  // To fix this problem we have to reinitialise the tree, and use
  // 'add_interpreter_command' function again for all elements.
  API_cntr = 0;
  for( i = 0; i < NUM_OF_API_FUNCS; i++ ){

    // Put the data to the buffer then rewrite the data with fixed parameters.
    buffer = API_tree[i];

    add_interpreter_command( buffer.name, buffer.desc, buffer.func );

    // Save the place data as well.
    API_tree[i].place = buffer.place;

  }
}

// This function is used to order the elements in API_tree array to
// get the fastest search speed
// this function needs 'API_cntr' to be zeroed out before the first call
void recursive_optimiser( int32_t start_index, int32_t stop_index ){

  int32_t mid;

  // End of recursive algorythm
  if( start_index > stop_index ){

    return;

  }

  // Find the middle of the intervall
  mid = ( start_index + stop_index ) / 2;

  // Put the right element to it's place
  swap_api_elements( API_cntr, mid );
  API_cntr++;

  // Do some recursion for the other intervalls
  recursive_optimiser( start_index, mid - 1 );
  recursive_optimiser( mid + 1, stop_index );


}

void execute( char *cmd, int(*resp_fn)(const char*, ...) ){

  // Stores the next elements address in the tree
  API_t *next;

  // Stores the previous elements address in the tree
  API_t *prev;

  // It will store string compersation result
  int8_t comp_res;

  // The begining of the argument list will be stored in this pointer
  char *arg;

  // This variable tracks the command name length
  uint32_t cmd_name_cntr;

  // If this flag is set, than the description message will be printed,
  // and the commands function won't be called.
  uint8_t show_description = 0;

  // If the INTERPRETER_BUFFER_SIZE is defined, then we have to
  // copy the command( cmd ) to the buffer.
  #ifdef INTERPRETER_BUFFER_SIZE
  strncpy( interpreter_buff, cmd, INTERPRETER_BUFFER_SIZE );

  // To make it compatible the code below we modify cmd to the buffer address.
  // I know it's mot elegand, but it is easy and fast.
  cmd = interpreter_buff;
  #endif


  // cmd is the address of the first character of the incoming command.
  // If we give arg variable the value stored in cmd means arg will point to
  // the first character of the command as well.
  arg = cmd;

  // Reset the name counter before we start counting
  cmd_name_cntr = 0;

  // Find the first space character or a string-end character.
  // At this time count how long is the command name( in characters )
  while( ( *arg != '\0' ) && ( *arg != ' ' ) && ( *arg != '?' ) ){

    cmd_name_cntr++;
    arg++;

  }

  // If a space character found we have to terminate the string there.
  // It is important because strcmp function will search for string terminator
  // character, and this way we can separate the command name from its arguments.
  // This method has a downside. If we pass a const char as command
  // to the execution function it will try to overwrite a character in it.
  // It is impossible if the input string is constant and it will result hard fault!
  // To prevent this we nead a buffer. This is why INTERPRETER_BUFFER_SIZE macro has
  // been created. If you want to pass const chars to your interpreter directly, you
  // have to define INTERPRETER_BUFFER_SIZE with a resonable size.
  // But if you can prove it, that there is no chace in your program to use const chars,
  // you can comment out INTERPRETER_BUFFER_SIZE macro. This can save some space in your RAM.
  if( *arg == ' ' ){

    *arg = '\0';
    arg++;

  }

  // The process is the same as above. The only difference is that this time
  // we have to set the show_description flag.
  else if( *arg == '?' ){

    *arg = '\0';
    arg++;
    show_description = 1;

  }

  // Initialise prev variable for the first compersation.
  prev = &API_tree[0];

  // Compare the first element in the tree with the command.
  comp_res = strcmp( (char*)*(prev->name), cmd );

  // Decide where to find the next element in the tree.
  (comp_res > 0) ? (next = (prev->left)) : ( next = (prev->right));

  // Go through the binary tree until you find a match, or until you find the
  // end of the tree.
  while( ( comp_res !=0 ) && ( next != NULL ) ){

    // Store the actual elements address to the prev variable.
    // This is needed because the next steps will overwrite the
    // next variable.
    prev = next;

    // Compare the actual element in the tree with the command.
    comp_res = strcmp( (char*)*(prev->name), cmd );

    // Decide where to find the next element in the tree.
    // This step will overwrite the next variable and we will lost our address.
    // We dont want that so this is why prev variable has to be used like this.
    (comp_res > 0) ? (next = (prev->left)) : ( next = (prev->right));

  }

  // If comp_res variable has a zero in it, that means in the last iteration
  // we had a match.
  if( comp_res == 0 ){

    // Because we have found the command in the API tree we have to choose
    // between description printing and executing.
    // If show_description flag is set, than we have to print the description.
    if( show_description ){

      // Print the description text to the output channel.

      if( resp_fn == NULL ){

        // Print to the default channel
        INTERPRETER_PRINTF( "%s: %s\r\n", (char*)*( prev->name ), (char*)*( prev->desc ) );

      }

      else{

        // Print to the given channel
        resp_fn(  "%s: %s\r\n", (char*)*( prev->name ), (char*)*( prev->desc )  );

      }

    }

    // If show_description flag is not set, than we have to execute the commands function.
    else{

      // Execute commands function.
      (prev -> func)( arg, resp_fn );

    }


  }

  else{

    // If we went through the whole tree and we did not found the command in it,
    // we have to notice the user abut the problem. Maybe a Type-O

    if( resp_fn == NULL ){

      // Print to the default channel
      INTERPRETER_PRINTF( "Command \'%s\' not found!!!\r\n", cmd );

    }

    else{

      // Print to the given channel
      resp_fn( "Command \'%s\' not found!!!\r\n", cmd );

    }


  }

}
