#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"

#include <editline/readline.h>

enum { LVAL_NUM, LVAL_ERR };
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };

/* Declare new lval Struct */
typedef struct {
  int type;
  long num;
  int err;
} lval;

lval lval_num( long x ) {
  lval v;
  v.type = LVAL_NUM;
  v.num = x;
  return v;
}


/* Print an "lval" */
void lval_print( lval v ) {
  switch ( v.type ) {
    /* In the case that the type is a number print it */
    /* Then break out of the switch */
    case LVAL_NUM:
      printf( "%li", v.num ); break;

    /* In the case the type is an error */
    case LVAL_ERR:
      /* Check what type of error it is an print it */
      if ( v.err == LERR_DIV_ZERO ) {
        printf( "Error: Division By Zero!" );
      }
      if ( v.err == LERR_BAD_OP ) {
        printf( "Error: Invalid Operator!" );
      }
      if ( v.err == LERR_BAD_NUM ) {
        printf( "Error: Invalid Number!" );
      }

      break;
  }
}

void lval_println( lval v ) {
  lval_print( v );
  putchar( '\n' );
}

lval lval_err( int x ) {
  lval v;
  v.type = LVAL_ERR;
  v.err = x;
  return v;
}

lval eval_op( lval x, char* op, lval y ) {

  if( x.type == LVAL_ERR ) { return x; }
  if( y.type == LVAL_ERR ) { return y; }

  if (strcmp(op, "+") == 0) { return lval_num( x.num + y.num ); }
  if (strcmp(op, "-") == 0) { return lval_num( x.num - y.num ); }
  if (strcmp(op, "*") == 0) { return lval_num( x.num * y.num ); }
  if (strcmp(op, "/") == 0) { 
    if( y.num == 0 ) {
      return lval_err( LERR_DIV_ZERO );
    }
    return lval_num( x.num / y.num ); 
  }
  return lval_err( LERR_BAD_OP );
}

lval eval( mpc_ast_t* t ) {
  if (strstr( t->tag, "number")) {
    errno = 0;
    long x = strtol( t->contents, NULL, 10 );
    return errno != ERANGE ? lval_num( x ) : lval_err( LERR_BAD_NUM );
  }

  char* op = t->children[1]->contents;

  lval x = eval( t->children[2]);

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
      lval result = eval( r.output );
      lval_println( result );
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
