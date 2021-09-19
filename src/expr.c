#include "defs.h"
#include "data.h"
#include "decl.h"

//parsing of expressions


static struct ASTnode *primary(void){
  struct ASTnode *n;
  int id;

  // for an INTLIT token make a leaf AST node for it
  // Scan the next token otherwise
  switch(Token.token){
    case T_INTLIT:
      {
        n = mkastleaf(A_INTLIT, Token.intvalue);
        break;
      }
    default:
      fatald("Syntax error, token", Token.token);
  }

  scan(&Token);
  return n;
}

// convert token into AST operation
int arithop(int tokentype)
{
  switch(tokentype){
      case T_PLUS:
        return A_ADD;
      case T_STAR:
        return A_MULTIPLY;
      default:
        fatald("Syntax Error, Token" , tokentype);
  }
}


// Operator Precedence
static int OpPrec[] = {0, 10, 20, 0};
// PlaceHolder, A_ADD, A_MULTIPLY, placeHolder

static int op_precidence(int tokentype)
{
  int prec = OpPrec[tokentype];
  if(prec == 0)
    fatald("Syntax Error, Token" , tokentype);
  return prec;
}



// Return a AST tree whos root is a binary operator
struct ASTnode *binexpr(int ptp)
{
  struct ASTnode *n, *left, *right;
  int tokentype;

  // get the interger literal on the left
  // Whilst Also Retriving the next token
  left = primary();
  tokentype = Token.token;
  if(tokentype == T_SEMI) // Are we at the end of the expression / equation
    return left;

  // While the precedence of this token is more than that of the previous token
  while(op_precidence(tokentype) > ptp){
    scan(&Token);

    // recevsivly build the right hand side of the tree
    right = binexpr(OpPrec[tokentype]);

    // build a tree with both sub trees
    left = mkastnode(arithop(tokentype), left, right, 0);

    //Update the current token
    tokentype = Token.token;
    if(tokentype == T_SEMI)
      return left;
  }


  return left;
}
