/*
    Longest Common Subsequence Algorithm
    ------------------------------------
    Given two strings, find their longest common subsequence. Note
    that this differs from the longest common subsequence algorithm:
    unlike substrings, subsequences are not required to occupy
    consecutive positions within the original sequences. This is a
    classic dynamic programming algorithm for string processing.

    Time complexity
    ----------------
    O(M*N), where M and N are the lengths of the two strings.

    Space complexity
    ----------------
    O(M*N), where M and N are the lengths of the two strings.
*/

#ifndef LONGEST_COMMON_SUBSEQUENCE_HPP
#define LONGEST_COMMON_SUBSEQUENCE_HPP

#include <algorithm>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::max;

vector<vector<int>> calc_lcs(const string& s1, const string& s2) {
    // M+1 by N+1 lengths matrix
    vector<vector<int>> lengths(s1.length()+1, vector<int>(s2.length()+1, 0));

    for (size_t i = 1; i < s1.length() + 1; i++) {
        for (size_t j = 1; j < s2.length() + 1; j++) {
            // When the characters match, add 1
            if (s1[i - 1] == s2[j - 1]) {
                lengths[i][j] = lengths[i - 1][j - 1] + 1;
            }
            // Pick the maximum neighbor
            else {
                lengths[i][j] = max(lengths[i - 1][j], lengths[i][j - 1]);
            }
        }
    }

    return lengths;
}

string get_lcs(const string& s1, const string& s2) {
    vector<vector<int>> lengths = calc_lcs(s1, s2);

    size_t i = lengths.size() - 1;
    size_t j = lengths[0].size() - 1;

    string lcs;
    while (i != 0 and j != 0) {
        if (s1[i - 1] == s2[j - 1]) {   // if there's a match
            lcs += s1[i - 1];       // save the character
            i--, j--;
        } else if (lengths[i - 1][j] > lengths[i][j - 1]) {
            i--;    // move to the left
        } else {
            j--;    // move to the right
        }
    }

    return string(lcs.rbegin(), lcs.rend());    // return the reversed string
}

#endif // LONGEST_COMMON_SUBSEQUENCE_HPP
