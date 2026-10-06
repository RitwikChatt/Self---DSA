#include<bits/stdc++.h>
using namespace std;

int longestCommonSubsequence2DDP(string text1, string text2) {
    int m = text1.length(), n = text2.length();

    if(m == 0 or n == 0) return 0;

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

    string lcs = "";

    for(int i = 0; i < dp[m - 1][n - 1]; i++) {
        lcs += '$';
    }

    int i = m - 1, j = n - 1, index = dp[m - 1][n - 1] - 1;

    while(i >= 0 and j >= 0) {
        if(text1[i] == text2[j]) {
            lcs[index] = text1[i];
            index--;
            i--, j--;
        } else if(i == 0) {
            j--;
        } else if(j == 0) {
            i--;
        } else if(dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    cout << lcs << endl;

    return dp[m - 1][n - 1];
}

int longCommSubstr2DDP(string& s1, string& s2) {
    int m = s1.length(), n = s2.length();

    //dp[i][j] -> length of the longest common substring ending exactly at s1[i] and s2[j].

    vector<vector<int>> dp(m, vector<int>(n));

    int lcs = INT_MIN;

    for(int j = 0; j < n; j++) {
        dp[0][j] = (s1[0] == s2[j]);
        lcs = max(lcs, dp[0][j]);
    }

    for(int i = 0; i < m; i++) {
        dp[i][0] = (s1[i] == s2[0]);
        lcs = max(lcs, dp[i][0]);
    }

    for(int i = 1; i < m; i++) {
        for(int j = 1; j < n; j++) {
            if(s1[i] == s2[j]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
                lcs = max(lcs, dp[i][j]);
            }
        }
    }

    return lcs;
}

int longCommSubstr1DDP(string& s1, string& s2) {
    int m = s1.length(), n = s2.length();

    //dp[j] -> length of the longest common substring ending exactly at s1[curr] and s2[j].

    vector<int> dp(n);

    int lcs = INT_MIN;

    for(int j = 0; j < n; j++) {
        dp[j] = (s1[0] == s2[j]);
        lcs = max(lcs, dp[j]);
    }

    for(int i = 1; i < m; i++) {
        vector<int> temp(n);
        temp[0] = (s1[i] == s2[0]);
        lcs = max(lcs, temp[0]);

        for(int j = 1; j < n; j++) {
            if(s1[i] == s2[j]) {
                temp[j] = 1 + dp[j - 1];
                lcs = max(lcs, temp[j]);
            }
        }

        dp = temp;
    }

    return lcs;
}

int longestCommonSubsequence(string& s1, string& s2) {
    int m = s1.length(), n = s2.length();

    //dp[j] -> Length of LCS in text1[0 ... curr] and text2[0 ... j]

    vector<int> dp(n);

    dp[0] = (s1[0] == s2[0]);

    for(int j = 1; j < n; j++) {
        if(s1[0] == s2[j]) {
            dp[j] = 1;
        } else {
            dp[j] = dp[j - 1];
        }
    }

    for(int i = 1; i < m; i++) {
        vector<int> temp(n);

        if(s1[i] == s2[0]) {
            temp[0] = 1;    
        } else {
            temp[0] = dp[0];
        }

        for(int j = 1; j < n; j++) {
            if(s1[i] == s2[j]) {
                temp[j] = 1 + dp[j - 1];
            } else {
                temp[j] = max(dp[j], temp[j - 1]);
            }
        }

        dp = temp;
    }

    return dp[n - 1];
}

int longestPalindromeSubseq(string s) {
    string revS = s;

    reverse(revS.begin(), revS.end());

    return longestCommonSubsequence(s, revS);
}

int findMinInsertions(string &s) {
    return s.length() - longestPalindromeSubseq(s);
}

int minOperations(string &s1, string &s2) {
    return s1.length() + s2.length() - 2 * longestCommonSubsequence(s1, s2);
}

int minSuperSeq(string &s1, string &s2) {
    return s1.length() + s2.length() - longestCommonSubsequence(s1, s2);
}

string shortestCommonSupersequence(string str1, string str2) {
    int m = str1.length(), n = str2.length();

    //dp[i][j] -> LCS of substring of str1 of length i and substring of str2 of length j.

    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(str1[i - 1] == str2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    string scs = "";

    int lenSCS = m + n - dp[m][n];

    for(int i = 0; i < lenSCS; i++) scs += '$';

    int i = m, j = n, index = lenSCS - 1;

    while(i and j) {
        if(str1[i - 1] == str2[j - 1]) {
            scs[index] = str1[i - 1];
            i--, j--;
        } else if(dp[i - 1][j] > dp[i][j - 1]) {
            scs[index] = str1[i - 1];
            i--;
        } else {
            scs[index] = str2[j - 1];
            j--;
        }

        index--;
    }

    while(i) {
        scs[index] = str1[i - 1];
        index--;
        i--;
    }

    while(j) {
        scs[index] = str2[j - 1];
        index--;
        j--;
    }

    return scs;
}

int numDistinct(string s, string t) {
    
}

int main() {
    string s = "babgbag", t = "bag";

    cout << numDistinct(s, t) << endl;
    return 0;
}