#include "t2.h"

#include <stdio.h>
#include <stdlib.h>

int** matrix_maker (int size)
{
	int** result = (int**) malloc (size * size * sizeof (int));

	for (int i = 0; i < size; i++)
	{
		result[i] = (int*) calloc (size, sizeof (int));
	}

	return result;
}

Graph* create_graph (int num_nodes)
{
	printf ("Creating Graph\n");

	Graph* result = (Graph*) malloc (sizeof (Graph));

	if (!result)
	{
		printf ("Error");
		free (result);
		return NULL;
	}

	result->Graph_Size = num_nodes;
	result->Matrix     = matrix_maker (num_nodes);

	if (!result || !result->Graph_Size || !result->Matrix)
	{
		printf ("Error");
		return NULL;
	}

	/*for (int i = 0; i < num_nodes; i++)
	{
	        for (int j = 0; j < num_nodes; j++)
	        {
	                result->Matrix[i][j] = 0;
	        }
	}*/

	return result;
}

void add_edge (Graph* g, int from, int to, int weight)
{
	if ((0 < from < g->Graph_Size) && (0 < to < g->Graph_Size) && (0 < weight))
	{
		g->Matrix[from][to] = weight;
		g->Matrix[to][from] = weight;
	}
	else
		printf (" Invalid Nodes ");
}

void bfs (Graph* g, int origin)
{
	printf ("\nBFS:\n");

	int   num_nodes = g->Graph_Size;
	int*  queue     = (int*) calloc (2 * num_nodes, sizeof (int));
	bool* visited   = (bool*) calloc (num_nodes, sizeof (bool));
	int   front     = 0;
	int   rear      = 0;

	queue[rear++] = origin;

	while (front < rear)
	{
		int node      = queue[front++];
		visited[node] = true;

		printf ("%c \n", 'A' + node);

		for (int i = 0; i < num_nodes; i++)
		{
			if (g->Matrix[node][i] != 0 && visited[i] == false)
			{
				queue[rear++] = i;
				visited[i]    = true;
				// printf ("\t %c, ", 'A' + i);
			}
		}
		// printf ("\n");
	}

	free (visited);
	free (queue);
}

void dfs (Graph* g, int origin)
{
	printf ("\nDFS:\n");

	int num_nodes = g->Graph_Size;

	int*  stack   = (int*) calloc (2 * num_nodes, sizeof (int));
	bool* visited = (bool*) calloc (num_nodes, sizeof (bool));
	int   sp      = 0;

	stack[sp++] = origin;

	while (sp > 0)
	{
		int node = stack[--sp];

		if (visited[node] == false)
		{
			visited[node] = true;

			printf ("%c \n", 'A' + node);

			for (int i = num_nodes - 1; i > 0; i--)
			{
				if (g->Matrix[node][i] != 0 && !visited[i])
				{
					stack[sp++] = i;
					// printf ("\t %c, ", 'A' + i);
				}
			}
			// printf ("\n");
		}
	}

	free (stack);
	free (visited);
}

void dijkstra (Graph* g, int origin)
{
	printf ("\nPrinting Dijkstra:\n");

	int num_nodes = g->Graph_Size;

	int*  smallest_path_from_origin = (int*) malloc (num_nodes * sizeof (int));
	int*  nearest_node_from_origin  = (int*) malloc (num_nodes * sizeof (int));
	bool* visited                   = (bool*) calloc (num_nodes, sizeof (bool));

	for (int i = 0; i < num_nodes; i++)
	{
		smallest_path_from_origin[i] = INT_MAX;
		nearest_node_from_origin[i]  = -1;
	}

	smallest_path_from_origin[origin] = 0;
	nearest_node_from_origin[origin]  = origin;

	for (int visited_nodes = 0; visited_nodes < num_nodes; visited_nodes++)
	{
		int node = -1;
		int dist = INT_MAX;

		for (int i = 0; i < num_nodes; i++)
		{
			if (!visited[i] && smallest_path_from_origin[i] < dist)
			{
				node = i;
				dist = smallest_path_from_origin[i];
			}
		}

		if (node == -1)
		{
			break;
		}

		visited[node] = true;
		printf (" %c ", 'A' + node);

		for (int i = 0; i < num_nodes; i++)
		{
			if (g->Matrix[node][i] != 0 && !visited[i])
			{
				int new_dist = dist + g->Matrix[node][i];
				if (new_dist < smallest_path_from_origin[i])
				{
					smallest_path_from_origin[i] = new_dist;
					nearest_node_from_origin[i]  = node;
				}
			}
		}
	}

	printf ("\n");

	for (int i = 0; i < num_nodes; i++)
	{
		printf ("Distance for node %c is %d, through %c \n",
		        'A' + i,
		        smallest_path_from_origin[i],
		        nearest_node_from_origin[i] == -1 ? '-' : 'A' + nearest_node_from_origin[i]);
	}

	free (smallest_path_from_origin);
	free (nearest_node_from_origin);
	free (visited);
}

void delete_graph (Graph* graph)
{
	if (graph)
	{
		for (int i = 0; i < graph->Graph_Size; i++)
		{
			free (graph->Matrix[i]);
		}
		free (graph->Matrix);
		free (graph);
	}
}
