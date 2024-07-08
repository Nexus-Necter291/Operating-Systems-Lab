#include <include/syscall.h>
#include <unistd.h>

int j_read(void *args)
{
    int fd = ((struct sys_read_arg *)args)->fd;
    void *buf = ((struct sys_read_arg *)args)->buf;
    int count = ((struct sys_read_arg *)args)->count;
    return read(fd, buf, count);
}

int j_write(void *args)
{
    int fd = ((struct sys_write_arg *)args)->fd;
    void *buf = ((struct sys_write_arg *)args)->buf;
    int count = ((struct sys_write_arg *)args)->count;
    return write(fd, buf, count);
}

int j_open(void *args)
{
    char *pathname = ((struct sys_open_arg *)args)->pathname;
    int flags = ((struct sys_open_arg *)args)->flags;
    return open(pathname, flags);
}

int j_close(void *args)
{
    int fd = ((struct sys_close_arg *)args)->fd;
    return close(fd);
}

int j_fork()
{
    return fork();
}