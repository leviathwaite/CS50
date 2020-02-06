// already lowercase, get key
		    int key = hash_function(value);
		    printf("word %s,  key %d \n", value, key);
		    // count number of words
		    word_count++;
		    // assign value to new_node's word variable
 		    //new_node->word = value;
	 	    strcpy(new_node->word, value);

 	
		    // if spot empty, insert
 		    if (root[key]== NULL)
		    {
			    root[key]= new_node;
 			    break;
 		    }
	        else
	        {

 		        // keep track of current and previous nodes
 		        //node* curr = root[key]->next; //TODO right?
		        node* curr = root[key];
 		        node* prev = NULL;
 
 		        while (curr != NULL)
 		        {
 			        // check spot for duplicates
 			        if (strcmp(value, curr->word) == 0)
 			        {
 				        free(new_node);
 				        return false;
			        }
 			        // keep looking for correct spot
 			        else if(strcmp(value, curr->word) > 0)
 			        {
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
