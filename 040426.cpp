#include<bits/stdc++.h>
using namespace std;

int climbStairsTabulation(int n) {
    vector<int> dp(n + 1);

    dp[0] = dp[1] = 1;

    for(int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

int climbStairsSpaceOptimized(int n) {
    int prevprev, prev, curr;

    prevprev = 1, prev = curr = 1;

    for(int i = 2; i <= n; i++) {
        curr = prevprev + prev;
        prevprev = prev;
        prev = curr;
    }

    return curr;
}

int robTabulation(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n);

    dp[0] = nums[0];

    if(n > 1) {
        dp[1] = max(nums[0], nums[1]);
    }

    for(int i = 2; i < n; i++) {
        int pick = nums[i] + dp[i - 2];
        int notPick = dp[i - 1];

        dp[i] = max(pick, notPick);
    }

    return dp[n - 1];
}

int robSpaceOptimized(vector<int>& nums) {
    int n = nums.size();

    int prevprev, prev, curr;

    prevprev = nums[0];
    curr = prevprev;

    if(n > 1) {
        prev = max(nums[0], nums[1]);
        curr = prev;
    }

    for(int i = 2; i < n; i++) {
        int pick = nums[i] + prevprev;
        int notPick = prev;

        curr = max(pick, notPick);

        prevprev = prev;
        prev = curr;
    }

    return curr;
}

int coinChange(vector<int>& coins, int amount) {
    int n = coins.size();

    //dp[i][j] = Minimum coins required to make j amount using i coins

    vector<vector<int>> dp(n + 1, vector<int>(amount + 1));

    for(int j = 0; j <= amount; j++) {
        dp[0][j] = INT_MAX;
    }

    for(int i = 0; i <= n; i++) {
        dp[i][0] = 0;
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= amount; j++) {
            int pick = INT_MAX;
            if(j - coins[i - 1] >= 0 and dp[i][j - coins[i - 1]] != INT_MAX) {
                pick = 1 + dp[i][j - coins[i - 1]];
            }
            int notPick = dp[i - 1][j];
            dp[i][j] = min(pick, notPick);
        }
    }

    return dp[n][amount] == INT_MAX ? -1 : dp[n][amount];
    
}

int main() {
    vector<int> coins = {2};
    int amount = 3;
    cout << coinChange(coins, amount) << endl;
    return 0;
}