#include<bits/stdc++.h>
using namespace std;

bool canPartitionKSubsets(vector<int>& nums, int k) {
    int totalSum = accumulate(nums.begin(), nums.end(), 0);

    if(totalSum % k) return false;

    int n = nums.size(), target = totalSum / k;

    sort(nums.begin(), nums.end());

    if(nums[n - 1] > target) return false;

    vector<bool> dp(1 << n);

    dp[0] = true;

    vector<int> sum(1 << n);

    for(int mask = 0; mask < (1 << n); mask++) {
        if(!dp[mask]) continue;

        for(int i = 0; i < n; i++) {
            if(mask & (1 << i)) continue;

            int newMask = mask | (1 << i);

            if(sum[mask] % target + nums[i] > target) {
                dp[newMask] = false;
                continue;
            }

            dp[newMask] = true;
            sum[newMask] = sum[mask] + nums[i];
        }
    }

    return dp[(1 << n) - 1];
}

void countArrangementHelper(int mask, int n, int& beautifulArrangements) {
    if(mask == (1 << n) - 1) {
        beautifulArrangements++;
        return;
    }

    int pos = __builtin_popcount(mask) + 1;

    for(int num = 1; num <= n; num++) {
        if(mask & (1 << (num - 1)) or (num % pos and pos % num)) continue;

        countArrangementHelper(mask | (1 << (num - 1)), n, beautifulArrangements);
    }
}

int countArrangement(int n) {
    vector<int> dp(1 << n);
    dp[0] = 1;

    for(int mask = 0; mask < (1 << n); mask++) {
        int pos = __builtin_popcount(mask) + 1;

        for(int num = 1; num <= n; num++) {
            if(mask & (1 << (num - 1)) or (num % pos and pos % num)) continue;

            dp[mask | (1 << (num - 1))] += dp[mask];
        }
    }

    return dp[(1 << n) - 1];
}

int main() {
    int n = 4;

    cout << countArrangement(n) << endl;
    return 0;
}