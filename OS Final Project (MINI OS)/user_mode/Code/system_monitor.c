#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void header()
{
    system("clear");
    puts("");
    puts("                 _______     _______ _______ ______ __  __   __  __  ____  _   _ _____ _______ ____  _____  ");
    puts("                / ____\\ \\   / / ____|__   __|  ____|  \\/  | |  \\/  |/ __ \\| \\ | |_   _|__   __/ __ \\|  __ \\ ");
    puts("               | (___  \\ \\_/ / (___    | |  | |__  | \\  / | | \\  / | |  | |  \\| | | |    | | | |  | | |__) |");
    puts("                \\___ \\  \\   / \\___ \\   | |  |  __| | |\\/| | | |\\/| | |  | | . ` | | |    | | | |  | |  _  / ");
    puts("                ____) |  | |  ____) |  | |  | |____| |  | | | |  | | |__| | |\\  |_| |_   | | | |__| | | \\ \\ ");
    puts("               |_____/   |_| |_____/   |_|  |______|_|  |_| |_|  |_|\\____/|_| \\_|_____|  |_|  \\____/|_|  \\_\\");
    puts("");
}

void system_monitor()
{
    while (1)
    {
        header();
        FILE *cpu_info = popen("top -bn1 | grep 'Cpu(s)' | sed 's/.*, *\\([0-9.]*\\)%* id.*/\\1/' | awk '{print 100 - $1}'", "r");
        if (cpu_info != NULL)
        {
            float cpu_usage;
            fscanf(cpu_info, "%f", &cpu_usage);
            pclose(cpu_info);

            printf("System Monitor : \n");
            puts("---------------");
            printf("    CPU Usage: %.2f%%\n", cpu_usage);
        }
        else
        {
            printf("Error fetching CPU usage.\n");
        }

        // Get memory usage (in MB)
        FILE *mem_info = popen("free -m | awk '/Mem:/ {print $3}'", "r");
        if (mem_info != NULL)
        {
            int memory_usage;
            fscanf(mem_info, "%d", &memory_usage);
            pclose(mem_info);

            printf("    Memory Usage: %d MB\n", memory_usage);
        }
        else
        {
            printf("Error fetching memory usage.\n");
        }

        // Get disk usage (in GB)
        FILE *disk_info = popen("df -h / | awk 'NR==2 {print $3}'", "r");
        if (disk_info != NULL)
        {
            float disk_usage;
            fscanf(disk_info, "%f", &disk_usage);
            pclose(disk_info);

            printf("    Disk Usage: %.2f GB\n", disk_usage / 1024);
        }
        else
        {
            printf("Error fetching disk usage.\n");
        }

        // Get network activity (incoming and outgoing bytes)
        FILE *net_info = popen("cat /proc/net/dev | grep eth0 | awk '{print $2}' && cat /proc/net/dev | grep eth0 | awk '{print $10}'", "r");
        if (net_info != NULL)
        {
            int incoming_bytes, outgoing_bytes;
            fscanf(net_info, "%d", &incoming_bytes);
            fscanf(net_info, "%d", &outgoing_bytes);
            pclose(net_info);
            puts("");
            printf("Network Activity : \n");
            puts("-----------------");
            printf("    Incoming: %d bytes\n", incoming_bytes);
            printf("    Outgoing: %d bytes\n", outgoing_bytes);
        }
        else
        {
            printf("Error fetching network activity.\n");
        }

        // Refresh every 3 seconds
        sleep(3);
    }
}

int main()
{
    system_monitor();
    return 0;
}
