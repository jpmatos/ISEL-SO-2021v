#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <fcntl.h>

#define MAX_CMD_LEN 2024
#define MAX_ARGS_AMOUNT 24
#define MAX_CMD_AMOUNT 24

char *trim(char *str);

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
        else
            trim(fileExit);
        trim(userInput);

        ///Split Commands
        char *cmds[MAX_CMD_AMOUNT];
        cmds[0] = strtok(userInput, "|");
        trim(cmds[0]);
        for (int i = 0; cmds[i] != NULL; i++) {
            cmds[i + 1] = strtok(NULL, "|");
            trim(cmds[i + 1]);
        }

        ///Open file if there was a pipe
        int fileFd = 0;
        if (fileExit != NULL) {
            fileFd = open(fileExit, O_WRONLY | O_CREAT, 0666);
        }

        ///Loop each command
        int fildesOldRead;
        int fildes[2];
        pipe(fildes);       //0-read 1-write
        for (int i = 0; cmds[i] != NULL; i++) {

            /// Set up pipes for this loop
            if(i != 0){
                if(i != 1)
                    close(fildesOldRead);
                fildesOldRead = fildes[0];
                pipe(fildes);
            }

            ///Split Arguments
            char *args[MAX_ARGS_AMOUNT];
            args[0] = strtok(cmds[i], " ");
            trim(args[0]);
            for (int j = 0; args[j] != NULL; j++) {
                args[j + 1] = strtok(NULL, " ");
                trim(args[j + 1]);
            }

            ///Fork
            pid_t pid = fork();
            if (pid == 0) {
                ///Child Process

                ///If not last command: Connect current command's stdout to pipe-in
                if (cmds[i + 1] != NULL) {
                    close(STDOUT_FILENO);
                    dup2(fildes[1], STDOUT_FILENO);
                }
                    ///If it is last command: Check to see if a output file was open and
                    ///connect current command's stdout to said file
                else if (fileFd != 0) {
                    close(STDOUT_FILENO);
                    dup2(fileFd, STDOUT_FILENO);
                }

                ///If not the first command: Connect stdin to pipe-out (previous command stdout)
                if (i != 0) {
                    close(STDIN_FILENO);
                    dup2(fildesOldRead, STDIN_FILENO);
                }

                ///Execute the command (Current child becomes said command)
                execvp(cmds[i], args);
                puts("SHOULD NEVER RUN");
            } else {
                ///Parent Process

                ///Close pipe-in
                close(fildes[1]);

                ///Wait for child to finish
                int res;
                waitpid(pid, &res, 0);
            }
        }

        ///Close file if one was open
        if (fileFd != 0)
            close(fileFd);
    }
    return 0;
}

char *trim(char *str) {

    if (str == NULL)
        return NULL;

    //Set head to start of string
    char *head = str;

    //Set tail to end of string
    char *tail = NULL;
    size_t len = strlen(str);
    tail = str + len - 1;

    //Move head until it isn't a white space
    while (isspace((unsigned char) *head))
        ++head;

    //Move tail until it isn't a white space
    while (isspace((unsigned char) *tail))
        --tail;

    //Set new string start
    if (str + len - 1 != tail)
        *(tail + 1) = '\0';

    //Set new string end
    tail = str;
    while (*head)
        *tail++ = *head++;
    *tail = '\0';

    return str;
}
