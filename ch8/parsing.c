#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"

#include <editline/readline.h>

long eval_op(long x, char* op, long y) {
  if (strcmp(op, "+") == 0) { return x + y; }
  if (strcmp(op, "-") == 0) { return x - y; }
  if (strcmp(op, "*") == 0) { return x * y; }
  if (strcmp(op, "/") == 0) { return x / y; }
  if (strcmp(op, "%") == 0) { return x % y; }
  return 0;
}

long eval( mpc_ast_t* t) {
  if (strstr( t->tag, "number")) {
    return atoi(t->contents);

  }
  char* op = t->children[1]->contents;
  long x = eval( t->children[2]);

  if (strcmp(op, "-") == 0 && t->children_num == 4) {
    return 0 - x;
  }

  int i = 3;
  while(strstr(t->children[i]->tag, "expr")){
    x = eval_op( x, op, eval( t->children[i] ) );
    i++;
  }
  return x;
}


int main( int argc, char** argv ) {
  mpc_parser_t* Number = mpc_new( "number" );
  mpc_parser_t* Symbol = mpc_new( "symbol" );
  mpc_parser_t* Sexpr = mpc_new( "sexpr" );
  mpc_parser_t* Expr = mpc_new( "expr" );
  mpc_parser_t* Lispy = mpc_new( "lispy" );

  mpca_lang( MPCA_LANG_DEFAULT,
      "                                                   \
      number   : /-?[0-9]+/ ;                             \
      symbol   : '+' | '-' | '*' | '/' ;                  \
      sexpr    : '(' <expr>* ')' ;                        \
      expr     : <number> | <symbol> | <sexpr> ;          \
      lispy    : /^/ <expr>* /$/ ;                        \
      ",
      Number, Symbol, Sexpr, Expr, Lispy);


  puts( "Lispy Version 0.0.0.0.8" );
  puts( "Press C-c to Exit\n");

  while( 1 ) {
    char* input = readline( "vesopolisp> ");
    add_history( input );

    mpc_result_t r;
    if ( mpc_parse( "<stdin>", input, Lispy, &r )) {
      long result = eval( r.output );
      printf("%li\n", result );
      mpc_ast_delete( r.output );
    }else{
      mpc_err_print( r.error );
      mpc_err_delete( r.error );
    }

    free( input );
  }
  mpc_cleanup( 5, Number, Symbol, Sexpr, Expr, Lispy );
  return 0;
}
