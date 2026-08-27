#include<bits/stdc++.h>
using namespace std;

int minDistance2DDP(string word1, string word2) {
    int m = word1.length(), n = word2.length();

    //dp[i][j] -> Minimum number of operations required to convert word1[i ... (m - 1)] to word2[j ... (n - 1)]

    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for(int j = n - 1; j >= 0; j--) {
        dp[m][j] = n - j;
    }

    for(int i = m - 1; i >= 0; i--) {
        dp[i][n] = m - i;
    }

    for(int i = m - 1; i >= 0; i--) {
        for(int j = n - 1; j >= 0; j--) {
            if(word1[i] == word2[j]) {
                dp[i][j] = dp[i + 1][j + 1];
            } else {
                dp[i][j] = 1 + min({dp[i][j + 1], dp[i + 1][j], dp[i + 1][j + 1]});
            }
        }
    }

    return dp[0][0];
}

int minDistance1DDP(string word1, string word2) {
    int m = word1.length(), n = word2.length();

    //dp[j] -> Minimum operations required to convert the current word to word2[j ... (n - 1)]

    vector<int> dp(n + 1);

    for(int j = n - 1; j >= 0; j--) {
        dp[j] = n - j;
    }

    for(int i = m - 1; i >= 0; i--) {
        int diag = dp[n];
        dp[n] = m - i;
        for(int j = n - 1; j >= 0; j--) {
            int temp = dp[j];
            if(word1[i] == word2[j]) {
                dp[j] = diag;
            } else {
                dp[j] = 1 + min({dp[j], dp[j + 1], diag});
            }
            diag = temp;
        }
    }

    return dp[0];
}

int longestPalindromeSubseq2DDP(string s) {
    int n = s.length();

    //dp[i][j] -> The length of LPS of s[i ... j]

    vector<vector<int>> dp(n, vector<int>(n));

    for(int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }

    for(int i = n - 2; i >= 0; i--) {
        for(int j = i + 1; j < n; j++) {
            if(s[i] == s[j]) {
                dp[i][j] = 2 + dp[i + 1][j - 1];
            } else {
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[0][n - 1];
}

int longestPalindromeSubseq1DDP(string s) {
    int n = s.length();

    //dp[j] -> The length of LPS of s[i ... j]

    vector<int> dp(n);

    dp[n - 1] = 1;

    for(int i = n - 2; i >= 0; i--) {
        int diag = dp[i];
        dp[i] = 1;
        for(int j = i + 1; j < n; j++) {
            int temp = dp[j];
            if(s[i] == s[j]) {
                dp[j] = 2 + diag;
            } else {
                dp[j] = max(dp[j - 1], dp[j]);
            }
            diag = temp;
        }
    }

    return dp[n - 1];
}

int main() {
    
    return 0;
}