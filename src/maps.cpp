#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include<bits/stdc++.h>

using namespace std;

void r()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}
int main() {
// #ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
// #endif

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    r();
    int n;
    cin >> n;
    unordered_map<string, int>m ;

    while (n > 0) {
        n = n - 1;
        int a[n], i = -1;
        i++;
        cin >> a[i];

        if (a[i] == 1)
        {
            string s;
            cin >> s;
            int v;
            cin >> v;
            if (m.find(s) == m.end())
            {
                m.insert(make_pair(s, v));
            }
            else
                m[s] = m[s] + v;
        }
        else if (a[i] == 2)
        {
            string s;
            cin >> s;

            m[s] = 0;
        }
        else if (a[i] == 3) {
            string s;
            cin >> s;
            cout << m[s] << endl;

        }

    }
    // for (auto& it : m) {
    //     cout << it.first << ' '
    //          << it.second << '\n';
    // }
    return 0;
}



