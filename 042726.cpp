#include<bits/stdc++.h>
using namespace std;

int climbStairs(int n) {
    //dp[i] -> number of distinct ways to climb i stairs
    //dp[i] = dp[i - 1] + dp[i - 2]
    vector<int> dp(n + 1);

    //Base cases
    dp[0] = 1, dp[1] = 1;

    for(int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

int climbStairsSpaceOptimized(int n) {
    int curr, prev = 1, prevprev = 1;

    for(int i = 2; i <= n; i++) {
        curr = prev + prevprev;
        prevprev = prev;
        prev = curr;
    }

    return curr;
}

int minCostClimbingStairs(vector<int>& cost) {
    int n = cost.size();

    //dp[i] -> Minimum cost to reach ith stair
    //dp[i] = min(dp[i - 2] + cost[i - 2], dp[i - 1] + cost[i - 1])

    vector<int> dp(n + 1);

    //Base case
    dp[0] = 0, dp[1] = 0;

    for(int i = 2; i <= n; i++) {
        dp[i] = min(dp[i - 2] + cost[i - 2], dp[i - 1] + cost[i - 1]);
    }

    return dp[n];
}

int minCostClimbingStairsSpaceOptimized(vector<int>& cost) {
    int n = cost.size();

    int curr, prev = 0, prevprev = 0;

    for(int i = 2; i <= n; i++) {
        curr = min(prevprev + cost[i - 2], prev + cost[i - 1]);
        prevprev = prev;
        prev = curr;
    }

    return curr;
}

// int rob(vector<int>& nums) {
//     int n = nums.size();

//     //dp[i] -> Maximum amount of money I can rob till ith house
//     //dp[i] = max(nums[i] + dp[i - 2], dp[i - 1])

//     vector<int> dp(n);

//     //Base cases
//     dp[0] = nums[0];
    
//     if(n > 1) {
//         dp[1] = max(nums[0], nums[1]);
//     }

//     for(int i = 2; i < n; i++) {
//         dp[i] = max(nums[i] + dp[i - 2], dp[i - 1]);
//     }

//     return dp[n - 1];
// }

int robSpaceOptimized(vector<int>& nums) {
    int n = nums.size();

    int curr, prev = INT_MIN, prevprev;

    prevprev = nums[0];
    
    if(n > 1) {
        prev = max(nums[0], nums[1]);
    }

    curr = max(prevprev, prev);

    for(int i = 2; i < n; i++) {
        curr = max(nums[i] + prevprev, prev);
        prevprev = prev;
        prev = curr;
    }

    return curr;
}

int robUtil(const vector<int>& nums) {
    int n = nums.size();

    int curr, prev = INT_MIN, prevprev;

    prevprev = nums[0];

    if(n > 1) {
        prev = max(nums[0], nums[1]);
    }

    curr = max(prevprev, prev);

    for(int i = 2; i < n; i++) {
        curr = max(nums[i] + prevprev, prev);
        prevprev = prev;
        prev = curr;
    }

    return curr;
}

int rob(vector<int>& nums) {
    int n = nums.size(), scenario1, scenario2;

    if(n == 1) {
        return nums[0];
    }

    scenario1 = robUtil({nums.begin(), nums.end() - 1});
    scenario2 = robUtil({nums.begin() + 1, nums.end()});

    return max(scenario1, scenario2);
}

int fib(int n) {
    //dp[i] -> ith fibonacci number
    //dp[i] = dp[i - 1] + dp[i - 2]

    vector<int> dp(n + 1);

    //Base cases
    dp[0] = 0;

    if(n) {
        dp[1] = 1;
    }

    for(int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

int fibSpaceOptimized(int n) {
    int curr, prev = INT_MIN, prevprev;

    prevprev = 0;

    if(n) {
        prev = 1;
    }

    curr = max(prev, prevprev);

    for(int i = 2; i <= n; i++) {
        curr = prev + prevprev;
        prevprev = prev;
        prev = curr;
    }

    return curr;
}

int tribonacci(int n) {
    //dp[i] -> ith tribonacci number
    //dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3]

    vector<int> dp(n + 1);

    //Base cases
    dp[0] = 0;

    if(n >= 1) {
        dp[1] = 1;
    }

    if(n >= 2) {
        dp[2] = 1;
    }

    for(int i = 3; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
    }

    return dp[n];
}

int tribonacciSpaceOptimized(int n) {
    int curr, prevprevprev, prevprev = INT_MIN, prev = INT_MIN;

    prevprevprev = 0;

    if(n >= 1) {
        prevprev = 1;
    }

    if(n >= 2) {
        prev = 1;
    }

    curr = max({prevprevprev, prevprev, prev});

    for(int i = 3; i <= n; i++) {
        curr = prev + prevprev + prevprevprev;
        prevprevprev = prevprev;
        prevprev = prev;
        prev = curr;
    }

    return curr;
}

int uniquePaths(int m, int n) {
    //dp[i][j] = Number of possible unique paths to reach (i, j)
    //dp[i][j] = dp[i][j - 1] + dp[i - 1][j]

    vector<vector<int>> dp(m, vector<int>(n));

    //Base cases
    dp[0][0] = 1;

    for(int j = 1; j < n; j++) {
        dp[0][j] = dp[0][j - 1];
    }

    for(int i = 1; i < m; i++) {
        dp[i][0] = dp[i - 1][0];
    }

    for(int i = 1; i < m; i++) {
        for(int j = 1; j < n; j++) {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }

    return dp[m - 1][n - 1];
}

int uniquePathsSpaceOptimized(int m, int n) {
    //dp[j] = Number of possible unique paths to reach jth column in current row
    //dp[j] = dp[j] + dp[j - 1] 

    vector<int> dp(n);

    //Base cases
    dp[0] = 1;

    for(int j = 1; j < n; j++) {
        dp[j] = dp[j - 1];
    }

    for(int i = 1; i < m; i++) {
        for(int j = 1; j < n; j++) {
            dp[j] = dp[j] + dp[j - 1];
        }
    }

    return dp[n - 1];
}

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();

    //dp[i][j] -> Number of possible unique paths to reach (i, j)
    //If obstacleGrid[i][j] == 0, dp[i][j] = dp[i - 1][j] + dp[i][j - 1]

    vector<vector<int>> dp(m, vector<int>(n));

    //Base cases
    if(!obstacleGrid[0][0]) {
        dp[0][0] = 1;
    }

    for(int j = 1; j < n; j++) {
        if(obstacleGrid[0][j]) {
            continue;
        }
        dp[0][j] = dp[0][j - 1];
    }

    for(int i = 1; i < m; i++) {
        if(obstacleGrid[i][0]) {
            continue;
        }
        dp[i][0] = dp[i - 1][0];
    }

    for(int i = 1; i < m; i++) {
        for(int j = 1; j < n; j++) {
            if(obstacleGrid[i][j]) {
                continue;
            }
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }

    return dp[m - 1][n - 1];
}

int uniquePathsWithObstaclesSpaceOptimized(vector<vector<int>>& obstacleGrid) {
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();

    //dp[i][j] -> Number of possible unique paths to reach jth column in current row
    //If obstacleGrid[i][j] == 0, dp[j] += dp[j - 1]

    vector<int> dp(n);

    //Base cases
    if(!obstacleGrid[0][0]) {
        dp[0] = 1;
    }

    for(int j = 1; j < n; j++) {
        if(obstacleGrid[0][j]) {
            continue;
        }
        dp[j] = dp[j - 1];
    }

    for(int i = 1; i < m; i++) {
        if(obstacleGrid[i][0]) {
            dp[0] = 0;
        }
        for(int j = 1; j < n; j++) {
            if(obstacleGrid[i][j]) {
                dp[j] = 0;
            } else {
                dp[j] += dp[j - 1];
            }
        }
    }

    return dp[n - 1];
}

int minPathSum(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();

    //dp[i][j] -> Minimum cost to reach (i, j)
    //dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j]

    vector<vector<int>> dp(m, vector<int>(n));

    //Base cases
    dp[0][0] = grid[0][0];

    for(int j = 1; j < n; j++) dp[0][j] = dp[0][j - 1] + grid[0][j];

    for(int i = 1; i < m; i++) dp[i][0] = dp[i - 1][0] + grid[i][0];

    for(int i = 1; i < m; i++) {
        for(int j = 1; j < n; j++) {
            dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
        }
    }

    return dp[m - 1][n - 1];
}

int minPathSumSpaceOptimized(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();

    //dp[j] -> Minimum cost to reach jth column in current row
    //dp[j] = min(dp[j], dp[j - 1]) + grid[i][j]

    vector<int> dp(n);

    //Base cases
    dp[0] = grid[0][0];

    for(int j = 1; j < n; j++) dp[j] = dp[j - 1] + grid[0][j];

    for(int i = 1; i < m; i++) {
        dp[0] += grid[i][0];
        for(int j = 1; j < n; j++) {
            dp[j] = min(dp[j], dp[j - 1]) + grid[i][j];
        }
    }

    return dp[n - 1];
}

int minFallingPathSum(vector<vector<int>>& matrix) {
    int n = matrix.size();

    //dp[i][j] -> Minimum sum of falling path to (i, j)
    //dp[i][j] = min({dp[i - 1][j], dp[i - 1][j - 1], dp[i - 1][j + 1]}) + matrix[i][j]

    vector<vector<int>> dp(n, vector<int>(n));

    //Base case
    dp[0] = matrix[0];

    for(int i = 1; i < n; i++) {
        for(int j = 0; j < n; j++) {
            dp[i][j] = dp[i - 1][j];

            if(j - 1 >= 0) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
            }

            if(j + 1 < n) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j + 1]);
            }

            dp[i][j] += matrix[i][j];
        }
    }

    return *min_element(dp[n - 1].begin(), dp[n - 1].end());
}

int minFallingPathSumSpaceOptimized(vector<vector<int>>& matrix) {
    int n = matrix.size();

    //dp[j] -> Minimum sum of falling path to jth column in current row
    //dp[j] = min({dp[j], dp[j - 1], dp[j + 1]}) + matrix[i][j]

    vector<int> dp(n);

    //Base case
    dp = matrix[0];

    for(int i = 1; i < n; i++) {
        int prev;
        for(int j = 0; j < n; j++) {
            int temp = dp[j];

            if(j - 1 >= 0) {
                dp[j] = min(dp[j], prev);
            }

            if(j + 1 < n) {
                dp[j] = min(dp[j], dp[j + 1]);
            }

            dp[j] += matrix[i][j];
            prev = temp;
        }
    }

    return *min_element(dp.begin(), dp.end());
}

int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size();

    //dp[i][j] -> Minimum path sum to reach (i, j)
    //dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - 1]) + triangle[i][j]

    vector<vector<int>> dp(n, vector<int>(n, INT_MAX));

    dp[0][0] = triangle[0][0];

    for(int i = 1; i < n; i++) {
        dp[i][0] = dp[i - 1][0] + triangle[i][0];
    }

    for(int i = 1; i < n; i++) {
        for(int j = 1; j <= i; j++) {
            dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - 1]) + triangle[i][j];
        }
    }

    return *min_element(dp[n - 1].begin(), dp[n - 1].end());
}

int minimumTotalSpaceOptimized(vector<vector<int>>& triangle) {
    int n = triangle.size();

    //dp[j] -> Minimum path sum to reach jth column in current row
    //dp[j] = min(dp[j], dp[j - 1]) + triangle[i][j]

    vector<int> dp(n, INT_MAX);

    dp[0] = triangle[0][0];

    for(int i = 1; i < n; i++) {
        int prev = dp[0];
        dp[0] += triangle[i][0];

        for(int j = 1; j <= i; j++) {
            int temp = dp[j];
            dp[j] = min(dp[j], prev) + triangle[i][j];
            prev = temp;
        }

    }

    return *min_element(dp.begin(), dp.end());
}

int maximalSquare(vector<string>& matrix) {
    
}

int main() {
    vector<string> matrix = {
        "10100", 
        "10111", 
        "11111", 
        "10010"
    };

    cout << maximalSquare(matrix) << endl;
    return 0;
}