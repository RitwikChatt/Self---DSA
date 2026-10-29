#include<bits/stdc++.h>
using namespace std;

int mctFromLeafValuesOn4On2(vector<int>& arr) {
    int n = arr.size();

    vector<vector<int>> dp(n, vector<int>(n));

    for(int i = n - 2; i >= 0; i--) {
        for(int j = i + 1; j < n; j++) {
            dp[i][j] = INT_MAX;

            for(int k = i; k < j; k++) {
                int leftMax = *max_element(arr.begin() + i, arr.begin() + k + 1),
                rightMax = *max_element(arr.begin() + k + 1, arr.begin() + j + 1);

                dp[i][j] = min(dp[i][j], leftMax * rightMax + dp[i][k] + dp[k + 1][j]);
            }
        }
    }

    return dp[0][n - 1];
}

int mctFromLeafValuesOn3On2(vector<int>& arr) {
    int n = arr.size();

    vector<vector<int>> rangeMax(n, vector<int>(n));

    for(int i = 0; i < n; i++) {
        rangeMax[i][i] = arr[i];

        for(int j = i + 1; j < n; j++) {
            rangeMax[i][j] = max(rangeMax[i][j - 1], arr[j]);
        } 
    }

    vector<vector<int>> dp(n, vector<int>(n));

    for(int i = n - 2; i >= 0; i--) {
        for(int j = i + 1; j < n; j++) {
            dp[i][j] = INT_MAX;
            
            for(int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], rangeMax[i][k] * rangeMax[k + 1][j] + dp[i][k] + dp[k + 1][j]);     
            }
        }
    }

    return dp[0][n - 1];
}

int main() {
    vector<int> arr = {6,2,4};

    cout << mctFromLeafValuesOn3On2(arr) << endl;
    return 0;
}