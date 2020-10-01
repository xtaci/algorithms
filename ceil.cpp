#include<bits/stdc++.h>
#include<stdio.h>
#include<stdlib.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file 
#include <ext/pb_ds/tree_policy.hpp> 
#include <functional>
using namespace __gnu_pbds;
using namespace std;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> new_data_set; 
#define endl "\n"
#define FILEIO freopen("test1.txt", "r", stdin);freopen("output.txt", "w", stdout);
#define LL long long 
#define mod 1000000007LL
#define fast ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define pb push_back
#define pp pop_back
//#define p push
#define I insert
#define bg begin()
#define ed end()
#define sz size()
#define all(v) v.begin(),v.end()
#define ALL(v) v.rbegin(),v.rend()
typedef vector<LL> vi;
typedef pair<int,int> pii;
typedef vector<pii> vii;
typedef map<LL ,LL > mii;
typedef priority_queue<int> pq;
typedef queue<int>que;
typedef stack<int>stk;
#define Inf 100000005LL
#define f first
#define s second

vi vect;

LL find_ceil(int start , int end , int ele)
{                                                   
    LL res=__LONG_LONG_MAX__;

    while(start<=end)
    {
        int mid = start + (end-start)/2;

        if(vect[mid]==ele){
            return ele;
        }

        if(vect[mid]<ele)
             start = mid+1;
        else
        {
            res = vect[mid];
            end = mid-1;
        }
             
            
        
    }
    return res;
}

int main()
{
    int n , ele;
    cin>>n >>ele;

    vect.resize(n);

    for(int i=0;i<n;i++)
        cin>>vect[i];
    sort(all(vect));    

    cout<<find_ceil(0 , n-1 , ele)<<endl; 

}