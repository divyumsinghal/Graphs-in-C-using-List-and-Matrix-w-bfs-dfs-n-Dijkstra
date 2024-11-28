#ifndef T2_H_
#define T2_H_

#define MAX_VERTICES 10  // you can assume that the graph has at most 10 vertex

typedef enum bool
{
	false = 0,
	true  = 1
} bool;

typedef struct Graph
{
	int   Graph_Size;
	int** Matrix;

} Graph;

Graph* create_graph (int num_nodes);                       // creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
void   add_edge (Graph* g, int from, int to, int weight);  // adds an undirected weighted edge between from and to
void   bfs (Graph* g, int origin);                         // implements breath first search and prints the results
void   dfs (Graph* g, int origin);                         // implements depth first search and prints the results
void   dijkstra (Graph* g, int origin);                    // implements the dijkstra algorithm and prints the order in which the nodes are made permament, and the length of the shortest path between the origin node and all the other nodes
void   delete_graph (Graph* g);

#endif