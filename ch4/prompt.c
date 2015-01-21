#include <stdio.h>
#include <stdlib.h>

#ifdef _win32
#include <string.h>
static char buffer[2048];
char* readline( char* prompt ) {
  fputs( prompt, stdout );
  fgets( buffer, 2048, stdin );

  char* cpy = malloc( strlen( buffer ) + 1 );
  strcpy( cpy, buffer );
  cpy[ strlen(cpy) -1 ] = "\0";
  return cpy;
}

void add_history( char* unused ) {
  /* no op */
}
#elif __APPLE__
 /* the programmer likes apples */

#endif

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
