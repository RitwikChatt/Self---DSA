#include<bits/stdc++.h>
using namespace std;

bool wordBreak(string s, vector<string>& wordDict) {
    int n = s.length();

    unordered_set<string> words(wordDict.begin(), wordDict.end());

    vector<bool> dp(n + 1);

    dp[0] = true;

    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < i; j++) {
            if(dp[j] and words.find(s.substr(j, i - j)) != words.end()) {
                dp[i] = true;
                break;
            }
        }
    }

    return dp[n];
}

int maxEnvelopes(vector<vector<int>>& envelopes) {
    int n = envelopes.size();

    sort(envelopes.begin(), envelopes.end(), [](vector<int>& a, vector<int>& b) {
        return a[0] < b[0] or (a[0] == b[0] and a[1] > b[1]);
    });

    vector<int> lis;

    for(int i = 0; i < n; i++) {
        if(lis.empty() or envelopes[i][1] > lis.back()) {
            lis.push_back(envelopes[i][1]);
        } else {
            lis[lower_bound(lis.begin(), lis.end(), envelopes[i][1]) - lis.begin()] = envelopes[i][1];
        }
    }

    return lis.size();
}

int findLongestChain(vector<vector<int>>& pairs) {
    int n = pairs.size(), lis = 1;
    
    sort(pairs.begin(), pairs.end());

    vector<int> dp(n, 1);

    for(int i = 1; i < n; i++) {
        for(int j = i - 1; j >= 0; j--) {
            if(pairs[j][1] < pairs[i][0]) {
                dp[i] = max(dp[i], 1 + dp[j]);
            }
        }

        lis = max(lis, dp[i]);
    }

    return lis;
}

int minScoreTriangulation(vector<int>& values) {
    int n = values.size();

    vector<vector<int>> dp(n, vector<int>(n));

    for(int i = n - 3; i >= 0; i--) {
        for(int j = i + 2; j < n; j++) {
            dp[i][j] = INT_MAX;
            for(int k = i + 1; k < j; k++) {
                dp[i][j] = min(dp[i][j], values[i] * values[k] * values[j] + dp[i][k] + dp[k][j]);
            }
        }
    }

    return dp[0][n - 1];
}

int main() {
    vector<int> values = {1,3,1,4,1,5};

    cout << minScoreTriangulation(values) << endl;
    return 0;
}