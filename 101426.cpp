#include<bits/stdc++.h>
using namespace std;

int matrixMultiplication(vector<int> &arr) {
    int n = arr.size();

    // dp[i][j] -> Minimum operations required to multiply matrices i -> j

    vector<vector<int>> dp(n, vector<int>(n));

    for(int i = n - 2; i >= 1; i--) {
        for(int j = i + 1; j < n; j++) {
            dp[i][j] = INT_MAX;

            for(int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], arr[i - 1] * arr[k] * arr[j] + dp[i][k] + dp[k + 1][j]);
            }
        }
    }

    return dp[1][n - 1];
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 3};

    cout << matrixMultiplication(arr) << endl;
    return 0;
}