#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("Temperature in F: ");
    float f = GetFloat();
    
    float c = 5.0 / 9.0 * (f - 32.0);
    
    printf("%.1f\n", c);
}
