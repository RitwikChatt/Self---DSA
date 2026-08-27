#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> uniqueCombinations;

void combinationSum2Util(int idx, int sum, vector<int>& ds, int target, vector<int>& candidates) {
    if(sum > target) {
        return;
    }
    if(sum == target) {
        uniqueCombinations.push_back(ds);
        return;
    }
    for(int i = idx; i < candidates.size(); i++) {
        if(i > idx and candidates[i] == candidates[i - 1]) {
            continue;
        }
        ds.push_back(candidates[i]);
        combinationSum2Util(i + 1, sum + candidates[i], ds, target, candidates);
        ds.pop_back();
    }
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<int> ds;
    combinationSum2Util(0, 0, ds, target, candidates);
    return uniqueCombinations;
}

int main() {
    vector<int> candidates = {10,1,2,7,6,1,5};
    int target = 8;
    vector<vector<int>> res = combinationSum2(candidates, target);
    for(auto x : res) {
        for(auto y : x) {
            cout << y << ' ';
        }
        cout << endl;
    }
    return 0;
}