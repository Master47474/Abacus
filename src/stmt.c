#include "defs.h"
#include "data.h"
#include "decl.h"


void expr_statement(void)
// 'expr' binaryExpression ;
{
  struct ASTnode* tree;

  // Match the statment as the first token
  match(T_K_EXPRESSION, "expr");

  // lets make a syntax tree of the expression
  tree = binexpr(0);
  // Generate the intermediate code of the tree


  semi();
}




//parse one or more statements
void statements(void){
  while (1) {
    //printf("%d\n", Token.token);
    switch (Token.token) {
    case T_K_EXPRESSION:
      expr_statement();
      break;
    case T_EOF:
      return;
    default:
      fatald("Syntax error, token", Token.token);
    }
  }
}
