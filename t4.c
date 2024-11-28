#include "t4.h"

int next_field (FILE* csv, char* word, int max_len)
{
	int  i             = 0;
	bool inside_quotes = false;
	char c;

	while ((c = fgetc (csv)) != EOF)
	{
		if (i >= max_len - 1)
			break;

		if (c == '"')
		{
			inside_quotes = !inside_quotes;
			continue;
		}

		if (c == ',' && !inside_quotes)
		{
			word[i] = '\0';
			return 0;
		}

		if (c == '\n' && !inside_quotes)
		{
			word[i] = '\0';
			return 1;
		}

		if (i < max_len - 1)
		{
			word[i++] = c;
		}
	}

	word[i] = '\0';

	return feof (csv) ? -1 : 0;
}

void add_edge (int src, int dest, int weight)
{
	NextNode* new_edge                = (NextNode*) malloc (sizeof (NextNode));
	new_edge->destination         = dest;
	new_edge->weight              = weight;
	new_edge->next                = map->List_of_Nodes[src].edges;
	map->List_of_Nodes[src].edges = new_edge;
}

int load_edges (char* fname)
{
	int   num = 0;
	FILE* csv = fopen (fname, "r");

	if (!csv)
	{
		printf ("Error opening file.\n");
		return false;
	}
	else
	{
		printf ("edges.csv loaded!\n");
	}

	char word[40];

	while (next_field (csv, word, 40) != -1)
	{
		int vertex1 = atoi (word);

		next_field (csv, word, 40);
		int vertex2 = atoi (word);

		next_field (csv, word, 40);
		int weight = atoi (word);

		add_edge (vertex1, vertex2, weight);
		add_edge (vertex2, vertex1, weight); 
		num++;
	}

	printf ("Loaded %d edges \n", num);
	fclose (csv);
	return true;
}

int load_vertices (char* fname)
{
	int num            = 0;
	map                = (Graph*) malloc (sizeof (Graph));
	map->List_of_Nodes = (Node*) calloc (NUM_NODES, sizeof (Node));

	FILE* csv = fopen (fname, "r");

	if (!csv)
	{
		printf ("Error opening file.\n");
		return false;
	}
	else
	{
		printf ("vertices.csv loaded!\n");
	}

	char word[40];

	while (next_field (csv, word, 40) != -1)
	{
		int id = atoi (word);

		next_field (csv, word, 40);
		strcpy (map->List_of_Nodes[id].Name, word);

		next_field (csv, word, 40);
		strcpy (map->List_of_Nodes[id].Latitude, word);

		next_field (csv, word, 40);
		strcpy (map->List_of_Nodes[id].Longitude, word);
		num++;
	}

	printf ("Loaded %d vertices \n", num);
	fclose (csv);
	return true;
}

void shortest_path (int startNode, int endNode)
{
	printf ("\nCalculating Dijkstra's shortest path:\n");

	int*  smallest_path_from_origin = (int*) malloc (NUM_NODES * sizeof (int));
	int*  nearest_node_from_origin  = (int*) malloc (NUM_NODES * sizeof (int));
	bool* visited                   = (bool*) calloc (NUM_NODES, sizeof (bool));

	for (int i = 0; i < NUM_NODES; i++)
	{
		smallest_path_from_origin[i] = INT_MAX;
		nearest_node_from_origin[i]  = -1;
	}

	smallest_path_from_origin[startNode] = 0;

	for (int visited_nodes = 0; visited_nodes < NUM_NODES; visited_nodes++)
	{
		int node             = -1;
		int current_distance = INT_MAX;

		for (int i = 0; i < NUM_NODES; i++)
		{
			if (!visited[i] && smallest_path_from_origin[i] < current_distance)
			{
				node             = i;
				current_distance = smallest_path_from_origin[i];
			}
		}

		if (node == -1)
		{
			break;
		}

		visited[node] = true;

		for (NextNode* edge = map->List_of_Nodes[node].edges; edge; edge = edge->next)
		{
			int neighbor = edge->destination;
			if (!visited[neighbor])
			{
				int new_distance = current_distance + edge->weight;
				if (new_distance < smallest_path_from_origin[neighbor])
				{
					smallest_path_from_origin[neighbor] = new_distance;
					nearest_node_from_origin[neighbor]  = node;
				}
			}
		}
	}

	if (smallest_path_from_origin[endNode] != INT_MAX)
	{
		printf ("\nShortest path to node %d has a distance of %d.\n", endNode, smallest_path_from_origin[endNode]);
		printf ("Path:\n");

		int path[NUM_NODES];
		int path_length = 0;
		for (int node = endNode; node != -1; node = nearest_node_from_origin[node])
		{
			path[path_length++] = node;
		}

		for (int i = path_length - 1; i >= 0; i--)
		{
			printf ("%5d, %30s, %10s, %10s\n",
			        path[i],
			        map->List_of_Nodes[path[i]].Name,
			        map->List_of_Nodes[path[i]].Latitude,
			        map->List_of_Nodes[path[i]].Longitude);
		}
		printf ("\n");
	}
	else
	{
		printf ("\nNode %d is unreachable from node %d.\n", endNode, startNode);
	}

	free (smallest_path_from_origin);
	free (nearest_node_from_origin);
	free (visited);
}

void free_memory (void)
{
	if (map)
	{
		for (int i = 0; i < NUM_NODES; i++)
		{
			NextNode* edge = map->List_of_Nodes[i].edges;
			while (edge)
			{
				NextNode* temp = edge;
				edge       = edge->next;
				free (temp);
			}
		}
		free (map->List_of_Nodes);
		free (map);
	}
}
