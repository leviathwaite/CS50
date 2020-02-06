/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Searches with recursive binary search
 * Returns true if value is in array of n values, else false.
 */
 
 bool binarysearch(int target, int array[], int n)
 {
   int start = 0;
   int end = n - 1;
   
   while(end >= start)
   {
        // look at middle
        int middle = (start + end) / 2;
        //printf("middle = %i\n", array[middle]);
        // if number found, return true
        if(target == array[middle])
        {
            return true;
        }
        // else if number higher search left
        else if(target < array[middle])
            {
               // printf("target = %i < array[middle] = %i\n", target, array[middle]);
                end = middle - 1;
            }
        // else if number lower search right
        else
        {
            // printf("target = %i > array[middle] = %i\n", target, array[middle]);
            start = middle + 1;
        }
   }
   
   return false;
 }

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{

/**
    // search values for value, iterate n times
    for(int i = 0; i < n; i++)
    {
        if(value == values[i])
        {
            return true;
        }
    }

    // if not found return false
    return false;
*/
    //printf("looking for %i, n = %i\n", value, n);
    
   //search values for value using binary search
   return binarysearch(value, values, n);

}

/**
 * Sorts array of n values using insertion sort
 */
void insertionsort(int values[], int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        // find index of smallest value in values
        int indexOfMin = i;
        
        for(int j = i; j < n - 1; j++)
        {
            if(values[i] > values[j])
            {
                indexOfMin = j;
            }
        }
        //swap 1st index with indexOfMin
    }
}

/**
 * Sorts array of n values using bubble sort
 */
void bubblesort(int values[], int n)
{

    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(values[i] > values[j])
            {
               // swap i index to j
                int temp = values[i];
                values[i] = values[j];
                values[j] = temp;
            }
        }
        
    }
    
    
    return;
}


/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    
    // check before
    for(int i = 0; i < n; i++)
    {
        //printf("Before, haystack[%i] = %i \n", i, values[i]);
    }
    
    bubblesort(values, n);
    
    // check after
    for(int i = 0; i < n; i++)
    {
        //printf("After, haystack[%i] = %i \n", i, values[i]);
    }
    
    return;
}



