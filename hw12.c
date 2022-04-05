#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf(stderr, "Incorrect number of arguments.\n");
		fprintf(stderr, "Usage: ./pa11 <input file>\n");		
		return EXIT_FAILURE;
	}

	float result; //store the result of your calculation here.
	
	/* Insert code here to perform the RPN calculation.
	Don't forget to free any memory you allocate once you're done with it! */

	// Creating Stack
	StackLL * s = createStack();
	if (s == NULL)
	{
		return EXIT_FAILURE;
	}

	// Opening input file
	FILE * fptr = fopen(argv[1], "r");
	if (fptr == NULL)
	{
		freeStack(s);
		return EXIT_FAILURE;
	}

	// Returning if calculator failed
	if (!calculator(fptr, s))
	{
		freeStack(s);
		fclose(fptr);
		return EXIT_FAILURE;
	}
	else
	{
		result = s->top->value;	

		printf("%f\n", result);

		freeStack(s);
		fclose(fptr);
		return EXIT_SUCCESS;
	}
}
