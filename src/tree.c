#include "defs.h"
#include "data.h"
#include "decl.h"



// Build a generic AST node
struct ASTnode *mkastnode(int op, struct ASTnode *left, struct ASTnode *right, int intvalue)
{
  struct ASTnode *n;

  // Malloc a new AST Node
  n = (struct ASTnode *)malloc(sizeof(struct ASTnode));
  if(n == NULL){
    fatal("Unable to malloc in mkastnode()");
  }

  // Copy into each field
  n->op = op;
  n->left = left;
  n->right = right;
  n->v.intvalue = intvalue;
  return n;
}


// Make AST leaf
struct ASTnode *mkastleaf(int op, int intvalue){
  return mkastnode(op, NULL, NULL, intvalue);
}

//make a unary AST node: onyl one child
struct ASTnode *mkastunary(int op, struct ASTnode *left, int intvalue){
  return mkastnode(op, left, NULL, intvalue);
}
