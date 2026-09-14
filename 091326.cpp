#include<bits/stdc++.h>
using namespace std;

vector<int> findNumOfValidWordsBrute(vector<string>& words, vector<string>& puzzles) {
    int m = words.size(), n = puzzles.size();

    vector<int> numValidWords(n);

    for(int i = 0; i < n; i++) {
        int puzzleMask = 0;

        for(auto ch : puzzles[i]) {
            puzzleMask |= (1 << (ch - 'a'));
        }

        for(auto word : words) {
            int wordMask = 0;

            for(auto ch : word) {
                wordMask |= (1 << (ch - 'a'));
            }

            numValidWords[i] += (wordMask & (1 << (puzzles[i][0] - 'a'))) and ((wordMask & puzzleMask) == wordMask);
        }
    }

    return numValidWords;
}

vector<int> findNumOfValidWordsOptimal(vector<string>& words, vector<string>& puzzles) {
    int m = words.size(), n = puzzles.size();

    vector<int> numValidWords(n);

    unordered_map<int, int> maskFrequencyMapping;

    for(auto word : words) {
        int bitMask = 0;
        for(auto ch : word) {
            bitMask |= 1 << (ch - 'a');
        }
        maskFrequencyMapping[bitMask]++;
    }

    for(int i = 0; i < n; i++) {
        for(int mask = 0; mask < (1 << 7); mask++) {
            int subset = 0;
            for(int j = 0; j < 7; j++) {
                if((mask & 1) and (mask & (1 << j))) {
                    subset |= (1 << (puzzles[i][j] - 'a'));
                }
            }
            numValidWords[i] += maskFrequencyMapping[subset];
        }
    }

    return numValidWords;
}

vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
    
}

int main() {
    vector<string> products = {"mobile","mouse","moneypot","monitor","mousepad"};
    string searchWord = "mouse";

    for(auto x : suggestedProducts(products, searchWord)) {
        for(auto y : x) {
            cout << y << ' ';
        }
        cout << endl;
    }
    return 0;
}