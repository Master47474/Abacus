#ifndef _DEFS_H
#define _DEFS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define TEXTLEN 512 //length of symbols in input
#define NSYMBOLS 1024 // number of symbol table entries

//Enums of tokens
enum {
  T_EOF, // Stars at = 0 btw
  T_PLUS,
  T_STAR,
  T_INTLIT, T_SEMI, T_IDENT,
  //keywords
  T_K_INT, T_K_EXPRESSION
};

// Token Struct
struct token {
  int token;  //TOKEN TYPE FROM THE ENUM LISTED ABOE
  int intvalue; // FOR A T_INTLIT
};


// AST node types
enum {
  A_ADD=1,
  A_MULTIPLY,
  A_INTLIT
};

// Abstract Syntax Tree Struture
struct ASTnode {
  int op; // Operation to be performed on this tree
  struct ASTnode *left;
  struct ASTnode *right;
  union {
    int intvalue; //for A_INTLIT
    int id; // for the A_IDENT symbol slot
  } v;
};


//symbol table structre
struct symtable{
  char* name; // name of a symbol
};

#endif // _DEFS_H
