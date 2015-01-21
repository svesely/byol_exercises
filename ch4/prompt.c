#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include <editline/history.h>

/* declare a buffer for user input of size 2048 */
static char input[2048];

int main( int argc, char** argv ) {
  puts( "Lispy Version 0.0.0.0.1" );
  puts( "Press C-c to Exit\n");

  while( 1 ) {
    char* input = readline( "vesopolisp> ");
    add_history( input );
    printf( "No, you're a %s", input);
    free( input );
  }
  return 0;
}
