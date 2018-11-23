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

void helper_print_levelorder(struct process* root)
{
	/*
		prints the binary tree rooted at root using levelorder traversal - ie. level by level
		
		Argument:
		root -- root of the binary tree
	*/
	
	
}


void print_levelorder(struct process *root)
{
	/*
		prints the binary tree rooted at root using levelorder traversal - ie. level by level
		
		Argument:
		root -- root of the binary tree
	*/
	
	printf("Level order: ");
	helper_print_levelorder(root);
	printf("\n");
}
