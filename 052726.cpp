#include<bits/stdc++.h>
using namespace std;

int coinChange2DDP(vector<int>& coins, int amount) {
    int n = coins.size();

    //dp[i][j] -> Minimum coins needed to make amount i using first j coins

    vector<vector<int>> dp(amount + 1, vector<int>(n + 1));

    for(int i = 0; i <= amount; i++) {
        dp[i][0] = INT_MAX;
    }

    for(int i = 1; i <= amount; i++) {
        for(int j = 1; j <= n; j++) {
            int pick = INT_MAX, notPick = dp[i][j - 1];
            if(i - coins[j - 1] >= 0 and dp[i - coins[j - 1]][j] != INT_MAX) {
                pick = 1 + dp[i - coins[j - 1]][j];
            }
            dp[i][j] = min(pick, notPick);
        }
    }

    return dp[amount][n] == INT_MAX ? -1 : dp[amount][n];
}

int coinChange1DDP(vector<int>& coins, int amount) {
    int n = coins.size();

    //dp[j] -> Minimum coins needed to make amount i using coins upto current index

    vector<int> dp(amount + 1, INT_MAX);

    for(int i = 1; i <= n; i++) {
        dp[0] = 0;
        for(int j = 1; j <= amount; j++) {
            int pick = INT_MAX, notPick = dp[j];
            if(j - coins[i - 1] >= 0 and dp[j - coins[i - 1]] != INT_MAX) {
                pick = 1 + dp[j - coins[i - 1]];
            }
            dp[j] = min(pick, notPick);
        }
    }

    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

int change2DDP(int amount, vector<int>& coins) {
    int n = coins.size();

    //dp[i][j] -> total number of combinations that make up amount j using first i coins.

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

int change1DDP(int amount, vector<int>& coins) {
    //dp[j] -> total number of combinations that make up amount j using coins upto current index.

    vector<int> dp(amount + 1);

    for(auto coin : coins) {
        dp[0] = 1;
        for(int j = 1; j <= amount; j++) {
            if(j - coin >= 0) {
                dp[j] += dp[j - coin];
            }
        }
    }

    return dp[amount];
}

int jump(vector<int>& nums) {
    int n = nums.size();

    //dp[i] -> Minimum number of jumps to reach index i

    vector<int> dp(n);

    dp[0] = 0;

    for(int i = 1; i < n; i++) {
        int temp = INT_MAX;
        for(int j = i - 1; j >= 0; j--) {
            if(j + nums[j] >= i) {
                temp = min(temp, dp[j]);
            }
        }
        dp[i] = 1 + temp;
    }

    return dp[n - 1];
}

int findWaysToPairPeople(int n) {
    //dp[i] -> Number of ways in which i people can join the dance floor.

    vector<int> dp(n + 1);

    dp[0] = 1, dp[1] = 1;

    for(int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + (i - 1) * dp[i - 2];
    }

    return dp[n];
}

int findWaysToPairPeopleSpaceOptimized(int n) {
    int prevprev = 1, prev = 1;

    int curr = prev;

    for(int i = 2; i <= n; i++) {
        curr = prev + (i - 1) * prevprev;
    }

    return curr;
}

int main() {
    cout << findWaysToPairPeople(2) << endl;
    return 0;
}