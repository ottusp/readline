#include "readline.h"

int main(){
  FILE * file = fopen("readline.c", "r");
  char * string = readline(file);
  
  while(string != NULL) {
    printf("%s\n", string);
    free(string);
    string = readline(file);
  }

  fclose(file);

  return 0;
}