#include<bits/stdc++.h>
using namespace std;

bool ifTheseDifferByOneCharacter(string& a, string& b) {
    int m = a.length(), n = b.length();

    if(n - m != 1) {
        return false;
    }

    int i = 0, j = 0;

    while(i < m and j < n) {
        if(a[i] == b[j]) {
            i++;
        }
        j++;
    }

    return i == m;
}

int longestStrChain2DDP(vector<string>& words) {
    int n = words.size();

    sort(words.begin(), words.end(), [](const string& a, const string& b) {
        if(a.size() != b.size()) {
            return a.size() < b.size();
        }

        return a < b;
    });

    vector<vector<int>> dp(n + 1, vector<int>(n + 1));

    for(int i = n - 1; i >= 0; i--) {
        for(int j = i - 1; j >= -1; j--) {
            int notTake = dp[i + 1][j + 1], take = INT_MIN;

            if(j == -1 or ifTheseDifferByOneCharacter(words[j], words[i])) {
                take = 1 + dp[i + 1][i + 1];
            }

            dp[i][j + 1] = max(take, notTake);
        }
    }

    return dp[0][-1 + 1];
}

int longestStrChain1DDP(vector<string>& words) {
    int n = words.size();

    sort(words.begin(), words.end(), [](const string& a, const string& b) {
        if(a.size() != b.size()) {
            return a.size() < b.size();
        }

        return a < b;
    });

    vector<int> next(n + 1);

    for(int i = n - 1; i >= 0; i--) {
        vector<int> curr(n + 1);
        for(int j = i - 1; j >= -1; j--) {
            int notTake = next[j + 1], take = INT_MIN;

            if(j == -1 or ifTheseDifferByOneCharacter(words[j], words[i])) {
                take = 1 + next[i + 1];
            }

            curr[j + 1] = max(take, notTake);
        }

        next = curr;
    }

    return next[-1 + 1];
}

vector<int> longestIncreasingSubsequence(vector<int>& nums) {
    int n = nums.size();

    vector<int> lis(n, 1);

    for(int i = 1; i < n; i++) {
        for(int j = 0; j < i; j++) {
            if(nums[i] > nums[j]) {
                lis[i] = max(lis[i], 1 + lis[j]);
            }
        }
    }

    return lis;
}

vector<int> longestDecreasingSubsequence(vector<int>& nums) {
    int n = nums.size();

    vector<int> lds(n, 1);

    for(int i = n - 2; i >= 0; i--) {
        for(int j = i + 1; j < n; j++) {
            if(nums[i] > nums[j]) {
                lds[i] = max(lds[i], 1 + lds[j]);
            }
        }
    }

    return lds;
}

int longestBitonicSequence(int n, vector<int> &nums) {
    vector<int> lis = longestIncreasingSubsequence(nums), lds = longestDecreasingSubsequence(nums);

    int lbs = 0;

    for(int i = 0; i < n; i++) {
        if(lis[i] > 1 and lds[i] > 1) {
            lbs = max(lbs, lis[i] + lds[i] - 1);
        }
    }

    return lbs;
}

int findNumberOfLIS(vector<int>& nums) {
    int n = nums.size();

    // lis[i] -> Length of LIS ending at i
    // count[i] -> Number of increasing subsequences of length lis[i] ending at i

    vector<int> lis(n, 1), count(n, 1);

    int maxi = lis[0];

    for(int i = 1; i < n; i++) {
        for(int j = 0; j < i; j++) {
            if(nums[i] > nums[j]) {
                if(1 + lis[j] > lis[i]) {
                    lis[i] = 1 + lis[j];
                    count[i] = count[j];
                } else if(1 + lis[j] == lis[i]) {
                    count[i] += count[j];
                }
            }
        }
        maxi = max(maxi, lis[i]);
    }

    int ans = 0;

    for(int i = 0; i < n; i++) {
        if(lis[i] == maxi) {
            ans += count[i];
        }
    }

    return ans;
}

int matrixMultiplication(vector<int> &arr) {
    int n = arr.size();

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