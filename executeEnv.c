#include "main.h"

void executeEnv() {
	char *command = "env";
	char *args[] = {"env", NULL};
		execvp(command, args);
	}
