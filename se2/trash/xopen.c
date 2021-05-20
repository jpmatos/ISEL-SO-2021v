#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>

long xopen(char *str) {
    return syscall(SYS_open, str, O_RDWR | O_CREAT | O_APPEND, 0777);
}