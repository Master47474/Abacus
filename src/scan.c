#include "defs.h"
#include "data.h"
#include "decl.h"


//return the position of charcter c in string s
// or -1 if c not found
static int chrpos(char* s, int c){
  char *p;

  p = strchr(s,c);
  return (p ? p-s : -1);
}


//get the next character from the input file.
static int next(void){
  int c;

  if(Putback){ // If theres something that was putback
    c = Putback;
    Putback = 0;
    return c;
  }

  c = fgetc(Infile);
  if('\n' == c)
    Line++;
  return c;
}

//put back an unwanted char
static void putback(int c){
  Putback = c;
}

//skip past input that we dont need such as white space new lines ect.
static int skip(void){
  int c;

  c = next();
  while(c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'){
    c = next();
  }

  return c;
}

//Scan and return an integer literal
static int scanint(int c){
  int k, val = 0;

  //convert each char into an in value
  while ((k = chrpos("0123456789", c)) >= 0){
    val = val*10 + k;
    c = next();
  }

  // then we have a non integer so put it back
  putback(c);
  return val;
}


//Scan and return a string or idenity
static int scanident(int c, char* buf, int lim){
  int i = 0;

  //allow digits, alpha and underscores
  while(isalpha(c) || isdigit(c) || '_' == c){
    //error if we hit the identifier length limit
    //else append to buf[] and get next char
    if(i == lim - 1){
      printf("identifier too long on line %d\n", Line);
      exit(1);
    }else if(i < lim - 1){
      buf[i++] = c;
    }
    c = next();
  }
  //we hit a non valid char, put it back
  //Nul-terminate the buf and return length
  putback(c);
  buf[i] = '\0';
  return i;

}

//given a word from the input, return the matching keyword token number
// or 0 if it is not a keyword
//use switch on first letter so we can save computing time
static int keyword(char* s){
   switch (*s){
     case 'e':
      {
        if(!strcmp(s, "expr"))
          return (T_K_EXPRESSION);
        break;
      }
   }
   return 0;
}


// Scan the next token in the input
// return 1 if found else 0 if no tokens left
int scan(struct token *t)
{
    int c, tokentype;

    //skip whitespace
    c = skip();
    //determine the token based on the input char
  switch(c){
    case EOF:
      t->token = T_EOF;
      return 0;
    case '+':
      t->token = T_PLUS;
      break;
    //case '-':
      //t->token = T_MINUS;
      //break;
    case '*':
      t->token = T_STAR;
      break;
    //case '/':
      //t->token = T_SLASH;
      //break;
    case ';':
      t->token = T_SEMI;
      break;
    //case '=':
      //t->token = T_EQUALS;
      //break;
    default:
      //if its a digit scan the int value
      if(isdigit(c)){
        t->intvalue = scanint(c);
        t->token = T_INTLIT;
        break;
      } else if(isalpha(c) || c == '_'){
        //read in a keyword or identifier
        scanident(c, Text, TEXTLEN);
        //if its a recgonised keyword, return that token
        if( tokentype = keyword(Text)){
          t->token = tokentype;
          break;
        }

        //if not regognised then it must be an identifier
        t->token = T_IDENT;
        break;
      }
    // The character isn't part of any recognised token, error
    fatalc("Unrecognised character", c);
  }

  //we found a token
  return 1;
}
