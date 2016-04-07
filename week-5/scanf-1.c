#include <stdio.h>

int main(void)
{
    char* s;
    printf("String please: ");
    scanf("%s", s);
    printf("Thanks for the %s!\n", s);
}