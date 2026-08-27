#include<bits/stdc++.h>
using namespace std;

vector<int> getSneakyNumbersBrute(vector<int>& nums) {
    vector<int> ans;
    map<int, int> freq;
    for(auto it : nums) {
        freq[it]++;
    }
    for(auto it : freq) {
        if(it.second == 2) {
            ans.push_back(it.first);
        }
    }
    return ans;
}

vector<int> getSneakyNumbersOptimal(vector<int>& nums) {
    vector<int> imposters;
    sort(nums.begin(), nums.end());
    int i = 0, n = nums.size(), expected = 0;
    while(i < n) {
        if(expected != nums[i]) {
            imposters.push_back(nums[i]);
        } else {
            expected++;
        }
        i++;
    }
    return imposters;
}

vector<int> pivotArrayBrute(vector<int>& nums, int pivot) {
    vector<int> leftPart, rightPart, result;
    int pivotFreq = 0;
    int n = nums.size();
    for(int i = 0;i < n;i++) {
        if(nums[i] < pivot) {
            leftPart.push_back(nums[i]);
        } else if(nums[i] == pivot) {
            pivotFreq++;
        } else {
            rightPart.push_back(nums[i]);
        }
    }
    for(auto it : leftPart) {
        result.push_back(it);
    }
    for(int i = 0;i < pivotFreq;i++) {
        result.push_back(pivot);
    }
    for(auto it : rightPart) {
        result.push_back(it);
    }
    return result;
}

vector<int> pivotArrayOptimal(vector<int>& nums, int pivot) {
    
}

int main() {
    vector<int> nums = {9,12,5,10,14,3,10};
    int pivot = 10;
    vector<int> ans = pivotArrayOptimal(nums, pivot);
    for(auto it : ans) {
        cout << it << ' ';
    }
    return 0;
}