#include<bits/stdc++.h>
using namespace std;

int maxCoins(vector<int>& nums) {
    nums.insert(nums.begin(), 1);
    nums.push_back(1);

    int n = nums.size();

    vector<vector<int>> dp(n, vector<int>(n));

    for(int i = n - 2; i >= 1; i--) {
        for(int j = i; j <= n - 2; j++) {
            for(int k = i; k <= j; k++) {
                dp[i][j] = max(dp[i][j], nums[i - 1] * nums[k] * nums[j + 1] + dp[i][k - 1] + dp[k + 1][j]);
            }
        }
    }

    return dp[1][n - 2];
}

int main() {
    vector<int> nums = {3,1,5,8};

    cout << maxCoins(nums) << endl;
    return 0;
}