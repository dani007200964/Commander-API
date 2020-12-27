//  Include Guard
#ifndef INTERPRETER_H_
#define INTERPRETER_H_


#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define NUM_OF_API_FUNCS 7

//  structure for instruction data
typedef struct API_t{

  struct API_t *left;       //  Left element on a binatry tree branch
  struct API_t *right;      //  Right element on a binary tree branch
  const char **name;        //  Name of the instruction
  const char **desc;        //  Description of the command
  void(*func)(char*,char*); //  Function pointer to the command function

}API_t;


void add_interpreter_instruction(const char **name, const char **desc, void(*func)(char*,char*));

void init_interpreter(void);

void print_apis_in_order(API_t *head);


void teszt(void);

#endif