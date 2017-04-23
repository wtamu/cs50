/*
 *  vigenere.c
 *      accepts single command line argument, alphabetical keyword
 *      prompts user for text
 *      encrypts text, rotate by keyword
 *
 *  Author: wtamura
 *  Date: 2/11/16
 */

#include <stdio.h>
#include <string.h>     // strlen()
#include <ctype.h>      // isalpha()
#include <cs50.h>

int main(int argc, char* argv[]) {

    // Error Checking: number of arguments
    if(argc != 2) {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    
    // Error Checking: argument is alpha
    for(int i = 0, j = strlen(argv[1]); i < j; i++) {
        if(!isalpha(argv[1][i])) {
            printf("Invalid character input");
            return 1;  
        }
    }
    
    // Get key
    char *k = argv[1];
    int k_len = strlen(k);
    
    // Get text
    // printf("Text: ");
    char *s = GetString();
    
    // Encrypt text
    for(int i = 0, j = strlen(s), k_index = 0; i < j; i++) {
        
        // If alpha, uppercase
        if(isupper(s[i])) {
            printf("%c", 'A' + (((s[i] - 'A') + (toupper(k[k_index]) - 'A')) % 26));
            k_index = (k_index + 1) % k_len;
        }
        // If alpha, lowercase
        else if(islower(s[i])) {
            printf("%c", 'a' + (((s[i] - 'a') + (tolower(k[k_index]) - 'a')) % 26));
            k_index = (k_index + 1) % k_len;
        }
        else {
            printf("%c", s[i]);
        }
    }
    printf("\n");
    
    return 0;
}