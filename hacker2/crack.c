// Brute Force crack crypt() encrypted password

#define _XOPEN_SOURCE
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, string argv[])
{
    void incrementChar(char string[], int index);

    // Check if correct # of arguments given
    if (argc != 2)
    {
        printf("Wrong number of arguments. Please try again.\n");

        return 1;
    }

    // Get Salt
    char salt[3];
    strncpy(salt, argv[1], 2);
    salt[2] = '\0';

    // Load dictionary of words
    FILE *dict = fopen("/usr/share/dict/words", "r");
    char word[255];

    // Check if file loads, otherwise return error
    if (dict == NULL)
    {
        printf("Error opening file");

        return 1;
    }

    // Loop through file to get strings
    while (fgets(word, 255, (FILE*)dict) != NULL)
    {
        // Check if word is 8 chars and if running crypt on word equals input
        if (strlen(word) <= 9 && strcmp(crypt(word, salt), argv[1]) == 0)
        {
            // Print password
            printf("%s", word);

            return 0;
        }
    }

    // Close file
    fclose(dict);

    // If not in the dictionary, brute force it
    // Initialize string to all null characters
    char test[9] = { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' };

    do
    {
        // Compares until next null character
        if (strcmp(crypt(test, salt), argv[1]) == 0)
        {
            // Print password
            printf("%s\n", test);

            return 0;
        }

        // Increment letter
        incrementChar(test, 0);
    }
    while (test[8] == '\0');

    printf("Password not found\n");

    return 0;
}

// Function to increment character and carry over if necessary
void incrementChar(char string[], int index)
{
    if (string[index] == '\0')
    {
        string[index] = '!';
    }
    else if (string[index] == '~')
    {
        string[index] = '!';
        incrementChar(string, index + 1);
    }
    else
    {
        string[index]++;
    }
}
