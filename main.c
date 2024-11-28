#include <curl/curl.h>
#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define URL "https://api.smartdublin.ie/"

typedef struct Node
{
	int          StopId;
	char         Name[50];
	double       Latitude;
	double       Longitude;
	struct Node* Next;
} Node;

typedef struct Graph
{
	int    Graph_Size;
	Node** List;
} Graph;

Graph* map;

size_t write_callback (void* ptr, size_t size, size_t nmemb, char* data)
{
	size_t new_len = size * nmemb;
	strncat (data, ptr, new_len);
	return new_len;
}

int fetch_data_from_api (const char* url, char* data)
{
	CURL*    curl;
	CURLcode res;

	curl_global_init (CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init ();
	if (!curl)
	{
		fprintf (stderr, "Failed to initialize CURL\n");
		return 1;
	}

	curl_easy_setopt (curl, CURLOPT_URL, url);
	curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt (curl, CURLOPT_WRITEDATA, data);

	res = curl_easy_perform (curl);
	if (res != CURLE_OK)
	{
		fprintf (stderr, "CURL request failed: %s\n", curl_easy_strerror (res));
		curl_easy_cleanup (curl);
		return 1;
	}

	curl_easy_cleanup (curl);
	curl_global_cleanup ();
	return 0;
}

int load_real_time_data (const char* url)
{
	char data[10000] = "";  // Buffer for API response

	if (fetch_data_from_api (url, data))
	{
		return 1;
	}

	json_t*      root;
	json_error_t error;

	root = json_loads (data, 0, &error);
	if (!root)
	{
		fprintf (stderr, "JSON parsing error: %s\n", error.text);
		return 1;
	}

	// Example parsing JSON data (this will depend on the actual API response format)
	// You can modify it based on the structure returned by the API
	json_t* buses = json_object_get (root, "buses");
	if (!json_is_array (buses))
	{
		fprintf (stderr, "Error: buses data is not an array\n");
		return 1;
	}

	size_t  index;
	json_t* bus;
	json_array_foreach (buses, index, bus)
	{
		int         stopId    = json_integer_value (json_object_get (bus, "stop_id"));
		const char* name      = json_string_value (json_object_get (bus, "name"));
		double      latitude  = json_real_value (json_object_get (bus, "latitude"));
		double      longitude = json_real_value (json_object_get (bus, "longitude"));

		// You can now update your graph with this information
		Node* newNode   = (Node*) malloc (sizeof (Node));
		newNode->StopId = stopId;
		strcpy (newNode->Name, name);
		newNode->Latitude  = latitude;
		newNode->Longitude = longitude;
		newNode->Next      = NULL;

		map->List[stopId] = newNode;
	}

	json_decref (root);
	return 0;
}

int main ()
{
	map             = (Graph*) malloc (sizeof (Graph));
	map->Graph_Size = 10000;
	map->List       = (Node**) calloc (map->Graph_Size, sizeof (Node*));

	// Example URL for the Dublin Bus API endpoint
	const char* api_url = URL "bus_data_endpoint";  // Replace with the actual API URL

	if (load_real_time_data (api_url))
	{
		fprintf (stderr, "Failed to load real-time data\n");
		return 1;
	}

	// At this point, you should have populated the map with bus stop data
	// Now you can proceed to use Dijkstra's algorithm or any other logic

	return 0;
}
