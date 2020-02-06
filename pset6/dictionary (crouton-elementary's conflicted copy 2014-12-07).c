/****************************************************************************
 * dictionary.c
 *
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
node root[SIZE];

// int to keep track of number of words loaded
int word_count = 0;






// TODO tolower and length here since required for hash_function
// hash function, takes word returns int key
int hash_function(char* value)
{
	int length = strlen(value);

	// hash is 3 digits, hundredths and tenths space = a-z, ones space = length, if over 9 = 0
	// fit length, 1-9, if longer put in 0
	if(length > 9)
	{
		length = 0;
	}

	// hash on first letter of string
	int hash = ((char)value[0] - 96) * 10;
	hash = hash + length;
	
	return hash; // % SIZE;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // var to modify case
	char* word_lower = (char*)word;
	// convert to lowercase
	for(int i = 0; word[i]; i++)
	{
  		word_lower[i] = tolower(word_lower[i]);
	}

	// get hash key
	int key = hash_function(word_lower);

	

    // keep track of current and previous nodes
	node* curr = &root[key];
 	node* prev = NULL;

	// iterate thru dictionary 
 	//while (curr != NULL)
	while(1)
 	{

		printf("word_lower = %s, curr->word = %s, key = %i \n", word_lower, root[key].word, key);
		if(curr == NULL)
		{
			return false;
		}
		
		/*
 		// check for match
 		if (strcmp(word_lower, curr->word) == 0)
 		{
			printf("match \n");
 			return true;
		}
		*/

		// check for match
 		if (strncmp(word_lower, curr->word, LENGTH +1) == 0)
 		{
			printf("match \n");
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
/*
	// init root array
	for(int i = 0; i < SIZE; i++)
	{
		root[i] = NULL;
	}
*/
    
	char value[LENGTH+1];
	//char* value = '';
    
	// malloc space for a new node
 	node* new_node = malloc(sizeof(node));
 	
	// make sure new_node created
	if (new_node == NULL)
 	{
		printf("Failed to create new node. \n");
 		return false;
	}

    // open and check that dictionary opened
	FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
       	printf("Could not open %s.\n", dictionary);
        return false;
    }
    
    
    while (fgets(value, LENGTH + 1, fp) != NULL) {

	
	
	// check value
	printf("value = %s \n", value);
 
    	// already lowercase, get key
    	int key = hash_function(value);
	    
    	// copy value into new_node
        strcpy(new_node->word, value);
        //new_node->next = NULL;
	    
	// if space is NULL, insert
        if(root[key].word == NULL)
        {
         	root[key].word = value;
		return true;
	}
	// if root is empty look for end of list and insert
        else
	{
		node curr = root[key];
		node temp = NULL;
		while(curr->next != NULL)
		{
			temp = curr;
			curr = curr->next;
		}
		curr->next = new_node;
		return true;
	}  	
	

    
   }
 	return false;

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
/*
   //iterate thru list while not null and free words
	//TODO
	//start at head or end and save pointer to next then remove node until one after pointer = null
	// don't lose the rest of the list
 	
 	node* temp = NULL;

	for(int i = 0; i < SIZE; i++)
	{
 		node* curr = root[i]->next;
 		while (curr != NULL)
 		{
			printf("freeing");
 			temp = curr;
 			curr = curr->next;
 			free(temp);
 		}
	}
*/
	return true;
}
