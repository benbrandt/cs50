// Program to take name and return initials

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    void initialize(string name);
    
    string name = GetString();
    
    if (name != NULL)
    {
        initialize(name);
    }
    
    return 0;
}

void initialize(string name)
{
    // Get first letter as initial
    printf("%c", toupper(name[0]));
    
    // Go through rest of name
    for (int i = 1, n = strlen(name); i < n; i++)
    {
        // Get Letter after space
        if (name[i] == ' ')
        {
            printf("%c", toupper(name[i + 1]));
        }   
    }
    
    // Print new line
    printf("\n");
}