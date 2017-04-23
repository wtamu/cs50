/*
 *  greedy.c
 *      asks user how much change is owed
 *      prints minimum number of coins to make change
 *      
 *  Author: wtamura
 *  Date: 2/10/16
 */
 
#include <stdio.h>
#include <cs50.h>
#include <math.h>

#define QUARTER 25
#define DIME    10
#define NICKEL   5
#define PENNY    1

int main() {

// Declare Variables
float change;
int x, n_quarter, n_dime, n_nickel, n_penny;

// Init Count to Zero
n_quarter = n_dime = n_nickel = n_penny = 0;

    // Prompt User
    do {
        printf("Change Owed: ");
        change = GetFloat();
    } while(change < 0.0);
    
    // Convert to Int
    x = roundf(change * 100.0);
    
    // Quarters
    while (x - QUARTER >= 0) {
        x = x - QUARTER;
        n_quarter++;
    }
    
    // Dimes
    while (x - DIME >= 0) {
        x = x - DIME;
        n_dime++;
    }
    
    // Nickels
    while (x - NICKEL >= 0) {
        x = x - NICKEL;
        n_nickel++;
    }
    
    // Pennies
    while (x - PENNY >= 0) {
        x = x - PENNY;
        n_penny++;
    }
    
    printf("%d\n", n_quarter + n_dime + n_nickel + n_penny);
    
    return 0;
}