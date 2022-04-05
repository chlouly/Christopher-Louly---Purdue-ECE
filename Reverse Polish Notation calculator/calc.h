#ifndef CALCH
#define CALCH
#include <stdbool.h> 

// Typedef for each Node on the stack
typedef struct StackNode {
	struct StackNode * next;
	float value;
} StackNode;

// Typedef for a pointer to the Stack linked list
typedef struct StackLL {
	StackNode * top;
} StackLL;

	/*   STACK FUNCTIONS (FOR STACK.C)   */

// Create a stack
StackLL * createStack();

// Create a Node
StackNode * createNode(float value);

// Push function declaration
bool push(StackLL * Stack, float value);

// Pop function declaration
bool pop(StackLL * Stack, float * value);

// Free a node
void freeNode(StackNode * node);

// Free a stack
void freeStack(StackLL * Stack);

	/*   CALCULATOR FUNCTIONS (FOR CLAC.C)   */

// Check if something is an operand
int isOperand(char * string);

// Reads the file and does calculation
bool calculator(FILE * fptr, StackLL * s);

#endif
