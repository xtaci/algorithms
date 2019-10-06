#include<bits/stdc++.h>
#include<iostream>
#define mod 1000000007
typedef long long int lli;
lli fib(lli n,lli memo[])
{
        lli res;
        if(memo[n]!=0)
                return memo[n];
        if(n==1 ||  n==2)
                res = 1;
        else
                res = fib(n-1,memo) + fib(n-2,memo);
        memo[n]=res;
        return res;
}
using namespace std;
int main()
{
        lli memo[100000]={0},n,p;
        cout<<"Enter the value of n :\n";
        cin>>n;
        p = fib(n,memo);
        cout<<p<<endl;
        return 0;
}

