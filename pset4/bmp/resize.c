/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // *** ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    // *** Error Checking: argv[1] isdigit
    for(int i = 0, len = strlen(argv[1]); i < len; i++)
        if(!isdigit(argv[1][i])) {
            //printf("Error! Non-numeric resize value...\n");
            return -1;
        }
            
    // *** remember resize value
    int resize = atoi(argv[1]);
    
    // *** Error Checking: 0 < argv[1] <= 100
    if(resize < 1 || resize > 100) {
        //printf("Error! Resize value should be within 1 to 100...\n");
        return -2;
    }
    
    // *** remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // Store infile values
    int in_biWidth = bi.biWidth;
    int in_biHeight = bi.biHeight;
    //printf("in_biWidth = %d\n", in_biWidth);
    //printf("in_biHeight = %d\n", in_biHeight);
    
    // Modify outfile values
    bi.biWidth *= resize;
    bi.biHeight *= resize;
    //printf("bi.biWidth = %d\n", bi.biWidth);
    //printf("bi.biHeight = %d\n", bi.biHeight);
    
    int new_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //printf("new_padding = %d\n", new_padding);
    
    bi.biSizeImage = ((bi.biWidth * sizeof(RGBTRIPLE)) + new_padding) * abs(bi.biHeight);
    bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (bi.biSizeImage);
    //printf("bi.biSizeImage = %d\n", bi.biSizeImage);
    //printf("bf.bfSize = %d\n", bf.bfSize);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding =  (4 - (in_biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //printf("padding = %d\n", padding);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(in_biHeight); i < biHeight; i++)
    {
        // Store scanline to repeat *resize* times
        RGBTRIPLE a[1000];
        int index = 0;
        
        // iterate over pixels in scanline
        for (int j = 0; j < in_biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // write RGB triple to outfile
            for(int w1 = 0; w1 < resize; w1++) {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                a[index++] = triple;
            }
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < new_padding; k++)
            fputc(0x00, outptr);
        
        // Repeat for resize Height
        for(int w2 = 0; w2 < resize - 1; w2++) {
            for(int w3 = 0; w3 < index; w3++) {
                fwrite(&a[w3], sizeof(RGBTRIPLE), 1, outptr);
            }
            // Padding
            for (int k = 0; k < new_padding; k++)
                fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
