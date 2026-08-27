#include<bits/stdc++.h>
using namespace std;

int lengthOfLongestSubstring(string s) {
    int n = s.length();
    if(!n) return n;
    int l = 0, len = INT_MIN;
    unordered_set<char> uniqueCharacters;
    for(int r = 0; r < n; r++) {
        while(uniqueCharacters.find(s[r]) != uniqueCharacters.end()) {
            uniqueCharacters.erase(s[l]);
            l++;
        }
        uniqueCharacters.insert(s[r]);
        len = max(len, r - l + 1);
    }
    return len;
}

string minWindow(string s, string t) {
    unordered_map<char, int> need, window;
    for(char c : t) need[c]++;
    int have = 0, required = need.size();
    int left = 0, start = 0;
    int minLen = INT_MAX;
    for(int right = 0; right < s.length(); right++) {
        window[s[right]]++;
        if(need.count(s[right]) and window[s[right]] == need[s[right]]) {
            have++;
        }
        while(have == required) {
            if((right - left + 1) < minLen) {
                minLen = right - left + 1;
                start = left;
            }
            window[s[left]]--;
            if(need.count(s[left]) and window[s[left]] < need[s[left]]) {
                have--;
            }
            left++;
        }
    }
    return minLen == INT_MAX ? "" : s.substr(start, minLen);
}

bool isPalindrome(string s) {
    int l = 0, r = s.length() - 1;
    while(l < r) {
        if(s[l++] != s[r--]) {
            return false;
        }
    }
    return true;
}

vector<vector<int>> palindromePairsBrute(vector<string>& words) {
    int n = words.size();
    vector<vector<int>> res;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i != j and isPalindrome(words[i] + words[j])) {
                res.push_back({i, j});
            }
        }
    }
    return res;
}

vector<vector<int>> palindromePairs(vector<string>& words) {
    int n = words.size();
    vector<vector<int>> pairs;
    unordered_map<string, int> wordIndexMapping;
    for(int i = 0; i < n; i++) {
        wordIndexMapping[words[i]] = i;
    }
    for(int i = 0; i < n; i++) {
        string word = words[i];
        for(int j = 0; j <= word.length(); j++) {
            string left = word.substr(0, j);
            string right = word.substr(j);
            if(isPalindrome(right)) {
                string revLeft = left;
                reverse(revLeft.begin(), revLeft.end());
                if(wordIndexMapping.find(revLeft) != wordIndexMapping.end() and wordIndexMapping[revLeft] != i) {
                    pairs.push_back({i, wordIndexMapping[revLeft]});
                }
            }
            if(j > 0 and isPalindrome(left)) {
                string revRight = right;
                reverse(revRight.begin(), revRight.end());
                if(wordIndexMapping.find(revRight) != wordIndexMapping.end() and wordIndexMapping[revRight] != i) {
                    pairs.push_back({wordIndexMapping[revRight], i});
                }
            }
        }
    }
    return pairs;
}

void setZeroes(vector<vector<int>>& matrix) {
    int n = matrix.size(), m = matrix[0].size();
    bool firstRowZero = false, firstColZero = false;
    for(int j = 0; j < m; j++) {
        if(matrix[0][j] == 0) {
            firstRowZero = true;
            break;
        }
    }
    for(int i = 0; i < n; i++) {
        if(matrix[i][0] == 0) {
            firstColZero = true;
            break;
        }
    }
    for(int i = 1; i < n; i++) {
        for(int j = 1; j < m; j++) {
            if(matrix[i][j] == 0) {
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    }
    for(int i = 1; i < n; i++) {
        for(int j = 1; j < m; j++) {
            if(matrix[i][0] == 0 or matrix[0][j] == 0) {
                matrix[i][j] = 0;
            }
        }
    }
    if(firstRowZero) {
        for(int j = 0; j < m; j++) {
            matrix[0][j] = 0;
        }
    }
    if(firstColZero) {
        for(int i = 0; i < n; i++) {
            matrix[i][0] = 0;
        }
    }
}

int main() {
    vector<vector<int>> matrix = {
        {0,1,2,0}, 
        {3,4,5,2}, 
        {1,3,1,5}
    };
    setZeroes(matrix);
    for(auto x : matrix) {
        for(auto y : x) {
            cout << y << ' ';
        }
        cout << endl;
    }
    return 0;
}