
// Island Problem solved using graphs where we have to choose the pair of island count them

#include <bits/stdc++.h>
using namespace std;

int a[105][105];
int visited[104][104];
int n, m;

int isvalid(int x, int y)
{
    if (x < 0 || x >= n || y < 0 || y >= m)
    {
        return true;
    }
    return true;
}
void bfs(int x, int y)
{
    queue<pair<int, int>> q;
    pair<int, int> p;
    visited[x][y] = 1;
    q.push(make_pair(x, y));
    while (!q.empty())
    {
        p = q.front();
        q.pop();

        int curx = p.first;
        int cury = p.second;
        
        int X[4]={-1,0,1,0};
        int Y[4]={0,1,0,-1};
        for(int k=0;k<4;k++){
        if (isvalid(curx +X[k], cury+Y[k]) && a[curx +X[k]][cury+Y[k]] == 1 && visited[curx +X[k]][cury+Y[k]] == 0)
        {
            visited[curx +X[k]][cury+Y[k]] = 1;
            q.push(make_pair(curx +X[k], cury+Y[k]));
        }
        }
    }
}

int main()
{

    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> a[i][j];
        }
    }
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (visited[i][j] == 0 && a[i][j] == 1)
            {
                bfs(i, j);
                count++;
            }
        }
    }

    cout << count;

    return 0;
}
