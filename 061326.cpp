#include<bits/stdc++.h>
using namespace std;

int numDistinct(string s, string t) {
    int m = s.length(), n = t.length();

    //dp[i][j] -> Number of distinct subsequences of s[0 ... i-1] that equals t[0 ... j-1]

    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for(int i = 0; i <= m; i++) {
        dp[i][0] = 1;
    }

    for(int j = 1; j <= n; j++) {
        dp[0][j] = 0;
    }

    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            int pick = 0, notPick = dp[i - 1][j];
            if(s[i - 1] == t[j - 1]) {
                pick = dp[i - 1][j - 1];
            }
            dp[i][j] = pick + notPick;
        }
    }

    return dp[m][n];
}

int numDistinct1DDP(string s, string t) {
    int m = s.length(), n = t.length();

    //dp[j] -> Number of distinct subsequences of s[0 ... i-1] that equals t[0 ... j-1]

    vector<long long> dp(n + 1);

    dp[0] = 1;

    for(int i = 1; i <= m; i++) {
        int diag = dp[0];
        for(int j = 1; j <= n; j++) {
            int pick = 0, notPick = dp[j];
            if(s[i - 1] == t[j - 1]) {
                pick = diag;
            }
            int temp = dp[j];
            dp[j] = pick + notPick;
            diag = temp;
        }
    }

    return dp[n];
}

string longestPalindrome(string s) {
    int n = s.length();

    //dp[i][j] -> true if s[i ... j] is a palindrome

    vector<vector<bool>> dp(n, vector<bool>(n));

    int start = 0, maxLen = 1;

    for(int i = 0; i < n; i++) {
        dp[i][i] = true;
        if(i + 1 < n) {
            dp[i][i + 1] = (s[i] == s[i + 1]);
            if(dp[i][i + 1]) {
                start = i, maxLen = 2;
            }
        }
    }

    for(int i = n - 3; i >= 0; i--) {
        for(int j = i + 2; j < n; j++) {
            dp[i][j] = (s[i] == s[j]) and dp[i + 1][j - 1];
            if(dp[i][j] and j - i + 1 > maxLen) {
                start = i, maxLen = j - i + 1;
            }
        }
    }

    return s.substr(start, maxLen);
}

int countSubstrings(string s) {
    int n = s.length();

    //dp[i][j] -> true if s[i ... j] is a palindrome

    vector<vector<int>> dp(n, vector<int>(n));

    int count = 0;

    for(int i = 0; i < n; i++) {
        dp[i][i] = 1;
        count += dp[i][i];
        if(i + 1 < n) {
            dp[i][i + 1] = s[i] == s[i + 1];
            count += dp[i][i + 1];
        } 
    }

    for(int i = n - 3; i >= 0; i--) {
        for(int j = i + 2; j < n; j++) {
            if(s[i] == s[j] and dp[i + 1][j - 1]) {
                dp[i][j] = 1;
            }
            count += dp[i][j];
        }
    }

    return count;
}

bool isMatch(string s, string p) {
    
}

int main() {
    cout << isMatch("ab", ".*") << endl;
    return 0;
}