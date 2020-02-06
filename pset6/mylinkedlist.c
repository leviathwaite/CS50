/**
 * linked.c
 *
 * week 7 section
 * fall 2013
 *
 * practice using linked lists
 */

 #include <cs50.h>
 #include <stdbool.h>
 #include <stdio.h>

 // typedef a node for the linked list
 typedef struct node
{
 int n;
 struct node* next;
}
 node;

 // function prototypes
 bool insert_node(int value);
 void print_nodes(node* list);
 void free_nodes(node* list);

 // global variable for the head of the list
 node* head = NULL;

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
 			free_nodes(head);
 			printf("Goodbye!\n");
 			return 0;
 
 			// insert int into linked list
 			case 1:
 			printf("Please enter an int: ");
			// sections/7/src7/linked.c
 			int v = GetInt();
 			char* success = insert_node(v) ? "was" : "was not";
 			printf("The insert %s successful.\n", success);
 			break;
 
 			// print all ints
 			case 2:
 			print_nodes(head);
 			break;
 
 			default:
 			printf("Not a valid option.\n");
 			break;
 		}
 	}
 }

 /**
 * Create a new node for a given value and insert it into a list.
 */
 bool insert_node(int value)
 {
	//create new node malloc
	node* new_node = malloc(sizeof(node));
	// check that new_node created
	if( new_node == NULL)
	{
		return false;
	}

	// assign value to new_node
	new_node-> = value;

	//create current and prev nodes
	node* curr = list;
	node* prev = NULL;
	
	
	
	//iterate thru list,
	while(curr != NULL)
	{
		//if value less than node
		if(value < curr->n)
		{
			// insert before
			new_node->next = curr;
			if(prev == NULL)
			{
				head = new_node;
			}
			else
			{
				prev->next = new_node;
			}
			return true;
		}	

		//if value greater then node
		if(value > curr->n)
		{
			// move forward & update pointers
			prev = curr;
			curr = curr->next;
		}

		//if value same
		if(value == curr->n)
		{
			// free
			free(new_node);
			return false
		}

	}
	// must be at end of the list
	new_node->next = NULL;
	head = new_node;
	return true;
 }

 /**
 * Print out all of the ints in a list.
 */
 void print_nodes(node* list)
 {
 	// TODO
	/* 
	iterate thru list while not null printing values until null
	*/
 }

 /**
 * Frees all of the nodes in a list upon exiting the program.
 */
 void free_nodes(node* list)
 { 
	//TODO
	/* start at head or end and save pointer to next then remove node until one after pointer = null
 }
