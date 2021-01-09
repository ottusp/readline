#include "readline.h"

#define STRING_CHUNK 4096

#define TRUE 1
#define FALSE 0
#define BOOL char

#define STATUS char
#define ERROR 0
#define SUCCESS 1

BOOL endOfLineReached(char letter) {
  return letter == '\n' || letter == EOF || letter == '\0';
}

BOOL isLineFull(unsigned int lineLen) {
  return lineLen % STRING_CHUNK == 0 || (lineLen + 1) % STRING_CHUNK == 0;
}

STATUS reallocLine(char ** line, unsigned int lineLen) {
  char * newString = calloc(lineLen + STRING_CHUNK, 1);
  
  if(newString == NULL)
    return ERROR;
  
  if(*line != NULL) {
    strcpy(newString, *line);
    free(*line);
  }
  *line = newString;
  
  return SUCCESS;
}

char * readline(FILE * file){
  char * line = NULL;
  char letter;
  unsigned int lineLen = 0;
  STATUS status = ERROR;

  while(fscanf(file, "%c", &letter) == 1 && !endOfLineReached(letter)) {

    if(isLineFull(lineLen)) {
      status = reallocLine(&line, lineLen);
      if(status == ERROR) break;
    }

    line[lineLen] = letter;
    lineLen++;
  }

  if(status == SUCCESS) {
    if(lineLen == 0)
      free(line);
    else {
      line[lineLen - 1] == '\0';

      if(lineLen >= 2)
        if(line[lineLen - 2] == '\r')
          line[lineLen - 2] == '\0';
      return line;
    }
  }
  else
    return NULL;
}