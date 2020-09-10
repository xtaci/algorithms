//
// Created by Scarlat Marius on 9/10/20.
//

#include <iostream>
#include <vector>

#include "eratostene_sieve.h"

using namespace std;
using namespace alg;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(false); cout.tie(false);

    EratosteneSieve < 100 > sieve;
    sieve.build();

    vector < int > prime = sieve.getPrimes();

    cout << "PRIME NUMBERS UP TO 100\n";

    for(auto it : prime)
        cout << it << ' ';

    int x;
    cin >> x;

    bool isPrime = sieve.isPrime(x);

    if(isPrime)
        cout << x << " is prime\n";
    else
        cout << x << " is not prime\n";

    return 0;
}
