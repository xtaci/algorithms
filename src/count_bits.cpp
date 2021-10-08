#include <bits/stdc++.h>
#define mod 1000000007
#define ll long long
using namespace std;

int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N;
    cin>>N;
    int oneCount=0,zeroCount=0;
    while(N){
        if(N%2==1)
            oneCount++;
        else
            zeroCount++;
        N/=2;
    }
    cout<<"Count of number of set BITS: "<<oneCount<<endl;
    cout<<"Count of number of unset BITS: "<<zeroCount<<endl;

}
