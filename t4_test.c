#include "t4.h"

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{

	if (argc < 3)
	{
		argv[1] = "./db/vertices.csv";
		argv[2] = "./db/edges.csv";
	}

	if (!load_vertices (argv[1]))
	{
		printf ("Failed to load vertices\n");
		return EXIT_FAILURE;
	}

	if (!load_edges (argv[2]))
	{
		printf ("Failed to load edges\n");
		return EXIT_FAILURE;
	}

	// get the start and end point
	printf ("Please enter stating bus stop >\t\t");
	int startingNode;
	scanf ("%d", &startingNode);
	printf ("Please enter destination bus stop >\t");
	int endingNode;
	scanf ("%d", &endingNode);

	shortest_path (startingNode, endingNode);

	free_memory ();

	return EXIT_FAILURE;
}