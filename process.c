// process.c
// implements a binary tree, uses it for making a process tree
// Farhang Tarlan, Winter 2013

#include "process.h"
#define min(a,b) (a<b ? a:b)


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
	free_queue(&line);
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
	free_queue(&line);
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
				{
					free_queue(&line);
					return 0;
				}
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
	free_queue(&line);
	return 1;	
	
}


void free_queue(struct queue** line)
{
	/*
		removes all the nodes in the queue pointed to by line, freeing its memorty
		
		Arguements:
		line -- double pointer to the front of the queue
	*/
	
	if (*line)
	{
		dequeue(line);
		free_queue(line);
	}
	
	line = NULL;
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

int contains_pid(struct process *root, int value)
{
	/*
		returns 1 if a node with the given PID, value, exists in the binary tree rooted at root
		
		Arguements:
		root -- root of the binary tree
		value -- PID value to be searched for
		
		Returns:
		0 or 1 -- 1 if the tree contains a node with PID = value. 0 otherwise.
	*/
	
	if (root)
	{
		// if the current node has the pid = value, we have found the node
		if (root -> pid == value)
			return 1;
			
		// if the current node does not have the pid equal to value, recurse on its left and right nodes.
		int contains_left = contains_pid(root -> left, value);
		// no need to recurse on the right branch if value is already found in the left subtree
		if (contains_left == 1)
			return 1;
		return contains_pid(root -> right, value);
	}
	return 0;
}


int helper_total_mem(struct process* root, int sum)
{
	/*
		helper function to compute the total memory used in the binary tree rooted at root
		
		Arguements:
		root -- root of the binary tree
		sum -- sum of the memory used computed so far
		
		Return:
		adds the memroy of the current node to the sum passed in to the helper function
	*/
	
	if (root)
	{
		// add the memory used in the current node
		int mem_used = sum + (root -> mem_used);
		
		// if there are left or right subtrees, add the memory used in the branches recursively
		if (root -> left)
			mem_used = helper_total_mem(root -> left, mem_used);
		if (root -> right)
			mem_used = helper_total_mem(root -> right, mem_used);

		return mem_used; 
	}
	
	return sum;
}


int total_mem(struct process *root)
{
	/*
		computes the total amount of memory stored in the binary tree rooted at root
		
		Arguement:
		root -- root of the binary tree
		
		Return:
		total -- total amount of memory (sum of mem_used attribute) stored in the tree nodes
	*/
	
	int total = 0;
	total = helper_total_mem(root, total);
	return total;	
}


int can_add(struct process *root, struct process *new_node, int max_mem)
{
	/*
		tests whether a new node, new_node, can be added to the binary tree rooted at root. To add a new node, the tree must
		not already contain a node with the same pid, and the total memory used in the new tree must not exceed mem_used
		
		Arguements:
		root -- root of the binary tree
		new_nde -- new node to be added to the binary tree
		mem_used -- maximum allowance of memory of the new tree after adding new_node
		
		Returns:
		add -- 1 if new_node can be added to the tree. 0 otherwise.
	*/
	
	assert(new_node);
	int add = 0;
	int contains = contains_pid(root, new_node -> pid);
	
	if (contains == 0)
	{
		int mem_used = total_mem(root) + new_node -> mem_used;
		if (mem_used <= max_mem)
			add = 1;
	}	
	return add;
}


void helper_insert_levelorder(struct queue** line, struct process* to_add)
{
	/*
		helper function to add a new node, to_add, to a binary tree stored in level order in argument line, in the first
		available level order position
		
		Arguements:
		line -- queue that contains the binary tree in level order
		to_add -- new node to be added to the binary tree
	*/
	
	if (*line)
	{
		if ((*line) -> proc -> left)
		{
			enqueue((*line) -> proc -> left, line);
		}
		else
		{	
			(*line) -> proc -> left = to_add;
			return;
		}
		
		if ((*line) -> proc -> right)
		{
			enqueue((*line) -> proc -> right, line);
		}
		else
		{
			(*line) -> proc -> right = to_add;
			return;
		}
		
		dequeue(line);
		helper_insert_levelorder(line, to_add);
	}
}


void insert_levelorder(struct process **root, struct process *to_add, int max_mem)
{
	/*
		adds a new node, to_add, to the binary tree rooted at root in the first available position in the level order traversal.
		Note that this operation can only be performed when the resulting tree is complete. For a node to be added, can_add
		must return true.
		
		Arguements:
		root -- double pointer to the root of the binary tree
		to_add -- new node to be inserted into the subtree
		max_mem -- max memory allowance of the resulting tree (after insertion of the new node) 
	*/
	
	assert(can_add(*root, to_add, max_mem));
	
	if (*root)
	{
		struct queue* line = NULL;
		enqueue(*root, &line);
		helper_insert_levelorder(&line, to_add);
		free_queue(&line); 
	}
	else
		*root = to_add;
	
	assert(is_complete(*root));	
}


void helper_create_tree(struct process** root, int pid, int mem, int max_mem, int still_to_go)
{
	/*
		helper function to create a binary tree - loop replacement!
		
		Arguements:
		root -- double pointer to the root of the binary tree
		pid -- pid of the node to be created in this call of the function
		mem -- momory of the node to be created in this call of the function
		max_mem -- maximum memory allowance of the tree to be created
		still_to_go -- works as a loop terminator, indicating the number of nodes that still need to be created
	*/
	
	if (*root)
	{
		insert_levelorder(root, make_process(pid, mem), max_mem);
	}
	else
		insert_levelorder(root, make_process(pid, mem), max_mem);
	
	if (still_to_go > 1)
		helper_create_tree(root, pid+1, mem, max_mem, still_to_go-1);
	
}

struct process* create_tree(int first_pid, int max_mem, int mem_per_proc, int num_nodes)
{
	/*
		creates a binary tree with with num_nodes. The nodes will have pid's in the range
		[first_pid, first_pid+num_nodes] and mem_per_proc memory.
		
		Arguements:
		first_pid -- pid of the first node in the binary tree. Each subsequent node takes the next integer pid
		max_mem -- maximum memory allowance of the binary tree
		mem_per_proc -- memory of the of the binary tree nodes
		num_nodes -- number of nodes in the binary to be created
		
		Returns:
		root -- root of the binary tree created
	*/
	
	struct process* root = NULL;
	helper_create_tree(&root, first_pid, mem_per_proc, max_mem, num_nodes);
	return root;
}


int helper_is_sorted(struct queue* line, int highest)
{
	/*
		helper function to determine if the binary tree represented by line is sorted.
		
		Arguements:
		line -- pointer to the head of the queue that stores the binary tree
		highest -- highest pid seen so far
		
		Returns:
		0/1 -- 1 if binary tree is sorted in level order. 0 otherwise
	*/
	
	if (line)
	{
		if (line -> proc -> left)
		{
			// for the tree to be sorted in level order, the left child has to be larger than the root
			if (line -> proc -> left -> pid < highest)
				return 0;
			enqueue(line -> proc -> left, &line);
		}
		
		if (line -> proc -> right)
		{
			// for a tree to be level order sorted, the right child has to be larger than the root
			if (line -> proc -> right -> pid < highest)
				return 0;
				
			// also for a tree to be level order sorted, the right child has to be larger than the left child
			if (line -> proc -> left)
			{
				if ((line -> proc -> right -> pid) < (line -> proc -> left -> pid))
					return 0;
			}
			enqueue(line -> proc -> right, &line);
		}
		
		dequeue(&line);
		if (line)
			return helper_is_sorted(line, line -> proc -> pid);
	}
	
	return 1;
}


int is_sorted(struct process *root)
{
	/*
		returns 1 if the binary tree rooted at root is sorted in the level order traversal. An empty tree is sorted.
		
		Arguement:
		root -- pointer to the root of the binary tree
		
		Returns:
		sorted -- 1 if the tree is sorted. 0 otherwise
	*/
	
	struct queue* line = NULL;
	enqueue(root, &line);
	if (root)
		return helper_is_sorted(line, root -> pid);	
	return 1;
}


struct process* helper_get_min(struct queue* line, int threshold, struct process* smallest_node)
{
	/*
		helper function to return the node with smallest pid that is greater than or equal to smallest
		
		Arguements:
		line -- pointer to the front of the queue that represents the binary tree
		threshold -- threshold integer we want to find the smallest node greater than or equal to
		smallest_node -- the node in the binary tree with the smallest pid value greater than the threshold
		
		Returns:
		 -- pointer to the node that satisfies the above requirements
	*/
	
	if (line)
	{
		int curr_val = line -> proc -> pid;
		
		if (smallest_node == NULL && curr_val >= threshold)
		{
			smallest_node = line -> proc;
		}
		
		else if (smallest_node != NULL && curr_val >= threshold && curr_val < smallest_node->pid)
		{
			smallest_node = line -> proc;
		}
			
		if (line -> proc -> left)
			enqueue(line -> proc -> left, &line);
		
		if (line -> proc -> right)
			enqueue(line -> proc -> right, &line);
		
		dequeue(&line);
		return helper_get_min(line, threshold, smallest_node);
	}
	
	return smallest_node;
}


struct process* get_min(struct process *root, int smallest_val)
{
	/*
		returns the node with the smallest pid value that is larger than or equal to smallest_val
		Asserts the binary tree is level order sorted
		
		Arguements:
		root -- root of the binary tree
		smallest_val -- the threshold we want to find the smallest node with larger pid value than
		
		Returns:
		 -- returns the actual node of the binary tree
	*/
	
	assert(is_sorted(root));
	struct queue* line = NULL;
	enqueue(root, &line);
	if (root)
		return helper_get_min(line, smallest_val, NULL);
	return NULL;		
}


int get_absolute_min(struct process* root, int so_far)
{
	/*
		Returns the smallest pid value found in the binary tree rooted at root
		
		Argument:
		root -- root of the binary tree
		
		Return:
		int -- smallest pid value found in any node of the binary tree
	*/
	
	if (root)
	{
		int left, right, smaller;
		left = get_absolute_min(root -> left, so_far);
		right = get_absolute_min(root -> right, so_far);
		smaller = min(left, right);
		smaller = min(smaller, root -> pid);
		so_far = min(smaller, so_far);
	}
	return so_far;
}


void build_levelorder_queue(struct queue** first, struct queue** second)
{
	/*
		builds a level order queue representing the nodes of a binary tree
		
		Argument:
		first -- double pointer to the head of the first queue that works as a temporary buffer. Initially holds tree root
		second -- double pointer to the head ot the second queue that will eventually hold the tree
	*/
	
	if (*first)
	{
		if ((*first) -> proc -> left)
			enqueue((*first) -> proc -> left, first);
		if ((*first) -> proc -> right)
			enqueue((*first) -> proc -> right, first);
		
		struct process* temp = dequeue(first);
		
		if (temp)
		{
			enqueue(temp, second);
			build_levelorder_queue(first, second);
		}
	}
}


void merge_sort(struct queue** line)
{
	/*
		merge sorts the given queue fronted by line
		
		Argument:
		line -- pointer to the head of the queue
	*/
	
	struct queue* left;
	struct queue* right;
	struct queue* head = *line; 
	  
	// base case -- length 0 or 1
	if ((head == NULL) || (head -> next == NULL)) 
		return; 
	  
	// split head into 'left' and right sublists
	split(head, &left, &right);  
	  
	// Recursively sort the sublists
	merge_sort(&left); 
	merge_sort(&right); 
	  
	// merge the two sorted lists together
	*line = merge(left, right); 
}


void split(struct queue* line, struct queue** left, struct queue** right)
{
	/*
		splits the given queue into left and right halves. 
		
		Arguments:
		line -- pointer to the head of the queue
		left -- double pointer to the head of the left half. Initially empty, will point to the beginning of the left half by 
				the end of the function call
		right -- double pointer to the head of the right half. Initially empty, will point to the beginning of the right 
				half by the end of the function call
	*/
	
	struct queue* slow;
	struct queue* fast; 
    slow = line; 
    fast = line -> next; 
  
    // advance 'ast two nodes, and advance slow one node
    
    while (fast != NULL) 
    { 
		fast = fast -> next; 
		if (fast != NULL) 
		{ 
		    slow = slow -> next; 
		    fast = fast -> next; 
		} 
    } 
  
    // slow is before the midpoint in the queue, so split the queue in two at that point
    *left = line; 
    *right = slow -> next; 
    slow->next = NULL; 
}


struct queue* merge(struct queue* left, struct queue* right)
{
	/*
		merges the two halves of a queue
		
		Arguments:
		left -- first queue to be merged
		right -- second queue to be merged
		
		Return:
		results -- merged queues resulting from merging left and right in ascending order
	*/
	
	struct queue* result = NULL; 
  
	// if either left or right are NULL, just return the other one and we are done
	if (!left) 
		return right; 
	else if (!right) 
		return left; 
	  
	// pick the smaller of the left and right indices, and recurse
	if (left -> proc -> pid <= right -> proc -> pid) 
	{ 
		result = left; 
		result -> next = merge(left -> next, right); 
	} 
	else
	{ 
		result = right; 
		result -> next = merge(left, right -> next); 
	} 
	
	return result; 
} 


void set_children_to_null(struct queue** line)
{
	/*
		sets the children of the nodes of the queue, that each represent a node in a binary tree, to NULL
		
		Argument:
		line -- double pointer to the head of the queue
	*/
	
	struct queue* curr = *line;
	
	for (curr = *line; curr != NULL; curr = curr -> next)
	{
		curr -> proc -> left = NULL;
		curr -> proc -> right = NULL;
	}

}


void helper_build_tree(struct process** tree, struct queue* line, int mem)
{
	/*
		given a queue that represents a binary tree, builds the tree representation of the queue
		
		Argument:
		line -- pointer to the head of the queue
		
		Return:
		tree -- pointer to the root of the binary tree created
	*/
	
	struct queue* curr = line;
	
	for (curr = line; curr != NULL; curr = curr -> next)
	{
		insert_levelorder(tree, curr -> proc, mem);	
	}
}


int rebuild_tree(struct process **root)
{
	/*
		given a binary tree, if it is not complete and level order sorted, it rebuilds the tree to satisfy these two conditions
		
		Arguement:
		root -- double pointer to the root of the binary tree
		
		Returns:
		work_needed -- 1 if the functions rebuilds the tree to be complete and level order sorted. 0 if the tree already 
						satisfies the above two conditions.
	*/
	
	int work_needed = 0;
	
	if (root)
	{
		// if the tree is not complete and is not sorted, rebuild the tree and set the return variable to 1
		if (is_complete(*root) == 0 || is_sorted(*root) == 0)
		{
			struct queue* temp = NULL;								// temporary for building the queue
			struct queue* line = NULL;								// the queue that is going to hold the tree
			struct process* new_tree = NULL;
			
			enqueue(*root, &temp);
			build_levelorder_queue(&temp, &line);					// builds a level order queue from the tree
			merge_sort(&line);										// merge sorts the queue
			free_queue(&temp);										// freeing the temporary queue
			
			int mem = total_mem(*root) + 1;
			set_children_to_null(&line);							// set every nodes' children in the old tree to null
			helper_build_tree(&new_tree, line, mem);				// builds a complete sorted tree from the queue

			*root = new_tree;
			work_needed = 1;		
		}
	}
	
	return work_needed;	
}
 

int kill(struct process **root, int pid)
{
	int work_done = 0;

	if (root)
	{
		work_done = 1;
		struct queue* temp = NULL;
		struct queue* line = NULL;
		struct process* new_tree = NULL;
		struct queue* curr;
		struct queue* dummy;
		int mem = total_mem(*root);

		// build a level order queue representation of the tree
		enqueue(*root, &temp);
		build_levelorder_queue(&temp, &line);		
		set_children_to_null(&line);
		free_queue(&temp);

		// for the case when the node to be removed is at the beginning of the queue (ie. root of the tree)
		if (line -> proc -> pid == pid)
		{
			dummy = line;
			line = line -> next;
			free(dummy);		
		}
		
		// for the case when the node to be removed is not a the root of the binary tree
		else
		{
			for (curr = line; curr -> next != NULL; curr = curr -> next)
			{
				if (curr -> next -> proc -> pid == pid)
				{
					dummy = curr -> next;
					curr -> next = dummy -> next;
					free(dummy);
					break;
				}
			}
		}
		
		// build a new tree with the desired node removed from a sorted level order queue representation of the tree
		merge_sort(&line);
		helper_build_tree(&new_tree, line, mem);
		*root = new_tree;
	}
	
	return work_done;
}
