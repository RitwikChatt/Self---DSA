#include<bits/stdc++.h>
using namespace std;

bool isSubsetSum2DDP(vector<int>& arr, int sum) {
    int n = arr.size();

    //dp[i][j] -> true if arr[0 ... i] has a subsequence with sum j

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

bool isSubsetSum1DDP(vector<int>& arr, int sum) {
    int n = arr.size();

    //dp[j] -> true if we have a subsequence with sum j till current index

    vector<bool> dp(sum + 1);

    dp[0] = true;

    for(int j = 1; j <= sum; j++) {
        dp[j] = (arr[0] == j);
    }

    for(int i = 1; i < n; i++) {
        vector<bool> temp(sum + 1);
        temp[0] = true;
        for(int j = 1; j <= sum; j++) {
            temp[j] = dp[j];

            if(j - arr[i] >= 0) {
                temp[j] = temp[j] or dp[j - arr[i]];
            }
        }
        dp = temp;
    }

    return dp[sum];
}

bool canPartition(vector<int>& nums) {
    int sum = accumulate(nums.begin(), nums.end(), 0);

    return (sum % 2 == 0) and isSubsetSum1DDP(nums, sum / 2);
}

int minDifference(vector<int>& arr) {
    int n = arr.size();

    //dp[j] -> True if we can have a subsequence with a sum j till current index

    int totalSum = accumulate(arr.begin(), arr.end(), 0);

    vector<bool> dp(totalSum + 1);

    dp[0] = true;

    for(int num : arr) {
        for(int j = totalSum; j >= num; j--) {
            dp[j] = dp[j] or dp[j - num];   
        }
    }

    int minDiff = INT_MAX;

    for(int s1 = 0; s1 <= totalSum / 2; s1++) {
        if(dp[s1]) {
            int s2 = totalSum - s1;
            minDiff = min(minDiff, abs(s1 - s2));
        }
    }

    return minDiff;
}

int perfectSum2DDP(vector<int>& arr, int target) {
    int n = arr.size();

    //dp[i][j] -> Count of subsets in arr[0 ... i] with a sum equal to j

    vector<vector<int>> dp(n, vector<int>(target + 1));

    dp[0][0] = (arr[0] == 0) ? 2 : 1;

    for(int j = 1; j <= target; j++) {
        dp[0][j] = (arr[0] == j);
    }

    for(int i = 1; i < n; i++) {
        for(int j = 0; j <= target; j++) {
            dp[i][j] = dp[i - 1][j];

            if(j - arr[i] >= 0) {
                dp[i][j] += dp[i - 1][j - arr[i]];
            }
        }
    }

    return dp[n - 1][target];
}

int perfectSum1DDP(vector<int>& arr, int target) {
    int n = arr.size();

    //dp[j] -> Count of subsets till current index with a sum equal to j

    vector<int> dp(target + 1);

    dp[0] = 1;

    for(int num : arr) {
        for(int j = target; j >= num; j--) {
            dp[j] += dp[j - num];
        }
    }

    return dp[target];
}

int main() {
    vector<int> arr = {5, 2, 3, 10, 6, 8};
    int target = 10;

    cout << perfectSum1DDP(arr, target) << endl;
    return 0;
}