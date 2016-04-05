/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, resizing by n
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    // get amount to resize by
    int n = atoi(argv[1]);
    
    // Ensure n is between 1 and 100
    if (n < 1 || n > 100)
    {
        printf("n must be between 1 and 100\n");
        return 2;
    }

    // remember filenames
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
    BITMAPFILEHEADER in_bf, out_bf;
    fread(&in_bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER in_bi, out_bi;
    fread(&in_bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    // Get Original file's padding
    int oldPadding =  (4 - (in_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    out_bf = in_bf;
    out_bi = in_bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (out_bf.bfType != 0x4d42 || out_bf.bfOffBits != 54 || out_bi.biSize != 40 || 
        out_bi.biBitCount != 24 || out_bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // Update width, and height in Bitmap info header
    out_bi.biWidth *= n;
    out_bi.biHeight *= n;
    
    // determine padding for scanlines
    int newPadding =  (4 - (out_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // Update size in Bitmap info header
    out_bi.biSizeImage = out_bi.biWidth * abs(out_bi.biHeight) * 
        sizeof(RGBTRIPLE) + newPadding * abs(out_bi.biHeight);
    
    // Update Size in Bitmap File Header
    out_bf.bfSize = out_bf.bfOffBits + out_bi.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&out_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&out_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(in_bi.biHeight); i < biHeight; i++)
    {
        // Setup array to store pixels in
        RGBTRIPLE row[out_bi.biWidth];
        int current_pixel = 0;
        
        // iterate over pixels in scanline
        for (int k = 0; k < in_bi.biWidth; k++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // Repeat each pixel n times
            for (int m = 0; m < n; m++, current_pixel++)
            {
                row[current_pixel] = triple;
            }
        }
        
        // repeat each row n times
        for (int j = 0; j < n; j++)
        {
            // Write row to out file
            fwrite(&row, sizeof(row), 1, outptr);
            
            // Add padding to new file
            for (int p = 0; p < newPadding; p++)
            {
                fputc(0x00, outptr);
            }   
        }
        
        // skip over padding in old file, if any
        fseek(inptr, oldPadding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
