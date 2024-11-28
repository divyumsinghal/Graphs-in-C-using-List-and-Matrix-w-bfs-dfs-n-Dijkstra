#ifndef T3_H_
#define T3_H_

#define num_nodes 10000

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum bool
{
	false = 0,
	true  = 1
} bool;

typedef struct Node
{
	int  StopId;
	char Name[40];
	char Latitude[40];
	char Longitude[40];

} Node;

typedef struct Graph
{
	int** Adjacency_Matrix;
	Node* List_of_Nodes;
} Graph;

Graph* map;

int  load_edges (char* fname);                    // loads the edges from the CSV file of name fname
int  load_vertices (char* fname);                 // loads the vertices from the CSV file of name fname
void shortest_path (int startNode, int endNode);  // prints the shortest path between startNode and endNode, if there is any
void free_memory (void);                          // frees any memory that was used
int  next_field (FILE* csv, char* word, int max_len);
#endif