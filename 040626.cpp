#include<bits/stdc++.h>
using namespace std;

int minPathSum2DDP(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();

    //dp[i][j] -> Minimum cost to reach (i, j)
    vector<vector<int>> dp(m, vector<int>(n));

    //Base case
    dp[0][0] = grid[0][0];

    for(int j = 1; j < n; j++) {
        dp[0][j] = grid[0][j] + dp[0][j - 1];
    }

    for(int i = 1; i < m; i++) {
        for(int j = 0; j < n; j++) {
            dp[i][j] = grid[i][j];

            if(j - 1 >= 0) {
                dp[i][j] += min(dp[i - 1][j], dp[i][j - 1]);
            } else {
                dp[i][j] += dp[i - 1][j];
            }

        }

    }

    return dp[m - 1][n - 1];
}

int minPathSum1DDP(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();

    //dp[j] -> Minimum cost to reach column j in the current row.
    vector<int> dp(n);

    for(int j = 0; j < n; j++) {
        dp[j] = grid[0][j];
        if(j - 1 >= 0) {
            dp[j] += dp[j - 1];
        }
    }

    for(int i = 1; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(j - 1 >= 0) {
                dp[j] = grid[i][j] + min(dp[j], dp[j - 1]);
            } else {
                dp[j] += grid[i][j];
            }
        } 
    }

    return dp[n - 1];
}

int longestCommonSubsequence2DDP(string text1, string text2) {
    int m = text1.length(), n = text2.length();

    //dp[i][j] -> The length of LCS of substring of text1 starting at i
    // and substring of text2 starting at j.

    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for(int i = m - 1; i >= 0; i--) {

        for(int j = n - 1; j >= 0; j--) {

            if(text1[i] == text2[j]) {
                dp[i][j] = 1 + dp[i + 1][j + 1];
            } else {
                dp[i][j] = max(dp[i + 1][j], dp[i][j + 1]);
            }

        }

    }

    return dp[0][0];
}

int longestCommonSubsequence1DDP(string text1, string text2) {
    int m = text1.length(), n = text2.length();

    //dp[j] -> The length of LCS of current string and substring of text2 starting at j.

    vector<int> dp(n + 1);

    for(int i = m - 1; i >= 0; i--) {
        int diag = 0;
        for(int j = n - 1; j >= 0; j--) {
            int temp = dp[j];
            if(text1[i] == text2[j]) {
                dp[j] = 1 + diag;
            } else {
                dp[j] = max(dp[j], dp[j + 1]);
            }
            diag = temp;
        }
    }

    return dp[0];
}

int main() {
    
    return 0;
}