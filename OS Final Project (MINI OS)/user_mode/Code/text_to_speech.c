#include <stdio.h>
#include <stdlib.h>

void header()
{
    system("clear");
    puts("");
    puts("                           _____ _______   _______    _____ _____    ___________ _____ _____ _____  _   _ ");
    puts("                          |_   _|  ___\\ \\ / /_   _|  |_   _|  _  |  /  ___| ___ \\  ___|  ___/  __ \\| | | |");
    puts("                            | | | |__  \\ V /  | |      | | | | | |  \\ `--.| |_/ / |__ | |__ | /  \\/| |_| |");
    puts("                            | | |  __| /   \\  | |      | | | | | |   `--. \\  __/|  __||  __|| |    |  _  |");
    puts("                            | | | |___/ /^\\ \\ | |      | | \\ \\_/ /  /\\__/ / |   | |___| |___| \\__/\\| | | |");
    puts("                            \\_/ \\____/\\/   \\/ \\_/      \\_/  \\___/   \\____/\\_|   \\____/\\____/ \\____/\\_| |_/");
    puts("");
}

int main()
{
    header();
    char sentence[1000];

    printf("Enter a sentence: ");
    fgets(sentence, sizeof(sentence), stdin);

    printf("You entered: %s", sentence);

    char command[1100];
    snprintf(command, sizeof(command), "echo \"%s\"| festival --tts", sentence);
    system(command);

    printf("\nPress any key to continue...");
    return 0;
}
