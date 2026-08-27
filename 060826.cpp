#include<bits/stdc++.h>
using namespace std;

// bool canPartition(vector<int>& nums) {
//     int sum = accumulate(nums.begin(), nums.end(), 0);

//     if(sum % 2) {
//         return false;
//     }

//     int target = sum / 2;

//     int n = nums.size();

//     //dp[i][j] -> Verdict if it is possible to make sum j using the first i elements from nums

//     vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

//     for(int i = 0; i <= n; i++) {
//         dp[i][0] = true;
//     }

//     for(int i = 1; i <= n; i++) {
//         for(int j = 1; j <= target; j++) {
//             bool notPick = dp[i - 1][j], pick = false;
//             if(j - nums[i - 1] >= 0) {
//                 pick = dp[i - 1][j - nums[i - 1]];
//             }
//             dp[i][j] = pick or notPick;
//         }
//     }

//     return dp[n][target];
// }

// bool canPartition1DDP(vector<int>& nums) {
//     int sum = accumulate(nums.begin(), nums.end(), 0);

//     if(sum % 2) {
//         return false;
//     }

//     int target = sum / 2;

//     int n = nums.size();

//     //dp[j] -> Verdict if it is possible to make sum j using the elements till this point

//     vector<bool> dp(target + 1, false);

//     dp[0] = true;

//     for(int i = 1; i <= n; i++) {
//         for(int j = target; j >= nums[i - 1]; j--) {
//             dp[j] = dp[j] or dp[j - nums[i - 1]];
//         }
//     }

//     return dp[target];
// }

int minCostClimbingStairs(vector<int>& cost) {
    int n = cost.size();

    int prevprev = 0, prev = 0, curr;

    for(int i = 2; i <= n; i++) {
        curr = min(prev + cost[i - 1], prevprev + cost[i - 2]);
        prevprev = prev;
        prev = curr;
    }

    return curr;
}

int robHelper(const vector<int>& nums) {
    int n = nums.size();

    int prevprev = nums[0];

    if(n == 1) {
        return prevprev;
    }

    int prev = max(nums[0], nums[1]);
    int curr = prev;

    for(int i = 2; i < n; i++) {
        curr = max(prevprev + nums[i], prev);
        prevprev = prev;
        prev = curr;
    }

    return curr;
}

int rob(vector<int>& nums) {
    int firstScenario = robHelper({nums.begin(), nums.end() - 1});
    int secondScenario = robHelper({nums.begin() + 1, nums.end()});

    return max(firstScenario, secondScenario);
}

int minFallingPathSum(vector<vector<int>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();

    //dp[i][j] -> Minimum path sum to reach cell (i, j)

    vector<vector<int>> dp(m, vector<int>(n));

    dp[0] = matrix[0];

    for(int i = 1; i < m; i++) {
        
        dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]) + matrix[i][0];
        dp[i][n - 1] = min(dp[i - 1][n - 1], dp[i - 1][n - 2]) + matrix[i][n - 1];

        for(int j = 1; j < n - 1; j++) {
            dp[i][j] = min({dp[i - 1][j - 1], dp[i - 1][j], dp[i - 1][j + 1]}) + matrix[i][j];
        }
    }

    return *min_element(dp[m - 1].begin(), dp[m - 1].end());
}

int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size();

    //dp[i][j] -> Minimum path sum to reach (i, j)

    vector<vector<int>> dp(n, vector<int>(n, INT_MAX));

    dp[0][0] = triangle[0][0];

    for(int i = 1; i < n; i++) {
        for(int j = 0; j <= i; j++) {
            int minTillNow = dp[i - 1][j];

            if(j - 1 >= 0) {
                minTillNow = min(minTillNow, dp[i - 1][j - 1]);
            }

            dp[i][j] = minTillNow + triangle[i][j];
        }
    }

    return *min_element(dp[n - 1].begin(), dp[n - 1].end());
}

int minimumTotal1DDP(vector<vector<int>>& triangle) {
    int n = triangle.size();

    //dp[j] -> Minimum path sum to reach jth column in current row

    vector<int> dp(n, INT_MAX);

    dp[0] = triangle[0][0];

    for(int i = 1; i < n; i++) {
        int temp;
        for(int j = 0; j <= i; j++) {
            int minTillNow = dp[j];

            if(j - 1 >= 0) {
                minTillNow = min(minTillNow, temp);
            }

            temp = dp[j];
            dp[j] = minTillNow + triangle[i][j];
        }
    }

    return *min_element(dp.begin(), dp.end());
}

int maximalSquare(vector<string>& matrix) {
    int m = matrix.size(), n = matrix[0].length();

    //dp[i][j] -> Maximum length of side of square ending at (i, j)

    vector<vector<int>> dp(m, vector<int>(n));

    dp[0][0] = matrix[0][0] - '0';

    int maxLen = dp[0][0];

    for(int i = 1; i < m; i++) {
        dp[i][0] = matrix[i][0] - '0';
        maxLen = max(maxLen, dp[i][0]);
    }

    for(int j = 1; j < n; j++) {
        dp[0][j] = matrix[0][j] - '0';
        maxLen = max(maxLen, dp[0][j]);
    }

    for(int i = 1; i < m; i++) {
        for(int j = 1; j < n; j++) {
            if(matrix[i][j] == '1') {
                dp[i][j] = 1 + min({dp[i][j - 1], dp[i - 1][j - 1], dp[i - 1][j]});
                maxLen = max(maxLen, dp[i][j]);
            }
        }
    }

    return maxLen * maxLen;
}

