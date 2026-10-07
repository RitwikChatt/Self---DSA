#include<bits/stdc++.h>
using namespace std;

int numDistinct2DDP(string s, string t) {
    int m = s.length(), n = t.length();

    //dp[i][j] -> Number of distinct subsequences of s[0 ... i] that match t[0 ... j]

    vector<vector<unsigned long long>> dp(m, vector<unsigned long long>(n));

    dp[0][0] = (s[0] == t[0]);

    for(int i = 1; i < m; i++) {
        dp[i][0] = dp[i - 1][0];

        if(s[i] == t[0]) {
            dp[i][0]++;
        }
    }

    for(int i = 1; i < m; i++) {
        for(int j = 1; j < n; j++) {
            if(s[i] == t[j]) {
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return dp[m - 1][n - 1];
}

int numDistinct1DDP(string s, string t) {
    int m = s.length(), n = t.length();

    vector<unsigned long long> prev(n);

    prev[0] = (s[0] == t[0]);

    for(int i = 1; i < m; i++) {
        vector<unsigned long long> curr(n);

        curr[0] = prev[0];

        if(s[i] == t[0]) {
            curr[0]++;
        }

        for(int j = 1; j < n; j++) {
            if(s[i] == t[j]) {
                curr[j] = prev[j - 1] + prev[j];
            } else {
                curr[j] = prev[j];
            }
        }

        prev = curr;
    }

    return prev[n - 1];
}

int minDistance2DDP(string word1, string word2) {
    int m = word1.length(), n = word2.length();

    if(m < n) {
        return minDistance2DDP(word2, word1);
    }

    //dp[i][j] -> Minimum number of operations required to convert word1[0 ... i-1] to word2[0 ... j-1]

    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for(int j = 1; j <= n; j++) dp[0][j] = j;

    for(int i = 1; i <= m; i++) dp[i][0] = i;

    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(word1[i - 1] != word2[j - 1]) {
                dp[i][j] = 1 + min({dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]});
            } else {
                dp[i][j] = dp[i - 1][j - 1];
            }
        }
    }

    return dp[m][n];
}

int minDistance1DDP(string word1, string word2) {
    int m = word1.length(), n = word2.length();

    if(m < n) {
        return minDistance1DDP(word2, word1);
    }

    vector<int> prev(n + 1);

    for(int j = 1; j <= n; j++) prev[j] = j;

    for(int i = 1; i <= m; i++) {
        vector<int> curr(n + 1);
        curr[0] = i;

        for(int j = 1; j <= n; j++) {
            if(word1[i - 1] != word2[j - 1]) {
                curr[j] = 1 + min({curr[j - 1], prev[j], prev[j - 1]});
            } else {
                curr[j] = prev[j - 1];
            }
        }

        prev = curr;
    }

    return prev[n];
}

bool isMatch2DDP(string s, string p) {
    int m = s.length(), n = p.length();

    //dp[i][j] -> true if first i characters in s matches the first j characters in p

    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));

    dp[0][0] = true;
    dp[0][1] = (p[0] == '*');

    for(int j = 2; j <= n; j++) {
        dp[0][j] = dp[0][j - 1] and (p[j - 1] == '*');
    }

    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if((s[i - 1] == p[j - 1]) or (p[j - 1] == '?')) {
                dp[i][j] = dp[i - 1][j - 1];
            } else if(p[j - 1] == '*') {
                dp[i][j] = dp[i][j - 1] or dp[i - 1][j];
            }
        }
    }

    return dp[m][n];
}

bool isMatch1DDP(string s, string p) {
    int m = s.length(), n = p.length();

    vector<bool> prev(n + 1);

    prev[0] = true;
    prev[1] = (p[0] == '*');

    for(int j = 2; j <= n; j++) {
        prev[j] = prev[j - 1] and (p[j - 1] == '*');
    }

    for(int i = 1; i <= m; i++) {
        vector<bool> curr(n + 1);
    
        for(int j = 1; j <= n; j++) {
            if((s[i - 1] == p[j - 1]) or (p[j - 1] == '?')) {
                curr[j] = prev[j - 1];
            } else if(p[j - 1] == '*') {
                curr[j] = curr[j - 1] or prev[j];
            }
        }

        prev = curr;
    }

    return prev[n];
}

int maxProfit1(vector<int>& prices) {
    int prefixMin = prices[0], profit = 0;

    for(int i = 1; i < prices.size(); i++) {
        profit = max(profit, prices[i] - prefixMin);
        prefixMin = min(prefixMin, prices[i]);
    }

    return profit;
}

