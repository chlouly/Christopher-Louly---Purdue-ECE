#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "path.h"
#include "solver.h"
#include "paths.h"

int main(int argc, char ** argv) {
	if (argc != 3) {
		fprintf(stderr, "Wrong number of command line args\n");
		fprintf(stderr, "Usage: ./hw11 mazeFile pathFile\n");
		return EXIT_FAILURE;
	}
	
	Maze * m = readMaze(argv[1]);
	
	if (m == NULL) {
		return EXIT_FAILURE;
	}
	
	PathLL * paths = solveMaze(m);
	
	FILE * fptr = fopen(argv[2], "w");
	if (fptr == NULL) {
		freeMaze(m);
		free(m);
		freePaths(paths);
		fclose(fptr);
		return EXIT_FAILURE;
	} else {
		printPaths(paths, fptr);
		freeMaze(m);
		free(m);
		freePaths(paths);
		fclose(fptr);
	}
		
	return EXIT_SUCCESS;
}
