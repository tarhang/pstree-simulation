#include "process.h"

int main(int argc, const char * argv[])
{
    if(argc != 3)
    {
        printf("Please enter only the first PID and maximum size of memory.\n");
        return 0;
    }
    else
    {
	// second tree from test_two
	struct process* second = make_process(7, 7);
	second->right = make_process(8, 8);
	second->right->left = make_process(9, 9);
	second->right->right = make_process(10, 10);
	second->right->left->right = make_process(11, 11);

	// Test 1: can_add_alternate
	printf("Testing can_add_alternate\n");
	// accepts non-unique PIDs
	printf("%d\n", can_add_alternate(second, make_process(7, 7), 1000) ); // 1
	printf("%d\n", can_add_alternate(second, make_process(11, 7), 1000) ); // 1
	printf("%d\n", can_add_alternate(second, make_process(12, 7), 1000) ); // 1
	// max memory
	printf("%d\n", can_add_alternate(second, make_process(12, 1), 0) ); // 0
	printf("%d\n", can_add_alternate(second, make_process(12, 1), 45) ); // 0
	printf("%d\n", can_add_alternate(second, make_process(12, 1), 46) ); // 1
	printf("%d\n", can_add_alternate(second, make_process(12, 1), 47) ); // 1
	// adding NULL
//	printf("%d\n", can_add_alternate(second, NULL, 46) ); // should abort --  can_add_alternate: Assertion `new_node' failed.


	// Test 2: spawn
//	spawn(NULL, 4); // should abort as root is NULL
 	spawn(second, 50); // should abort as second's root has children
//	struct process* third = make_process(1, 1);
// 	spawn(third, -1); // should abort as invalid amount of memory
//	spawn(third, 1); // won't add anything new
//	print_levelorder(third); // 1
//	print_inorder(third); // 1

//	spawn(third, 8);
//	print_levelorder(third); // 1 1 2 1 3 2 4 1 5 3 6 2 7 4 8
//	print_inorder(third); // 1 1 5 1 3 3 6 1 2 2 7 2 4 4 8

//	struct process* fourth = make_process(50, 2);
//	spawn(fourth, 6);
//	print_levelorder(fourth); // 50 50 51 50 52 51
//	print_inorder(fourth); // 50 50 52 50 51 51
	
//	struct process* fifth = make_process(50, 2);
//	spawn(fifth, 7);
//	print_levelorder(fifth); // 50 50 51 50 52 51
//	print_inorder(fifth); // 50 50 52 50 51 51

	// Test 3: is_leaf
//	printf("%d\n", is_leaf(fourth, fourth->left->left)); // 1
//	printf("%d\n", is_leaf(fourth, fourth)); // 0
//	printf("%d\n", is_leaf(fourth, third->left->left)); // 0
//	printf("%d\n", is_leaf(fourth, third)); // 0
//	printf("%d\n", is_leaf(NULL, third)); // 0
//	printf("%d\n", is_leaf(NULL, NULL)); // 1
//	printf("%d\n", is_leaf(third, NULL)); // 0

	// Test 4: time_to_crash -- output will depend on computer
//	printf("%d\n", time_to_crash(make_process(1, 1), 1 )); // will be probably 0
//	printf("%d\n", time_to_crash(make_process(1, 1), 1000 )); // should be greater than 0
//	printf("%d\n", time_to_crash(make_process(1, 1), 100000 )); // will be greater than 0
//	printf("%d\n", time_to_crash(make_process(1, 2), 100000 )); // will be less than the above
//	printf("%d\n", time_to_crash(make_process(1, 3), 100000 )); // will be less than the above
//	printf("%d\n", time_to_crash(make_process(1, 1000), 100000 )); // will be less than the above

	// Test 5: killall
//	killall(&second);
//	print_inorder(second); // prints no tree
//	killall(&third);
//	killall(&fourth);
//	killall(&fifth);
//	killall(NULL); 
	// after this, all memory should be freed. Check with valgrind.
	}

	return 0;
}
