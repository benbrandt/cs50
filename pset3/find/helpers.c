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
    
    // Linear search through array
    for (int i = 0; i < n; i++)
    {
        if (values[i] == value)
        {
            return true;
        }
    }
    
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