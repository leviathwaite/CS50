/**
 * linked.c
 *
 * pset6
 * fall 2013
 *
 * clang -ggd3 -O0 -std=c99 -Wall -Werror linkedstring.c -lcs50 -lm -o linkedstring
 * hashmap for loading and managing int nodes in memory
 */

 #include <cs50.h>
 #include <stdbool.h>
 #include <stdio.h>
 #include <ctype.h>
 #include <string.h>

 // typedef a node for the linked list
 typedef struct node
{
 char* word;
 struct node* next;
}
 node;

#define SIZE 270

 // function prototypes
int hash_function(char* value, int length);
 bool insert_node(char* value);
 void print_nodes(node **list);
 void free_nodes(node **list);

// root array
node *root[SIZE];

 // global variable for the head of the list
 // node* head = NULL;

 int main(void)
{
 	// offer the user two options
 	while(true)
 	{
 		printf("Please choose an option (0, 1, 2): ");
 		int option = GetInt();
 
 		switch(option)
 		{
 			// quit
 			case 0: 
 			free_nodes(root);
 			printf("Goodbye!\n");
 			return 0;
 
 			// insert int into linked list
 			case 1:
 			printf("Please enter a String: ");
			
 			char* v = GetString();
 			char* success = insert_node(v) ? "was" : "was not";
 			printf("The insert %s successful.\n", success);
 			break;
 
 			// print all ints
 			case 2:
 			print_nodes(root);
 			break;
 
 			default:
 			printf("Not a valid option.\n");
 			break;
 		}
 	}
 }

// hash function, takes word returns int key
int hash_function(char* value, int length)
{
	// hash is 3 digits, hundredths and tenths space = a-z, ones space = length, if over 9 = 0
	// fit length, 1-9, if longer put in 0
	if(length > 9)
	{
		length = 0;
	}

	// hash on first letter of string
	//int hash = tolower(value[0]) + 'A';
	int hash = ((char)value[0] - 96) * 10;
	hash = hash + length;
	printf("key: %d \n", hash); // % SIZE);
	return hash; // % SIZE;
}

 /**
 * Create a new node for a given value and insert it into a list.
 */
 bool insert_node(char* value)
 {
	int length = 0;
	// convert to lowercase
	//for ( ; *value; ++value) *value = tolower(*value);
	for(int i = 0; value[i]; i++)
	{
  		value[i] = tolower(value[i]);
		length++;
	}
	
	int key = hash_function(value, length);

	// malloc space for a new node
 	node* new_node = malloc(sizeof(node));
 	
	// make sure new_node created
	if (new_node == NULL)
 	{
 		return false;
	}
	// assign value to new_node's word variable
 	new_node->word = value;

 	
	// if spot empty, insert
 	if (root[key]== NULL)
	{
		root[key]= new_node;
 		return true;
 	}
	

 	// keep track of current and previous nodes
 	//node* curr = root[key]->next; //TODO right?
	node* curr = root[key];
 	node* prev = NULL;
 
 	while (curr != NULL)
 	{
 		// check spot for duplicates
 		if (strcmp(value, curr->word) == 0)
 		{
			printf("same word \n");
 			free(new_node);
 			return false;
		}
 		// keep looking for correct spot
 		else if(strcmp(value, curr->word) > 0)
 		{
			printf("greater than current \n");
			prev = curr;
			curr = curr->next;

			if(curr == NULL)
 			{
 				break;
			}
		}
		else if(strcmp(value, curr->word) < 0)
 		{
 			break;
 		}
 
	}
 
 	// insert the node in the correct position
 	new_node->next = curr;
 	if(prev == NULL)
 	{
 		root[key] = new_node;
 
	}
 	else
 	{
		prev->next = new_node;
 
	}
 
 	return true;
 }

 /**
 * Print out all of the ints in a list.
 */
 void print_nodes(node **list)
 {
	//iterate thru list while not null printing values until null
	for(int i = 0; i < SIZE; i++)
	{
		// store count
		int counter = 0;
	
		// keep track of current and previous nodes
 		node* curr = list[i];
 
 		while (curr != NULL)
 		{
			counter++;
			printf("root[%d] Node %d: %s\n", i, counter, curr->word);
 			curr = curr->next;
			
		}
	}
 }

 /**
 * Frees all of the nodes in a list upon exiting the program.
 */
 void free_nodes(node **list)
 { 
	//TODO
	/* start at head or end and save pointer to next then remove node until one after pointer = null*/
	// don't lose the rest of the list
 	
 	node* prev = NULL;

	for(int i = 0; i < SIZE; i++)
	{
 		node* curr = list[i];
 		while (curr != NULL)
 		{
 			prev = curr;
 			curr = curr->next;
 			free(prev);
 		}
	}
 }
