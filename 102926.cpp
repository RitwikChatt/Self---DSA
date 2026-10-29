#include<bits/stdc++.h>
using namespace std;

int mctFromLeafValues(vector<int>& arr) {
    int n = arr.size();

    vector<vector<int>> rangeMax(n, vector<int>(n));

    for(int i = 0; i < n; i++) {
        rangeMax[i][i] = arr[i];
        for(int j = i + 1; j < n; j++) {
            rangeMax[i][j] = max(rangeMax[i][j - 1], arr[j]);
        }
    }

    vector<vector<int>> dp(n, vector<int>(n));

    for(int i = n - 2; i >= 0; i--) {
        for(int j = i + 1; j < n; j++) {
            dp[i][j] = INT_MAX;
            for(int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], rangeMax[i][k] * rangeMax[k + 1][j] + dp[i][k] + dp[k + 1][j]);
            }
        }
    }

    return dp[0][n - 1];
}

double largestSumOfAverages(vector<int>& nums, int k) {
    int n = nums.size();

    vector<vector<int>> rangeSum(n, vector<int>(n));

    for(int i = 0; i < n; i++) {
        rangeSum[i][i] = nums[i];
        for(int j = i + 1; j < n; j++) {
            rangeSum[i][j] = rangeSum[i][j - 1] + nums[j];
        }
    }

    vector<vector<double>> dp(n, vector<double>(k));

    for(int cuts = 0; cuts < k; cuts++) dp[0][cuts] = nums[0];

    for(int i = 1; i < n; i++) {
        dp[i][0] = (double) rangeSum[0][i] / (double) (i + 1);
    }

    for(int i = 1; i < n; i++) {
        for(int cuts = 1; cuts < k; cuts++) {
            dp[i][cuts] = INT_MIN;
            for(int j = 0; j < i; j++) {
                dp[i][cuts] = max(dp[i][cuts], dp[j][cuts - 1] + (double) rangeSum[j + 1][i] / (double) (i - j));
            }
        }
    }

    return dp[n - 1][k - 1];
}

class TreeNode {
    public:
    int val;
    TreeNode *left, *right;

    TreeNode(int val) {
        this->val = val;
        this->left = NULL;
        this->right = NULL;
    }
};

class SkipRob {
    public:
    int skip, rob;
};

SkipRob robHelper(TreeNode* root) {
    if(!root) return {0, 0};

    SkipRob leftChild = robHelper(root->left), rightChild = robHelper(root->right);

    int skip = max(leftChild.skip, leftChild.rob) + max(rightChild.skip, rightChild.rob), 
        rob = root->val + leftChild.skip + rightChild.skip;

    return {skip, rob};
}

int rob(TreeNode* root) {
    auto [skip, rob] = robHelper(root);

    return max(skip, rob);
}

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(4);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right = new TreeNode(5);
    root->right->right = new TreeNode(1);

    cout << rob(root) << endl;
    return 0;
}