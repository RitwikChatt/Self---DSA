#include<bits/stdc++.h>
using namespace std;

bool canJump(vector<int>& nums) {
    int n = nums.size();
    int maxReach = 0;

    for(int i = 0; i < n; i++) {
        if(i > maxReach) {
            return false;
        }
        maxReach = max(maxReach, i + nums[i]);
    }

    return true;
}

int maxProfit(vector<int>& prices) {
    int n = prices.size();
    int minPrice = prices[0], profit = 0;

    for(int i = 1; i < n; i++) {
        profit = max(profit, prices[i] - minPrice);
        minPrice = min(minPrice, prices[i]);
    }

    return profit;
}

int coinChange(vector<int>& coins, int amount) {
    //dp[i] -> Minimum coins required to make amount i

    vector<int> dp(amount + 1, INT_MAX);

    //Base Case
    dp[0] = 0;

    for(int i = 1; i <= amount; i++) {
        for(int coin : coins) {
            int notPick = dp[i], pick = INT_MAX;
            if(i - coin >= 0 and dp[i - coin] != INT_MAX) {
                pick = 1 + dp[i - coin];
            }
            dp[i] = min(pick, notPick);
        }
    }

    return dp[amount] == INT_MAX ? -1 : dp[amount];

}

int numDecodingsTabulation(string s) {
    int n = s.length();

    //dp[i] = Number of ways to decode a substring starting from index i
    vector<int> dp(n + 1);

    //Base cases:

    //1. There is only 1 way to decode an empty string i.e., NO MESSAGE.
    dp[n] = 1;

    //2. If s[n - 1] = '0', there is no way to decode the substring, 
    //but if it is not '0' then there is just 1 way.
    dp[n - 1] = s[n - 1] == '0' ? 0 : 1;

    for(int i = n - 2; i >= 0; i--) {
        if(s[i] == '0') {
            continue;
        }

        dp[i] = dp[i + 1];

        int num = 10 * (s[i] - '0') + (s[i + 1] - '0');
        if(10 <= num and num <= 26) {
            dp[i] += dp[i + 2];
        }

    }

    return dp[0];
}

int numDecodingsSpaceOptimized(string s) {
    int n = s.length();

    int next, nextnext, curr;

    nextnext = 1;
    next = s[n - 1] == '0' ? 0 : 1;
    curr = next;

    for(int i = n - 2; i >= 0; i--) {
        if(s[i] == '0') {
            curr = 0;
            nextnext = next;
            next = curr;
            continue;
        }

        curr = next;

        int num = 10 * (s[i] - '0') + (s[i + 1] - '0');

        if(10 <= num and num <= 26) {
            curr += nextnext;
        }

        nextnext = next;
        next = curr;

    }

    return curr;
}

int waysToPairPeopleTabulation(int n) {
    //dp[i] -> Number of ways in which i people can join the dance
    vector<int> dp(n + 1);

    dp[1] = 1;
    dp[2] = 2;

    for(int i = 3; i <= n; i++) {
        dp[i] = dp[i - 1] + (i - 1) * dp[i - 2];
    }

    return dp[n];
}

int waysToPairPeopleSpaceOptimized(int n) {
    int prevprev, prev, curr;

    prevprev = 1;
    prev = 2;
    curr = prev;

    for(int i = 3; i <= n; i++) {
        curr = prev + (i - 1) * prevprev;
        prevprev = prev;
        prev = curr;
    }

    return curr;
}

int uniquePaths2DDP(int m, int n) {
    //dp[i][j] -> Number of possible unique paths the robot can take to reach (i, j)

    vector<vector<int>> dp(m, vector<int>(n));

    for(int i = 0; i < m; i++) {
        dp[i][0] = 1;
    }

    for(int j = 0; j < n; j++) {
        dp[0][j] = 1;
    }

    for(int i = 1; i < m; i++) {
        for(int j = 1; j < n; j++){
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }

    return dp[m - 1][n - 1];
}

int uniquePaths1DDP(int m, int n) {
    //dp[j] -> Number of ways to reach column j in current row

    //Base case
    vector<int> dp(n, 1);

    for(int i = 1; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(j > 0) {
                dp[j] += dp[j - 1];
            }
        }
    }

    return dp[n - 1];
}

int nCr(int n, int r) {
    r = min(r, n - r);
    long long res = 1;

    for(int i = 1; i <= r; i++) {
        res = res * (n - r + i) / i;
    }

    return res;
}

int uniquePathsOptimal(int m, int n) {
    int totalMoves = m + n - 2, totalDownMoves = m - 1;
    return nCr(totalMoves, totalDownMoves);
}

int uniquePathsWithObstacles2DDP(vector<vector<int>>& obstacleGrid) {
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();

    //dp[i][j] -> Number of possible unique paths the robot can take to reach (i, j)
    vector<vector<int>> dp(m, vector<int>(n));

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {

            if(!i and !j) {
                dp[i][j] = 1;
            }

            if(obstacleGrid[i][j]) {
                dp[i][j] = 0;
                continue;
            }

            if(i - 1 >= 0) {
                dp[i][j] = dp[i - 1][j];
            }

            if(j - 1 >= 0) {
                dp[i][j] += dp[i][j - 1];
            }

        }
    }

    return dp[m - 1][n - 1];
}

int uniquePathsWithObstacles1DDP(vector<vector<int>>& obstacleGrid) {
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();

    //dp[j] -> Number of possible unique paths the robot can take to reach the column j in current row.
    vector<int> dp(n);

    dp[0] = obstacleGrid[0][0] ? 0 : 1;

    for(int j = 1; j < n; j++) {
        if(obstacleGrid[0][j]) {
            dp[j] = 0;
        } else {
            dp[j] = dp[j - 1];
        }
    }

    for(int i = 1; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(obstacleGrid[i][j]) {
                dp[j] = 0;
                continue;
            }

            if(j - 1 >= 0) {
                dp[j] += dp[j - 1];
            }

        }
    }

    return dp[n - 1];
}

bool isMatch(string s, string p) {
    
}

int main() {
    isMatch("aa", "a") ? cout << "true" : cout << "false";
    return 0;
}