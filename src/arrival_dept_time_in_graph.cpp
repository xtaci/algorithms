#include<bits/stdc++.h>
using namespace std;

struct edge{
    int src,dest;
};

class Graph {
    public:
        vector<vector<int>> adjList;
    //constructor
    Graph(vector<edge> const &edges, int N){
        adjList.resize(N);
        for(auto &edge : edges){
            adjList[edge.src].push_back(edge.dest);
        }
    }
};

void dfs(Graph const &graph, int v, vector<int> arrival, vector<int> dept, vector<bool> &discovered, int &time)
{
    arrival[v] = time++;
    discovered[v] = true;
    for(auto u : graph.adjList[v]) {
        if(!discovered[u]){
            dfs(graph,u,arrival,dept,discovered,time);
        }
    }
    dept[v] = time++;
}



