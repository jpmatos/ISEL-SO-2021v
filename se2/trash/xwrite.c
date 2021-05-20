#include <unistd.h>
#include <sys/syscall.h>

long xwrite(int fd, const void *str, size_t len) {
    return syscall(SYS_write, fd, str, len);
}