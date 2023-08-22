#include "main.h"

int main(int ac, char **argv)
{
    char *prompt = "($) ";
    char *lineptr = NULL, *lineptr_copy = NULL;
    size_t n = 0;
    ssize_t nchars_read;
    const char *delim = " \n";
    int num_tokens = 0;
    char *token;
    int i;
    pid_t pid;

    /* declaring void variables */
    (void)ac;

    /* Create a loop for the shell's prompt */
    while (1)
    {
        printf("%s", prompt);
        nchars_read = getline(&lineptr, &n, stdin);
        /* check if the getline function failed or reached EOF or user use CTRL + D */
        if (nchars_read == -1)
        {
            printf("Exiting shell....\n");
            return (-1);
        }

        /* allocate space for a copy of the lineptr */
        lineptr_copy = malloc(sizeof(char) * nchars_read);
        if (lineptr_copy == NULL)
        {
            perror("tsh: memory allocation error");
            return (-1);
        }
        /* copy lineptr to lineptr_copy */
        strcpy(lineptr_copy, lineptr);

        /********** split the string (lineptr) into an array of words ********/
        /* calculate the total number of tokens */
        token = strtok(lineptr, delim);

        while (token != NULL)
        {
            num_tokens++;
            token = strtok(NULL, delim);
        }
        num_tokens++;

        /* Allocate space to hold the array of strings */
        argv = malloc(sizeof(char *) * num_tokens);

        /* Store each token in the argv array */
        token = strtok(lineptr_copy, delim);

        for (i = 0; token != NULL; i++)
        {
            argv[i] = malloc(sizeof(char) * strlen(token));
            strcpy(argv[i], token);

            token = strtok(NULL, delim);
        }
        argv[i] = NULL;
	 if (strcmp(argv[0], "exit") == 0) {
		if(argv[1]){
		int exitstatus = atoi(argv[1]);
		exit(exitstatus);
		}else{
           	exit(0);
                }
        } else if (strcmp(argv[0], "cd") == 0) {
                execute_cd(argv[1]);
         } else if (strcmp(argv[0], "setenv") == 0 && argv[1] && argv[2]){
                 if(setenv(argv[1], argv[2], 1) != 0){
                        perror("setenv error");
                }
         } else if (strcmp(argv[0], "unsetenv") == 0 && argv[1]){
                 if(unsetenv(argv[1]) != 0){
                        perror("unsetenv error");
                }
         } else {
       	 /* execute the command */
        pid = fork();
       	
	 if (pid == -1) {
            perror("fork failed");
            return 1;
        }

        if (pid == 0) {
            
	    if (strcmp(argv[0], "env") == 0) {
            executeEnv();
       	}  else if (strcmp(argv[0], "clear") == 0) {
            clearScreen();
	 } else{
		execmd(argv); 
	}
     	    perror("exec failed");  
            exit(1); 
        } else {
            int status;
            wait(&status);
        }
	 }
    }
    /* free up allocated memory */
    free(lineptr_copy);
    free(lineptr);

    return (0);
}
