#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <fcntl.h>

#define MAX_CMD_LEN 2024
#define MAX_ARGS_AMOUNT 24

int main() {
    char userInput[MAX_CMD_LEN];
    for (;;) {
        printf("$ ");

        ///Initial Checks
        if (fgets(userInput, MAX_CMD_LEN, stdin) == NULL)
            exit(1);
        size_t len = strlen(userInput);
        if (userInput[len - 1] == '\n')
            userInput[len - 1] = 0;
        if (strcmp(userInput, "exit") == 0)
            break;

        ///Split Filename
        char *fileExit;
        strtok_r(userInput, ">", &fileExit);
        if (fileExit[0] == '\0')
            fileExit = 0;

        ///Split Arguments
        char *args[MAX_ARGS_AMOUNT];
        args[0] = strtok(userInput, " ");
        for (int i = 0; args[i] != NULL; i++)
            args[i + 1] = strtok(NULL, " ");

        ///Fork
        pid_t pid = fork();
        if (pid == 0) {
            ///Execute the command (Current child becomes said command)
            execvp(args[0], args);
            puts("SHOULD NEVER RUN");
        } else {
            ///Wait for child to finish
            int res;
            waitpid(pid, &res, 0);
        }
    }
    return 0;
}
