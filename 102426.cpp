#include<bits/stdc++.h>
using namespace std;

int countWays(string &s) {
    int n = s.length();

    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2)));

    for(int i = 0; i < n; i += 2) {
        dp[i][i][1] = s[i] == 'T';
        dp[i][i][0] = s[i] == 'F';
    }

    for(int i = n - 3; i >= 0; i -= 2) {
        for(int j = i + 2; j < n; j += 2) {
            for(int k = i + 1; k <= j - 1; k += 2) {

                int lt = dp[i][k - 1][1], lf = dp[i][k - 1][0];
                int rt = dp[k + 1][j][1], rf = dp[k + 1][j][0];

                int ways, total = (lt + lf) * (rt + rf);

                if(s[k] == '&') ways = lt * rt; 
                else if(s[k] == '|') ways = lt * rf + lf * rt + lt * rt;
                else ways = lt * rf + lf * rt;

                dp[i][j][1] += ways;
                dp[i][j][0] += total - ways;
            }
        }
    }

    return dp[0][n - 1][1];
}

bool isPalindrome(int l, int r, string& s) {
    while(l < r) {
        if(s[l] != s[r]) {
            return false;
        }
        l++, r--;
    }

    return true;
}

int minCut(string s) {
    int n = s.length();

    vector<int> dp(n + 1);

    for(int i = n - 1; i >= 0; i--) {
        dp[i] = INT_MAX;
        for(int j = i; j < n; j++) {
            if(isPalindrome(i, j, s)) {
                dp[i] = min(dp[i], 1 + dp[j + 1]);
            }
        }
    }

    return dp[0] - 1;
}

int maxSumAfterPartitioning(vector<int>& arr, int k) {
    int n = arr.size();

    vector<int> dp(n + 1);

    for(int i = n - 1; i >= 0; i--) {
        int maxi = INT_MIN;
        dp[i] = INT_MIN;

        for(int j = i; j < min(i + k, n); j++) {
            maxi = max(maxi, arr[j]);
            dp[i] = max(dp[i], maxi * (j - i + 1) + dp[j + 1]);
        }
    }

    return dp[0];
}

vector<int> computeNSE(vector<int>& nums) {
    int n = nums.size();

    vector<int> nse(n, n);
    stack<int> st;

    for(int i = n - 1; i >= 0; i--) {
        while(!st.empty() and nums[st.top()] >= nums[i]) {
            st.pop();
        }

        if(!st.empty()) {
            nse[i] = st.top();
        }

        st.push(i);
    }

    return nse;
}

vector<int> computePSE(vector<int>& nums) {
    int n = nums.size();

    vector<int> pse(n, -1);
    stack<int> st;

    for(int i = 0; i < n; i++) {
        while(!st.empty() and nums[st.top()] >= nums[i]) {
            st.pop();
        }

        if(!st.empty()) {
            pse[i] = st.top();
        }

        st.push(i);
    }

    return pse;
}

int largestRectangleArea(vector<int>& heights) {
    int n = heights.size(), maxArea = INT_MIN;

    vector<int> nse = computeNSE(heights), pse = computePSE(heights);

    for(int i = 0; i < n; i++) {
        maxArea = max(maxArea, heights[i] * (nse[i] - pse[i] - 1));
    }

    return maxArea;
}

int maximalRectangle(vector<vector<char>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();

    vector<vector<int>> prefixMatrix(m, vector<int>(n));

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(matrix[i][j] == '0') {
                continue;
            }

            prefixMatrix[i][j] = (matrix[i][j] - '0');

            if(i - 1 >= 0) {
                prefixMatrix[i][j] += prefixMatrix[i - 1][j];
            } 
        }
    }

    int maxArea = INT_MIN;

    for(int i = 0; i < m; i++) {
        maxArea = max(maxArea, largestRectangleArea(prefixMatrix[i]));
    }

    return maxArea;
}

int countSquares2DDP(vector<vector<int>>& matrix) {
    int m = matrix.size(), n = matrix[0].size(), totalCount = 0;

    //dp[i][j] -> Number of square submatrices that have all ones ending at (i, j)

    vector<vector<int>> dp(m, vector<int>(n));

    for(int j = 0; j < n; j++) {
        dp[0][j] = matrix[0][j];
        totalCount += dp[0][j];
    } 

    for(int i = 0; i < m; i++) {
        dp[i][0] = matrix[i][0];
        totalCount += dp[i][0];
    }

    for(int i = 1; i < m; i++) {
        for(int j = 1; j < n; j++) {
            if(!matrix[i][j]) continue;
            
            dp[i][j] = 1 + min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});

            totalCount += dp[i][j];
        }
    }

    return totalCount;
}

int countSquares1DDP(vector<vector<int>>& matrix) {
    int m = matrix.size(), n = matrix[0].size(), totalCount = 0;

    vector<int> prev(n);

    for(int j = 0; j < n; j++) {
        prev[j] = matrix[0][j];
        totalCount += prev[j];
    }

    for(int i = 1; i < m; i++) {
        vector<int> curr(n);
        curr[0] = matrix[i][0];

        totalCount += curr[0];

        for(int j = 1; j < n; j++) {
            if(!matrix[i][j]) continue;
            
            curr[j] = 1 + min({prev[j - 1], prev[j], curr[j - 1]});

            totalCount += curr[j];
        }

        prev = curr;
    }

    return totalCount;
}

int main() {
    vector<vector<int>> matrix = {
        {0,1,1,1}, 
        {1,1,1,1}, 
        {0,1,1,1}
    };

    cout << countSquares2DDP(matrix) << endl;
    cout << countSquares1DDP(matrix) << endl;
    return 0;
}