#include "syscalls.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

    if(argc != 2) {
        puts("Incorrect number of arguments.");
        return 0;
    }

    //Get pid
    long sysPid = xgetpid();
    printf("sysPid: %ld.\n", sysPid);

    //Convert pid to a string
    char sysPidStr[12];
    sprintf(sysPidStr, "%ld", sysPid);

    //Prepare string to write
    char output[256] = "";
    strcat(output, sysPidStr);
    strcat(output, "\n39185 - Diogo Martins\n41462 - Hugo Cameira\n42390 - João Matos\n");

    //Open file
    long fid = xopen(argv[1]);
    puts("File opened.");

    //Write to file
    xwrite(fid, output, strlen(output));
    puts("File written.");

    //Close file
    xclose((int)fid);
    puts("File closed.");

    return 0;
}