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