// Program to determine the minimum number of coins needed when making change

#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    float change;
    int coins, cents;
	
    printf("O hai! ");
	
    // Get change owed, must be positive
    do
    {
        printf("How much change is owed?\n");
        change = GetFloat();
	}
    while (change < 0);
	
    // Avoid imprecision by converting to cents
    cents = (int) round(change * 100);
	
    // Initialize coins
    coins = 0;
	
    // Modulo math - Quarters
    coins += cents / 25;
    cents %= 25;
	
    // Modulo - Dimes
    coins += cents / 10;
    cents %= 10;
	
    // Modulo - Nickels
    coins += cents / 5;
    cents %= 5;
	
    // Pennies
    coins += cents;
	
    // Print Result
    printf("%i\n", coins);
	
    return 0;
}