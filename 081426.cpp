#include<bits/stdc++.h>
using namespace std;

int maximumPointsUtil(int day, int lastTask, vector<vector<int>>& mat, vector<vector<int>>& dp) {
    if(!day) {
        int maxPoints = 0;
        for(int i = 0; i <= 2; i++) {
            if(i == lastTask) {
                continue;
            }

            maxPoints = max(maxPoints, mat[0][i]);
        }
        
        return dp[day][lastTask] = maxPoints;
    }

    if(dp[day][lastTask] != -1) {
        return dp[day][lastTask];
    }

    int maxMeritPoints = 0;

    for(int i = 0; i <= 2; i++) {
        if(i == lastTask) {
            continue;
        }

        maxMeritPoints = max(maxMeritPoints, mat[day][i] + maximumPointsUtil(day - 1, i, mat, dp));
    }

    return dp[day][lastTask] = maxMeritPoints;
}

int maximumPointsMemoization(vector<vector<int>>& mat) {
    int n = mat.size();

    vector<vector<int>> dp(n, vector<int>(4, -1));

    int maxPoints = maximumPointsUtil(n - 1, 3, mat, dp);

    return maxPoints;
}

int maximumPoints2DDP(vector<vector<int>>& mat) {
    int n = mat.size();

    //dp[i][j] -> Maximum merit points that can be achieved till day i
    // if we perform task j on day i.

    vector<vector<int>> dp(n, vector<int>(3));

    for(int j = 0; j < 3; j++) {
        dp[0][j] = mat[0][j];
    }

    for(int i = 1; i < n; i++) {
        for(int j = 0; j < 3; j++) {
            int maxi = 0;
            for(int k = 0; k < 3; k++) {
                if(k == j) {
                    continue;
                }

                maxi = max(maxi, dp[i - 1][k]);
            }
            dp[i][j] = mat[i][j] + maxi;
        }
    }

    return *max_element(dp[n - 1].begin(), dp[n - 1].end());
}

int maximumPoints1DDP(vector<vector<int>>& mat) {
    int n = mat.size();

    //dp[j] -> Maximum merit points that can be achieved till this day
    // if we perform task j today.

    vector<int> dp = mat[0];

    for(int i = 1; i < n; i++) {
        vector<int> temp(3);
        for(int j = 0; j < 3; j++) {
            int maxi = 0;
            for(int k = 0; k < 3; k++) {
                if(k == j) {
                    continue;
                }

                maxi = max(maxi, dp[k]);
            }
            temp[j] = mat[i][j] + maxi;
        }
        dp = temp;
    }

    return *max_element(dp.begin(), dp.end());
}

int uniquePathsRecursiveUtil(int i, int j) {
    if(!i and !j) {
        return 1;
    }

    if(i < 0 or j < 0) {
        return 0;
    }

    int up = uniquePathsRecursiveUtil(i - 1, j);
    int left = uniquePathsRecursiveUtil(i, j - 1);

    return up + left;
}

int uniquePathsRecursive(int m, int n) {
    return uniquePathsRecursiveUtil(m - 1, n - 1);
}

int uniquePathsMemoizedUtil(int i, int j, vector<vector<int>>& dp) {
    if(!i and !j) {
        return 1;
    }

    if(i < 0 or j < 0) {
        return 0;
    }

    if(dp[i][j] != -1) return dp[i][j];

    int up = uniquePathsMemoizedUtil(i - 1, j, dp);
    int left = uniquePathsMemoizedUtil(i, j - 1, dp);

    return dp[i][j] = up + left;
}

int uniquePathsMemoized(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, -1));
    return uniquePathsMemoizedUtil(m - 1, n - 1, dp);
}

int uniquePaths2DDP(int m, int n) {
    //dp[i][j] -> Number of unique paths from (i, j) to (m - 1, n - 1).

    vector<vector<int>> dp(m, vector<int>(n, 1));

    for(int i = m - 2; i >= 0; i--) {
        for(int j = n - 2; j >= 0; j--) {
            dp[i][j] = dp[i + 1][j] + dp[i][j + 1];
        }
    }

    return dp[0][0];
}

int uniquePaths1DDP(int m, int n) {
    //dp[j] -> Number of unique paths from current row and jth column to (m - 1, n - 1).

    vector<int> dp(n, 1);

    for(int i = m - 2; i >= 0; i--) {
        for(int j = n - 2; j >= 0; j--) {
            dp[j] += dp[j + 1];
        }
    }

    return dp[0];
}

