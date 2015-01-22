#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"

#include <editline/readline.h>

char* answer = "Thanks for saying \"%s\"\n\n";

int main( int argc, char** argv ) {
  puts( "Lispy Version 0.0.0.0.1" );
  puts( "Press C-c to Exit\n");

  while( 1 ) {
    char* input = readline( "vesopolisp> ");
    add_history( input );
    printf( answer , input );
    free( input );
  }
  return 0;
}
