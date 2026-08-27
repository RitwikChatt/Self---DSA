#include<bits/stdc++.h>
using namespace std;

int calculateMinimumHP(vector<vector<int>>& dungeon) {
    int m = dungeon.size(), n = dungeon[0].size();

    //dp[i][j] -> Minimum HP needed to enter cell (i, j) and reach (m - 1, n - 1)

    vector<vector<int>> dp(m, vector<int>(n));

    dp[m - 1][n - 1] = max(1, 1 - dungeon[m - 1][n - 1]);

    for(int j = n - 2; j >= 0; j--) {
        dp[m - 1][j] = max(1, dp[m - 1][j + 1] - dungeon[m - 1][j]);
    }

    for(int i = m - 2; i >= 0; i--) {
        dp[i][n - 1] = max(1, dp[i + 1][n - 1] - dungeon[i][n - 1]);
    }

    for(int i = m - 2; i >= 0; i--) {
        for(int j = n - 2; j >= 0; j--) {
            dp[i][j] = max(1, min(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j]);
        }
    }

    return dp[0][0];
}

int calculateMinimumHP1DDP(vector<vector<int>>& dungeon) {
    int m = dungeon.size(), n = dungeon[0].size();

    //dp[j] -> Minimum HP needed to enter j-th column in current row and reach (m - 1, n - 1)

    vector<int> dp(n);

    dp[n - 1] = max(1, 1 - dungeon[m - 1][n - 1]);

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

int longestCommonSubsequence(string text1, string text2) {
    int m = text1.length(), n = text2.length();

    //dp[i][j] -> Length of LCS of strings s1 and s2 where len(s1) = i and len(s2) = j

    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(text1[i - 1] == text2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }
    }

    return dp[m][n];
}

int longestCommonSubsequence1DDP(string text1, string text2) {
    int m = text1.length(), n = text2.length();

    //dp[j] -> Length of LCS of strings s1 and s2

    vector<int> dp(n + 1);

    for(int i = 1; i <= m; i++) {
        int temp = dp[0];
        dp[0] = 0;
        for(int j = 1; j <= n; j++) {
            int diag = dp[j];
            if(text1[i - 1] == text2[j - 1]) {
                dp[j] = 1 + temp;
            } else {
                dp[j] = max({dp[j], dp[j - 1], temp});
            }
            temp = diag;
        }
    }

    return dp[n];
}

int longestPalindromeSubseq(string s) {
    string orig = s;
    reverse(s.begin(), s.end());
    return longestCommonSubsequence1DDP(orig, s);
}

bool canPartition(vector<int>& nums) {
    
}

int main() {
    vector<int> nums = {1,5,11,5};
    canPartition(nums) ? cout << "yes" : cout << "no";
    return 0;
}