int nCr(int n, int r) {
    r = min(r, n - r);

    long long res = 1;

    for(int i = 1; i <= r; i++) {
        res *= (n - r + i) / i;
    }

    return res;
}

int uniquePathsOptimal(int m, int n) {
    int totalMoves = m + n - 2, totalDownMoves = m - 1;
    return nCr(totalMoves, totalDownMoves);
}

int uniquePathsWithObstacles2DDP(vector<vector<int>>& obstacleGrid) {
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();

    //dp[i][j] -> Number of unique paths from (i, j) to (m - 1, n - 1)

    vector<vector<int>> dp(m, vector<int>(n));

    if(!obstacleGrid[m - 1][n - 1]) {
        dp[m - 1][n - 1] = 1;
    }

    for(int i = m - 2; i >= 0; i--) {
        if(!obstacleGrid[i][n - 1]) {
            dp[i][n - 1] = dp[i + 1][n - 1];
        }
    }

    for(int j = n - 2; j >= 0; j--) {
        if(!obstacleGrid[m - 1][j]) {
            dp[m - 1][j] = dp[m - 1][j + 1];
        }
    }

    for(int i = m - 2; i >= 0; i--) {
        for(int j = n - 2; j >= 0; j--) {
            if(!obstacleGrid[i][j]) {
                dp[i][j] = dp[i + 1][j] + dp[i][j + 1];
            }
        }
    }

    return dp[0][0];
}

int uniquePathsWithObstacles1DDP(vector<vector<int>>& obstacleGrid) {
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();

    //dp[j] -> Number of unique paths from current row and jth column to (m - 1, n - 1)

    vector<long long> dp(n);

    if(!obstacleGrid[m - 1][n - 1]) {
        dp[n - 1] = 1;
    }

    for(int j = n - 2; j >= 0; j--) {
        if(!obstacleGrid[m - 1][j]) {
            dp[j] = dp[j + 1];
        }
    }

    for(int i = m - 2; i >= 0; i--) {
        if(obstacleGrid[i][n - 1]) {
            dp[n - 1] = 0;
        }

        for(int j = n - 2; j >= 0; j--) {
            if(!obstacleGrid[i][j]) {
                dp[j] += dp[j + 1];
            } else {
                dp[j] = 0;
            }
        }
    }

    return dp[0];
}

int minimumCostPath(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();

    vector<vector<int>> dist(m, vector<int>(n, INT_MAX));

    priority_queue<
    tuple<int, int, int>, 
    vector<tuple<int, int, int>>, 
    greater<tuple<int, int, int>>
    > pq;

    dist[0][0] = grid[0][0];
    pq.push({grid[0][0], 0, 0});

    vector<int> dr = {-1, 0, 1, 0}, dc = {0, 1, 0, -1};

    while(!pq.empty()) {
        auto [d, r, c] = pq.top();
        pq.pop();

        for(int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if(nr >= 0 and nr < m and nc >= 0 and nc < n and d + grid[nr][nc] < dist[nr][nc]) {
                dist[nr][nc] = d + grid[nr][nc];
                pq.push({dist[nr][nc], nr, nc});
            }
        }
    }

    return dist[m - 1][n - 1];
}

int minPathSum2DDP(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();

    //dp[i][j] -> Minimum path sum from (i, j) to (m - 1, n - 1)

    vector<vector<int>> dp(m, vector<int>(n));

    dp[m - 1][n - 1] = grid[m - 1][n - 1];

    for(int i = m - 2; i >= 0; i--) dp[i][n - 1] = grid[i][n - 1] + dp[i + 1][n - 1];

    for(int j = n - 2; j >= 0; j--) dp[m - 1][j] = grid[m - 1][j] + dp[m - 1][j + 1];

    for(int i = m - 2; i >= 0; i--) {
        for(int j = n - 2; j >= 0; j--) {
            dp[i][j] = grid[i][j] + min(dp[i + 1][j], dp[i][j + 1]);
        }
    }

    return dp[0][0];
}

int minPathSum1DDP(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();

    //dp[j] -> Minimum path sum from current row and jth column to (m - 1, n - 1)

    vector<int> dp(n);

    dp[n - 1] = grid[m - 1][n - 1];

    for(int j = n - 2; j >= 0; j--) dp[j] = grid[m - 1][j] + dp[j + 1];

    for(int i = m - 2; i >= 0; i--) {
        dp[n - 1] += grid[i][n - 1];
        for(int j = n - 2; j >= 0; j--) {
            dp[j] = grid[i][j] + min(dp[j], dp[j + 1]);
        }
    }

    return dp[0];
}

int main() {
    

    return 0;
}