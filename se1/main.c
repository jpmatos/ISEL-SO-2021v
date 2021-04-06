#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMD_LEN 2024

int main() {
    char userInput[MAX_CMD_LEN];
    for (;;) {
        printf("$ ");

        if (fgets(userInput, MAX_CMD_LEN, stdin) == NULL)
            exit(1);
        size_t len = strlen(userInput);
        if (userInput[len - 1] == '\n')
            userInput[len - 1] = 0;
        if (strcmp(userInput, "exit") == 0)
            break;

        printf("%s\n", userInput);
    }
    return 0;
}