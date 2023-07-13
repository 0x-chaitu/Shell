#include "inputHandler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processHandler.h"

#define errExit(msg)                                                           \
  do {                                                                         \
    perror(msg);                                                               \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

#define SIZE sizeof(char)*BUFSIZ

char *readLine()
{
    int c;
    int position;
    int size;
    char *line;
    
    size = SIZE;
    line = malloc(size);
    position = 0;

    if (line == NULL) {
        errExit("allocation error");
    }

    while (1) {
        c = getchar();
        if ( c == EOF || c == '\n') {
            return line;
        }else {
            line[position++] = c;
        }


        if ( position >= size ) {
            line = realloc(line, size += SIZE );
            if (line == NULL) {
                errExit("allocation error");
            }
        }
    }
}

struct Args parseArguements(char *line){
    char *delimeters;
    char **args;
    char * field;
    int position;
    int size;
    struct Args parseArgs;

    delimeters = " \t\n";
    position = 0;
    size = SIZE;
    args = malloc(size);

    while ((field = strsep(&line, delimeters)) != NULL)
    {
        args[position++] = field;
    }


    parseArgs.argc = position;
    parseArgs.argv = args;
     

    return parseArgs;
}

void interactiveLoop(int status) {
    char *line;
    struct Args args;

    do
    {
        printf("wish>");
        line = readLine();
        args=parseArguements(line);
        status = childProcess(args);
    } while (status);
    
}