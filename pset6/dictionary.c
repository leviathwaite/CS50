/****************************************************************************
 * dictionary.c
 *
 * Robert Waite
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "dictionary.h"

typedef struct node
	{
		char word[LENGTH + 1];	
		struct node* next;
	}
	node;

// array of pointers to linked list
node* root[SIZE];

// int to keep track of number of words loaded
int word_count = 0;

// hash function, takes word returns int key
int hash_function(char* value)
{
	int length = strlen(value);

    /*
	 * hash is 3 digits, hundredths and tenths space = a-z, ones space = length, 
	 * if over 9 = 0 fit length, 1-9, if longer put in 0
	 */
	if(length > 9)
	{
		length = 0;
	}

    /*
	 * hash on first letter of string 
	 * 96 = 'a' -1 to shift to 1-26, * 10 brings to 10-260
	 */
	int hash = ((char)value[0] - 96) * 10;
	hash = hash + length;
	
	return hash;
}


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{

    // var to modify case
	char word_lower[LENGTH +1];
	// copy word to word_lower
	strcpy(word_lower, word);
	
	// convert to lowercase
	for(int i = 0; word[i]; i++)
	{
		// if not an apostrophe, make lowercase
		if(word_lower[i] != '\'')
		{
			word_lower[i] = tolower(word_lower[i]);
		}
	}

	// get hash key
	int key = hash_function(word_lower);

    // keep track of current and previous nodes
    node* curr = root[key];
	//strcpy(curr->word, root[key]->word);
 	node* prev = NULL;

	// iterate thru dictionary, while(true)
 	while (1)
 	{
 	    if(curr == NULL)
 	    {
 	        return false;
 	    }
 		// check for match
 		if (strcmp(word_lower, curr->word) == 0)
 		{
 		    
 			return true;
		}
		
		// step to next space
		prev = curr;
		curr = curr->next;
	}
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    
    // Open Dictionary
    FILE* fp = fopen(dictionary, "r");
    // check that file loaded
    if(fp == NULL)
    {
        printf("Could not open %s. \n", dictionary);
	    return false;
	}
	
	
	// create temp var for word to be stored in
	char word[LENGTH +1];
	
	// scan through dictionary
	while(fscanf(fp, "%s\n\'", word) != EOF)
	{
	   
	    // make new node
	    node* new_node = malloc(sizeof(node));
	    
	    // increment word_count
	    word_count++;
	    
	    // copy new word into new_node
	    strcpy(new_node->word, word);
	    
	    // get index key
	    int key = hash_function(word);
	    
	    // if root empty, insert
	    if(root[key] == NULL)
	    {
	        root[key] = new_node;
	        new_node->next = NULL;
	    }
	    // if root full, search thru till NULL
	    else
	    {
	        node* curr = root[key];
	        while(curr->next != NULL)
	        {
	            curr = curr->next;
	        }
	        // once next is empty, point it at new_node
	        curr->next = new_node;
	        new_node->next = NULL;
	    }
	}
	
	// close file
	fclose(fp); 
	
	return true;
}


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
	return word_count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{

	for(int i = 0; i < SIZE; i++)
	{
	    while(root[i] != NULL)
	    {
	        node* curr = root[i];
	        root[i] = curr->next;
	        free(curr); 
	    }  
	}
	 
	return true;
}

