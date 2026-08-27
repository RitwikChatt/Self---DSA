#include<bits/stdc++.h>
using namespace std;

int climbStairs(int n) {
    int curr, prev, prevprev;

    if(n == 1) {
        return 1;
    }

    prevprev = 1, prev = 1;

    for(int i = 2; i <= n; i++) {
        curr = prev + prevprev;
        prevprev = prev, prev = curr;
    }

    return curr;
}

int minCostClimbingStairs(vector<int>& cost) {
    int n = cost.size();

    int curr, prevprev = 0, prev = 0;

    for(int i = 2; i <= n; i++) {
        curr = min(prev + cost[i - 1], prevprev + cost[i - 2]);
        prevprev = prev, prev = curr;
    }

    return curr;
}

int minCost(vector<int>& height) {
    int n = height.size();

    int curr, prevprev = 0, prev = abs(height[0] - height[1]);

    for(int i = 2; i < n; i++) {
        curr = min(prev + abs(height[i - 1] - height[i]), prevprev + abs(height[i - 2] - height[i]));
        prevprev = prev, prev = curr;
    }

    return curr;
}

int robHelper(const vector<int>& nums) {
    int n = nums.size();

    if(n == 1) {
        return nums[0];
    }

    int curr, prevprev = nums[0], prev = max(nums[0], nums[1]);

    if(n == 2) {
        return prev;
    }

    for(int i = 2; i < n; i++) {
        curr = max(nums[i] + prevprev, prev);
        prevprev = prev, prev = curr;
    }

    return curr;
}

int rob(vector<int>& nums) {
    return max(robHelper(vector<int>(nums.begin(), nums.end() - 1)), 
        robHelper(vector<int>(nums.begin() + 1, nums.end())));
}

int main() {
    vector<int> nums = {1,2,3,1};
    
    cout << rob(nums) << endl;

    return 0;
}