#include<bits/stdc++.h>
using namespace std;

int minimumTotal2DDP(vector<vector<int>>& triangle) {
    int m = triangle.size();

    //dp[i][j] -> Minimum path sum from (i, j) to the bottom row

    vector<vector<int>> dp(m, vector<int>(m));

    dp[m - 1] = triangle[m - 1];

    for(int i = m - 2; i >= 0; i--) {
        for(int j = i; j >= 0; j--) {
            dp[i][j] = triangle[i][j] + min(dp[i + 1][j], dp[i + 1][j + 1]);
        }
    }

    return dp[0][0];
}

int minimumTotal1DDP(vector<vector<int>>& triangle) {
    int m = triangle.size();

    //dp[j] -> Minimum path sum from current row and j-th column to the bottom row

    vector<int> dp(m);

    dp = triangle[m - 1];

    for(int i = m - 2; i >= 0; i--) {
        vector<int> temp(m);
        for(int j = i; j >= 0; j--) {
            temp[j] = triangle[i][j] + min(dp[j], dp[j + 1]);
        }
        dp = temp;
    }

    return dp[0];
}

int maximumPath2DDP(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size();

    //dp[i][j] -> Maximum path sum from (i, j) to the bottom row

    vector<vector<int>> dp(n, vector<int>(m));

    dp[n - 1] = mat[n - 1];

    for(int i = n - 2; i >= 0; i--) {
        for(int j = m - 1; j >= 0; j--) {
            int left = dp[i + 1][max(j - 1, 0)];
            int right = dp[i + 1][min(j + 1, m - 1)];
            dp[i][j] = mat[i][j] + max({left, dp[i + 1][j], right});
        }
    }

    return *max_element(dp[0].begin(), dp[0].end());
}

int maximumPath1DDP(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size();

    //dp[j] -> Maximum path sum from current row and j-th column to the bottom row

    vector<int> dp(m);

    dp = mat[n - 1];

    for(int i = n - 2; i >= 0; i--) {
        vector<int> temp(m);
        for(int j = m - 1; j >= 0; j--) {
            int left = dp[max(j - 1, 0)];
            int right = dp[min(j + 1, m - 1)];
            temp[j] = mat[i][j] + max({left, dp[j], right});
        }
        dp = temp;
    }

    return *max_element(dp.begin(), dp.end());
}

int cherryPickup3DDP(vector<vector<int>>& grid) {
    int rows = grid.size(), cols = grid[0].size();

    //dp[row][col1][col2] -> Maximum number of cherries that can be 
    // collected onwards row if robot1 is at col1 and robot2 is at col2

    vector<vector<vector<int>>> dp(rows, vector<vector<int>>(cols, vector<int>(cols)));

    for(int col1 = 0; col1 < cols; col1++) {
        for(int col2 = 0; col2 < cols; col2++) {

            dp[rows - 1][col1][col2] = grid[rows - 1][col1];

            if(col1 != col2) {
                dp[rows - 1][col1][col2] += grid[rows - 1][col2];
            }
        }
    }

    for(int row = rows - 2; row >= 0; row--) {
        for(int col1 = 0; col1 < cols; col1++) {
            for(int col2 = 0; col2 < cols; col2++) {

                dp[row][col1][col2] = grid[row][col1];

                if(col1 != col2) {
                    dp[row][col1][col2] += grid[row][col2];
                }

                int maxi = INT_MIN;

                for(int i = -1; i <= 1; i++) {
                    for(int j = -1; j <= 1; j++) {
                        if(col1 + i >= 0 and col1 + i < cols 
                            and col2 + j >= 0 and col2 + j < cols) {
                                maxi = max(maxi, dp[row + 1][col1 + i][col2 + j]);
                            }
                    }
                }

                dp[row][col1][col2] += maxi;
            }
        }
    }

    return dp[0][0][cols - 1];
}

int cherryPickup2DDP(vector<vector<int>>& grid) {
    int rows = grid.size(), cols = grid[0].size();

    //dp[col1][col2] -> Maximum number of cherries that can be collected 
    // from current row onwards if robot1 is at col1 and robot2 is at col2

    vector<vector<int>> dp(cols, vector<int>(cols));

    for(int col1 = 0; col1 < cols; col1++) {
        for(int col2 = 0; col2 < cols; col2++) {
            dp[col1][col2] = grid[rows - 1][col1];
            if(col1 != col2) {
                dp[col1][col2] += grid[rows - 1][col2];
            }
        }
    }

    for(int row = rows - 2; row >= 0; row--) {
        vector<vector<int>> temp(cols, vector<int>(cols));
        for(int col1 = 0; col1 < cols; col1++) {
            for(int col2 = 0; col2 < cols; col2++) {

                temp[col1][col2] = grid[row][col1];

                if(col1 != col2) {
                    temp[col1][col2] += grid[row][col2];
                }

                int maxi = INT_MIN;

                for(int i = -1; i <= 1; i++) {
                    for(int j = -1; j <= 1; j++) {
                        if(col1 + i >= 0 and col1 + i < cols 
                            and col2 + j >= 0 and col2 + j < cols) {
                                maxi = max(maxi, dp[col1 + i][col2 + j]);
                            }
                    }
                }
                temp[col1][col2] += maxi;
            }
        }
        dp = temp;
    }

    return dp[0][cols - 1];
}

int main() {
    vector<vector<int>> grid = {
        {3,1,1},
        {2,5,1},
        {1,5,5},
        {2,1,1}
    };

    cout << cherryPickup2DDP(grid) << endl;
    return 0;
}