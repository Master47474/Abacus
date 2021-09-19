#ifndef _DECL_H
#define _DECL_H

// Declare functions from files
//scan.c
int scan(struct token *t);

// tree.c
struct ASTnode *mkastnode(int op, struct ASTnode *left,
			  struct ASTnode *right, int intvalue);
struct ASTnode *mkastleaf(int op, int intvalue);
struct ASTnode *mkastunary(int op, struct ASTnode *left, int intvalue);

//match.c
void match(int t, char *what);
void semi(void);

// fatal.c
void fatal(char* s);
void fatals(char* s1, char *s2);
void fatald(char* s, int d);
void fatalc(char* s, int c);


//expr.c
struct ASTnode *binexpr(int ptp);

//stmt.c
void statements(void);

#endif // _DECL_H
