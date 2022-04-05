#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "calc.h"
//Stack Functions
StackLL * createStack()
{
	StackLL * Stack = (StackLL *) malloc(sizeof(StackLL));
	Stack->top = NULL;
	return (Stack);
}

StackNode * createNode(float input)
{
	// Actually allocating node
	StackNode * retval = (StackNode *) malloc(sizeof(StackNode));
	retval->next = NULL;

	// Reading string
	retval->value = input;
	return (retval);
}

bool push (StackLL * Stack, float input)
{
	StackNode * node = createNode(input);
	
	if (node == NULL)
	{
		return false;
	}

	if (Stack->top == NULL)
	{
		Stack->top = node;
		return true;
	}
	
	node->next = Stack->top;
	Stack->top = node;

	return true;
}

bool pop (StackLL * Stack, float * value)
{
	if (Stack->top == NULL)
	{
		return false;
	}

	StackNode * temp = NULL;

	temp = Stack->top;
	*value = temp->value;
	Stack->top = Stack->top->next;
	freeNode(temp);

	return true;
}

void freeNode(StackNode * node)
{
	free(node);	
}

void freeStack(StackLL * Stack)
{
	StackNode * temp = Stack->top;

	while (Stack->top != NULL)
	{
		Stack->top = temp->next;
		freeNode(temp);
		temp = Stack->top;
	}

	free(Stack);
}

