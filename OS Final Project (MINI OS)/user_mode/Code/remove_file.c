#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void header()
{
    system("clear");
    puts("");
    puts("                              ______ ________  ________  _   _ _____   ______ _____ _      _____ ");
    puts("                              | ___ \\  ___|  \\/  |  _  || | | |  ___|  |  ___|_   _| |    |  ___|");
    puts("                              | |_/ / |__ | .  . | | | || | | | |__    | |_    | | | |    | |__  ");
    puts("                              |    /|  __|| |\\/| | | | || | | |  __|   |  _|   | | | |    |  __| ");
    puts("                              | |\\ \\| |___| |  | \\ \\_/ /\\ \\_/ / |___   | |    _| |_| |____| |___ ");
    puts("                              \\_| \\_\\____/\\_|  |_/\\___/  \\___/\\____/   \\_|    \\___/\\_____/\\____/ ");
    puts("");
}

void remove_file(const char *filename)
{
    if (remove(filename) == 0)
    {
        printf("\n\t\t\t\tFile '%s' removed successfully.\n", filename);
    }
    else
    {
        printf("\n\t\t\t\tError removing file '%s'. File not found or permission denied.\n", filename);
    }
}

int main()
{
    header();
    char filename[100];

    printf("Enter filename to remove: ");
    scanf("%s", filename);

    if (access(filename, F_OK) != -1)
    {
        remove_file(filename);
    }
    else
    {
        printf("\n\t\t\t\tError: File '%s' not found in the current directory.\n", filename);
    }

    char c;
    printf("\nPress any key to continue...");
    scanf(" %c", &c);

    return 0;
}