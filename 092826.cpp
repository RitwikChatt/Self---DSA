#include<bits/stdc++.h>
using namespace std;

int knapSack2DDP(vector<int>& val, vector<int>& wt, int capacity) {
    int n = val.size();

    //dp[i][j] -> Maximum value that can be achieved if we can choose items 
    // in the range 0 - i using a bag of maximum capacity j

    vector<vector<int>> dp(n, vector<int>(capacity + 1));

    for(int j = 0; j <= capacity; j++) {
        dp[0][j] = val[0] * (j / wt[0]);
    }

    for(int i = 1; i < n; i++) {
        for(int j = 1; j <= capacity; j++) {
            dp[i][j] = dp[i - 1][j];

            if(j - wt[i] >= 0) {
                dp[i][j] = max(dp[i][j], val[i] + dp[i][j - wt[i]]);
            }
        }
    }

    return dp[n - 1][capacity];
}

int knapSack1DDP(vector<int>& val, vector<int>& wt, int capacity) {
    int n = val.size();

    //dp[j] -> Maximum value that can be achieved if we can choose items 
    // till this point using a bag of maximum capacity j

    vector<int> dp(capacity + 1);

    for(int j = 0; j <= capacity; j++) {
        dp[j] = val[0] * (j / wt[0]);
    }

    for(int i = 1; i < n; i++) {
        for(int j = wt[i]; j <= capacity; j++) {
            dp[j] = max(dp[j], val[i] + dp[j - wt[i]]);
        }
    }

    return dp[capacity];
}

int cutRod(vector<int> &price) {
    
}

int main() {
    vector<int> price = {1, 5, 8, 9, 10, 17, 17, 20};

    cout << cutRod(price) << endl;
    return 0;
}