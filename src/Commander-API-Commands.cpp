#include "Commander-API-Commands.hpp"

void commander_millis_func( char *args, Stream *response ){

  char buff[ 20 ];

  sprintf( buff, "%lu", millis() );

  response -> print( buff );

}
