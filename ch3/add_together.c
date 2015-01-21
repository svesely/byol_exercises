#include <stdio.h>

int add_together( int x, int y ) {
  int result = x + y;
  return result;
}

int main( int argc, char** argv ) {
  printf("%d", add_together( 30, 7 ));
  return 0;
}
