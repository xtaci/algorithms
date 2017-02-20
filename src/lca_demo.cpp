#include "LCA.h"
#include <cstdio>
#include <vector>
#include <iostream>
/**
*Constructor is initialized with a Adjacency List that
*describe a tree and If It doesn't describe a tree it asserts failure.
*/

LCA::LCA(std::vector< std::pair<int,int> > edges): _numberOfNodes(edges.size() + 1), _maxLog(getMaxLog())
{
    //First we initialize the needed vectors
    parent.resize(_numberOfNodes);
    nodeHeight.resize(_numberOfNodes);
    visited.resize(_numberOfNodes);
    adjList.resize(_numberOfNodes);
    binaryLiftDp = std::vector< std::vector<int> >(_numberOfNodes, std::vector<int>(_maxLog));
    /**Construction of the Adjacency List to increase
    *The efficiency of the tree traversal to O(V + E).
    */
    for(auto edge : edges){
        adjList[edge.first].push_back(edge.second);
        adjList[edge.second].push_back(edge.first);
    }
    //Initialize the Dynamic programming Vector.
    initDP();
}

/**
*DFS is used to find the parent and the height of each node
*allowing the use of Binary Lifting.
*/
void LCA::dfs(int currentNode, int currentParent)
{
    visited[currentNode] = true;
    parent[currentNode] = currentParent;
    nodeHeight[currentNode] = nodeHeight[currentParent] + 1;
    int adjacencySize = adjList[currentNode].size();
    for(int idx = 0; idx < adjacencySize; idx++){
        int nextNode = adjList[currentNode][idx];
        if(!visited[nextNode])
        {
            dfs(nextNode, currentNode);
        }
    }
}

/**
*Used to Calculate the Log to the base of two
*for the number of the nodes to create the sparse table
*used in binary Lifting.
*/
int LCA::getMaxLog(){
    int curValue = 1;
    int curLog = 1;
    while(curValue < _numberOfNodes) curValue *= 2, curLog++;
    return curLog;
}

void LCA::initDP()
{
    dfs(0, -1);
    for(int i = 0; i < _numberOfNodes; i++) binaryLiftDp[i][0] = parent[i];
    for(int i = 1; i <= _maxLog; i++)
    {
        for(int j = 0; j < _numberOfNodes; j++)
        {
            /**
            * Since the ith parent of the current node is equal to
            * the ith / 2 parent to the ith /2 parent of the current node
            * That's why the Recurrence relation is described as follow
            */
            if(binaryLiftDp[j][i - 1] != -1)
                binaryLiftDp[j][i] = binaryLiftDp[binaryLiftDp[j][i - 1]][i - 1];
            else binaryLiftDp[j][i] = -1;
        }
    }
}

int LCA::lcaQuery(int a, int b)
{
    /**
    * First Both nodes must have same height
    * So we will rise the node with the deeper height up in
    * the tree to where they're equal.
    */
    if(nodeHeight[a] < nodeHeight[b]) std::swap(a,b);
    for(int i = _maxLog; i >= 0; i--)
    {
        if(binaryLiftDp[a][i] + 1 && nodeHeight[binaryLiftDp[a][i]] >= nodeHeight[b])
            a = binaryLiftDp[a][i];
    }
    /**
    * If the node Lower is the LCA then return it.
    * Else keep moving both nodes up as much as they aren't the same
    * until it's only 1 node left which is the direct parent of both of them
    */
    if(a == b) return a;
    for(int i = _maxLog; i >= 0; i--)
    {
        if(binaryLiftDp[a][i] + 1 && binaryLiftDp[a][i] - binaryLiftDp[b][i])
            a = binaryLiftDp[a][i], b = binaryLiftDp[b][i];
    }
    return parent[a];
}

int main(){
    std::vector< std::pair<int,int> > edges;
    edges.push_back({0,1});
    edges.push_back({1,2});
    edges.push_back({2,3});
    edges.push_back({1,4});
    LCA* l = new LCA(v);
    std::cout << l->lcaQuery(0,1) << endl;
    std::cout << l->lcaQuery(3,4) << endl;
    std::cout << l->lcaQuery(3,2) << endl;
}