int coinChange(vector<int>& coins, int amount) {
    int n = coins.size();

    //dp[i][j] -> Minimum coins needed to make amount j using first i coins

    vector<vector<int>> dp(n + 1, vector<int>(amount + 1));

    for(int j = 0; j <= amount; j++) {
        dp[0][j] = INT_MAX;
    }

    for(int i = 1; i <= n; i++) {
        dp[i][0] = 0;
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= amount; j++) {
            int notPick = dp[i - 1][j], pick = INT_MAX;
            if(j - coins[i - 1] >= 0) {
                pick = 1 + dp[i][j - coins[i - 1]];
            }
            dp[i][j] = min(pick, notPick);
        }
    }

    return dp[n][amount] == INT_MAX ? -1 : dp[n][amount];
}

int coinChange1DDP(vector<int>& coins, int amount) {
    int n = coins.size();

    //dp[j] -> Minimum coins needed to make amount j using coins upto this point.

    vector<int> dp(amount + 1, INT_MAX);

    for(int i = 1; i <= n; i++) {
        dp[0] = 0;
        for(int j = 1; j <= amount; j++) {
            int notPick = dp[j], pick = INT_MAX;
            if(j - coins[i - 1] >= 0) {
                pick = 1 + dp[j - coins[i - 1]];
            }
            dp[j] = min(pick, notPick);
        }
    }

    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

int change(int amount, vector<int>& coins) {
    int n = coins.size();

    //dp[i][j] -> Number of combinations that make up amount j using first i coins

    vector<vector<int>> dp(n + 1, vector<int>(amount + 1));

    for(int j = 1; j <= amount; j++) {
        dp[0][j] = 0;
    }

    for(int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= amount; j++) {
            
            int notPick = dp[i - 1][j], pick = 0;

            if(j - coins[i - 1] >= 0) {
                pick = dp[i][j - coins[i - 1]];
            }

            dp[i][j] = pick + notPick;

        }
    }

    return dp[n][amount];
}

int change1DDP(int amount, vector<int>& coins) {
    int n = coins.size();

    //dp[j] -> Number of combinations that make up amount j using coins upto this point

    vector<int> dp(amount + 1);

    dp[0] = 1;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= amount; j++) {
            
            int notPick = dp[j], pick = 0;

            if(j - coins[i - 1] >= 0) {
                pick = dp[j - coins[i - 1]];
            }

            dp[j] = pick + notPick;
            
        }
    }

    return dp[amount];
}

bool canPartition(vector<int>& nums) {
    int sum = accumulate(nums.begin(), nums.end(), 0);

    if(sum % 2) {
        return false;
    }

    int target = sum / 2, n = nums.size();

    //dp[i][j] -> verdict if it is possibe to have a subset of nums using first i elements which has a sum equal to j

    vector<vector<int>> dp(n + 1, vector<int>(target + 1));

    for(int j = 1; j <= target; j++) {
        dp[0][j] = false;
    }

    for(int i = 0; i <= n; i++) {
        dp[i][0] = true;
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= target; j++) {
            int notPick = dp[i - 1][j], pick = false;
            if(j - nums[i - 1] >= 0) {
                pick = dp[i - 1][j - nums[i - 1]];
            }
            dp[i][j] = pick or notPick;
        }
    }

    return dp[n][target];
}

bool canPartition1DDP(vector<int>& nums) {
    int sum = accumulate(nums.begin(), nums.end(), 0);

    if(sum % 2) {
        return false;
    }

    int target = sum / 2, n = nums.size();

    //dp[j] -> verdict if it is possibe to have a subset of nums using elements upto this point which has a sum equal to j

    vector<bool> dp(target + 1);

    dp[0] = true;

    for(int i = 1; i <= n; i++) {
        for(int j = target; j >= nums[i - 1]; j--) {
            dp[j] = dp[j] or dp[j - nums[i - 1]];
        }
    }

    return dp[target];
}

int findTargetSumWays(vector<int>& nums, int target) {
    int n = nums.size();

    //dp[i][j] -> Number of expressions that can be built using first i elements from nums that sum up to j

    vector<vector<int>> dp(n + 1, vector<int>(target + 1));

    for(int j = 1; j <= target; j++) {
        dp[0][j] = 0;
    }

    for(int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= target; j++) {
            int plus = 0, minus = 0;
            
            if(j - nums[i - 1] >= 0) {
                plus = dp[i - 1][j - nums[i - 1]];
            }

            if(j + nums[i - 1] <= target) {
                minus = dp[i - 1][j + nums[i - 1]];
            }

            dp[i][j] = plus + minus;
        }
    }

    return dp[n][target];
}

int main() {
    vector<int> nums = {1,5,11,5};
    int target = 3;

    cout << findTargetSumWays(nums, target) << endl;

    return 0;
}