// Program to take name and return initials

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    void initialize(string name);
    
    string name = GetString();
    
    // Check if null
    if (name != NULL)
    {
        initialize(name);
    }
    
    return 0;
}

void initialize(string name)
{
    int start = 0;
    
    // Get first letter as initial, checking for spaces
    while (name[start] == ' ')
    {
        start++;
    }
    
    printf("%c", toupper(name[start]));
    
    // Go through rest of name
    for (int i = start + 1, n = strlen(name); i < n; i++)
    {
        // Get Letter after space
        while (name[i] == ' ')
        {
            i++;
            
            // Only print if next char is not a space
            if (i < n && name[i] != ' ')
            {
                printf("%c", toupper(name[i]));
            }
        }   
    }
    
    // Print new line
    printf("\n");
}