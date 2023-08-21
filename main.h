#ifndef MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_PATH_LENGTH 1024

void executeEnv();
void clearScreen();
void execmd(char **argv);
char *get_location(char *command);
void execute_cd(const char *path);

#endif 
