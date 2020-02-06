#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // setup variable to hold input from user
    int steps = -1;
    
    printf("This program draws a half-pyramid with height provided user.\n");
    
    // accept input from user(0-23)
    while(steps < 0 || steps > 23)
    {
        printf("Enter a positive number no greater than 23, please: ");
        steps = GetInt();
    }
    /**
    if(steps == 1)
    {
        printf("I will draw %i step for you... \n", steps);
    }
    else
    {
        printf("I will draw %i steps for you... \n", steps);
    }
    */
    
    for(int i = steps; i > 0; i--)
    {
        // for loop to draw spaces
        for(int j = 1; j < i; j++)
        {
            printf(" ");
        }
        
        // for loop to draw hashtag/pound sign
        for(int k = -2; k < steps - i; k++)
        {
            printf("#");
        }
        // jump to next line
        printf("\n");
    }
    
}
