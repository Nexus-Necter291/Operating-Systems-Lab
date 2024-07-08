#include <stdint.h>
#include <include/syscall_table.h>
#include "driver.c"

int syscall_handler(int syscall_num, void *args[])
{
    if (syscall_num == sys_read)
    {
        j_read(args);
    }

    else if (syscall_num == sys_write)
    {
        j_write(args);
    }

    else if (syscall_num == sys_open)
    {
        j_open(args);
    }

    else if (syscall_num == sys_close)
    {
        j_close(args);
    }

    else if (syscall_num == sys_fork)
    {
        j_fork();
    }
}
