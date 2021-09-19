#ifndef _DATA_H
#define _DATA_H

#ifndef extern_
  #define extern_ extern
#endif

extern_ int Line;
extern_ int Putback;
extern_ FILE *Infile;
extern_ FILE *Outfile;

extern_ struct token Token; //holds last scanned token

extern_ char Text[TEXTLEN + 1]; // holds last scanned identifier

extern_ struct symtable Gsym[NSYMBOLS]; //global symbol table
#endif // _DATA_H
