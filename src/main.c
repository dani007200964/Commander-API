/*
 * Created on June 18 2020
 *
 * Copyright (c) 2020 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 */


#include <stdio.h>

#include "../inc/interpreter.h"


int main(){

    //  The interpreter modifies the content of
    //  the string it gets. Make shore you backup
    //  it before use it is used after.
    //  Also note that this variable must not have
    //  a const type. const char* as argument will
    //  cause crash!
    char cmd_to_execute[100] = "stop 10";

    printf("Program begin...\r\n");

    //  Interpreter initialization code
    init_interpreter();

    //  Execute string stored in cmd_to_execute
    execute( cmd_to_execute, printf );

    //  Try with empty response function
    execute( cmd_to_execute, NULL );

    //  Modify the content of cmd_to_execute
    strcpy( cmd_to_execute, "start 31" );
    //  Execute string stored in cmd_to_execute
    execute( cmd_to_execute, printf );

    //  Modify the content of cmd_to_execute
    strcpy( cmd_to_execute, "left 3" );
    //  Execute string stored in cmd_to_execute
    execute( cmd_to_execute, printf );

    //  Modify the content of cmd_to_execute
    strcpy( cmd_to_execute, "right 0" );
    //  Execute string stored in cmd_to_execute
    execute( cmd_to_execute, printf );


    printf( "Program end..." );

    return 0;
}
