#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

/** INTERFACE FUNCTIONS **/

PathLL * buildPaths() {
	PathLL * retval = (PathLL *)malloc(sizeof(PathLL));
	retval->head = NULL;
	return retval;
}

void freePaths(PathLL * p) {

	PathNode * cur = p->head;	

	while (cur != NULL)
	{
		p->head = p->head->next;
		freeNode(cur);
		cur = p->head;
	}
	free(p);
}

PathNode * buildNode(char * path) {
	PathNode * retval = (PathNode *)malloc(sizeof(PathNode));
	retval->path = (char *) malloc(strlen(path) + 1);
	strcpy(retval->path, path);
	retval->next = NULL;
	return(retval);
	
	//WARNING: don't forget to use strcpy to copy path into the
	//new node. Don't just set them equal, otherwise if the input path changes
	//the node will have the wrong path.
}

void freeNode(PathNode * p) {
	free(p->path);
	free(p);	
}


bool addNode(PathLL * paths, char * path) {
	//If the path is empty
	//printf("\nIn add Node function\n");
	if (paths->head == NULL)
	{
	//	printf("\nList was empty\n");
		paths->head = buildNode(path);
		return true;
	}

	//If it contains the node already
	if (containsNode(paths, path))
	{
	//	printf("\nThe node was already in the list\n");
		return false;
	}
	
	//If the new node belongs at the front of the list
	if (pathComp(paths->head->path, path) < 0)
	{
		PathNode * temp = paths->head;
		paths->head = buildNode (path);
		paths->head->next = temp;
		return true;
	}

	//If node belongs in the middle or at the end of the list
	PathNode * cur = paths->head;

        while (cur->next != NULL)
        {
                if (pathComp(cur->next->path, path) < 0)
                {
                        PathNode * temp = cur->next;
                        cur->next = buildNode (path);
			cur->next->next = temp;
			return true;
		}
		cur = cur->next;
	}

	if (cur->next == NULL)
	{
		cur->next = buildNode(path);
		return true;
	}

	//If it gets this far and hasnt returned, it failed
	return false;
}

bool removeNode(PathLL * paths, char * path) {
	//checking if the node exists
	if (!containsNode (paths, path))
	{
		return false;
	}

	PathNode * cur = paths->head;

        //If first node is the node to be removed
        if (strcmp(path, paths->head->path) == 0)
	{
		paths->head = cur->next;
		free (cur);
		return true;
	}

	//If the path to be removed isn't first
	while (cur->next != NULL)
	{
		if (strcmp(cur->next->path, path) == 0)
		{
			PathNode * temp = cur->next;
			cur->next = cur->next->next;
			free(temp);
			return true;
		}
		cur = cur->next;
	}

	//If it makes it here without returning it probably failed
	return false;

}

bool containsNode(PathLL * paths, char * path) {
	PathNode * cur = paths->head;

	while (cur != NULL)
	{
		if (0 == strcmp(path, cur->path))
		{
			return true;
		}
		cur = cur->next;
	}
	
	return false;
}

void printPaths(PathLL * paths, FILE * fptr) {
	PathNode * curr = paths->head;
	int i = 0;
	while (curr != NULL) {
		fprintf(fptr, "Path %2d: %s\n", i, curr->path);
		i++;
		curr = curr->next;
	}
}

//My path comparison helper function
//Returns +ve int when Path 1 is better
//Returns -ve int when Path 2 is better
//Returns 0 when path1 = path2

int pathComp(char * path1, char * path2) {
	//Checking if Equal
	if (strcmp(path1, path2) == 0)
	{
		return (0);
	}
	
	//Comparing length
	int i = 0;
	while ((path1[i] != 0) && (path2[i] != 0))
	{
		i++;
	}

	if (path1[i] != path2[i])
	{
//		printf("\nReturning from LENGTH\n");
		return(path2[i] - path1[i]);
	}
	
	//Comparing No. of turns
	int numTurns1 = 0;
	int numTurns2 = 0;
	i = 0;

	while (path1[i + 1] != 0)
	{
		numTurns1 += (path1[i] == path1[i + 1]) ? 0 : 1;
		numTurns2 += (path2[i] == path2[i + 1]) ? 0 : 1;
		i++;
	}

	if (numTurns1 != numTurns2)
	{
//		printf("\nReturning from NUM TURNS\n");
		return(numTurns2 - numTurns1);
	}

	//Compare Aplhabetical order
	i = 0;
	while (path1[i] == path2[i])
	{
		i++;
	}
	
//	printf("\nReturning from ALPH ORDER\n");
	return(path2[i] - path1[i]);
}
