#include<bits/stdc++.h>
using namespace std;

int findTargetSumWays(vector<int>& nums, int target) {
    int n = nums.size();

    int totalSum = accumulate(nums.begin(), nums.end(), 0);

    if(abs(target) > totalSum) {
        return 0;
    }

    if((totalSum + target) % 2) {
        return 0;
    }

    int goal = (totalSum + target) / 2;

    //dp[j] -> Number of subsets which have a sum equal to j using elements till this point from nums

    vector<int> dp(goal + 1);

    dp[0] = 1;

    for(int i = 1; i <= n; i++) {
        for(int j = goal; j >= nums[i - 1]; j--) {
            dp[j] += dp[j - nums[i - 1]];   
        }
    }

    return dp[goal];
}

int longestCommonSubsequence(string text1, string text2) {
    int n1 = text1.length(), n2 = text2.length();

    //dp[i][j] -> Length of LCS of text1[0 ... i - 1] and text2[0 ... j - 1]

    vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1));

    for(int i = 1; i <= n1; i++) {
        for(int j = 1; j <= n2; j++) {
            if(text1[i - 1] == text2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max({dp[i - 1][j], dp[i - 1][j - 1], dp[i][j - 1]});
            }
        }
    }

    return dp[n1][n2];
}

int longestCommonSubsequence1DDP(string text1, string text2) {
    int n1 = text1.length(), n2 = text2.length();

    //dp[j] -> Length of LCS of text1[0 ... i - 1] and text2[0 ... j - 1]

    vector<int> dp(n2 + 1);

    for(int i = 1; i <= n1; i++) {
        int diag = dp[0];
        for(int j = 1; j <= n2; j++) {
            int temp = dp[j];
            if(text1[i - 1] == text2[j - 1]) {
                dp[j] = 1 + diag;
            } else {
                dp[j] = max({dp[j], diag, dp[j - 1]});
            }
            diag = temp;
        }
    }

    return dp[n2];
}

int minDistance(string word1, string word2) {
    int n1 = word1.length(), n2 = word2.length();

    //dp[i][j] -> Minimum operations required to convert word1[0 ... i - 1] to word2[0 ... j - 1]

    vector<int> dp(n2 + 1);

    for(int j = 1; j <= n2; j++) dp[j] = j;

    for(int i = 1; i <= n1; i++) {
        int diag = dp[0];
        dp[0] = i;
        for(int j = 1; j <= n2; j++) {
            int temp = dp[j];
            if(word1[i - 1] != word2[j - 1]) {
                dp[j] = 1 + min({dp[j], diag, dp[j - 1]});
            } else {
                dp[j] = diag;
            }
            diag = temp;
        }   
    }

    return dp[n2];
}

int numDistinct(string s, string t) {
    
}

int main() {
    cout << numDistinct("rabbbit", "rabbit") << endl;
    return 0;
}