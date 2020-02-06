/**
 * resize.c
 *
 * Robert Waite
 * Computer Science 50
 * Problem Set 5
 * clang -ggd3 -O0 -std=c99 -Wall -Werror resize.c -lcs50 -lm -o resize
 *
 * Resizes a BMP by number provided from user.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

#define HEADERSIZE 54
#define RATIO 8

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy sizeFactor infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // remember number from user
    int resizeFactor = atoi(argv[1]);
    
    // check resizeFactor within range 1-100
    if(resizeFactor < 1 || resizeFactor > 100)
    {
        printf("resize within 1-100 \n");
        return 2;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
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
    
    // biWidth = old x resizeFactor
    long biWidth = bi.biWidth * resizeFactor;
    
     // determine padding for scanlines
    int padding =  (4 - (biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // biHeight = abs of biHeight * resizeFactor
    long biHeight = abs(bi.biHeight) * resizeFactor;
    
    // if old is negative make new negative
    if(bi.biHeight < 0)
    {
        biHeight = -biHeight;
    }
    
    
    // biSizeImage = (biWidth + padding) * abs(biHeight)
    DWORD biSizeImage = ((biWidth * sizeof(RGBTRIPLE))+ padding) * abs(biHeight);
    
    
    // bfSize = biSizeImage + header
    DWORD bfSize = biSizeImage  + HEADERSIZE;
   
    
    // get Original Values
    long originalWidth = bi.biWidth;
    long originalHeight = bi.biHeight;
    int originalPadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // write new values to bf and bi
    bi.biWidth = biWidth;
    bi.biHeight = biHeight;
    bi.biSizeImage = biSizeImage;
    
    bf.bfSize = bfSize;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // make array new scanline width
    RGBTRIPLE scanlinePixels[biWidth];
    
    // vertical
    for(int i = 0; i < abs(originalHeight); i++)
    {

    	int counter = 0;
    
        // horzontal
    	for(int j = 0; j < originalWidth; j++)
    	{
        
        	// temporary storage
        	RGBTRIPLE triple;
        
        	// read RGB triple from infile
		fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
		
        	// write resizeFactor number of times to scanlinePixels
        	for(int k = 0; k < resizeFactor; k++)
        	{
            		scanlinePixels[counter] = triple;
            		counter++;
            
       		 }

		


    	}

	// skip over padding, if any
       		fseek(inptr, originalPadding, SEEK_CUR);

   	for(int l = 0; l < resizeFactor; l++)
    	{

    		// write scanlinePixels to outfile
    		fwrite(&scanlinePixels, sizeof(scanlinePixels[0]), biWidth, outptr);

		    for (int m = 0; m < padding; m++)
            	{
                fputc(0x00, outptr);
            	}
   	    }
    }
  

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
