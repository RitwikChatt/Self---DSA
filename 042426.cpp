#include<bits/stdc++.h>
using namespace std;

int nthUglyNumber(int n) {
    //dp[i] -> i-th ugly number

    vector<int> dp(n + 1);
    dp[1] = 1;

    int i2, i3, i5;
    i2 = i3 = i5 = 1;

    for(int i = 2; i <= n; i++) {
        dp[i] = min({2 * dp[i2], 3 * dp[i3], 5 * dp[i5]});

        if(dp[i] == 2 * dp[i2]) {
            i2++;
        }

        if(dp[i] == 3 * dp[i3]) {
            i3++;
        }

        if(dp[i] == 5 * dp[i5]) {
            i5++;
        }
    }

    return dp[n];
}

int subarraySumBrute(vector<int>& nums, int k) {
    int count = 0, n = nums.size();

    for(int i = 0; i < n; i++) {
        int sum = 0;
        for(int j = i; j < n; j++) {
            sum += nums[j];
            if(sum == k) {
                count++;
            }
        }
    }

    return count;
}

int subarraySumOptimal(vector<int>& nums, int k) {
    int n = nums.size(), count = 0;
    unordered_map<int, int> subArraySumFrequencyMapping;

    subArraySumFrequencyMapping[0] = 1;
    int sum = 0;

    for(int i = 0; i < n; i++) {
        sum += nums[i];
        count += subArraySumFrequencyMapping[sum - k];
        subArraySumFrequencyMapping[sum]++;
    }

    return count;
}

vector<int> twoSumBrute(vector<int>& numbers, int target) {
    int n = numbers.size();

    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(numbers[i] + numbers[j] == target) {
                return {i + 1, j + 1};
            }
        }
    }

    return {-1, -1};
}

vector<int> twoSumOptimal(vector<int>& numbers, int target) {
    int n = numbers.size();
    int l = 0, r = n - 1;

    while(l < r) {
        int sum = numbers[l] + numbers[r];

        if(sum == target) {
            break;
        } else if(sum > target) {
            r--;
        } else {
            l++;
        }
    }

    return {l + 1, r + 1};
}

int findPairs(vector<int>& nums, int k) {
    
}

int main() {
    vector<int> nums = {3,1,4,1,5};
    int k = 2;
    cout << findPairs(nums, k) << endl;
    return 0;
}