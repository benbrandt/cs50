/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // Ensure value is positive
    if (value < 0)
    {
        return false;
    }
    
    // Set initial min and max values
    int min = 0, max = n - 1;
    
    // While there are still elements in the list
    while (n > 0)
    {
        // Set middle to half of difference between min and max
        int middle = (max - min) / 2 + min;
        
        // If value is middle value, return true
        if (values[middle] == value)
        {
            return true;
        }
        // If value is less than middle, set max to one less than middle
        else if (values[middle] > value)
        {
            max = middle - 1;
        }
        
        // If value is greater than middle, set min to one greater than middle
        else if (values[middle] < value)
        {
            min = middle + 1;
        }
        
        // Set new number of elements to those between min and max
        n = max - min + 1;
    }
    
    // If number is not found, return false
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // selection sorting algorithm
    for (int i = 0; i < n - 1; i++)
    {
        // Set minimum
        int min = i;
        
        for (int j = i; j < n; j++) 
        {
            // Find index of minimum value
            if (values[min] > values[j])
            {
                min = j;
            }
        }
        
        // Check if min changed
        if (min != i)
        {
            // swap i with lowest value
            int temp = values[min];
            values[min] = values[i];
            values[i] = temp;
        }
    }
    
    return;
}
