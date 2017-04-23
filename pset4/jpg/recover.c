/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>

#define BUFFER 512
#define TRUE 1
#define FALSE 0

int main(void)
{
    // Create Buffer
    typedef unsigned char BYTE;
    BYTE buf[BUFFER];
    int count = 0;      // Count of JPEGs found
    int found = FALSE;  // Identifies if jpg is found;
    
    /* 1. Open File */
    FILE *card = fopen("card.raw", "r");
    if(card == NULL) {
        fclose(card);
        fprintf(stderr, "Could not create file.\n");
        return -1;
    }
    
    // declare file struct
        FILE *jpg = NULL;
        
    /* 2. Read until EOF */
    while(fread(&buf, BUFFER, 1, card) == 1) {
        
        // start of new jpg?
        if(buf[0] == 0xff && buf[1] == 0xd8 && buf[2] == 0xff && (buf[3] >= 0xe0 && buf[3] <= 0xef)) {
            
            // found is TRUE
            found = TRUE;
            
            // jpg file name
            char jpgname[20];
            sprintf(jpgname, "%.3d.jpg", count);
            
            // increment count
            count++;
            
            // first time jpeg is found
            if(count == 1) {
                // open file for writing image
                jpg = fopen(jpgname, "a");
                if(jpg == NULL) {
                    fclose(jpg);
                    fprintf(stderr, "Count not create jpg number %d!\n", count);
                    return -2;
                }
            }
            // after first time jpeg is found
            else {
                fclose(jpg);
                jpg = fopen(jpgname, "a");
                if(jpg == NULL) {
                    fclose(jpg);
                    fprintf(stderr, "Count not create jpg number %d!\n", count);
                    return -3;
                }
            }

            // write buffer to file
            fwrite(&buf, BUFFER, 1, jpg);
        }
        // already found jpg?
        else if(found == TRUE) {
            fwrite(&buf, BUFFER, 1, jpg);
        }
        // no jpg found
        else {
            continue;
        }
    }
    
    /* Close File */
    fclose(card);
    
    return 0;
}
