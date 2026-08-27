#include<bits/stdc++.h>
using namespace std;

int scoreDiff(int l, int r, vector<int>& nums) {
    if(l == r) {
        return nums[l];
    }
    return max(nums[l] - scoreDiff(l+1, r, nums), nums[r] - scoreDiff(l, r - 1, nums));
}

bool predictTheWinner(vector<int>& nums) {
    return scoreDiff(0, nums.size() - 1, nums) >= 0;
}

bool predictTheWinnerOptimal(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(n));
    for(int i = 0; i < n; i++) {
        dp[i][i] = nums[i];
    }
    for(int l = n - 2; l >= 0; l--) {
        for(int r = l + 1; r < n; r++) {
            dp[l][r] = max(nums[l] - dp[l + 1][r], nums[r] - dp[l][r - 1]);
        }
    }
    return dp[0][n - 1] >= 0;
}

int main() {
    
    return 0;
}