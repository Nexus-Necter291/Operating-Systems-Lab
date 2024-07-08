#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <time.h>

#define MAX_PROCESSES 10

struct process
{
    int pid;
    float size;
    float cpu_usage;
    __time_t creation_time;
    int status;
};

struct process processes[MAX_PROCESSES];
int process_count = 0;

int ram_remaining = 0;
int cpu_cores_remaining = 0;

void add_process(int pid, float size, float cpu_usage, int priority)
{
    if (process_count < MAX_PROCESSES)
    {
        struct process new_process;
        new_process.pid = pid;
        new_process.size = size;
        new_process.cpu_usage = cpu_usage;
        new_process.creation_time = time(NULL);
        new_process.status = 1;

        processes[process_count++] = new_process;
    }
    else
    {
        printf("Error: Maximum process limit reached.\n");
    }
}

void allocate_resources(int *ram, int *num_cores)
{
    *ram = *ram - 0.5;
    *num_cores = *num_cores - 1;
}

void release_resources(int *ram, int *cores)
{
    *ram += 0.5;
    *cores += 1;
}

void header()
{
    system("clear");
    puts("");
    puts("                            $$\\      $$\\ $$$$$$\\ $$\\   $$\\ $$$$$$\\        $$$$$$\\   $$$$$$\\  ");
    puts("                            $$$\\    $$$ |\\_$$  _|$$$\\  $$ |\\_$$  _|      $$  __$$\\ $$  __$$\\ ");
    puts("                            $$$$\\  $$$$ |  $$ |  $$$$\\ $$ |  $$ |        $$ /  $$ |$$ /  \\__|");
    puts("                            $$\\$$\\$$ $$ |  $$ |  $$ $$\\$$ |  $$ |        $$ |  $$ |\\$$$$$$\\  ");
    puts("                            $$ \\$$$  $$ |  $$ |  $$ \\$$$$ |  $$ |        $$ |  $$ | \\____$$\\ ");
    puts("                            $$ |\\$  /$$ |  $$ |  $$ |\\$$$ |  $$ |        $$ |  $$ |$$\\   $$ |");
    puts("                            $$ | \\_/ $$ |$$$$$$\\ $$ | \\$$ |$$$$$$\\        $$$$$$  |\\$$$$$$  |");
    puts("                            \\__|     \\__|\\______|\\__|  \\__|\\______|       \\______/  \\______/ ");
    puts("");
}

void startup(int ram, int hard_drive_size, int num_cores)
{
    printf("Mini OS is starting with the following specifications:\n");
    printf("RAM: %d GB\n", ram);
    printf("Hard Drive Size: %d GB\n", hard_drive_size);
    printf("Number of CPU Cores: %d\n", num_cores);
    printf("\nCountdown:\n");

    for (int i = 5; i >= 1; i--)
    {
        printf("\r%2d", i);
        fflush(stdout);
        sleep(1);
    }

    printf("\rGO!\n");
    system("clear");
}

