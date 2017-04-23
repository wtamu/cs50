/*
 *  initials.c
 *      prompt user for name
 *      print initials, uppercase and no spaces
 *
 *  Author: wtamura
 *  Date: 2/11/16
 */

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>

#define IN 1
#define OUT 0

int main() {
// Declare Variables
char* s;
int state;

    // Prompt User
    // printf("Name: ");
    s = GetString();
    
    // Iterate over string
    state = OUT;
    for(int i = 0; s[i] != '\0'; i++) {
        
        // If alpha
        if(isalpha(s[i])) {
           if(state == OUT) {
                printf("%c", toupper(s[i]));
                state = IN;
           } 
        }
        // If space
        else if(isspace(s[i])) {
            if(state == IN) {
                state = OUT;    
            }
        }
    }
    printf("\n");
    
    return 0;
}