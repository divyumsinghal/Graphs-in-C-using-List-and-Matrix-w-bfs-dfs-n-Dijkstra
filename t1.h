#ifndef T1_H_
#define T1_H_

typedef enum bool
{
	false = 0,
	true  = 1
} bool;

typedef struct Graph
{
	int   size;
	int** List;
	int*  List_size;
} Graph;

Graph* create_graph (int num_nodes);           // Creates a graph with num_nodes nodes
void   add_edge (Graph* g, int from, int to);  // Adds a directed edge
void   bfs (Graph* g, int origin);             // Implements breadth-first search and prints the results
void   dfs (Graph* g, int origin);             // Implements depth-first search and prints the results
void   dijkstra (Graph* g, int origin);        // implements the dijkstra algorithm and prints the order in which the nodes are made permament, and the length of the shortest path between the origin node and all the other nodes
void   delete_graph (Graph* g);                // Frees the memory allocated for the graph

#endif
