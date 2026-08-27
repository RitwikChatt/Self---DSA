#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> combinations;

void combinationSumUtil(int sum, int lastUsed, vector<int>& ds,vector<int>& candidates, int target) {
    if(sum == target) {
        combinations.push_back(ds);
        return;
    }
    if(sum > target) {
        return;
    }
    for(int i = lastUsed; i < candidates.size(); i++) {
        ds.push_back(candidates[i]);
        combinationSumUtil(sum + candidates[i], i, ds, candidates, target);
        ds.pop_back();
    }
}

int hIndex(vector<int>& citations) {
    int n = citations.size();
    int low = 0, high = n - 1;
    int ans;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(n - mid >= citations[mid]) {
            low = mid + 1;
            ans = citations[mid];
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<int> ds;
    combinationSumUtil(0, 0, ds, candidates, target);
    return combinations;
}

int main() {
    vector<int> citations = {3,0,6,1,5};
    sort(citations.begin(), citations.end());
    cout << hIndex(citations) << endl;
    return 0;
}