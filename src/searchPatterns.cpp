//
// Created by Sithum on 2021-01-01.
//

#include "clientClass.h"

#include <iostream>



class patternSearchNaive {

    char* pattern;
    char* text;
    // naive bias pattern search
public: void search(char* pattern, char* text) {
    int txt = strlen(text);
    int pat = strlen(pattern);

    for (int i = 0; i <= txt - pat; i++) {
        // for pattern matching 
        for (int j = 0; j < pat; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
            // if pattern matches 
            if (j = pat) {
                std::cout << "Pattern found" << i << std::endl;
            }
        }
    }

}

};

//for Knuth morris pratt algorithm
class patternSearchKMP {

    //occurance of text[],pattern[]
public:
    void search(char* pattern, char* text) {

        int txt = strlen(text);
        int pat = strlen(pattern);

        // to hold longest prefix suffix
        // value for pattern
        int lps[1];

        //preprocess the pattern(calculate lps[] array)
        LPS(pattern, pat, lps);

        int index = 0;
        int j_index = 0;

        while (index < txt) {
            if (pattern[j_index] == text[index]) {
                j_index++; // index for pattern
                index++; // index for text
            }

            if (j_index == pat) {
                std::cout << "Index found " << index - j_index << std::endl;
                j_index = lps[j_index - 1];
            }

            //mismatch after pattern match
            else if (index < pat && pattern[j_index] != text[index]) {
                if (j_index != 0) {
                    j_index = lps[j_index - 1];
                }
                else {

                    index = index++;
                }
            }
        }

    }

public: void LPS(char* pattern, int pat, int* lps) {

    int lenght = 0;

    lps[0] = 0;

    // the loop calculates lps[index] for index = 1 to pat-1 
    int index = 1;

    while (index < pat) {
        if (pattern[index] == pattern[lenght]) {

            lenght++;
            lps[index] = lenght;
            index++;
        }
        else {
            if (lenght != 0) {
                lenght = lps[lenght - 1];
            }
            else {
                lps[index] = 0;
                index++;

            }
        }
    }


}
};