#include<bits/stdc++.h>
using namespace std;

int cutRod2DDP(vector<int> &price) {
    int n = price.size();

    //dp[i][j] -> Maximum value that can be obtained by combining rods of length at most i to form a rod of length j.

    vector<vector<int>> dp(n + 1, vector<int>(n + 1));

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            dp[i][j] = dp[i - 1][j];

            if(j - i >= 0) {
                dp[i][j] = max(dp[i][j], price[i - 1] + dp[i][j - i]);
            }
        }
    }

    return dp[n][n];
}

int cutRod1DDP(vector<int> &price) {
    int n = price.size();

    //dp[j] -> Maximum value that can be obtained by combining rods of at most current length to form a rod of length j.

    vector<int> dp(n + 1);

    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j++) {
            dp[j] = max(dp[j], price[i - 1] + dp[j - i]);
        }
    }

    return dp[n];
}

int longestCommonSubsequence2DDP(string text1, string text2) {
    int m = text1.length(), n = text2.length();

    //dp[i][j] -> Length of LCS in text1[0 ... i] and text2[0 ... j]

    vector<vector<int>> dp(m, vector<int>(n));

    dp[0][0] = (text1[0] == text2[0]);

    for(int i = 1; i < m; i++) {
        if(text1[i] == text2[0]) {
            dp[i][0] = 1;
        } else {
            dp[i][0] = dp[i - 1][0];
        }
    }

    for(int j = 1; j < n; j++) {
        if(text1[0] == text2[j]) {
            dp[0][j] = 1;
        } else {
            dp[0][j] = dp[0][j - 1];
        }
    }

    for(int i = 1; i < m; i++) {
        for(int j = 1; j < n; j++) {
            if(text1[i] == text2[j]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[m - 1][n - 1];
}

int longestCommonSubsequence1DDP(string text1, string text2) {
    int m = text1.length(), n = text2.length();

    //dp[j] -> Length of LCS in text1[0 ... i] and text2[0 ... j]

    vector<int> dp(n);

    dp[0] = (text1[0] == text2[0]);

    for(int j = 1; j < n; j++) {
        if(text1[0] == text2[j]) {
            dp[j] = 1;
        } else {
            dp[j] = dp[j - 1];
        }
    }

    for(int i = 1; i < m; i++) {
        vector<int> temp(n);

        if(text1[i] == text2[0]) {
            temp[0] = 1;
        } else {
            temp[0] = dp[0];
        }

        for(int j = 1; j < n; j++) {
            if(text1[i] == text2[j]) {
                temp[j] = 1 + dp[j - 1];
            } else {
                temp[j] = max(dp[j], temp[j - 1]);
            }
        }

        dp = temp;
    }

    return dp[n - 1];
}

int main() {
    
    return 0;
}