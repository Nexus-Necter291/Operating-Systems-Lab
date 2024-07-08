#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void header()
{
    system("clear");
    puts("");
    puts("                            _______        _____ _  __   __  __          _   _          _____ ______ _____  ");
    puts("                           |__   __|/\\    / ____| |/ /  |  \\/  |   /\\   | \\ | |   /\\   / ____|  ____|  __ \\ ");
    puts("                              | |  /  \\  | (___ | ' /   | \\  / |  /  \\  |  \\| |  /  \\ | |  __| |__  | |__) |");
    puts("                              | | / /\\ \\  \\___ \\|  <    | |\\/| | / /\\ \\ | . ` | / /\\ \\| | |_ |  __| |  _  / ");
    puts("                              | |/ ____ \\ ____) | . \\   | |  | |/ ____ \\| |\\  |/ ____ \\ |__| | |____| | \\ \\ ");
    puts("                              |_/_/    \\_\\_____/|_|\\_\\  |_|  |_/_/    \\_\\_| \\_/_/    \\_\\_____|______|_|  \\_\\");
    puts("");
    puts("");
}

void task_manager()
{
    int row_count = 1;

    while (1)
    {
        header();
        // system("clear");
        printf("No.    PID\tName\t    CPU Usage   Memory Usage\n");

        FILE *ps_info = popen("ps -eo pid,comm,%cpu,%mem --sort=-%cpu | head -n 10", "r");
        if (ps_info != NULL)
        {
            char line[256];
            while (fgets(line, sizeof(line), ps_info) != NULL)
            {
                int pid;
                char name[50];
                float cpu_usage, mem_usage;
                sscanf(line, "%d %s %f %f", &pid, name, &cpu_usage, &mem_usage);
                printf("%-6d%-9d%-16s%-12.2f%-12.2f\n", row_count++, pid, name, cpu_usage, mem_usage);
            }
            pclose(ps_info);
        }
        else
        {
            printf("Error fetching process information.\n");
        }
        row_count = 1;
        sleep(3);
    }
}

int main()
{
    task_manager();
    return 0;
}