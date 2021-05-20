#include <stddef.h>
#ifndef SYSCALLS_H
#define SYSCALLS_H

long xgetpid();
long xopen(char *str);
long xwrite(int fd, const void *str, size_t len);
long xclose(int fd);

#endif
