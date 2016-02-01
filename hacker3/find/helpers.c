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
 * Merges two arrays back into parent array
 */
void merge(int values[], int left[], int right[], int middle, int total)
{
    int left_size = middle, right_size = total - middle;
    int i = 0, j = 0;
    
    // Loop through values array
    for (int k = 0; k < total; k++)
    {
        // If elements left on left and either no elements on right or left is
        // larger than right, then use next left value
        if (i < left_size && (j >= right_size || left[i] <= right[j]))
        {
            values[k] = left[i];
            i++;
        }
        // else use next right value
        else
        {
            values[k] = right[j];
            j++;
        }
    }
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // If 1 or less elements stop
    if (n < 2)
    {
        return;
    }
    
    // Set middle value, and left and right arrays
    int middle = n / 2;
    int left[middle];
    int right[n - middle];
        
    // Split values into two arrays
    for (int i = 0; i < n; i++)
    {
        // If less than middle, put in left, otherwise right
        if (i < middle)
        {
            left[i] = values[i];
        }
        else
        {
            right[i - middle] = values[i];
        }
    }
        
    // Sort left and right arrays
    sort(left, middle);
    sort(right, n - middle);
    
    // Merge sorted arrays
    merge(values, left, right, middle, n);
}