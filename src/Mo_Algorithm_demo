#include "bits/stdc++.h"
 
using namespace std;
#define Arena cin.sync_with_stdio(0);cin.tie(0);cout.tie(0);
 
typedef long double ld;
typedef long long ll;
ll mod = 1e9 + 7;
 
#define N 311111
#define A 1111111
#define BLOCK 555 //sqrt(N)
 
int cnt[A], a[N], ans[N], answer = 0;
 
struct Node{
    int L, R, i;
}q[N];
 
bool cmp(Node x, Node y){
    if(x.L/BLOCK != y.L/BLOCK){
        return x.L/BLOCK < y.L/BLOCK;
    }
    return x.R < y.R;
}
 
void add(int pos){
    cnt[a[pos]]++;
    if(cnt[a[pos]] == 1)
        answer++;
}
 
void remove(int pos){
    cnt[a[pos]]--;
    if(cnt[a[pos]] == 0)
        answer--;
}
 
 
int main() {
    Arena
    int n;
    cin>>n;
 
    for(int i = 0; i < n; i++)cin>>a[i];
 
    int m;
    cin>>m;
 
    for(int i = 0; i < m; i++){
        cin>>q[i].L>>q[i].R;
        q[i].L--; q[i].R--;
        q[i].i = i;
    }
 
    sort(q, q+m, cmp);
 
    int currL = 0, currR = 0;
    for(int i = 0; i < m; i++){
        int L = q[i].L, R = q[i].R;
        while(currL < L){
            remove(currL);
            currL++;
        }
        while(currL > L){
            add(currL-1);
            currL--;
        }
        while(currR <= R){
            add(currR);
            currR++;
        }
        while(currR > R+1){
            remove(currR-1);
            currR--;
        }
        ans[q[i].i] = answer;
    }
    for(int i = 0; i < m; i++){
        cout<<ans[i]<<"\n";
    }
 
  }
 
