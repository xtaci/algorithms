#include <bits/stdc++.h>
using namespace std;

vector<int>graph[1003]; // first n elements (0 to n-1) are set a therefter are set b
int n,m; // n is the left set and m is the right set size.

bool check(int i,bool *seen,int *match)
{
    for(int j=0;j<graph[i].size();j++){
        if(!seen[graph[i][j]]){
            seen[graph[i][j]]=true;
            if(match[graph[i][j]]<0||check(match[graph[i][j]],seen,match)){
                match[graph[i][j]]=i;
                return true;
            }
        }
    }
    return false;
}

int bpm()
{
    int match[5+n+m];
    memset(match,-1,sizeof(match));
    int ans=0;
    for(int i=0;i<n;i++){
        bool seen[n+m+5];
        memset(seen,false,sizeof(seen));
        if(check(i,seen,match))
        ans++;
    }
    return ans;
}

int main()
{
    //freopen("in.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    int t;
    cin>>t;
    int cas=1;
    while (t--){
        for (int i=0;i<1003;i++)
            graph[i].clear();
        cin>>n;
        int a[n];
        for (int i=0;i<n;i++) {
            cin>>a[i];
        }
        cin>>m;
        int b[m];
        for (int i=0;i<m;i++){
            cin>>b[i];
            // according to some function push it in graph
            for (int j=0;j<n;j++)
                graph[j].push_back(n+i);
        }
        cout<<"Case "<<cas++<<": "<<bpm()<<endl;
    }
    return 0;
}

