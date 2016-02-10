#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("Say something: ");
    string s = GetString();
    
    printf("Say something: ");
    string t = GetString();
    
    if (s == t)
    {
        printf("You typed the same thing!\n");
    }
    else
    {
        printf("You typed different things!\n");
    }
}