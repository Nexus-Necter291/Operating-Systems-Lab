#include <stdio.h>
#include <stdlib.h>

void system_settings()
{
    // Display current date and time
    printf("Current Date and Time : \n");
    puts("---------------------");
    system("date");

    // Display system uptime
    printf("\nSystem Uptime :\n");
    puts("--------------");
    system("uptime");

    // Display CPU information
    printf("\nCPU Information :\n");
    puts("---------------");
    system("cat /proc/cpuinfo | grep 'model name' | uniq");
}

int main()
{
    printf("System Settings\n");

    // Display system information
    system_settings();

    return 0;
}