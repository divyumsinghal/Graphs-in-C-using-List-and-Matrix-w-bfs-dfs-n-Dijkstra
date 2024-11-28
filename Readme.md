# Assignment 4: Searching with Graphs

## Objective
This assignment focuses on implementing and understanding graph representations, traversals, and algorithms, specifically Breadth-First Search (BFS), Depth-First Search (DFS), and Dijkstra's algorithm. 

---

## Task 1: BFS and DFS

In this task, adjacency lists are used to represent a directed graph. The following functions were implemented in `t1.c`:

1. **Graph Creation**:
   - `Graph* create_graph(int num_nodes);` initializes a graph with `num_nodes` stored in alphabetical order.
   
2. **Edge Addition**:
   - `void add_edge(Graph *g, int from, int to);` adds a directed edge between nodes.

3. **Breadth-First Search (BFS)**:
   - `void bfs(Graph* g, int origin);` traverses the graph level by level starting from the `origin` node. Nodes are visited in alphabetical order when multiple options are available.

4. **Depth-First Search (DFS)**:
   - `void dfs(Graph* g, int origin);` traverses the graph by exploring as deeply as possible before backtracking. Nodes are visited in alphabetical order when multiple options are available.

5. **Graph Deletion**:
   - `void delete_graph(Graph* g);` ensures all allocated memory is freed, preventing memory leaks.


#### **Design Choices**

1. **Graph Representation:**
   - Here, I use an adjacency list to represent the graph because which is memory-efficient, especially for sparse graphs. 
   - The graph is implemented as an array of pointers (`int** List`), where each pointer points to a dynamically allocated array containing the neighbors of a node.

2. **Node Management:**
   - Nodes are stored in alphabetical order (A, B, C, ...):
       - The slot `0` is node `A`, `1` is `B` and so on.
   - The `List_size` array tracks the number of neighbors for each node.

3. **Algorithm Design:**
   - **BFS:** I used a queue to ensure breadth-first traversal, visiting all neighbors of a node before moving deeper into the graph.
   - **DFS:** A stack was used for depth-first traversal, which ensures nodes are visited as deeply as possible before backtracking.

### Output:
```
Creating Graph

DFS:
A
B
C
D
F
E

BFS:
A
B
D
E
C
F

Dijkstra's Algorithm:
Permanent: A, Distance: 0
Permanent: B, Distance: 1
Permanent: D, Distance: 1
Permanent: E, Distance: 1
Permanent: C, Distance: 2
Permanent: F, Distance: 2

Shortest distances from A:
To A: 0
To B: 1
To C: 2
To D: 1
To E: 1
To F: 2
```

---

## Task 2: Dijkstra's Algorithm

Adjacency matrices were used to represent the weighted graph in this task. The following functions were implemented in `t2.c`:

1. **Graph Creation**:
   - `Graph* create_graph(int num_nodes);` initializes a graph with `num_nodes` stored in alphabetical order.

2. **Edge Addition**:
   - `void add_edge(Graph *g, int from, int to, int weight);` adds a weighted edge between nodes.

3. **Dijkstra's Algorithm**:
   - `void dijkstra(Graph* g, int origin);` finds the shortest paths from the `origin` to all other nodes. Nodes are processed in alphabetical order if multiple options are available.

4. **Graph Deletion**:
   - `void delete_graph(Graph* g);` ensures all allocated memory is freed.

#### **Design Choices**

1. **Graph Representation:**
   - here, I usean adjacency matrix for this task since Dijkstra's algorithm frequently queries edge weights between nodes. The matrix representation enables O(1) edge weight lookups. 

2. **Weighted Graph Implementation:**
   - The `Matrix` is initialized to store edge weights, with a default value (e.g., `INT_MAX`) to represent non-existent edges.
   - The graph is undirected, so each edge is symmetric: `Matrix[from][to] = Matrix[to][from]`.

3. **Algorithm Design:**
   - I implemented Dijkstra’s algorithm using a simple iterative approach, maintaining a `dist[]` array for shortest path estimates and a `visited[]` array to track permanent nodes.


### Output:
```
Creating Graph

DFS:
A
B
C
D
E
F
G

BFS:
A
B
C
F
D
E
G

Printing Dijkstra:
A  B  C  G  E  D  F
Distance for node A is 0, through A
Distance for node B is 1, through A
Distance for node C is 2, through B
Distance for node D is 7, through E
Distance for node E is 5, through C
Distance for node F is 7, through E
Distance for node G is 3, through B
```

---

## Task 3: On the Buses

This task involves modeling Dublin's public transport system using real-world data. The graph can be represented using both adjacency matrices and adjacency lists, but for this sparse graph, adjacency lists are more efficient. 

### Implementations:

1. **Graph Representations**:
   - Both adjacency list and adjacency matrix representations were implemented to compare their advantages. 
     - **Adjacency Matrix**:
       - Easier to implement and provides constant-time edge lookups.
       - Consumes more memory, especially for sparse graphs.
     - **Adjacency List**:
       - Space-efficient for sparse graphs.
       - Slower for edge lookups, but overall ideal for this use case due to the graph's sparsity.

2. **Data Loading**:
   - `int load_vertices(char *fname);` reads nodes (bus stops) from a CSV file.
   - `int load_edges(char *fname);` reads edges (routes and distances) from a CSV file.

3. **Shortest Path**:
   - `void shortest_path(int startNode, int endNode);` uses Dijkstra's algorithm to calculate and print the shortest path from the `startNode` to the `endNode`.

4. **Memory Management**:
   - `void free_memory(void);` ensures all allocated memory is freed.

   
### Design Choices:

- For this assignment, I believe that the list based implementaion is more efficient as the memory overhead is significantly lesser as it is avery sparse graph.


### Output:
```
vertices.csv loaded!
Loaded 4807 vertices
edges.csv loaded!
Loaded 6180 edges
Please enter stating bus stop >         300
Please enter destination bus stop >     253

Calculating Dijkstra's shortest path:

Shortest path to node 253 has a distance of 7242.
Path:
  300,             Eden Quay,    53.34826889,     -6.255763056
  497,         Amiens Street,    53.35050306,     -6.250701111
  515,         Amiens Street,    53.35350389,     -6.248088889
  516,       North Strand Rd,      53.35568,     -6.245661944
 4384,       North Strand Rd,    53.35767111,     -6.242686111
  519,       North Strand Rd,    53.36030194,     -6.239553056
  521,       Annesley Bridge,     53.361625,     -6.237988889
  522,           Marino Mart,    53.36327194,     -6.235341111
  523,           Marino Mart,    53.36428111,     -6.231608056
  669,         Malahide Road,    53.36631111,     -6.228656944
  670,         Malahide Road,      53.36895,     -6.226008889
  671,         Malahide Road,    53.37071889,     -6.224138056
  672,         Malahide Road,     53.373465,     -6.221061111
 4382,         Malahide Road,       53.3749,        -6.2196
 1185,           Collins Ave,    53.37637111,     -6.221506111
 1186,           Collins Ave,    53.37764194,     -6.226321944
 1187,           Collins Ave,    53.37860611,       -6.23134
 1188,           Collins Ave,    53.38001389,     -6.235576944
 1189,           Collins Ave,    53.38072194,     -6.237976944
  216,         Beaumont Road,    53.38232889,     -6.238176111
  217,         Beaumont Road,    53.38432389,       -6.23678
  242,         Beaumont Road,      53.38565,     -6.231991944
  243,         Beaumont Road,    53.38577889,      -6.229525
  253,     Beaumont Hospital,    53.38994194,     -6.224378889


```
