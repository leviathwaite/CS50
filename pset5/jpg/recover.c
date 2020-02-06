/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 * clang -ggd3 -O0 -std=c99 -Wall -Werror recover.c -lcs50 -lm -o recover
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#//include "bmp.h"

typedef uint8_t  BYTE;

	#define CHUNK 512
	#define JPG0 0xff
	#define JPG1 0xd8
	#define JPG2 0xff
	#define JPG3A 0xe0
	#define JPG3B 0xe1
	#define numberOfJpgs 50

// prototypes
int findNext(FILE* file, int startPosition);
void saveJpg(FILE* file, int location, int number);

	int jpgPositions[numberOfJpgs];

	int main(int argc, char* argv[])
	{
    	// TODO 
   	// Open memory card file, store in inptr
   	FILE* inptr = fopen("card.raw", "r");
    	if (inptr == NULL)
    		{
       		printf("Could not open card.raw \n");
        	return 2;
    		}
   

	int start = 0;

/*
	for(int i = 0; i < 100; i++)
	{
		ends[i] = findEnds(inptr);
		printf("ends[%d] = %d \n", i, ends[i]);
	}
*/	
	// find start of jpegs
	for(int i = 0; i < numberOfJpgs; i++)
	{
		jpgPositions[i] = findNext(inptr, start);
		start = jpgPositions[i];
	}
	

	

	for(int i = 0; i < numberOfJpgs; i++)
	{
		if(jpgPositions[i] != -1)
		{
			saveJpg(inptr, jpgPositions[i] -1, i);
		}
	}


   fclose(inptr);
   
	return 0;
}
   

int findNext(FILE* file, int startPosition)
{
	BYTE buffer;
	fseek(file, startPosition, SEEK_SET);
	
	// while not end of file, search thru bytes
	while(fread(&buffer, sizeof(buffer), 1, file) == 1)
	{
		
		// store position of pointer
		startPosition = ftell(file);
		
		
		// read in BYTE from file and put in buffer		
		//fread(&buffer, sizeof(buffer), 1, file);

		// try to find start
		if(buffer == JPG0)
		{
			// if found match, check next BYTE
			fread(&buffer, sizeof(buffer), 1, file);
			if(buffer == JPG1)
			{
		
				// if found match, check next BYTE		
				fread(&buffer, sizeof(buffer), 1, file);
				if(buffer == JPG2)
				{
					fread(&buffer, sizeof(buffer), 1, file);


					if(buffer == JPG3A || buffer == JPG3B)
					{
					
						return startPosition;
						
					}

				
				}
			}
		}
    		
	}
	
	return -1;
}
/*
// finds all 50
int findEnds(FILE* file)
{
	// temp
	BYTE temp;

	
	while(fread(&temp, sizeof(temp), 1, file) == 1)
	{
		if(temp == 0xff)
		{
			fread(&temp, sizeof(temp), 1, file);
			if(temp == 0xd9)
			{
				return ftell(file);
			}
		}
	}
	return -1;
}
*/


void saveJpg(FILE* file, int location, int number)
{
	

	// Temp storage
	BYTE bufferChunk[CHUNK];

	// go to jpg start position
	fseek(file, location, SEEK_SET);

	
	// read CHUNK from inptr
	fread(&bufferChunk, sizeof(bufferChunk[0]), CHUNK, file); 
	{
		/*
		// peek at bufferChunk
		printf("bufferChunk starts with: %#1x", bufferChunk[0]);
		printf(", %#1x", bufferChunk[1]);
		printf(", %#1x", bufferChunk[2]);
		printf(", %#1x \n", bufferChunk[3]);
		*/

		// create output file TODO naming ###.jpg incremental
	
   		char str[10];
		sprintf(str, "%03d.jpg", number);

		FILE* outptr = fopen(str, "w");
			if(outptr == NULL)
			{
				fclose(file);
				fprintf(stderr, "Could not create file");
				// TODO how to close program on load failure???
				//return 3;
				
			}


		// write to outptr
        	fwrite(&bufferChunk, sizeof(bufferChunk[0]), CHUNK, outptr);

		// check next chunk for start of jpg, if none continue writing to file

		int startofnew = 0; // false
		//int firstrun = 1;

		
		while(startofnew == 0)
		{
			
		
			// read CHUNK from inptr
			if(fread(&bufferChunk, sizeof(bufferChunk[0]), CHUNK, file) == CHUNK)
			{

	
				if(bufferChunk[0] == JPG0 && bufferChunk[1] == JPG1 && bufferChunk[2] == JPG2 && (bufferChunk[3] == JPG3A || bufferChunk[3] == JPG3B))
				{
					
					startofnew = 1; // true
					
				}


				else
				{
				fwrite(&bufferChunk, sizeof(bufferChunk[0]), CHUNK, outptr);
				}

			}
			else
			{
				startofnew = 1; // true
			}

		}

		fclose(outptr);
	}


}


