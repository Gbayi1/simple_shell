#include "main.h"

void execute_cd(const char *path) {
char current_path[MAX_PATH_LENGTH];

    if (path == NULL || strcmp(path, "") == 0) {
        path = getenv("HOME");
    } else if (strcmp(path, "-") == 0) {
        path = getenv("OLDPWD");
    }

    if (path == NULL) {
        fprintf(stderr, "Invalid path.\n");
        return;
    }

    if (getcwd(current_path, sizeof(current_path)) == NULL) {
        perror("getcwd");
        return;
    }

    if (chdir(path) != 0) {
        perror("chdir");
        return;
    }
    setenv("OLDPWD", current_path, 1);
    setenv("PWD", path, 1);
}
