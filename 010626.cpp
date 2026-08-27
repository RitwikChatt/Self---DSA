#include<bits/stdc++.h>
using namespace std;

void subsequences(int idx, vector<int>& ds, vector<int>& nums) {
    if(idx == nums.size()) {
        for(auto it : ds) {
            cout << it << ' ';
        }
        cout << endl;
        return;
    }
    ds.push_back(nums[idx]);
    subsequences(idx + 1, ds, nums);
    ds.pop_back();
    subsequences(idx + 1, ds, nums);
}

int main() {
    vector<int> nums = {1, 2, 2, 3};
    sort(nums.begin(), nums.end());
    vector<int> ds;
    subsequences(0, ds, nums);
    return 0;
}