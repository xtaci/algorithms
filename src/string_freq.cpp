#include <bits/stdc++.h>
using namespace std;

void printFrequency(string str)
{
    // Define an unordered_map
    unordered_map<char, int> M;
    /* YOU CAN WRITE MAP ABOVE INSTEAD OF unordered_map TO GET SORTED RESULT*/

    // Traverse string str check if
    // current character is present
    // or not
    for (int i = 0; str[i]; i++) {

        // If the current characters
        // is not found then insert
        // current characters with
        // frequency 1
        if (M.find(str[i]) == M.end()) {
            M.insert(make_pair(str[i], 1));
        }

        // Else update the frequency
        else {
            M[str[i]]++;
        }
    }

    // Traverse the map to print the
    // frequency
    for (auto& it : M) {
        cout << it.first << ' '
             << it.second << '\n';
    }
}

// Driver Code
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif

    string str ;
    cin >> str;

    // Function call
    printFrequency(str);
    return 0;
}