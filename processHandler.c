#include "processHandler.h"
#include "inputHandler.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

#define errExit(msg)                                                           \
  do {                                                                         \
    perror(msg);                                                               \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

int childProcess(struct Args args)
{
    __pid_t rc ;
    int status;
    char *path;
    path = malloc(sizeof(char)*BUFSIZ);



    if((rc = fork()) == -1){
        errExit("Error: ");
    }else if( rc == 0  ) {
        if (args.argc > 0){ 
            strcat(path, "/usr/bin/" );
            strcat(path, args.argv[0] );
            if (access(args.argv[0], X_OK) == 0){
                if (execv(args.argv[0], args.argv) == -1){
                    errExit("Error: ");
                }
            }
            else {
                if (access(path, X_OK) == 0){
                    if (execv(path, args.argv) == -1){
                        errExit("Error: ");
                    }
                }
                else {
                    if (strcmp(args.argv[0], "exit") == 0){
                        exit(SIGUSR1);
                    } else if (strcmp(args.argv[0], "cd") == 0) {

                        if (args.argv[1] == NULL || args.argv[2] != NULL) errExit("Error: ");
                        if (chdir(args.argv[1]) == -1){
                            errExit("Error: ");
                        }
                    }else  errExit("Error: ");
                }
            }

        }
    }else {
        do {
            waitpid(rc, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
       
        if(status == 2560){
            return 0;
        }
    }
    return 1;

}
