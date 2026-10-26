#include<bits/stdc++.h>
using namespace std;

int paintWalls2DDP(vector<int>& cost, vector<int>& time) {
    int n = cost.size();

    vector<vector<int>> dp(n + 1, vector<int>(n + 1));

    for(int j = 1; j <= n; j++) {
        dp[0][j] = INT_MAX;
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            int skip = dp[i - 1][j], pay = INT_MAX;

            if(dp[i - 1][max(0, j - 1 - time[i - 1])] != INT_MAX) {
                pay = cost[i - 1] + dp[i - 1][max(0, j - 1 - time[i - 1])];
            }

            dp[i][j] = min(skip, pay);
        }
    }

    return dp[n][n];
}

int paintWalls1DDP(vector<int>& cost, vector<int>& time) {
    int n = cost.size();

    vector<int> prev(n + 1, INT_MAX);

    prev[0] = 0;

    for(int i = 1; i <= n; i++) {
        vector<int> curr(n + 1);

        for(int j = 1; j <= n; j++) {
            int skip = prev[j], pay = INT_MAX;

            if(prev[max(0, j - 1 - time[i - 1])] != INT_MAX) {
                pay = cost[i - 1] + prev[max(0, j - 1 - time[i - 1])];
            }

            curr[j] = min(skip, pay);
        }

        prev = curr;
    }

    return prev[n];
}

bool isMatch2DDP(string s, string p) {
    int m = s.length(), n = p.length();

    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));

    dp[0][0] = true;

    for(int j = 2; j <= n; j++) {
        dp[0][j] = dp[0][j - 2] and (p[j - 1] == '*');
    }

    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(s[i - 1] == p[j - 1] or p[j - 1] == '.') {
                dp[i][j] = dp[i - 1][j - 1];
            } else if(p[j - 1] == '*') {
                dp[i][j] = dp[i][j - 2];

                if(s[i - 1] == p[j - 2] or p[j - 2] == '.') {
                    dp[i][j] = dp[i][j] or dp[i - 1][j];
                }
            }
        }
    }

    return dp[m][n];
}

bool isMatch1DDP(string s, string p) {
    int m = s.length(), n = p.length();

    vector<bool> prev(n + 1);

    prev[0] = true;

    for(int j = 2; j <= n; j++) {
        prev[j] = prev[j - 2] and (p[j - 1] == '*');
    }

    for(int i = 1; i <= m; i++) {
        vector<bool> curr(n + 1);

        for(int j = 1; j <= n; j++) {
            if(s[i - 1] == p[j - 1] or p[j - 1] == '.') {
                curr[j] = prev[j - 1];
            } else if(p[j - 1] == '*') {
                curr[j] = curr[j - 2];

                if(s[i - 1] == p[j - 2] or p[j - 2] == '.') {
                    curr[j] = curr[j] or prev[j];
                }
            }
        }

        prev = curr;
    }

    return prev[n];
}

bool isInterleave2DDP(string s1, string s2, string s3) {
    int m = s1.length(), n = s2.length();

    if(m + n != s3.length()) return false;

    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));

    dp[0][0] = true;

    for(int i = 1; i <= m; i++) dp[i][0] = dp[i - 1][0] and (s1[i - 1] == s3[i - 1]);

    for(int j = 1; j <= n; j++) dp[0][j] = dp[0][j - 1] and (s2[j - 1] == s3[j - 1]);

    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            dp[i][j] = ((s1[i - 1] == s3[i + j - 1]) and dp[i - 1][j]) 
                or ((s2[j - 1] == s3[i + j - 1]) and dp[i][j - 1]);
        }
    }

    return dp[m][n];
}

bool isInterleave1DDP(string s1, string s2, string s3) {
    int m = s1.length(), n = s2.length();

    if(m + n != s3.length()) return false;

    vector<bool> prev(n + 1);

    prev[0] = true;

    for(int j = 1; j <= n; j++) prev[j] = prev[j - 1] and (s2[j - 1] == s3[j - 1]);

    for(int i = 1; i <= m; i++) {
        vector<bool> curr(n + 1);
        curr[0] = prev[0] and (s1[i - 1] == s3[i - 1]);

        for(int j = 1; j <= n; j++) {
            curr[j] = ((s1[i - 1] == s3[i + j - 1]) and prev[j]) or 
                ((s2[j - 1] == s3[i + j - 1]) and curr[j - 1]);
        }

        prev = curr;
    }

    return prev[n];
}

int main() {
    string s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac";

    isInterleave1DDP(s1, s2, s3) ? cout << "true" : cout << "false";
    return 0;
}