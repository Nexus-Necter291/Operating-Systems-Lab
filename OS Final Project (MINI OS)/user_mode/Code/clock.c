#include <stdio.h>
#include <time.h>
#include <unistd.h>

void header()
{
    system("clear");
    puts("");
    puts("                                                  _____  _     _____ _____  _   __");
    puts("                                                 /  __ \\| |   |  _  /  __ \\| | / /");
    puts("                                                 | /  \\/| |   | | | | /  \\/| |/ / ");
    puts("                                                 | |    | |   | | | | |    |    \\ ");
    puts("                                                 | \\__/\\| |___\\ \\_/ / \\__/\\| |\\  \\");
    puts("                                                  \\____/\\_____/\\___/ \\____/\\_| \\_/");
    puts("");
}

int main()
{
    while (1)
    {
        printf("\033[H\033[J");
        header();

        time_t currentTime;
        struct tm *localTime;

        time(&currentTime);
        localTime = localtime(&currentTime);

        printf("Current time: %02d:%02d:%02d %s\n",
               (localTime->tm_hour > 12) ? (localTime->tm_hour - 12) : localTime->tm_hour,
               localTime->tm_min, localTime->tm_sec,
               (localTime->tm_hour >= 12) ? "PM" : "AM");

        printf("Current date: %02d/%02d/%04d\n",
               localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900);

        sleep(1);
    }

    return 0;
}