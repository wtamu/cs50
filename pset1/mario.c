/*
 *  mario.c
 *      creates half pyramid using hashes (#)
 *      prompt user for pyramid height, <= 23
 *      reprompt if not non-negative integer
 *      print pyramid, aligning bottom-left corner
 *
 *  Author: wtamura
 *  Date: 2/10/16
 */
 
#include <stdio.h>
#include <cs50.h>

int main(){
int height, hash, space;    
    
    // Prompt User
    do {
        printf("Height: ");
        height = GetInt();
    } while(height < 0 || height > 23);
    
    for(int i = 1; i <= height; i++) {
        
        // Spaces
        for(space = height - i; space > 0; space--)
            printf(" ");
        
        // Hashes
        for(hash = i + 1; hash > 0; hash--)
            printf("#");
        
        // New Line
        printf("\n");
    }
    
    return 0;   
}