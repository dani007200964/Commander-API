#include <stdio.h>

#include "../inc/interpreter.h"


int main(){

    char response[100];

    char cmd[100] = "cica 1";

    printf("Program START...\r\n");


    init_interpreter();


    execute( cmd, response );

    strcpy( cmd, "kutya 10" );
    execute( cmd, response );

    strcpy( cmd, "retek 10" );
    execute( cmd, response );


    return 0;
}