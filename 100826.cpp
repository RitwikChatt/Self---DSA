#include<bits/stdc++.h>
using namespace std;

int maxProfit5(vector<int>& prices) {
    int n = prices.size();

    vector<vector<int>> dp(n, vector<int>(2));

    dp[0][1] = -prices[0];

    for(int day = 1; day < n; day++) {
        dp[day][0] = max(dp[day - 1][0], prices[day] + dp[day - 1][1]);

        int prevFree = (day - 2 >= 0) ? dp[day - 2][0] : 0;
        dp[day][1] = max(dp[day - 1][1], -prices[day] + prevFree);
    }

    return dp[n - 1][0];
}

int maxProfit62DDP(vector<int>& prices, int fee) {
    int days = prices.size();

    vector<vector<int>> dp(days, vector<int>(2));

    dp[0][1] = -prices[0] - fee;

    for(int day = 1; day < days; day++) {
        dp[day][0] = max(dp[day - 1][0], prices[day] + dp[day - 1][1]);
        dp[day][1] = max(dp[day - 1][1], -prices[day] - fee + dp[day - 1][0]);
    }

    return dp[days - 1][0];
}

int maxProfit61DDP(vector<int>& prices, int fee) {
    int days = prices.size();

    vector<int> prev(2);

    prev[1] = -prices[0] - fee;

    for(int day = 1; day < days; day++) {
        vector<int> curr(2);

        curr[0] = max(prev[0], prices[day] + prev[1]);
        curr[1] = max(prev[1], -prices[day] - fee + prev[0]);

        prev = curr;
    }

    return prev[0];
}

int maxProfit33DDP(vector<int> &prices) {
    int days = prices.size();

    vector<vector<vector<int>>> dp(days, vector<vector<int>>(2, vector<int>(3, INT_MIN)));

    dp[0][0][0] = 0;
    dp[0][1][0] = -prices[0];

    for(int day = 1; day < days; day++) {
        for(int transaction = 0; transaction <= 2; transaction++) {
            dp[day][0][transaction] = dp[day - 1][0][transaction];

            if(transaction - 1 >= 0 and dp[day - 1][1][transaction - 1] != INT_MIN) {
                dp[day][0][transaction] = max(dp[day][0][transaction], prices[day] + dp[day - 1][1][transaction - 1]);
            }

            dp[day][1][transaction] = dp[day - 1][1][transaction];

            if(dp[day - 1][0][transaction] != INT_MIN) {
                dp[day][1][transaction] = max(dp[day][1][transaction], -prices[day] + dp[day - 1][0][transaction]);
            }
        }
    }

    return max({dp[days - 1][0][0], dp[days - 1][0][1], dp[days - 1][0][2]});
}

int maxProfit32DDP(vector<int> &prices) {
    int days = prices.size();

    vector<vector<int>> prev(2, vector<int>(3, INT_MIN));

    prev[0][0] = 0;
    prev[1][0] = -prices[0];

    for(int day = 1; day < days; day++) {
        vector<vector<int>> curr(2, vector<int>(3, INT_MIN));

        for(int transaction = 0; transaction <= 2; transaction++) {
            curr[0][transaction] = prev[0][transaction];

            if(transaction - 1 >= 0 and prev[1][transaction - 1] != INT_MIN) {
                curr[0][transaction] = max(curr[0][transaction], prices[day] + prev[1][transaction - 1]);
            }

            curr[1][transaction] = prev[1][transaction];

            if(prev[0][transaction] != INT_MIN) {
                curr[1][transaction] = max(curr[1][transaction], -prices[day] + prev[0][transaction]);
            }
        }

        prev = curr;
    }

    return max({prev[0][0], prev[0][1], prev[0][2]});
}

int maxProfit42DDP(vector<int> &prices, int k) {
    int days = prices.size();

    vector<vector<int>> prev(2, vector<int>(k + 1, INT_MIN));

    prev[0][0] = 0;
    prev[1][0] = -prices[0];

    for(int day = 1; day < days; day++) {
        vector<vector<int>> curr(2, vector<int>(k + 1, INT_MIN));

        for(int transaction = 0; transaction <= k; transaction++) {
            curr[0][transaction] = prev[0][transaction];

            if(transaction - 1 >= 0 and prev[1][transaction - 1] != INT_MIN) {
                curr[0][transaction] = max(curr[0][transaction], prices[day] + prev[1][transaction - 1]);
            }

            curr[1][transaction] = prev[1][transaction];

            if(prev[0][transaction] != INT_MIN) {
                curr[1][transaction] = max(curr[1][transaction], -prices[day] + prev[0][transaction]);
            }
        }

        prev = curr;
    }

    int ans = INT_MIN;

    for(int transaction = 0; transaction <= k; transaction++) {
        ans = max(ans, prev[0][transaction]);
    }

    return ans;
}

int lengthOfLISBruteforce(vector<int>& nums) {
    int n = nums.size(), lis = INT_MIN;

    for(int i = 0; i < (1 << n); i++) {
        vector<int> subsequence;
        
        for(int j = 0; j < n; j++) {
            if(i & (1 << j)) {
                subsequence.push_back(nums[j]);
            }
        }

        bool increasing = true;
        int len = 1;

        for(int j = 1; j < subsequence.size(); j++) {
            if(subsequence[j] <= subsequence[j - 1]) {
                increasing = false;
                break;
            }
            len++;
        }

        if(increasing) {
            lis = max(lis, len);
        }
    }

    return lis;
}

int lengthOfLIS2DDP(vector<int>& nums) {
    int n = nums.size();

    // dp[i][j] -> Length of LIS starting from the ith index 
    // where j is the index of the previously selected element.

    vector<vector<int>> dp(n + 1, vector<int>(n + 1));

    for(int i = n - 1; i >= 0; i--) {
        for(int j = i - 1; j >= -1; j--) {
            int notTake = dp[i + 1][j + 1], take = INT_MIN;

            if(j == -1 or nums[i] > nums[j]) {
                take = 1 + dp[i + 1][i + 1];
            }

            dp[i][j + 1] = max(notTake, take);
        }
    }

    return dp[0][0];
}

int lengthOfLIS1DDP(vector<int>& nums) {
    int n = nums.size();

    vector<int> next(n + 1);

    for(int i = n - 1; i >= 0; i--) {
        vector<int> curr(n + 1);
        for(int j = i - 1; j >= -1; j--) {
            int notTake = next[j + 1], take = INT_MIN;

            if(j == -1 or nums[i] > nums[j]) {
                take = 1 + next[i + 1];
            }

            curr[j + 1] = max(notTake, take);
        }

        next = curr;
    }

    return next[0];
}

int main() {
    
    return 0;
}