int maxProfit22DDP(vector<int>& prices) {
    int n = prices.size();

    // dp[i][0] -> Maximum profit that can be achieved on the ith day provided we 
    // are not holding the stock at the end of the day.
    // dp[i][1] -> Maximum profit that can be achieved on the ith day provided we
    // are holding the stock at the end of the day.

    vector<vector<int>> dp(n, vector<int>(2));

    dp[0][1] = -prices[0];

    for(int i = 1; i < n; i++) {
        dp[i][0] = max(dp[i - 1][0], prices[i] + dp[i - 1][1]);
        dp[i][1] = max(dp[i - 1][1], -prices[i] + dp[i - 1][0]);
    }

    return max(dp[n - 1][0], dp[n - 1][1]);
}

int maxProfit21DDP(vector<int>& prices) {
    int n = prices.size();

    vector<int> prev(2);

    prev[1] = -prices[0];

    for(int i = 1; i < n; i++) {
        vector<int> curr(2);

        curr[0] = max(prev[0], prices[i] + prev[1]);
        curr[1] = max(prev[1], -prices[i] + prev[0]);

        prev = curr;
    }

    return max(prev[0], prev[1]);
}

int maxProfit33DDP(vector<int>& prices) {
    int n = prices.size();

    vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(3, INT_MIN)));

    dp[0][0][0] = 0;
    dp[0][1][0] = -prices[0];

    for(int i = 1; i < n; i++) {
        for(int k = 0; k <= 2; k++) {
            dp[i][0][k] = dp[i - 1][0][k];

            if(k - 1 >= 0 and dp[i - 1][1][k - 1] != INT_MIN) {
                dp[i][0][k] = max(dp[i][0][k], prices[i] + dp[i - 1][1][k - 1]);
            }

            dp[i][1][k] = dp[i - 1][1][k];

            if(dp[i - 1][0][k] != INT_MIN) {
                dp[i][1][k] = max(dp[i][1][k], -prices[i] + dp[i - 1][0][k]);
            }
        }
    }

    return max({dp[n - 1][0][0], dp[n - 1][0][1], dp[n - 1][0][2]});
}

int maxProfit32DDP(vector<int>& prices) {
    int n = prices.size();

    vector<vector<int>> prev(2, vector<int>(3, INT_MIN));

    prev[0][0] = 0;
    prev[1][0] = -prices[0];

    for(int i = 1; i < n; i++) {
        vector<vector<int>> curr(2, vector<int>(3, INT_MIN));

        for(int k = 0; k <= 2; k++) {
            curr[0][k] = prev[0][k];

            if(k - 1 >= 0 and prev[1][k - 1] != INT_MIN) {
                curr[0][k] = max(curr[0][k], prices[i] + prev[1][k - 1]);
            }

            curr[1][k] = prev[1][k];

            if(prev[0][k] != INT_MIN) {
                curr[1][k] = max(curr[1][k], -prices[i] + prev[0][k]);
            }
        }

        prev = curr;
    }

    return max({prev[0][0], prev[0][1], prev[0][2]});
}

int maxProfit42DDP(int k, vector<int>& prices) {
    int n = prices.size();

    vector<vector<int>> prev(2, vector<int>(k + 1, INT_MIN));

    prev[0][0] = 0;
    prev[1][0] = -prices[0];

    for(int i = 1; i < n; i++) {
        vector<vector<int>> curr(2, vector<int>(k + 1, INT_MIN));

        for(int trans = 0; trans <= k; trans++) {
            curr[0][trans] = prev[0][trans];

            if(trans - 1 >= 0 and prev[1][trans - 1] != INT_MIN) {
                curr[0][trans] = max(curr[0][trans], prices[i] + prev[1][trans - 1]);
            }

            curr[1][trans] = prev[1][trans];

            if(prev[0][trans] != INT_MIN) {
                curr[1][trans] = max(curr[1][trans], -prices[i] + prev[0][trans]);
            }
        }

        prev = curr;
    }

    int ans = INT_MIN;

    for(int trans = 0; trans <= k; trans++) {
        ans = max(ans, prev[0][trans]);
    }

    return ans;
}

int main() {
    int k = 2;
    vector<int> prices = {3,2,6,5,0,3};

    cout << maxProfit42DDP(k, prices) << endl;
    return 0;
}