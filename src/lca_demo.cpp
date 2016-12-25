#include <cstdio>
#include <vector>

const int MAX_NODE = 5000;
const int MAX_LOG = 20;

int numberOfNodes, maxLog;
std::vector< std::vector<int> > adjList;
int parent[MAX_NODE], nodeHeight[MAX_NODE];
bool visited[MAX_NODE];
int binaryLiftDp[MAX_NODE][MAX_LOG];

void dfs(int currentNode, int currentParent)
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

int getMaxLog(){
    int curValue = 1;
    int curLog = 1;
    while(curValue < numberOfNodes) curValue *= 2, curLog++;
    return curLog;
}

void initializeDP()
{
    nodeHeight[-1] = -1;
    maxLog = getMaxLog();
    dfs(0, -1);
    for(int i = 0; i < numberOfNodes; i++) binaryLiftDp[i][0] = parent[i];
    for(int i = 1; i <= maxLog; i++)
    {
        for(int j = 0; j < numberOfNodes; j++)
        {
            if(binaryLiftDp[j][i - 1] + 1)
                binaryLiftDp[j][i] = binaryLiftDp[binaryLiftDp[j][i - 1]][i - 1];
            else binaryLiftDp[j][i] = -1;
        }
    }
}

int LCA(int a, int b)
{
    if(nodeHeight[a] < nodeHeight[b]) std::swap(a,b);
    for(int i = maxLog; i >= 0; i--)
    {
        if(binaryLiftDp[a][i] + 1 && nodeHeight[binaryLiftDp[a][i]] >= nodeHeight[b])
            a = binaryLiftDp[a][i];
    }
    if(!(a - b)) return a;
    for(int i = maxLog; i >= 0; i--)
    {
        if(binaryLiftDp[a][i] + 1 && binaryLiftDp[a][i] - binaryLiftDp[b][i])
            a = binaryLiftDp[a][i], b = binaryLiftDp[b][i];
    }
    return parent[a];
}

void buildTree()
{
    printf("Enter number of nodes of the tree: ");
    scanf("%d", &numberOfNodes);
    adjList.resize(numberOfNodes, std::vector<int> ());
    for(int i = 0; i < numberOfNodes - 1; i++)
    {
        int firstNode, secondNode;
        printf("Enter the two nodes to be connected: ");
        scanf("%d %d", &firstNode, &secondNode);
        adjList[firstNode].push_back(secondNode);
        adjList[secondNode].push_back(firstNode);
    }
}

void answerQueries()
{
    int queryCount;
    printf("Enter the number of queries: ");
    scanf("%d", &queryCount);
    for(int i = 0; i < queryCount; i++)
    {
        int firstNode, secondNode;
        printf("Enter the two nodes : ");
        scanf("%d %d", &firstNode, &secondNode);
        printf("%d\n", LCA(firstNode, secondNode));
    }
}

int main()
{
    buildTree();
    initializeDP();
    answerQueries();
}
