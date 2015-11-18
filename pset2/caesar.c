// Caesar cipher

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Check if correct # of arguments given
    if (argc != 2 && !isdigit(argv[1]))
    {
        return 1;
    }
    
    // Convert input to int type
    int k = atoi(argv[1]);
    
    // Get text to encode
    string p = GetString();
    
    // Loop through text
    for (int i = 0, n = strlen(p); i < n; i++)
    {            
        // Keep case of letter
        if (isupper(p[i]))
        {
            // Get modulo number and add to appropriate case
            printf("%c", 'A' + (p[i] - 'A' + k) % 26);
        }
        else if (islower(p[i]))
        {
            printf("%c", 'a' + (p[i] - 'a' + k) % 26);
        }
        else
        {
            // return unchanged
            printf("%c", p[i]);
        }
    }
    
    printf("\n");
    
    return 0;
}