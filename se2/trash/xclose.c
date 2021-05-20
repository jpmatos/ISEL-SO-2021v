#include <unistd.h>
#include <sys/syscall.h>

long xclose(int fd) {
    return syscall(SYS_close, fd);
}