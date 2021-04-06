#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 2024
#define MAX_ARGS_AMOUNT 24
#define MAX_CMD_AMOUNT 24

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

        ///Split Commands
        char *cmds[MAX_CMD_AMOUNT];
        cmds[0] = strtok(userInput, "|");
        for (int i = 0; cmds[i] != NULL; i++)
            cmds[i + 1] = strtok(NULL, "|");

        ///Loop each command
        for (int i = 0; cmds[i] != NULL; i++) {
            ///Split Arguments
            char *args[MAX_ARGS_AMOUNT];
            args[0] = strtok(cmds[i], " ");
            for (int j = 0; args[j] != NULL; j++)
                args[j + 1] = strtok(NULL, " ");

            ///Fork
            pid_t pid = fork();
            if (pid == 0) {
                ///Execute the command
                execvp(args[0], args);
                puts("SHOULD NEVER RUN");
            } else {
                ///Wait for child to finish
                int res;
                waitpid(pid, &res, 0);
            }
        }
    }
    return 0;
}
