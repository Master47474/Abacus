#include "defs.h"
#define extern_
  #include "data.h"
#undef extern_
#include "decl.h"
#include <errno.h>





// Init Global Variables
static void init(void){
  Line = 1;
  Putback = '\n';
}

// Prit out error if program was started wrong
static void usage(char *prog){
  fprintf(stderr, "Usage: %s infile\n", prog);
  exit(1);
}



//Main Program: Check arguments and print a usage
// if we dont have an argument. Open up the input
// File and call scanfile to scan the tokens in it
int main(int argc, char* argv[])
{

  if(argc != 2)
    usage(argv[0]);

  init();

  //Open input file
  if((Infile = fopen(argv[1], "r")) == NULL){
    fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
    exit(1);
  }
  // Create the output file
  if ((Outfile = fopen("out.s", "w")) == NULL) {
    fprintf(stderr, "Unable to create out.s: %s\n", strerror(errno));
    exit(1);
  }

  // scan the very first thing in the file
  scan(&Token);
  statements();
  printf("Completed Compile\n");
  return 0;
}
