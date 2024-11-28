#ifndef T4_H_
#define T4_H_

#define NUM_NODES 10000

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum bool
{
	false = 0,
	true  = 1
} bool;

typedef struct NextNode
{
	int              destination;
	int              weight;
	struct NextNode* next;
} NextNode;

typedef struct Node
{
	int       StopId;
	char      Name[40];
	char      Latitude[40];
	char      Longitude[40];
	NextNode* edges;  // Adjacency list head
} Node;

typedef struct Graph
{
	Node* List_of_Nodes;
} Graph;

Graph* map;

int  load_edges (char* fname);                    // Loads edges from the CSV file
int  load_vertices (char* fname);                 // Loads vertices from the CSV file
void shortest_path (int startNode, int endNode);  // Prints the shortest path between startNode and endNode, if any
void free_memory (void);                          // Frees allocated memory

#endif
