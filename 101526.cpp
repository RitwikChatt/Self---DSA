#include<bits/stdc++.h>
using namespace std;

int minCost(int n, vector<int>& cuts) {
    vector<vector<int>> dp(n + 1, vector<int>(n + 1));

    for(int i = n - 1; i >= 0; i--) {
        for(int j = i + 1; j <= n; j++) {
            dp[i][j] = INT_MAX;

            for(int k = 0; k < cuts.size(); k++) {
                if(cuts[k] > i and cuts[k] < j) {
                    dp[i][j] = min(dp[i][j], j - i + dp[i][cuts[k]] + dp[cuts[k]][j]);
                }
            }

            if(dp[i][j] == INT_MAX) {
                dp[i][j] = 0;
            }
        }
    }

    return dp[0][n];
}

int minCostOptimal(int n, vector<int>& cuts) {
    sort(cuts.begin(), cuts.end());
    cuts.insert(cuts.begin(), 0);
    cuts.push_back(n);

    int m = cuts.size();

    vector<vector<int>> dp(m - 1, vector<int>(m));

    for(int i = m - 2; i >= 0; i--) {
        for(int j = i + 1; j < m; j++) {
            dp[i][j] = INT_MAX;

            for(int k = i + 1; k < j; k++) {
                dp[i][j] = min(dp[i][j], cuts[j] - cuts[i] + dp[i][k] + dp[k][j]);
            }

            if(dp[i][j] == INT_MAX) {
                dp[i][j] = 0;
            }
        }
    }

    return dp[0][m - 1];
}

int maxCoins(vector<int>& nums) {
    
}

int main() {
    vector<int> nums = {3,1,5,8};

    cout << maxCoins(nums) << endl;
    return 0;
}