#include<bits/stdc++.h>
using namespace std;

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

int sumNumbers(TreeNode* root) {
    int total = 0;

    function<void(TreeNode*, int)> sumNumbersHelper = [&](TreeNode* root, int curr) {
        if(!root) {
            return;
        }
        curr = curr * 10 + root->val;
        if(!root->left and !root->right) {
            total += curr;
            return;
        }
        sumNumbersHelper(root->left, curr);
        sumNumbersHelper(root->right, curr);
    };

    sumNumbersHelper(root, 0);
    return total;
}

vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
    vector<vector<int>> paths;
    vector<int> path;

    function<void(TreeNode*, int, vector<int>)> pathSumHelper = [&](TreeNode* root, int currSum, vector<int> path) {
        if(!root) {
            return;
        }

        currSum += root->val;
        path.push_back(root->val);

        if(!root->left and !root->right) {

            if(currSum == targetSum) {
                paths.push_back(path);
            }

            return;

        }

        pathSumHelper(root->left, currSum, path);
        pathSumHelper(root->right, currSum, path);

    };

    pathSumHelper(root, 0, path);
    
    return paths;
}

void pathsFromNode(TreeNode* root, long long currentSum, int& paths, int targetSum) {
    if(currentSum == targetSum) {
        paths++;
    }

    if(root->left) {
        pathsFromNode(root->left, currentSum + root->left->val, paths, targetSum);
    }
    if(root->right) {
        pathsFromNode(root->right, currentSum + root->right->val, paths, targetSum);
    }

}

int pathSumBrute(TreeNode* root, int targetSum) {
    if(!root) {
        return 0;
    }

    int pathsFromRoot = 0;

    pathsFromNode(root, root->val, pathsFromRoot, targetSum);

    int pathsFromLeftChild = pathSumBrute(root->left, targetSum);
    int pathsFromRightChild = pathSumBrute(root->right, targetSum);

    return pathsFromRoot + pathsFromLeftChild + pathsFromRightChild;

}

void pathSumHelper(TreeNode* root, long long pathSum, int targetSum, int& paths, 
    unordered_map<long long, int>& pathSumFreqMapping) {

    if(!root) {
        return;
    }

    pathSum += root->val;
    paths += pathSumFreqMapping[pathSum - targetSum];

    pathSumFreqMapping[pathSum]++;

    pathSumHelper(root->left, pathSum, targetSum, paths, pathSumFreqMapping);
    pathSumHelper(root->right, pathSum, targetSum, paths, pathSumFreqMapping);

    pathSumFreqMapping[pathSum]--;

}

int pathSumOptimal(TreeNode* root, int targetSum) {
    int paths = 0;

    if(!root) {
        return paths;
    }

    unordered_map<long long, int> pathSumFreqMapping;
    pathSumFreqMapping[0] = 1;

    pathSumHelper(root, 0, targetSum, paths, pathSumFreqMapping);
    
    return paths;
}

int main() {
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->left->left = new TreeNode(3);
    root->left->left->left = new TreeNode(3);
    root->left->left->right = new TreeNode(-2);
    root->left->right = new TreeNode(2);
    root->left->right->right = new TreeNode(1);
    root->right = new TreeNode(-3);
    root->right->right = new TreeNode(11);
    cout << pathSumOptimal(root, 8) << endl;
    return 0;
}