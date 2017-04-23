/*
 *  caesar.c
 *      accept single command line argument, non-negative int
 *      prompt user for string
 *      print cipher text, rotate by k
 *
 *  Author: wtamura
 *  Date: 2/11/16
 */

#include <stdio.h>
#include <stdlib.h>     // atoi()
#include <string.h>     // strlen()
#include <ctype.h>      // isdigit()
#include <cs50.h>


int main(int argc, char* argv[]) {

int k;
char* s;

    // Error Check: number of arguments
    if(argc != 2) {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    // Error Check: argument is non-negative integer
    for(int i = 0, j = strlen(argv[1]); i < j; i++) {
        if(!isdigit(argv[1][i]))
            return 2;
    }
    
    // Get key
    k = atoi(argv[1]);
    
    // Get text
    // printf("Text: ");
    s = GetString();
    
    // Encrypt text
    for(int i = 0, j = strlen(s); i < j; i++) {
        
        // If alpha, uppercase
        if(isupper(s[i])) {
            printf("%c", 'A' + (((s[i] - 'A') + k) % 26));
        }
        // If alpha, lowercase
        else if(islower(s[i])) {
            printf("%c", 'a' + (((s[i] - 'a') + k) % 26));
        }
        else {
            printf("%c", s[i]);
        }
        
    }
    printf("\n");
    
    return 0;
}