# pstree-simulation
This is a simulation of computer processes using tree data structures. As a bit of background, when the computer boots, it creates a process. That process creates child processes, which in turn create child processes, and so on. In this project, we assume each process can create up to two child processes, giving rise to the binary tree data structure used.

This project was implemented as a CSC190 course project at the University of Toronto in winter 2013. You can learn more about the project goals and requirements [here](http://www.cs.toronto.edu/~patitsas/cs190/lab5.html) and [here](http://www.cs.toronto.edu/~patitsas/cs190/lab6.html)

## Installation
To get a copy of this project on your local machine, navigate to the directory you want to clone this project to. Then clone this repository with 
```
git clone https://github.com/tarhang/pstree-simulation.git
```

## Usage
* `process.h` - contains the struct definitions and function headers
* `process_provided_parts.c` - contains the queue and stack implementations. Some helper methods for struct process are also included. These functions were provided, as the name suggests!
* `process.c` - contains the algorithm implementations. This is the core of the project
* `test_one.c`, `test_two.c`, and `test_three.c` - contain a main function with test cases for the algorithms developed. Compile each separately
* `Makefile` - contains the command-line compilation instructions to compile each of the three test files. To compile each of the test files, follow the instructions below in the command-line
  * type `make one` in the coomand line to create an executable file. `./one` executes the executable file
  * type `make two` in the command-line to create an executable file. This executable requires two additional command-line arguments (50 and 24). Run the executale with `./two 50 24`
