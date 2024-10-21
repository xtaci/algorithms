#include <bits/stdc++.h>
using namespace std;


void simpleSieve(int limit, vector<int> &prime)
{
    bool mark[limit+1];
    memset(mark, true, sizeof(mark));
 
    for (int p=2; p*p<limit; p++)
    {
        // If p is not changed, then it is a prime
        if (mark[p] == true)
        {
            // Update all multiples of p
            for (int i=p*2; i<limit; i+=p)
                mark[i] = false;
        }
    }
 
    // Print all prime numbers and store them in prime
    for (int p=2; p<limit; p++)
    {
        if (mark[p] == true)
        {
            prime.push_back(p);
            cout << p << "  ";
        }
    }
}


void segmentedSieve(int n)
{
    int limit = floor(sqrt(n))+1;
    vector<int> prime;  
    simpleSieve(limit, prime); 
 
    int low  = limit;
    int high = 2*limit;
 
    while (low < n)
    {
        bool mark[limit+1];
        memset(mark, true, sizeof(mark));
 
        for (int i = 0; i < prime.size(); i++)
        {
            int loLim = floor(low/prime[i]) * prime[i];
            if (loLim < low)
                loLim += prime[i];
 
            for (int j=loLim; j<high; j+=prime[i])
                mark[j-low] = false;
        }
 
        // Numbers which are not marked as false are prime
        for (int i = low; i<high; i++)
            if (mark[i - low] == true)
                cout << i << "  ";
 
        // Update low and high for next segment
        low  = low + limit;
        high = high + limit;
        if (high >= n) high = n;
    }
}
 
// Driver program to test above function
int main()
{
    int n = 100;
    cout << "Primes smaller than " << n << ":n";
    segmentedSieve(n);
    return 0;
}
