#include "main.h"
/**
 * cd - builtin cd: change directory
 * @args: arguments passed to cd
 * Return: always 1
 */

void execute_cd(char *path) {
    if (chdir(path) != 0) {
        perror("cd");
    }
}