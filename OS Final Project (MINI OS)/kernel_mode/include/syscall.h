#include <stdint.h>

struct sys_read_arg
{
    uint32_t fd;
    void *buf;
    uint64_t count;
};

struct sys_write_arg
{
    uint32_t fd;
    void *buf;
    uint64_t count;
};

struct sys_open_arg
{
    char *pathname;
    uint32_t flags;
    __mode_t mode;
};

struct sys_close_arg
{
    uint32_t fd;
};
