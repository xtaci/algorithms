//for no cycle
#include<bits/stdc++.h>
using namespace std;
int main()
{
    stack <int> gq;
   int v;
    cout<<"Enter the vertex : ";
    cin>>v;
    vector <int> vi[10];
    for(int i=1;i<=v;i++)
    {
        int k;
        cout<<"Enter -1  if no adjacent element is there\n";
        cout<<"enter the element adjacent to "<<i<<" :: ";
        do
        {
        cin>>k;
        if(k!=-1)
        {
        vi[i].push_back(k);
        }
        
        }while(k!=-1);
    }
    for(int i=1;i<=v;i++)
    {
             cout<< i<<" -> ";
        for(auto j=vi[i].begin();j!=vi[i].end();j++)
        {
            cout<<*j<<" ";
        }
        cout<<endl;
    }
    //cout<<1<<" ";

     vector <int> vect;
     vect.push_back(1);
     int p=1,y=1;
    while(y<=v)
    {
        y++;
        
        for(auto j=vi[p].begin();j!=vi[p].end();j++)
        {
            gq.push(*j);
        }
       // cout<<gq.front()<<" ";
        //auto find(vect.begin(),vect.end(),*j)!=vect.end();
        if(find(vect.begin(),vect.end(),gq.top())==vect.end())
            { vect.push_back(gq.top());
            }
        p=gq.top();
        gq.pop();
        
        
    }
    cout<<endl;
    cout<<"Dfs traversal started from verex 1 of the graph\n";
    cout<<"Dfs of the given graph is :: ";
    for(auto j=vect.begin();j!=vect.end();j++)
    {
        cout<<*j<<" ";
    }
    cout<<endl;

}

