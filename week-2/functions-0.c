#include <cs50.h>
#include <stdio.h>

void PrintName(string name);

int main(void)
{
    printf("Your name: ");
    string s = GetString();
    PrintName(s);
}

void PrintName(string name)
{
    printf("hello, %s\n", name);
}