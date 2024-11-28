#include "t3.h"

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

int** matrix_maker (int size)
{
	int** result = (int**) malloc (size * sizeof (int*));
	for (int i = 0; i < size; i++)
	{
		result[i] = (int*) calloc (size, sizeof (int));
	}
	return result;
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

		map->Adjacency_Matrix[vertex1][vertex2] = weight;
		map->Adjacency_Matrix[vertex2][vertex1] = weight;
		num++;
	}

	printf ("Loaded %d edges \n", num);


	fclose (csv);
	return true;
}

int load_vertices (char* fname)
{
	int num               = 0;
	map         = (Graph*) malloc (sizeof (Graph));
	map->List_of_Nodes   = (Node*) calloc (num_nodes, sizeof (Node));
	map->Adjacency_Matrix = matrix_maker (num_nodes);

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
		// printf (word);
		strcpy (map->List_of_Nodes[id].Latitude, word);
		// printf (map->List_of_Nodes[id].Latitude);

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

	int*  smallest_path_from_origin = (int*) malloc (num_nodes * sizeof (int));
	int*  nearest_node_from_origin  = (int*) malloc (num_nodes * sizeof (int));
	bool* visited                   = (bool*) calloc (num_nodes, sizeof (bool));

	for (int i = 0; i < num_nodes; i++)
	{
		smallest_path_from_origin[i] = INT_MAX;
		nearest_node_from_origin[i]  = -1;
	}

	smallest_path_from_origin[startNode] = 0;
	nearest_node_from_origin[startNode]  = startNode;

	for (int visited_nodes = 0; visited_nodes < num_nodes; visited_nodes++)
	{
		int node             = -1;
		int current_distance = INT_MAX;

		for (int i = 0; i < num_nodes; i++)
		{
			if (!visited[i] && smallest_path_from_origin[i] < current_distance)
			{
				node             = i;
				current_distance = smallest_path_from_origin[i];
			}
		}

		if (node == -1)
		{
			// printf ("Disconnected graph or unreachable nodes detected.\n");
			break;
		}

		visited[node] = true;

		for (int i = 0; i < num_nodes; i++)
		{
			if (map->Adjacency_Matrix[node][i] != 0 && !visited[i])
			{
				int new_distance = current_distance + map->Adjacency_Matrix[node][i];
				if (new_distance < smallest_path_from_origin[i])
				{
					smallest_path_from_origin[i] = new_distance;
					nearest_node_from_origin[i]  = node;
				}
			}
		}
	}

	/*printf ("\nShortest Path Results:\n");
	for (int i = 0; i < num_nodes; i++)
	{
		if (smallest_path_from_origin[i] != INT_MAX)
		{
			printf ("Node %d: Distance = %d, Previous = %d\n",
			        i,
			        smallest_path_from_origin[i],
			        nearest_node_from_origin[i]);
		}
	}*/

	if (smallest_path_from_origin[endNode] != INT_MAX)
	{
		printf ("\nShortest path to node %d has a distance of %d.\n", endNode, smallest_path_from_origin[endNode]);
		printf ("Path: \n");

		int path[num_nodes]; 
		int path_length = 0;
		for (int node = endNode; node != startNode; node = nearest_node_from_origin[node])
		{
			if (node == -1)  
			{
				printf ("Path reconstruction failed. Graph may be disconnected.\n");
				break;
			}
			path[path_length++] = node;
		}
		path[path_length++] = startNode;

		for (int i = path_length - 1; i >= 0; i--)
		{
			printf ("%5d, %30s, %10s, %10s \n", path[i], map->List_of_Nodes[path[i]].Name, map->List_of_Nodes[path[i]].Latitude, map->List_of_Nodes[path[i]].Longitude);
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
		for (int i = 0; i < num_nodes; i++)
		{
			free (map->Adjacency_Matrix[i]);
		}
		free (map->Adjacency_Matrix);
		free (map->List_of_Nodes);
		free (map);
	}
}
