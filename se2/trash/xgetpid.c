#include <unistd.h>
#include <sys/syscall.h>

long xgetpid() {
    long sysPid = syscall(SYS_getpid);
    return sysPid;
}