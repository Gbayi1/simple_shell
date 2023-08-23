#include "main.h"

void clearScreen() {
	char *command = "clear";
	char *args[] = {"clear", NULL};
	execvp(command, args);
        }
