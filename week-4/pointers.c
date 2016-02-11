#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    char* s = GetString();
    
    if (s == NULL)
    {
        return 1;
    }
    
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        printf("%c\n", *(s + i));
    }
}