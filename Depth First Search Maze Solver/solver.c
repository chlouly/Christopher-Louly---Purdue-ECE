#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "solver.h"
#include "mazehelper.h"
#include "path.h"
#include "list.h"

PathLL * solveMaze(Maze * m) {
	
	PathLL * successPaths = buildPaths();
	char * retval = malloc(((m->height * m->width) + 1) * sizeof(char));

	MazePos mp = {.xpos = m->start.xpos, .ypos = m->start.ypos};
	depthFirstSolve(m, mp, retval, 0, successPaths);
	
	free(retval);
	
	return successPaths;
}

void depthFirstSolve(Maze * m, MazePos curpos, char * path, int step, PathLL * successPaths) {
//	printf("\n\nIn solve function	STEP = %d\n\n", step);
  //Fill in. (Your best bet is to modify a working implementation from PA08)
	if (atEnd(curpos, m))
	{
//		printf("\n\nIn 'At end' if statement\n\n");
		path[step] = '\0';
		addNode(successPaths, path);
	//	printPaths(successPaths, stdout);
		return;
	}

	MazePos steps[4] = {
		{.xpos = curpos.xpos, .ypos = curpos.ypos - 1},	//NORTH
                {.xpos = curpos.xpos, .ypos = curpos.ypos + 1},	//SOUTH
                {.xpos = curpos.xpos + 1, .ypos = curpos.ypos},	//EAST
                {.xpos = curpos.xpos - 1, .ypos = curpos.ypos},	//WEST
	};

	int i;

	m->maze[curpos.ypos][curpos.xpos].visited = true;

	for (i = 0; i < 4; i++)
	{
		//printf("\n\n	IN FOR LOOP	i = %d\n\n", i);
		//printf("\n\nBefore new DFS func\n\n");
		if (squareOK(steps[i], m))
		{
			if (i == 0)
			{
				path[step] = 'n';
			}
			else if (i == 1)
			{
				path[step] = 's';
			}
			else if (i == 2)
			{
               	        	path[step] = 'e';
               		}
			else if (i == 3)
                	{
                	        path[step] = 'w';
               		}
                        depthFirstSolve(m, steps[i], path, step + 1, successPaths);	
		}
	}

	m->maze[curpos.ypos][curpos.xpos].visited = false;

//	printf("\n\nAt end of DFS function\n\n");
		
	return;
}
