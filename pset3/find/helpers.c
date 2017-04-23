/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */

#include <stdio.h>
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{

int min = 0;
int max = n;
int mid;

    // Print vals
    // printf("value: %d, size: %d, max: %d\n", value, n, max);
    
    while(min <= max) {
        
        // Get midpoint
        mid = (min + max) / 2;
        
        if(values[mid] > value) {
            max = mid - 1;
        }
        else if (values[mid] < value) {
            min = mid + 1;
        }
        else if (values[mid] == value) {
            return true;
        }
    }
    
    return false;
}

// Function Prototype
void swap(int *small, int *big);

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n - i; j++) {
            if(values[j] > values[j + 1])
                swap(&values[j], &values[j + 1]);
        }
    }
    
    // Print to test sorting
    // for(int i = 0; i < n; i++)
       // printf("Sorted: %d\n", values[i]);

    return;
}

/**
 *  Swaps elements
 */ 
void swap(int *a, int *b) {
int temp;
    
    temp = *a;
    *a = *b;
    *b = temp;
    
    // printf("Swap: a:%d, b:%d, temp:%d\n", *a, *b, temp);
    
    return;
}