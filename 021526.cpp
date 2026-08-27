#include<bits/stdc++.h>
using namespace std;

int triangleNumber(vector<int>& nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    int count = 0;
    for(int k = n - 1; k >= 2; k--) {
        int i = 0, j = k - 1;
        while(i < j) {
            if(nums[i] + nums[j] <= nums[k]) {
                i++;
            } else {
                count += (j - i);
                j--;
            }
        }
    }
    return count;
}

int maxLen(vector<int>& nums) {
    int n = nums.size();
    int prefixSum = 0, maxi = INT_MIN;
    unordered_map<int, int> prefixSumFirstSeenMap;
    prefixSumFirstSeenMap[0] = -1;
    for(int i = 0; i < n; i++) {
        prefixSum += nums[i];
        if(prefixSumFirstSeenMap.find(prefixSum) != prefixSumFirstSeenMap.end()) {
            maxi = max(maxi, i - prefixSumFirstSeenMap[prefixSum]);
        } else {
            prefixSumFirstSeenMap[prefixSum] = i;
        }
    }
    return maxi;
}

int longestConsecutive(vector<int>& nums) {
    int n = nums.size();
    if(!n) return n;
    unordered_set<int> hash(nums.begin(), nums.end());
    int maxLen = INT_MIN;
    for(auto ele : hash) {
        if(hash.find(ele - 1) == hash.end()) {
            int len = 1;
            int start = ele;
            while(hash.find(start + 1) != hash.end()) {
                len++;
                start++;
            }
            maxLen = max(maxLen, len);
        }
    }
    return maxLen;
}

int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> prefixSumFreqMap;
    prefixSumFreqMap[0] = 1;
    int prefixSum = 0, count = 0;
    for(auto it : nums) {
        prefixSum += it;
        count += prefixSumFreqMap[prefixSum - k];
        prefixSumFreqMap[prefixSum]++;
    }
    return count;
}

bool isAnagram(string s, string t) {
    if(s.length() != t.length()) {
        return false;
    }
    unordered_map<char, int> characterFreqMapping;
    for(char ch : s) {
        characterFreqMapping[ch]++;
    }
    for(char ch : t) {
        if(characterFreqMapping.find(ch) != characterFreqMapping.end()) {
            characterFreqMapping[ch]--;
            if(!characterFreqMapping[ch]) {
                characterFreqMapping.erase(ch);
            }
        } else {
            return false;
        }
    }
    return true;
}

bool checkRows(vector<vector<char>>& board) {
    for(int row = 0; row < 9; row++) {
        unordered_set<char> entries;
        for(int col = 0; col < 9; col++) {
            if(board[row][col] != '.') {
                if(entries.find(board[row][col]) != entries.end()) {
                    return false;
                }
                entries.insert(board[row][col]);
            }
        }
    }
    return true;
}

bool checkCols(vector<vector<char>>& board) {
    for(int col = 0; col < 9; col++) {
        unordered_set<char> entries;
        for(int row = 0; row < 9; row++) {
            if(board[row][col] != '.') {
                if(entries.find(board[row][col]) != entries.end()) {
                    return false;
                }
                entries.insert(board[row][col]);
            }
        }
    }
    return true;
}

bool checkSquares(vector<vector<char>>& board) {
    for(int row = 0; row < 9; row += 3) {
        for(int col = 0; col < 9; col += 3) {
            unordered_set<char> entries;
            for(int i = 0; i < 9; i++) {
                if(board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] != '.') {
                    if(entries.find(board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3]) != entries.end()) {
                        return false;
                    }
                    entries.insert(board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3]);
                }
            }
        }
    }
    return true;
} 

bool isValidSudoku(vector<vector<char>>& board) {
    return checkRows(board) and checkCols(board) and checkSquares(board);
}

int main() {
    
    return 0;
}