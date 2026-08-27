#include<bits/stdc++.h>
using namespace std;

int uniquePaths(int m, int n) {
    //dp[i][j] = Number of unique paths from (i, j) to (m - 1, n - 1)

    vector<vector<int>> dp(m, vector<int>(n, 1));

    for(int i = m - 2; i >= 0; i--) {
        for(int j = n - 2; j >= 0; j--) {
            dp[i][j] = dp[i][j + 1] + dp[i + 1][j];
        }
    }

    return dp[0][0];
}

int uniquePaths1DDP(int m, int n) {
    //dp[j] -> Number of unique paths from current row and j-th column to (m - 1, n - 1)

    vector<int> dp(n, 1);

    for(int i = m - 2; i >= 0; i--) {
        for(int j = n - 2; j >= 0; j--) {
            dp[j] += dp[j + 1];
        }
    }

    return dp[0];
}

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    //dp[i][j] -> Possible unique paths from (i, j) to (m - 1, n - 1)

    int m = obstacleGrid.size(), n = obstacleGrid[0].size();

    vector<vector<int>> dp(m, vector<int>(n));

    dp[m - 1][n - 1] = obstacleGrid[m - 1][n - 1] ? 0 : 1;

    for(int i = m - 2; i >= 0; i--) {
        dp[i][n - 1] = obstacleGrid[i][n - 1] ? 0 : dp[i + 1][n - 1];
    }

    for(int j = n - 2; j >= 0; j--) {
        dp[m - 1][j] = obstacleGrid[m - 1][j] ? 0 : dp[m - 1][j + 1];
    }

    for(int i = m - 2; i >= 0; i--) {
        for(int j = n - 2; j >= 0; j--) {
            dp[i][j] = obstacleGrid[i][j] ? 0 : dp[i][j + 1] + dp[i + 1][j];
        }
    }

    return dp[0][0];
}

int uniquePathsWithObstacles1DDP(vector<vector<int>>& obstacleGrid) {
    //dp[j] -> Possible unique paths from current row and j-th column to (m - 1, n - 1)

    int m = obstacleGrid.size(), n = obstacleGrid[0].size();

    vector<int> dp(n);

    dp[n - 1] = obstacleGrid[m - 1][n - 1] ? 0 : 1;

    for(int j = n - 2; j >= 0; j--) {
        dp[j] = obstacleGrid[m - 1][j] ? 0 : dp[j + 1];
    }

    for(int i = m - 2; i >= 0; i--) {
        dp[n - 1] = obstacleGrid[i][n - 1] ? 0 : dp[n - 1];
        for(int j = n - 2; j >= 0; j--) {
            dp[j] = obstacleGrid[i][j] ? 0 : dp[j + 1] + dp[j];
        }
    }

    return dp[0];
}

int minPathSum(vector<vector<int>>& grid) {
    //dp[i][j] -> Minimum path sum from (i, j) to (m - 1, n - 1)

    int m = grid.size(), n = grid[0].size();

    vector<vector<int>> dp(m, vector<int>(n));

    dp[m - 1][n - 1] = grid[m - 1][n - 1];

    for(int j = n - 2; j >= 0; j--) {
        dp[m - 1][j] = grid[m - 1][j] + dp[m - 1][j + 1];
    }

    for(int i = m - 2; i >= 0; i--) {
        dp[i][n - 1] = grid[i][n - 1] + dp[i + 1][n - 1];
    }

    for(int i = m - 2; i >= 0; i--) {
        for(int j = n - 2; j >= 0; j--) {
            dp[i][j] = grid[i][j] + min(dp[i][j + 1], dp[i + 1][j]);
        }
    }

    return dp[0][0];
}

int minPathSum1DDP(vector<vector<int>>& grid) {
    //dp[j] -> Minimum path sum from current row and j-th column to (m - 1, n - 1)

    int m = grid.size(), n = grid[0].size();

    vector<int> dp(n);

    dp[n - 1] = grid[m - 1][n - 1];

    for(int j = n - 2; j >= 0; j--) {
        dp[j] = grid[m - 1][j] + dp[j + 1];
    }

    for(int i = m - 2; i >= 0; i--) {
        dp[n - 1] += grid[i][n - 1];
        for(int j = n - 2; j >= 0; j--) {
            dp[j] = grid[i][j] + min(dp[j + 1], dp[j]);
        }
    }

    return dp[0];
}

int calculateMinimumHP(vector<vector<int>>& dungeon) {\
    
}

int main() {

    vector<vector<int>> dungeon = {
        {-2,-3,3}, 
        {-5,-10,1}, 
        {10,30,-5}
    };

    cout << calculateMinimumHP(dungeon) << endl;

    return 0;
}