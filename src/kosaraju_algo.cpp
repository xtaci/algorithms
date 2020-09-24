// C++ Implementation of Kosaraju's algorithm to print all SCCs 
/*
A directed graph is strongly connected if there is a path between all pairs of vertices. A strongly connected component (SCC) of a directed graph is a maximal strongly connected subgraph. For example, there are 3 SCCs in the following graph.
SCC
We can find all strongly connected components in O(V+E) time using Kosaraju’s algorithm. Following is detailed Kosaraju’s algorithm.
1) Create an empty stack ‘S’ and do DFS traversal of a graph. In DFS traversal, after calling recursive DFS for adjacent vertices of a vertex, push the vertex to stack. In the above graph, if we start DFS from vertex 0, we get vertices in stack as 1, 2, 4, 3, 0.
2) Reverse directions of all arcs to obtain the transpose graph.
3) One by one pop a vertex from S while S is not empty. Let the popped vertex be ‘v’. Take v as source and do DFS (call DFSUtil(v)). The DFS starting from v prints strongly connected component of v. In the above example, we process vertices in order 0, 3, 4, 2, 1 (One by one popped from stack)
*/
#include <iostream> 
#include <list> 
#include <stack> 
using namespace std; 

class Graph 
{ 
	int V; // No. of vertices 
	list<int> *adj; // An array of adjacency lists 

	// Fills Stack with vertices (in increasing order of finishing 
	// times). The top element of stack has the maximum finishing 
	// time 
	void fillOrder(int v, bool visited[], stack<int> &Stack); 

	// A recursive function to print DFS starting from v 
	void DFSUtil(int v, bool visited[]); 
public: 
	Graph(int V); 
	void addEdge(int v, int w); 

	// The main function that finds and prints strongly connected 
	// components 
	void printSCCs(); 

	// Function that returns reverse (or transpose) of this graph 
	Graph getTranspose(); 
}; 

Graph::Graph(int V) 
{ 
	this->V = V; 
	adj = new list<int>[V]; 
} 

// A recursive function to print DFS starting from v 
void Graph::DFSUtil(int v, bool visited[]) 
{ 
	// Mark the current node as visited and print it 
	visited[v] = true; 
	cout << v << " "; 

	// Recur for all the vertices adjacent to this vertex 
	list<int>::iterator i; 
	for (i = adj[v].begin(); i != adj[v].end(); ++i) 
		if (!visited[*i]) 
			DFSUtil(*i, visited); 
} 

Graph Graph::getTranspose() 
{ 
	Graph g(V); 
	for (int v = 0; v < V; v++) 
	{ 
		// Recur for all the vertices adjacent to this vertex 
		list<int>::iterator i; 
		for(i = adj[v].begin(); i != adj[v].end(); ++i) 
		{ 
			g.adj[*i].push_back(v); 
		} 
	} 
	return g; 
} 

void Graph::addEdge(int v, int w) 
{ 
	adj[v].push_back(w); // Add w to v’s list. 
} 

void Graph::fillOrder(int v, bool visited[], stack<int> &Stack) 
{ 
	// Mark the current node as visited and print it 
	visited[v] = true; 

	// Recur for all the vertices adjacent to this vertex 
	list<int>::iterator i; 
	for(i = adj[v].begin(); i != adj[v].end(); ++i) 
		if(!visited[*i]) 
			fillOrder(*i, visited, Stack); 

	// All vertices reachable from v are processed by now, push v 
	Stack.push(v); 
} 

// The main function that finds and prints all strongly connected 
// components 
void Graph::printSCCs() 
{ 
	stack<int> Stack; 

	// Mark all the vertices as not visited (For first DFS) 
	bool *visited = new bool[V]; 
	for(int i = 0; i < V; i++) 
		visited[i] = false; 

	// Fill vertices in stack according to their finishing times 
	for(int i = 0; i < V; i++) 
		if(visited[i] == false) 
			fillOrder(i, visited, Stack); 

	// Create a reversed graph 
	Graph gr = getTranspose(); 

	// Mark all the vertices as not visited (For second DFS) 
	for(int i = 0; i < V; i++) 
		visited[i] = false; 

	// Now process all vertices in order defined by Stack 
	while (Stack.empty() == false) 
	{ 
		// Pop a vertex from stack 
		int v = Stack.top(); 
		Stack.pop(); 

		// Print Strongly connected component of the popped vertex 
		if (visited[v] == false) 
		{ 
			gr.DFSUtil(v, visited); 
			cout << endl; 
		} 
	} 
} 
int main() 
{ 
	// Create a graph given in the above diagram 
	Graph g(5); 
	g.addEdge(1, 0); 
	g.addEdge(0, 2); 
	g.addEdge(2, 1); 
	g.addEdge(0, 3); 
	g.addEdge(3, 4); 

	cout << "Following are strongly connected components in "
			"given graph \n"; 
	g.printSCCs(); 

	return 0; 
} 

