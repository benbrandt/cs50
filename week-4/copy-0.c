#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    printf("Say something: ");
    char* s = GetString();
    
    if (s == NULL)
    {
        return 1;
    }
    
    string t = s;
    
    printf("Capitalizing copy...\n");
    
    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }
    
    printf("Original: %s\n", s);
    printf("Copy:     %s\n", t);
}