#include<bits/stdc++.h>
using namespace std;

int minTrioDegree(int n, vector<vector<int>>& edges) {
    vector<vector<int>> adjMat(n + 1, vector<int>(n + 1));
    vector<int> neighbours(n + 1);

    for(auto edge : edges) {
        int u = edge[0], v = edge[1];

        adjMat[u][v] = 1;
        adjMat[v][u] = 1;

        neighbours[u]++, neighbours[v]++;
    }

    int degree = INT_MAX;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(adjMat[i][j]) {
                for(int k = 1; k <= n; k++) {
                    if(k == j) {
                        continue;
                    }

                    if(adjMat[i][k] and adjMat[k][j]) {
                        degree = min(degree, neighbours[i] + neighbours[j] + neighbours[k] - 6);
                    }
                }
            }
        }
    }

    return degree == INT_MAX ? -1 : degree;
}

int lengthOfLIS2DDP(vector<int>& nums) {
    int n = nums.size();

    //dp[i][j + 1] -> Length of LIS starting from i where j is the element selected previously.

    vector<vector<int>> dp(n + 1, vector<int>(n + 1));

    for(int i = n - 1; i >= 0; i--) {
        for(int j = i - 1; j >= -1; j--) {
            int notTake = dp[i + 1][j + 1], take = INT_MIN;

            if(j == -1 or nums[i] > nums[j]) {
                take = 1 + dp[i + 1][i + 1];
            }

            dp[i][j + 1] = max(take, notTake);
        }
    }

    return dp[0][-1 + 1];
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

            curr[j + 1] = max(take, notTake);
        }

        next = curr;
    }

    return next[-1 + 1];
}

int lengthOfLIS1DDP2ndMethod(vector<int>& nums) {
    int n = nums.size(), lis = INT_MIN, lastIndex;

    //dp[i] -> Length of LIS ending at index i

    vector<int> dp(n, 1), hash(n);

    for(int i = 1; i < n; i++) {
        hash[i] = i;

        for(int j = 0; j < i; j++) {
            if(nums[j] < nums[i] and 1 + dp[j] > dp[i]) {
                dp[i] = 1 + dp[j];
                hash[i] = j;
            }
        }

        if(dp[i] > lis) {
            lis = dp[i];
            lastIndex = i;
        }
    }

    vector<int> subsequence;

    while((lastIndex >= 0) and (lastIndex != hash[lastIndex])) {
        subsequence.push_back(nums[lastIndex]);
        lastIndex = hash[lastIndex];
    }

    subsequence.push_back(nums[lastIndex]);

    reverse(subsequence.begin(), subsequence.end());

    for(auto x : subsequence) cout << x << ' ';

    cout << endl;
    
    return lis;
}

int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();

    vector<int> lis = {nums[0]};

    for(int i = 1; i < n; i++) {
        if(nums[i] > lis.back()) {
            lis.push_back(nums[i]);
        } else {
            lis[lower_bound(lis.begin(), lis.end(), nums[i]) - lis.begin()] = nums[i];
        }
    }

    return lis.size();
}

vector<int> largestDivisibleSubset(vector<int>& nums) {
    int n = nums.size(), lds = INT_MIN, lastIndex = 0;

    sort(nums.begin(), nums.end());

    vector<int> dp(n, 1), hash(n);

    for(int i = 1; i < n; i++) {
        hash[i] = i;

        for(int j = 0; j < i; j++) {
            if(nums[i] % nums[j] == 0 and 1 + dp[j] > dp[i]) {
                dp[i] = 1 + dp[j];
                hash[i] = j;
            }
        }

        if(dp[i] > lds) {
            lds = dp[i];
            lastIndex = i;
        }
    }

    vector<int> answer;

    while(lastIndex != hash[lastIndex]) {
        answer.push_back(nums[lastIndex]);
        lastIndex = hash[lastIndex];
    }

    answer.push_back(nums[lastIndex]);

    return answer;
}

int main() {
    vector<int> nums = {1,2,4,8};

    for(auto x : largestDivisibleSubset(nums)) {
        cout << x << ' ';
    }
    return 0;
}