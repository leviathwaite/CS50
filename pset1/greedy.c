#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Program takes dollar input from user and provides change in lowest coin count

int main(void)
{

    // CONSTANTS
    int QUARTER = 25;
    int DIME = 10;
    int NICKEL = 5;
    int PENNY = 1;

    // variables
    float changeOwed = -1; 
    int cents = 0; 
    int coins = 0; 

    // get input from user, make sure its a positive number
    while(changeOwed < 0)
    {
        printf("How much change is owed? $");
        changeOwed = GetFloat();
    }
    
    // convert dollars into cents(times by 100 then round)
    cents = (int) round(changeOwed * 100);
     
    // check for quaters
    coins = coins + (cents / QUARTER);
    cents = cents % QUARTER;
    
    // check for dimes
    coins = coins + (cents / DIME);
    cents = cents % DIME;
    
    // check for nickels
    coins = coins + (cents / NICKEL);
    cents = cents % NICKEL;
    
    // check for pennies
    coins = coins + (cents / PENNY);
    cents = cents % PENNY;
    
    // print number of coins used to make change
    printf("%d\n", coins);
     
}
