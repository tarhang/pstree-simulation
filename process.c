// process.c
// implements a binary tree, uses it for making a process tree
// Farhang Tarlan, Winter 2013

#include "process.h"


struct process* make_process(int pid, int mem_used)
{
	/*
		Creates a new process struc with the arguments given. sets the left and right children to NULL
	
		Arguments:
		pid -- integer indicating the pid attribute of the new process
		mem_used -- integer indicating the memory used of the new process
	
		Return:
		new_process -- a pointer to the new process struc created
	*/
	
	assert(pid >= 0);
	assert(mem_used > 0);
	struct process* new_process = (struct process*) malloc(sizeof(struct process*));
	new_process -> pid = pid;
	new_process -> mem_used = mem_used;
	new_process -> left = NULL;
	new_process -> right = NULL;
	return new_process;
}


void helper_print_postorder(struct process* root)
{
	/*
		helper function to print the binary tree rooted at root in postorder traversal - ie. left, right, root
		
		Argument:
		root -- root of the binary tree to be postorder-ly printed				
	*/
	
	if (root != NULL)
	{
		helper_print_postorder(root -> left);
		helper_print_postorder(root -> right);
		print_process(root);
	}
}


void print_postorder(struct process *root)
{
	/*
		prints the binary tree rooted at root using postorder traversal - ie. left, right, root
		
		Argument:
		root -- root of the binary tree
	*/	
	
	printf("Postorder: ");
	helper_print_postorder(root);
	printf("\n");
}


void helper_print_inorder(struct process* root)
{
	/*
		helper function to print the binary tree rooted at root inorder traversal - ie. left, root, right
		
		Argument:
		root -- root of the binary tree to be inorder-ly printed
	*/
	
	if (root != NULL)
	{
		helper_print_inorder(root -> left);
		print_process(root);
		helper_print_inorder(root -> right);
	}
}


void print_inorder(struct process *root)
{
	/*
		prints the binary tree rooted at root using inorder traversal - ie. left, root, right
		
		Argument:
		root -- root of the binary tree
	*/	
	
	printf("Inorder: ");
	helper_print_inorder(root);
	printf("\n");
}

void helper_print_levelorder(struct queue** line)
{
	/*
		prints the binary tree rooted at root using levelorder traversal - ie. level by level
		
		Argument:
		root -- root of the binary tree
	*/
	
	if (*line)
	{
		// enqueue the children of what was the head of the queue
		if ((*line) -> proc -> left)
		{
			enqueue((*line) -> proc -> left, line);
		}
		if ((*line) -> proc -> right)
		{
			enqueue((*line) -> proc -> right, line);
		}
		
		struct process* to_print = dequeue(line);
		print_process(to_print);
		helper_print_levelorder(line);
	}
}


void print_levelorder(struct process *root)
{
	/*
		prints the binary tree rooted at root using levelorder traversal - ie. level by level
		
		Argument:
		root -- root of the binary tree
	*/

	// creating a queue to add process tree nodes to
	struct queue* line = NULL;
	enqueue(root, &line);
				
	printf("Level order: ");
	if (root)
		helper_print_levelorder(&line);
	printf("\n");
}


int helper_num_nodes(struct queue* line, int num)
{
	/*
		helper function to compute the number of nodes in the binary tree rooted at tree
		
		Arguments:
		line -- head of the queue that stores the tree in a level order fashion
		num -- number of nodes seen thus far
		
		Return;
		returns the number of nodes after seeing the head of the subtree
	*/
	
	if (line)
	{
		// enqueue children of the root
		if (line -> proc -> left)
			enqueue(line -> proc -> left, &line);
		if (line -> proc -> right)
			enqueue(line -> proc -> right, &line);
		
		// dequeue the root, increment the counter
		dequeue(&line);
		return helper_num_nodes(line, num + 1);		
	}
	
	return num;
}

int num_nodes(struct process *root)
{
	/*
		returns the number of node in the binary tree rooted at root
		
		Argument:
		root -- root of the binary tree
		
		Return:
		
	*/

	struct queue* line = NULL;	
	enqueue(root, &line);
	if (root)
		return helper_num_nodes(line, 0);
	return 0;
}


int helper_is_complete(struct queue* line, int all_complete)
{
	/*
		helper function to determine if a binary tree, repreented in levelorder by the queue line, is complete
		
		Arguements:
		line -- queue data structure created by the levelorder traversal of the binary tree
		seen_empty -- 1 if a node with less than two children has been seen. 0 otherwise
		
		Return:
		-- 1 if the tree is complete. 0 otherwise
	*/
	int empty = 1 - all_complete;
	
	if (line)
	{
		// if an empty spot has been seen (a node with less than two children - hence all_copmlete = 0), all it takes for a 
		// tree to be incomplete is to see another node with at least one child
		if (all_complete == 0)
		{
			if (line -> proc -> left || line -> proc -> right)
				return 0;
		}
		
		// if we have not seen an empty spot (ie. all nodes has had two children - hence all_complete = 1), add their children. 
		// If they have less than two children, record that we have seen an empty spot.
		if (all_complete == 1)
		{
			if (line -> proc -> left)
				enqueue(line -> proc -> left, &line);
			else
			{
				empty = 1;
				
				// if a node has a right cihld after missing a left child, tree incomplete
				if (line -> proc -> right)
					return 0;
			}		
				
			if (line -> proc -> right)
				enqueue(line -> proc -> right, &line);
			else
				empty = 1;
		}
		
		dequeue(&line);
		return helper_is_complete(line, 1 - empty); 
	}
	
	return 1;
}


int is_complete(struct process *root)
{
	/*
		returns 1 if the binary tree rooted at root is complete
		
		Arguement:
		root -- root of the binary tree
		
		Return:
		-- 1 if the tree is complete. 0 otherwise
	*/
	
	struct queue* line = NULL;
	enqueue(root, &line);
	if (root)
		return helper_is_complete(line, 1);
	return 1;	
	
}


void remove_all(struct process** root)
{
	/*
		removes all the nodes of the binary tree rooted at root
		
		Arguement:
		root -- double pointer to the root of the binary tree
	*/
	
	if (root == NULL)
		return;
	
    if(*root)
    {
        struct process* curr = *root;

        if(curr -> left)
            remove_all(&(curr -> left));
        if(curr -> right)
            remove_all(&(curr -> right));

        free(curr);
        *root = NULL;
    }
}

