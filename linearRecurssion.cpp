//Template for solving Linear Recurence Relations in LogN time by using fast exponentiation
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned long long int ulli;
#define flash ios_base::sync_with_stdio(false); cin.tie(NULL);
#define mat(x, y, name) vector< vector<ll> > name (x, vector<ll>(y));
#define printMat(name) for (int i = 0; i < name.size(); i++) {for (int j = 0; j < res[i].size(); j++) cout << res[i][j] << " "; cout << endl;}

#define MOD 98765431

vector< vector<ll> > matMul(vector< vector<ll> > A, vector< vector<ll> > B)
{
    vector< vector<ll> > C(A.size(), vector<ll>(B[0].size()));
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < B[0].size(); j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < B.size(); k++)
                C[i][j] = (C[i][j] + ((A[i][k] * B[k][j]) % MOD)) % MOD;
        }
    }
    return C;
}

vector< vector<ll> > matPow(vector< vector<ll> > A, int p)
{
    if (p == 1)
        return A;
    if (p&1)
        return matMul(A, matPow(A, p-1));
    else
    {
        vector< vector<ll> > C = matPow(A, p/2);
        return matMul(C, C);
    }
}

int main()
{
    flash;

    return 0;
}
