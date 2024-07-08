#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <executable_file>\n", argv[0]);
        return 1;
    }

    char command[100];

    // Detect and use available terminal emulator
    if (system("which gnome-terminal > /dev/null 2>&1") == 0)
    {
        snprintf(command, sizeof(command), "gnome-terminal -e './%s'", argv[1]);
    }
    else if (system("which konsole > /dev/null 2>&1") == 0)
    {
        snprintf(command, sizeof(command), "konsole -e './%s'", argv[1]);
    }
    else if (system("which xfce4-terminal > /dev/null 2>&1") == 0)
    {
        snprintf(command, sizeof(command), "xfce4-terminal -e './%s'", argv[1]);
    }
    else
    {
        printf("No supported terminal emulator found.\n");
        return 1;
    }

    system(command);
    return 0;
}
