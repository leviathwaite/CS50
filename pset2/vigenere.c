#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
* vigenere.c
*
* Robert Waite
* theyearofrupert@hotmail.com
*
* takes key and encrypts sentence from user by keyword
*/ 

// converts key to 0-25 # and shows in style50(c is acceptable name)
char keytoNumber(char c)
{
    if (isupper(c))
    {
        return c - 65;
    }
    else
    {
        return c - 97;
    }
}

// converts ascii to 0-25 #
int lowerConvert(int i)
{
    return i - 97;
}

// converts ascii to 0-25 #
int upperConvert(int i)
{
    return i - 65;
}

int main(int argc, string argv[])
{
    
    // check number of args, quit if not just one
    if (argc != 2)
    {
        printf("wrong number of arguments provided, keyword expected\n");
        return 1;
    }
    
    // create and init variable to hold keyword length
    int keyLength = 0;
    
    // check if keyword contains non alphabet character, if found quit
    for(int i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("keyword contains non alphabet letter \n");
            return 1;
        }
        argv[1][i] = keytoNumber(argv[1][i]);
        keyLength = i + 1;
    }
    
    // get plain test from user and put into string text
   // printf("please type message to encrypt: \n");
    string text = GetString();
    
   

    int keySpace = 0;
    
    // encrypt text
    for(int i = 0; text[i] != '\0'; i++)
    {
        // shows in style50(name length is needed for clarity)
        int keySpaceValue = argv[1][keySpace];
    
        if (isalpha(text[i]))
        {
            if (islower(text[i]))
            {
                text[i] = lowerConvert(text[i]);
                text[i] = (text[i] + keySpaceValue) % 26;
                text[i] = text[i] + 97;
                
                // move to next keySpace
                keySpace = (keySpace + 1) % keyLength;
            }
            // if upper
            else 
            {
                text[i] = upperConvert(text[i]);
                text[i] = (text[i] + keySpaceValue) % 26;
                text[i] = text[i] + 65;
                
                // move to next keySpace
                keySpace = (keySpace + 1) % keyLength; 
            }
        }
        
    }
    
    printf("%s", text);
    printf("\n");   
}
