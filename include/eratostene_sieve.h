//
// Created by Scarlat Marius on 9/10/20.
//

#ifndef ALGORITHM_ERATOSTENE_SIEVE_H
#define ALGORITHM_ERATOSTENE_SIEVE_H

#include <vector>
#include <stdexcept>

namespace alg {

    /*
     * A short implementation of Eratostene's Sieve
     */

    template < int SIZE >
    class EratosteneSieve {

    private:

        int n;
        vector < bool > prime;
        vector < int > primeCache; // cache all the prime numbers when the build method is called
        bool build_called; // if build() had been called

        EratosteneSieve() {
            this->n = SIZE;
            prime.resize(SIZE + 1, true);
            build_called = false;
        }

        void build() {
            this->build_called = true;
            primeCache.emplace_back(2);

            prime[0] = prime[1] = false; // false means not prime

            // k * 2 is not prime, where k > 1
            for(int i = 4;i * i <= n;i += 2)
                prime[i] = false;

            for(int i = 3;i * i <= n; i += 2) {
                if (prime[i]) { // all the multiples of a prime number are not prime
                    primeCache.emplace_back(i);

                    for(int j = i + i;j <= n;j += i)
                        prime[j] = false;
                }
            }
        }

        bool isPrime(const unsigned int& nr) {
            if(nr > SIZE)
                throw std::out_of_range("Index out of range");

            if(!build_called)
                throw "You need to call build() first";

            return prime[nr];
        }

        vector < int > getPrimes() {
            return this->primeCache;
        }
    };

}

#endif //ALGORITHM_ERATOSTENE_SIEVE_H
