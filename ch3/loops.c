#include <stdio.h>

void hello_world() {
  puts( "Hello World!");
}

void hello_world_times( int times ) {
  for( int i = 0; i < times; i++ ) {
    hello_world();
  }
}


int main( int argc, char** argv ) {
  puts( "While");
  int i = 5;
  while ( i > 0) {
    hello_world();
    i = i - 1;
  }

  puts( "for");
  for( i = 0; i < 5; i++ ) {
    hello_world();
  }

  puts( "do" );
  i = 0;
  do {
    hello_world();
    i++;
  } while ( i < 5 );

  puts( "iteration in function ");
  hello_world_times( 10 );
  return 0;
}
