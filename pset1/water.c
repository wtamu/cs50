/*
 *  water.c
 *      prompts user for length of shower in minutes
 *      prints equivalent number of bottles of water
 *
 *  Author: wtamura
 *  Date: 2/10/16
 */

#include <stdio.h>
#include <cs50.h>

int main() {
int minute;
    
    printf("minutes: ");
    minute = GetInt();
    
    printf("bottles: %i\n", minute * 12);
    
    return 0;
}