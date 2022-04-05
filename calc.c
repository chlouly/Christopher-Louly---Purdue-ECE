#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "calc.h"

#define NUMOPERATIONS 4

bool calculator(FILE * fptr, StackLL * s)
{
	char * subject = (char *) malloc(50 * sizeof(char));
	float val1, val2;
	char c;
	/* isOperation ==
 		1   when subject is an operand
		0   when subject is a float
		-1  when subject is something else (like "P" or something)*/
	int isOperation;	

	while (fscanf(fptr, "%s", subject) != EOF)
	{
		isOperation = isOperand(subject);
		if (isOperation == (-1))
		{
			free(subject);
			return false;
		}	
		else if (isOperation)
		{
			// Note the order, val2 first then val1
			if ((!pop(s, &val2)) || (!pop(s, &val1)))
			{
				free(subject);
				return false;
			}
			else
			{
				c = subject[0];
				val1 = (c == '+')? (val1 + val2) : (c == '-')? (val1 - val2) : (c == '*')? (val1 * val2) : (val1 / val2);
				if (!push(s, val1))
				{
					free(subject);
					return false;
				}
			}	
		}
		else
		{
			if (!push(s, atof(subject)))
			{
				free(subject);
				return false;
			}
		}
	}

	if ((s->top == NULL) || (s->top->next != NULL))
	{
		free(subject);
		return false;
	}
	
	free(subject);		
	return true;
}

int isOperand(char * input)
{
	char * operands[NUMOPERATIONS] = {"+", "-", "*", "/"};

	int i = 0;

        for (i = 0; i < NUMOPERATIONS; i++)
        {
                if (!strcmp(input, operands[i]))
                {
                        return true;
                }
        }

	if ((atof(input) == 0) && ((!strcmp(input, "0")) && (!strcmp(input, "-0"))))
	{	
		// if an input isn't an operator or a number
		return (-1);
	}
        return false;
}

