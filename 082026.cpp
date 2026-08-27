#include<bits/stdc++.h>
using namespace std;

int countPartitions(vector<int>& nums) {
    int n = nums.size(), prefixSum = 0;

    int suffixSum = accumulate(nums.begin(), nums.end(), 0);

    int count = 0;

    for(int i = 0; i < n - 1; i++) {
        prefixSum += nums[i];
        suffixSum -= nums[i];

        if((prefixSum - suffixSum) % 2 == 0) {
            count++;
        }
    }

    return count;
}

int countPartitions(vector<int>& arr, int diff) {
    int n = arr.size();

    int totalSum = accumulate(arr.begin(), arr.end(), 0);

    //dp[j] -> Count of subsequences till the current index in arr that have a sum equal to j

    vector<int> dp(totalSum + 1);

    dp[0] = 1;

    for(int num : arr) {
        for(int j = totalSum; j >= num; j--) {
            dp[j] += dp[j - num];
        }
    }

    int count = 0;

    for(int s1 = 0; s1 <= totalSum / 2; s1++) {
        if(abs(2 * s1 - totalSum) == diff) {
            count += dp[s1];
        }
    }
    
    return count;
}

int knapsack2DDP(int W, vector<int> &val, vector<int> &wt) {
    int n = val.size();

    //dp[i][j] -> Maximum value that can be obtained till the i-th 
    //            index with a knapsack of maximum capacity j.

    vector<vector<int>> dp(n, vector<int>(W + 1));

    for(int j = 0; j <= W; j++) {
        dp[0][j] = (wt[0] <= j) ? val[0] : 0;
    }

    for(int i = 1; i < n; i++) {
        for(int j = 0; j <= W; j++) {
            dp[i][j] = dp[i - 1][j];

            if(j - wt[i] >= 0) {
                dp[i][j] = max(dp[i][j], val[i] + dp[i - 1][j - wt[i]]);
            }
        }
    }

    return dp[n - 1][W];
}

int knapsack1DDP(int W, vector<int> &val, vector<int> &wt) {
    int n = val.size();

    //dp[j] -> Maximum value that can be obtained till the 
    // current index with a knapsack of maximum capacity j.

    vector<int> dp(W + 1);

    for(int j = 0; j <= W; j++) {
        dp[j] = (wt[0] <= j) ? val[0] : 0;
    }

    for(int i = 1; i < n; i++) {
        for(int j = W; j >= 0; j--) {
            if(j - wt[i] >= 0) {
                dp[j] = max(dp[j], val[i] + dp[j - wt[i]]);
            }
        }
    }

    return dp[W];
}

int coinChange2DDP(vector<int>& coins, int amount) {
    int n = coins.size();

    //dp[i][j] -> Minimum coins required to make amount j using the first i coins.

    vector<vector<int>> dp(n + 1, vector<int>(amount + 1, INT_MAX));

    for(int i = 0; i <= n; i++) {
        dp[i][0] = 0;
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= amount; j++) {
            dp[i][j] = dp[i - 1][j];

            if(j - coins[i - 1] >= 0 and dp[i][j - coins[i - 1]] != INT_MAX) {
                dp[i][j] = min(dp[i][j], 1 + dp[i][j - coins[i - 1]]);
            }
        }
    }

    return dp[n][amount] == INT_MAX ? -1 : dp[n][amount];
}

int coinChange1DDP(vector<int>& coins, int amount) {
    int n = coins.size();

    //dp[j] -> Minimum coins required to make amount j using the coins we have processed so far.

    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;

    for(int i = 1; i <= n; i++) {
        for(int j = coins[i - 1]; j <= amount; j++) {
            if(dp[j - coins[i - 1]] != INT_MAX) {
                dp[j] = min(dp[j], 1 + dp[j - coins[i - 1]]);
            }
        }
    }

    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

int findTargetSumWays(vector<int>& nums, int target) {
    int n = nums.size();

    int totalSum = accumulate(nums.begin(), nums.end(), 0);

    if(abs(target) > totalSum) {
        return 0;
    }

    if((totalSum + target) % 2) {
        return 0;
    }

    int goal = (totalSum + target) / 2;

    //dp[j] -> Number of subsequences with a sum equal to j using the elements processed so far.

    vector<int> dp(goal + 1);

    dp[0] = 1;

    for(int num : nums) {
        for(int j = goal; j >= num; j--) {
            dp[j] += dp[j - num];
        }
    }

    return dp[goal];
}

int change(int amount, vector<int>& coins) {
    int n = coins.size();

    //dp[i][j] -> Number of combinations that make an amount j using the first i coins.

    vector<vector<long long>> dp(n + 1, vector<long long>(amount + 1));

    for(int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= amount; j++) {
            int pick = 0, notPick = dp[i - 1][j];

            if(j - coins[i - 1] >= 0) {
                pick = dp[i][j - coins[i - 1]];
            }

            dp[i][j] = (long long) pick + notPick;
        }
    }

    return dp[n][amount];
}

int main() {
    int amount = 5;
    vector<int> coins = {1,2,5};

    cout << change(amount, coins) << endl;
    return 0;
}