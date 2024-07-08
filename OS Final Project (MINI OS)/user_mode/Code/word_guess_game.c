#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_WORDS 30
#define MAX_WORD_LENGTH 20

void header()
{
    system("clear");
    puts("");
    puts("                       _    _  _________________    _____ _   _ _____ _____ _____    _____   ___  ___  ___ _____ ");
    puts("                      | |  | ||  _  | ___ \\  _  \\  |  __ \\ | | |  ___/  ___/  ___|  |  __ \\ / _ \\ |  \\/  ||  ___|");
    puts("                      | |  | || | | | |_/ / | | |  | |  \\/ | | | |__ \\ `--.\\ `--.   | |  \\// /_\\ \\| .  . || |__  ");
    puts("                      | |/\\| || | | |    /| | | |  | | __| | | |  __| `--. \\`--. \\  | | __ |  _  || |\\/| ||  __| ");
    puts("                      \\  /\\  /\\ \\_/ / |\\ \\| |/ /   | |_\\ \\ |_| | |___/\\__/ /\\__/ /  | |_\\ \\| | | || |  | || |___ ");
    puts("                       \\/  \\/  \\___/\\_| \\_|___/     \\____/\\___/\\____/\\____/\\____/    \\____/\\_| |_/\\_|  |_/\\____/ ");
    puts("");
}

char *get_random_word()
{
    const char *words[MAX_WORDS] = {
        "apple", "banana", "cherry", "orange", "grape",
        "strawberry", "pineapple", "watermelon", "kiwi", "mango",
        "blueberry", "peach", "lemon", "lime", "plum",
        "pear", "apricot", "pomegranate", "cranberry", "blackberry",
        "chair", "table", "desk", "lamp", "book",
        "computer", "keyboard", "mouse", "phone", "paper"};

    int index = rand() % MAX_WORDS;
    return strdup(words[index]);
}

int main()
{
    int word_found = 1;
    header();
    puts("");
    srand(time(0)); // Seed the random number generator
    char *secret_word = get_random_word();
    int word_length = strlen(secret_word);
    char *guessed_word = malloc(word_length + 1);
    memset(guessed_word, '_', word_length);
    guessed_word[word_length] = '\0';

    int attempts = 0;
    int correct_guesses = 0;
    char guess;

    printf("Welcome to Guess the Word!\n");
    printf("The secret word has %d letters.\n", word_length);

    while (correct_guesses < word_length)
    {
        printf("Secret word: %s\n", guessed_word);
        printf("Enter a letter guess: ");
        scanf(" %c", &guess);
        guess = tolower(guess); // Convert guess to lowercase for case insensitivity

        int found = 0;
        for (int i = 0; i < word_length; i++)
        {
            if (secret_word[i] == guess && guessed_word[i] != guess)
            {
                guessed_word[i] = guess;
                correct_guesses++;
                found = 1;
            }
        }

        if (!found)
        {
            attempts++;
            printf("Incorrect guess! Attempts: %d\n", attempts);
            if (attempts == 5)
            {
                word_found = 0;
                break;
            }
        }
    }

    if (word_found)
    {
        puts("");
        printf("Congratulations! You guessed the word \"%s\" in %d attempts.\n", secret_word, attempts);
    }
    else
    {
        puts("");
        printf("\t\t\t\tOops! Don't give up! Keep trying and you'll get it next time!\n");
        printf("\t\t\t\tThe secret word was %s.\n", secret_word);
    }
    char c;
    printf("Press any key to continue...");
    scanf(" %c"); // Wait for any key press
    free(secret_word);
    free(guessed_word);

    return 0;
}