#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void header()
{
    system("clear");
    puts("");
    puts("                           _    _ ___________   ____________ _____  _    _ _____ ___________ ");
    puts("                          | |  | |  ___| ___ \\  | ___ \\ ___ \\  _  || |  | /  ___|  ___| ___ \\");
    puts("                          | |  | | |__ | |_/ /  | |_/ / |_/ / | | || |  | \\ `--.| |__ | |_/ /");
    puts("                          | |/\\| |  __|| ___ \\  | ___ \\    /| | | || |/\\| |`--. \\  __||    / ");
    puts("                          \\  /\\  / |___| |_/ /  | |_/ / |\\ \\ \\_/ /\\  /\\  /\\__/ / |___| |\\ \\ ");
    puts("                           \\/  \\/\\____/\\____/   \\____/\\_| \\_|\\___/  \\/  \\/\\____/\\____/\\_| \\_|");
    puts("");
}

void web_browser(const char *url)
{
    char command[100];
    snprintf(command, sizeof(command), "google-chrome %s", url); // Use "google-chrome" command
    system(command);
}

int main()
{
    header();
    char url[100];
    printf("Enter the URL you want to open: ");
    if (fgets(url, sizeof(url), stdin) == NULL)
    {
        fprintf(stderr, "Error reading URL.\n");
        return 1;
    }

    url[strcspn(url, "\n")] = '\0';

    web_browser(url);
    char c;
    printf("Press any key to continue...");
    scanf(" %c");
    return 0;
}