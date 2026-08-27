#include<bits/stdc++.h>
using namespace std;

int calculateMinimumHP2DDP(vector<vector<int>>& dungeon) {
    int m = dungeon.size(), n = dungeon[0].size();

    //dp[i][j] -> Minimum health required to enter (i, j)

    vector<vector<int>> dp(m, vector<int>(n));

    //Base Case
    dp[m - 1][n - 1] = max(1, 1 - dungeon[m - 1][n - 1]);

    //Last column
    for(int i = m - 2; i >= 0; i--) {
        dp[i][n - 1] = max(1, dp[i + 1][n - 1] - dungeon[i][n - 1]);
    }

    //Last row
    for(int j = n - 2; j >= 0; j--) {
        dp[m - 1][j] = max(1, dp[m - 1][j + 1] - dungeon[m - 1][j]);
    }

    for(int i = m - 2; i >= 0; i--) {
        for(int j = n - 2; j >= 0; j--) {
            dp[i][j] = max(1, min(dp[i][j + 1], dp[i + 1][j]) - dungeon[i][j]);
        }
    } 

    return dp[0][0];
}

int calculateMinimumHP1DDP(vector<vector<int>>& dungeon) {
    int m = dungeon.size(), n = dungeon[0].size();

    //dp[j] -> Minimum health required to enter jth column in current row.

    vector<int> dp(n);

    //Base case
    dp[n - 1] = max(1, 1 - dungeon[m - 1][n - 1]);

    //Last row
    for(int j = n - 2; j >= 0; j--) {
        dp[j] = max(1, dp[j + 1] - dungeon[m - 1][j]);
    }

    for(int i = m - 2; i >= 0; i--) {
        dp[n - 1] = max(1, dp[n - 1] - dungeon[i][n - 1]);
        for(int j = n - 2; j >= 0; j--) {
            dp[j] = max(1, min(dp[j], dp[j + 1]) - dungeon[i][j]);
        }
    }

    return dp[0];
}

int main() {
    
    return 0;
}