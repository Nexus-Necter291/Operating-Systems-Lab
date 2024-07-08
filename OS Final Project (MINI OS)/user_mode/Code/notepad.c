#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>

#define MAX_CONTENT_LENGTH 1024

void notepad(char filename[])
{
    char content[MAX_CONTENT_LENGTH];
    int fd;

    fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    printf("Type your content. Press ESC to save and exit.\n");

    // Disable buffered input for immediate character reading
    struct termios old_term, new_term;
    if (tcgetattr(STDIN_FILENO, &old_term) == -1)
    {
        perror("tcgetattr");
        return 1;
    }
    new_term = old_term;
    new_term.c_lflag &= ~ICANON;
    new_term.c_cc[VMIN] = 1; // Read one character at a time
    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_term) == -1)
    {
        perror("tcsetattr");
        return 1;
    }

    int content_length = 0;
    char ch;
    while ((ch = getchar()) != 27)
    {
        if (content_length < MAX_CONTENT_LENGTH - 1)
        {
            content[content_length++] = ch;
        }
        else
        {
            printf("Warning: Maximum content length reached. Truncating.\n");
        }
    }

    content[content_length] = '\0'; // Null-terminate the content string

    // Restore terminal settings after reading all characters
    if (tcsetattr(STDIN_FILENO, TCSANOW, &old_term) == -1)
    {
        perror("tcsetattr");
        return 1;
    }

    // Write content to the file
    ssize_t bytes_written = write(fd, content, content_length);
    if (bytes_written == -1)
    {
        perror("write");
        close(fd);
        return 1;
    }

    printf("\nContent saved successfully to '%s'\n", filename);

    close(fd);
}

void header()
{
    system("clear");
    puts("");
    puts("                                _   _  ____ _______ ______ _____        _____  ");
    puts("                               | \\ | |/ __ \\__   __|  ____|  __ \\ /\\   |  __ \\ ");
    puts("                               |  \\| | |  | | | |  | |__  | |__) /  \\  | |  | |");
    puts("                               | . ` | |  | | | |  |  __| |  ___/ /\\ \\ | |  | |");
    puts("                               | |\\  | |__| | | |  | |____| |  / ____ \\| |__| |");
    puts("                               |_| \\_|\\____/  |_|  |______|_| /_/    \\_\\_____/ ");
    puts("");
}

int main()
{
    header();
    char filename[100];
    printf("Enter filename : ");
    if (fgets(filename, sizeof(filename), stdin) == NULL)
    {
        perror("fgets");
        return 1;
    }
    filename[strcspn(filename, "\n")] = '\0';

    notepad(filename);
}
