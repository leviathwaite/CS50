#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
* caesar.c
*
* Robert Waite
* theyearofrupert@hotmail.com
*
* takes positive number and encrypts sentence from user by number
*/ 


int main(int argc, string argv[])
{
    // if no arge or more then one, tell user and exit
    if (argc != 2)
    {
        printf("wrong number of arguments\n");
        return 1;
    }
    
    // check for positive number. if not tell user and exit
    
    // atoi converts string to int return 0 if not number
    int moveBy = atoi(argv[1]); 
    if (moveBy <= 0)
    {
        printf("invaild argument \n");
        return 1;
    }
    
    // get text to encrypt from user
    // printf("Please enter sentence to encrypt...\n");
    string text = GetString();
    
    // encrypt text
   
    for( int i = 0; i < strlen(text); i++)
    {
        int letter = text[i];
        moveBy = moveBy % 26;
        
        // check if letter is alphabet
        if (isalpha(letter))
        {
            // check if lowercase
            if (islower(letter))
            {
                letter = letter + moveBy;
                if (letter > 122)
                {
                    letter = (letter % 122) + 96; 
                }
                
            }
            // check if uppercase
            if (isupper(letter))
            {
                letter = letter + moveBy;
                if (letter > 90)
                {
                    letter = (letter % 90) + 64; 
                }
            }
        }
       
        printf("%c", letter); 
    }
    printf("\n");
    return 0;
}
