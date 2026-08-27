#include<bits/stdc++.h>
using namespace std;

bool isSubsetSumUtil(int idx, int s, vector<int>& arr, int sum) {
    if(s == sum) {
        return true;
    }

    if(idx == arr.size() or s > sum) {
        return false;
    }

    return isSubsetSumUtil(idx + 1, s + arr[idx], arr, sum) or isSubsetSumUtil(idx + 1, s, arr, sum);
}

bool isSubsetSum(vector<int>& arr, int sum) {
    int n = arr.size();

    //dp[i][j] -> Verdict if there exists a subsequence in arr[0 ... i] with a sum equal to j

    vector<vector<bool>> dp(n, vector<bool>(sum + 1));

    for(int i = 0; i < n; i++) {
        dp[i][0] = true;
    }

    for(int j = 1; j <= sum; j++) {
        dp[0][j] = (arr[0] == j);
    }

    for(int i = 1; i < n; i++) {
        for(int j = 1; j <= sum; j++) {
            dp[i][j] = dp[i - 1][j];

            if(j - arr[i] >= 0) {
                dp[i][j] = dp[i][j] or dp[i - 1][j - arr[i]];
            }
        }
    }

    return dp[n - 1][sum];
}

int main() {
    vector<int> arr = {3, 34, 4, 12, 5, 2};
    int sum = 9;

    isSubsetSum(arr, sum) ? cout << "true" : cout << "false";

    return 0;
}