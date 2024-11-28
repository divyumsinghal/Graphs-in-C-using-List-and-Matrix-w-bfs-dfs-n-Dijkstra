#include "t1.h"

#include <stdio.h>
#include <stdlib.h>

Graph* create_graph (int num_nodes)
{
	printf ("Creating Graph\n");

	Graph* result     = (Graph*) malloc (sizeof (Graph));
	result->List      = (int**) malloc (num_nodes * sizeof (int*));
	result->List_size = (int*) calloc (num_nodes, sizeof (int));
	result->size      = num_nodes;

	for (int i = 0; i < num_nodes; i++)
	{
		result->List[i] = NULL; 
	}

	return result;
}

void add_edge (Graph* g, int from, int to)
{
	if (from < g->size && to < g->size)
	{
		g->List[from]                     = (int*) realloc (g->List[from], (g->List_size[from] + 1) * sizeof (int));
		g->List[from][g->List_size[from]] = to;
		g->List_size[from]++;
	}
	else
	{
		printf ("Invalid nodes\n");
	}
}

void bfs (Graph* g, int origin)
{
	printf ("\nBFS:\n");

	int   num_nodes = g->size;
	int*  queue     = (int*) malloc (num_nodes * sizeof (int));
	bool* visited   = (bool*) calloc (num_nodes, sizeof (bool));
	int   front = 0, rear = 0;

	queue[rear++]   = origin;
	visited[origin] = true;

	while (front < rear)
	{
		int node = queue[front++];
		printf ("%c\n", 'A' + node);

		for (int i = g->List_size[node] - 1; i >= 0 ; i--)
		{
			int neighbor = g->List[node][i];
			if (!visited[neighbor])
			{
				queue[rear++]     = neighbor;
				visited[neighbor] = true;
			}
		}
	}

	free (queue);
	free (visited);
}

void dfs (Graph* g, int origin)
{
	printf ("\nDFS:\n");

	int   num_nodes = g->size;
	int*  stack     = (int*) malloc (num_nodes * sizeof (int));
	bool* visited   = (bool*) calloc (num_nodes, sizeof (bool));
	int   sp        = 0;

	stack[sp++] = origin;

	while (sp > 0)
	{
		int node = stack[--sp];

		if (!visited[node])
		{
			visited[node] = true;
			printf ("%c\n", 'A' + node);

			for (int i = 0; i < g->List_size[node] ; i++)
			{
				int neighbor = g->List[node][i];
				if (!visited[neighbor])
				{
					stack[sp++] = neighbor;
				}
			}
		}
	}

	free (stack);
	free (visited);
}

void dijkstra (Graph* g, int origin)
{
	printf ("\nDijkstra's Algorithm:\n");

	int*  dist    = (int*) malloc (g->size * sizeof (int));   
	bool* visited = (bool*) calloc (g->size, sizeof (bool)); 
	int*  prev    = (int*) malloc (g->size * sizeof (int));  

	for (int i = 0; i < g->size; i++)
	{
		dist[i] = INT_MAX;
		prev[i] = -1;
	}
	dist[origin] = 0;  

	for (int i = 0; i < g->size; i++)
	{
		int min_dist = INT_MAX, u = -1;
		for (int j = 0; j < g->size; j++)
		{
			if (!visited[j] && dist[j] < min_dist)
			{
				min_dist = dist[j];
				u        = j;
			}
		}

		if (u == -1) break;
		visited[u] = true;

		for (int k = 0; k < g->List_size[u]; k++)
		{
			int neighbor = g->List[u][k];
			if (!visited[neighbor] && dist[u] + 1 < dist[neighbor])
			{
				dist[neighbor] = dist[u] + 1;
				prev[neighbor] = u;
			}
		}

		printf ("Permanent: %c, Distance: %d\n", 'A' + u, dist[u]);
	}

	printf ("\nShortest distances from %c:\n", 'A' + origin);
	for (int i = 0; i < g->size; i++)
	{
		printf ("To %c: %d\n", 'A' + i, dist[i]);
	}

	free (dist);
	free (visited);
	free (prev);
}


void delete_graph (Graph* g)
{
	if (g)
	{
		for (int i = 0; i < g->size; i++)
		{
			free (g->List[i]);
		}
		free (g->List);
		free (g->List_size);
		free (g);
	}
}