int menu()
{
    int input;
    puts("0. Exit ");
    puts("1. Notepad ");
    puts("2. Create File and Check Info ");
    puts("3. Delete File ");
    puts("4. Calculator ");
    puts("5. Check Time ");
    puts("6. System Monitor ");
    puts("7. Task Manager ");
    puts("8. Web Browser ");
    puts("9. Word Guess Game ");
    puts("10. Text to Speech ");
    puts("11. Snake Game ");
    puts("12. Kernel Mode ");
    printf("\nSelect your option : ");
    scanf("%d", &input);
    return input;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s <RAM> <Hard Drive Size> <Number of Cores>\n", argv[0]);
        return 1;
    }
    int ram = atoi(argv[1]);
    int hard_drive_size = atoi(argv[2]);
    int num_cores = atoi(argv[3]);

    startup(ram, hard_drive_size, num_cores);
    ram_remaining = ram;
    cpu_cores_remaining = num_cores;
    while (1)
    {
        header();
        int input = menu();
        if (input == 1)
        {
            int pid = fork();

            if (pid == 0)
            {
                char *args[] = {"./new_terminal", "notepad", NULL};
                execvp(args[0], args);
                perror("execvp");
                return 1;
            }
            else if (pid < 0)
            {
                perror("fork");
                return 1;
            }
            else
            {
                struct rusage usage;
                getrusage(RUSAGE_SELF, &usage);
                double memory_size = usage.ru_maxrss; // Get memory size in kilobytes

                getrusage(RUSAGE_CHILDREN, &usage);
                allocate_resources(&ram_remaining, &cpu_cores_remaining);

                add_process(pid, memory_size, 0, 1);

                int status;
                waitpid(pid, &status, 0);
                release_resources(&ram_remaining, &cpu_cores_remaining);
            }
        }

        else if (input == 2)
        {
            int pid = fork();

            if (pid == 0)
            {
                char *args[] = {"./new_terminal", "create_file", NULL};
                execvp(args[0], args);
                perror("execvp");
                return 1;
            }
            else if (pid < 0)
            {
                perror("fork");
                return 1;
            }
            else
            {
                struct rusage usage;
                getrusage(RUSAGE_SELF, &usage);
                double memory_size = usage.ru_maxrss; // Get memory size in kilobytes

                getrusage(RUSAGE_CHILDREN, &usage);
                double cpu_usage = (usage.ru_utime.tv_sec + usage.ru_stime.tv_sec) +
                                   (usage.ru_utime.tv_usec + usage.ru_stime.tv_usec) / 1000000.0;
                allocate_resources(&ram_remaining, &cpu_cores_remaining);
                add_process(pid, memory_size, cpu_usage, 1);
                waitpid(pid, NULL, 0);
                release_resources(&ram_remaining, &cpu_cores_remaining);
            }
        }
        else if (input == 3)
        {
            int pid = fork();

            if (pid == 0)
            {
                char *args[] = {"./new_terminal", "remove_file", NULL};
                execvp(args[0], args);
                perror("execvp");
                return 1;
            }
            else if (pid < 0)
            {
                perror("fork");
                return 1;
            }
            else
            {
                struct rusage usage;
                getrusage(RUSAGE_SELF, &usage);
                double memory_size = usage.ru_maxrss; // Get memory size in kilobytes

                getrusage(RUSAGE_CHILDREN, &usage);
                double cpu_usage = (usage.ru_utime.tv_sec + usage.ru_stime.tv_sec) +
                                   (usage.ru_utime.tv_usec + usage.ru_stime.tv_usec) / 1000000.0;

                allocate_resources(&ram_remaining, &cpu_cores_remaining);
                add_process(pid, memory_size, cpu_usage, 1);
                waitpid(pid, NULL, 0);
                release_resources(&ram_remaining, &cpu_cores_remaining);
            }
        }
        else if (input == 4)
        {
            int pid = fork();

            if (pid == 0)
            {
                char *args[] = {"./new_terminal", "calculator", NULL};
                execvp(args[0], args);
                perror("execvp");
                return 1;
            }
            else if (pid < 0)
            {
                perror("fork");
                return 1;
            }
            else
            {
                struct rusage usage;
                getrusage(RUSAGE_SELF, &usage);
                double memory_size = usage.ru_maxrss; // Get memory size in kilobytes

                getrusage(RUSAGE_CHILDREN, &usage);
                double cpu_usage = (usage.ru_utime.tv_sec + usage.ru_stime.tv_sec) +
                                   (usage.ru_utime.tv_usec + usage.ru_stime.tv_usec) / 1000000.0;

                allocate_resources(&ram_remaining, &cpu_cores_remaining);
                add_process(pid, memory_size, cpu_usage, 1);
                waitpid(pid, NULL, 0);
                release_resources(&ram_remaining, &cpu_cores_remaining);
            }
        }
        else if (input == 5)
        {
            int pid = fork();

            if (pid == 0)
            {
                char *args[] = {"./new_terminal", "clock", NULL};
                execvp(args[0], args);
                perror("execvp");
                return 1;
            }
            else if (pid < 0)
            {
                perror("fork");
                return 1;
            }
            else
            {
                struct rusage usage;
                getrusage(RUSAGE_SELF, &usage);
                double memory_size = usage.ru_maxrss; // Get memory size in kilobytes

                getrusage(RUSAGE_CHILDREN, &usage);
                double cpu_usage = (usage.ru_utime.tv_sec + usage.ru_stime.tv_sec) +
                                   (usage.ru_utime.tv_usec + usage.ru_stime.tv_usec) / 1000000.0;

                allocate_resources(&ram_remaining, &cpu_cores_remaining);
                add_process(pid, memory_size, cpu_usage, 1);
                waitpid(pid, NULL, 0);
                release_resources(&ram_remaining, &cpu_cores_remaining);
            }
        }
        else if (input == 6)
        {
            int pid = fork();

            if (pid == 0)
            {
                char *args[] = {"./new_terminal", "system_monitor", NULL};
                execvp(args[0], args);
                perror("execvp");
                return 1;
            }
            else if (pid < 0)
            {
                perror("fork");
                return 1;
            }
            else
            {
                struct rusage usage;
                getrusage(RUSAGE_SELF, &usage);
                double memory_size = usage.ru_maxrss; // Get memory size in kilobytes

                getrusage(RUSAGE_CHILDREN, &usage);
                double cpu_usage = (usage.ru_utime.tv_sec + usage.ru_stime.tv_sec) +
                                   (usage.ru_utime.tv_usec + usage.ru_stime.tv_usec) / 1000000.0;

                allocate_resources(&ram_remaining, &cpu_cores_remaining);
                add_process(pid, memory_size, cpu_usage, 1);
                waitpid(pid, NULL, 0);
                release_resources(&ram_remaining, &cpu_cores_remaining);
            }
        }
        else if (input == 7)
        {
            int pid = fork();

            if (pid == 0)
            {
                char *args[] = {"./new_terminal", "task_manager", NULL};
                execvp(args[0], args);
                perror("execvp");
                return 1;
            }
            else if (pid < 0)
            {
                perror("fork");
                return 1;
            }
            else
            {
                struct rusage usage;
                getrusage(RUSAGE_SELF, &usage);
                double memory_size = usage.ru_maxrss; // Get memory size in kilobytes

                getrusage(RUSAGE_CHILDREN, &usage);
                double cpu_usage = (usage.ru_utime.tv_sec + usage.ru_stime.tv_sec) +
                                   (usage.ru_utime.tv_usec + usage.ru_stime.tv_usec) / 1000000.0;

                allocate_resources(&ram_remaining, &cpu_cores_remaining);
                add_process(pid, memory_size, cpu_usage, 1);
                waitpid(pid, NULL, 0);
                release_resources(&ram_remaining, &cpu_cores_remaining);
            }
        }
        else if (input == 8)
        {
            int pid = fork();

            if (pid == 0)
            {
                char *args[] = {"./new_terminal", "web_browser", NULL};
                execvp(args[0], args);
                perror("execvp");
                return 1;
            }
            else if (pid < 0)
            {
                perror("fork");
                return 1;
            }
            else
            {
                struct rusage usage;
                getrusage(RUSAGE_SELF, &usage);
                double memory_size = usage.ru_maxrss; // Get memory size in kilobytes

                getrusage(RUSAGE_CHILDREN, &usage);
                double cpu_usage = (usage.ru_utime.tv_sec + usage.ru_stime.tv_sec) +
                                   (usage.ru_utime.tv_usec + usage.ru_stime.tv_usec) / 1000000.0;

                allocate_resources(&ram_remaining, &cpu_cores_remaining);
                add_process(pid, memory_size, cpu_usage, 1);
                waitpid(pid, NULL, 0);
                release_resources(&ram_remaining, &cpu_cores_remaining);
            }
        }
        else if (input == 9)
        {
            int pid = fork();

            if (pid == 0)
            {
                char *args[] = {"./new_terminal", "word_guess_game", NULL};
                execvp(args[0], args);
                perror("execvp");
                return 1;
            }
            else if (pid < 0)
            {
                perror("fork");
                return 1;
            }
            else
            {
                struct rusage usage;
                getrusage(RUSAGE_SELF, &usage);
                double memory_size = usage.ru_maxrss; // Get memory size in kilobytes

                getrusage(RUSAGE_CHILDREN, &usage);
                double cpu_usage = (usage.ru_utime.tv_sec + usage.ru_stime.tv_sec) +
                                   (usage.ru_utime.tv_usec + usage.ru_stime.tv_usec) / 1000000.0;

                allocate_resources(&ram_remaining, &cpu_cores_remaining);
                add_process(pid, memory_size, cpu_usage, 1);
                waitpid(pid, NULL, 0);
                release_resources(&ram_remaining, &cpu_cores_remaining);
            }
        }
        else if (input == 10)
        {
            int pid = fork();

            if (pid == 0)
            {
                char *args[] = {"./new_terminal", "text_to_speech", NULL};
                execvp(args[0], args);
                perror("execvp");
                return 1;
            }
            else if (pid < 0)
            {
                perror("fork");
                return 1;
            }
            else
            {
                struct rusage usage;
                getrusage(RUSAGE_SELF, &usage);
                double memory_size = usage.ru_maxrss; // Get memory size in kilobytes

                getrusage(RUSAGE_CHILDREN, &usage);
                double cpu_usage = (usage.ru_utime.tv_sec + usage.ru_stime.tv_sec) +
                                   (usage.ru_utime.tv_usec + usage.ru_stime.tv_usec) / 1000000.0;

                allocate_resources(&ram_remaining, &cpu_cores_remaining);
                add_process(pid, memory_size, cpu_usage, 1);
                waitpid(pid, NULL, 0);
                release_resources(&ram_remaining, &cpu_cores_remaining);
            }
        }
        else if (input == 12)
        {
            system("clear");
            puts("                            _  ________ _____  _   _ ______ _         __  __  ____  _____  ______ ");
            puts("                           | |/ /  ____|  __ \\| \\ | |  ____| |       |  \\/  |/ __ \\|  __ \\|  ____|");
            puts("                           | ' /| |__  | |__) |  \\| | |__  | |       | \\  / | |  | | |  | | |__   ");
            puts("                           |  < |  __| |  _  /| . ` |  __| | |       | |\\/| | |  | | |  | |  __|  ");
            puts("                           | . \\| |____| | \\ \\| |\\  | |____| |____   | |  | | |__| | |__| | |____ ");
            puts("                           |_|\\_\\______|_|  \\_\\_| \\_|______|______|  |_|  |_|\\____/|_____/|______|");
            puts("");
            puts("");
            puts("Processes Details : ");
            puts("-------------------");
            printf("PID\t\tCREATION TIME\tSTATUS\n");
            for (int i = 0; i < process_count; i++)
            {
                char creation_time_str[9]; // Buffer to store formatted time (HH:MM:SS)
                strftime(creation_time_str, sizeof(creation_time_str), "%H:%M:%S", localtime(&processes[i].creation_time));

                printf("%d\t\t%s\t%d\n",
                       processes[i].pid, creation_time_str, processes[i].status);
            }
            printf("\nEnter the PID of the process to terminate: ");
            int pid_to_terminate;
            scanf("%d", &pid_to_terminate);

            // Loop through processes to find the matching PID and terminate it
            for (int i = 0; i < process_count; i++)
            {
                if (processes[i].pid == pid_to_terminate)
                {
                    // kill(pid_to_terminate, SIGTERM);
                    processes[i].status = 0; // Update status to indicate terminated
                    printf("Process with PID %d terminated.\n", pid_to_terminate);
                    break; // Exit loop once process is terminated
                }
            }

            printf("\nPress any key to continue...");
            getchar(); // Consume newline character left by scanf
            getchar(); // Wait for user to press any key
        }

        else if (input == 11)
        {
            int pid = fork();

            if (pid == 0)
            {
                char *args[] = {"./new_terminal", "snake_game", NULL};
                execvp(args[0], args);
                perror("execvp");
                return 1;
            }
            else if (pid < 0)
            {
                perror("fork");
                return 1;
            }
            else
            {
                struct rusage usage;
                getrusage(RUSAGE_SELF, &usage);
                double memory_size = usage.ru_maxrss; // Get memory size in kilobytes

                getrusage(RUSAGE_CHILDREN, &usage);
                double cpu_usage = (usage.ru_utime.tv_sec + usage.ru_stime.tv_sec) +
                                   (usage.ru_utime.tv_usec + usage.ru_stime.tv_usec) / 1000000.0;

                allocate_resources(&ram_remaining, &cpu_cores_remaining);
                add_process(pid, memory_size, cpu_usage, 1);
                waitpid(pid, NULL, 0);
                release_resources(&ram_remaining, &cpu_cores_remaining);
            }
        }

        else if (input == 0)
        {
            break;
        }
    }
    return 0;
}