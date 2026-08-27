#include<bits/stdc++.h>
using namespace std;

vector<string> allCombinations;

map<char, string> numberToLettersMapping = {
    {'2',  "abc"},
    {'3', "def"},
    {'4', "ghi"},
    {'5', "jkl"},
    {'6', "mno"},
    {'7', "pqrs"}, 
    {'8', "tuv"}, 
    {'9', "wxyz"}
};

void letterCombinationsUtil(int idx, string& str, string& digits) {
    if(idx == digits.size()) {
        allCombinations.push_back(str);
        return;
    }

    for(auto it : numberToLettersMapping[digits[idx]]) {
        str += it;
        letterCombinationsUtil(idx + 1, str, digits);
        str.pop_back();
    }
}

vector<string> letterCombinations(string digits) {
    string str = "";
    letterCombinationsUtil(0, str, digits);
    return allCombinations;
}

vector<vector<int>> combinations;

void combinationSum3Util(int idx, int sum, int lastPicked, vector<int>& ds, int k, int n) {
    if(idx == k) {
        if(sum == n) {
            combinations.push_back(ds);
        }
        return;
    }
    
    if(sum > n) {
        return;
    }

    for(int num = lastPicked + 1; num <= 9; num++) {
        ds.push_back(num);
        combinationSum3Util(idx + 1, sum + num, num, ds, k, n);
        ds.pop_back();
    }
}

vector<vector<int>> combinationSum3(int k, int n) {
    vector<int> ds;
    combinationSum3Util(0, 0, 0, ds, k, n);
    return combinations;
}

int findTargetSumWaysUtil(int idx, int sum, vector<int>& nums, int target) {
    if(idx == nums.size()) {
        if(sum == target) {
            return 1;
        }
        return 0;
    }

    int plus = findTargetSumWaysUtil(idx + 1, sum + nums[idx], nums, target);
    int minus = findTargetSumWaysUtil(idx + 1, sum - nums[idx], nums, target);

    return plus + minus;
}

int findTargetSumWays(vector<int>& nums, int target) {
    return findTargetSumWaysUtil(0, 0, nums, target);
}

vector<string> letterCasePermutationsList;

void letterCasePermutationUtil(int idx, string str, string s) {
    if(idx == s.length()) {
        letterCasePermutationsList.push_back(str);
        return;
    }

    str += s[idx];
    letterCasePermutationUtil(idx + 1, str, s);
    str.pop_back();

    if(s[idx] >= 'a' and s[idx] <= 'z') {
        str += toupper(s[idx]);
        letterCasePermutationUtil(idx + 1, str, s);
        str.pop_back();
    }

}

vector<string> letterCasePermutation(string s) {
    for(auto& c : s) {
        c = tolower(c);
    }
    string str = "";
    letterCasePermutationUtil(0, str, s);
    return letterCasePermutationsList;
}

void solveSudoku(vector<string>& board) {
    
}

int main() {
    vector<string> board = {
        "53..7....", 
        "6..195...", 
        ".98....6.", 
        "8...6...3", 
        "4..8.3..1", 
        "7...2...6", 
        ".6....28.", 
        "...419..5", 
        "....8..79"
    };
    solveSudoku(board);
    return 0;
}