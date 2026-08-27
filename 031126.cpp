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

void postorderTraversalUtil(TreeNode* root, vector<int>& postorder) {
    if(!root) {
        return;
    }
    postorderTraversalUtil(root->left, postorder);
    postorderTraversalUtil(root->right, postorder);
    postorder.push_back(root->val);
}

vector<int> postorderTraversal(TreeNode* root) {
    vector<int> postorder;
    postorderTraversalUtil(root, postorder);
    return postorder;
}

vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> levels;
    if(!root) {
        return levels;
    }
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        int sz = q.size();
        vector<int> level;
        for(int i = 0; i < sz; i++) {
            TreeNode* frontNode = q.front();
            q.pop();
            level.push_back(frontNode->val);
            if(frontNode->left) {
                q.push(frontNode->left);
            }
            if(frontNode->right) {
                q.push(frontNode->right);
            }
        }
        levels.push_back(level);
    }
    return levels;
}

int maxDepth(TreeNode* root) {
    if(!root) {
        return 0;
    }
    int lh = maxDepth(root->left);
    int rh = maxDepth(root->right);
    return 1 + max(lh, rh);
}

int height(TreeNode* root) {
    if(!root) {
        return 0;
    }
    int lh = height(root->left);
    int rh = height(root->right);
    return 1 + max(lh, rh);
}

bool isBalancedBrute(TreeNode* root) {
    if(!root) {
        return true;
    }
    int leftSubTreeHeight = height(root->left);
    int rightSubTreeHeight = height(root->right);
    int diff = abs(leftSubTreeHeight - rightSubTreeHeight);
    return diff <= 1 and isBalancedBrute(root->left) and isBalancedBrute(root->right);
}

int isBalancedUtil(TreeNode* root, bool& balanced) {
    if(!root) {
        return 0;
    }
    int lh = isBalancedUtil(root->left, balanced);
    int rh = isBalancedUtil(root->right, balanced);
    if(abs(lh - rh) > 1) {
        balanced = false;
    }
    return 1 + max(lh, rh);
}

bool isBalanced(TreeNode* root) {
    bool balanced = true;
    isBalancedUtil(root, balanced);
    return balanced;
}

int diameterOfBinaryTreeBrute(TreeNode* root) {
    if(!root) {
        return 0;
    }
    int lh = height(root->left);
    int rh = height(root->right);
    int dia = lh + rh;
    int diaLeftSubTree = diameterOfBinaryTreeBrute(root->left);
    int diaRightSubTree = diameterOfBinaryTreeBrute(root->right);
    return max({dia, diaLeftSubTree, diaRightSubTree});
}

int diameterOfBinaryTreeUtil(TreeNode* root, int& dia) {
    if(!root) {
        return 0;
    }
    int lh = diameterOfBinaryTreeUtil(root->left, dia);
    int rh = diameterOfBinaryTreeUtil(root->right, dia);
    dia = max(dia, lh + rh);
    return 1 + max(lh, rh);
}

int diameterOfBinaryTree(TreeNode* root) {
    int dia = 0;
    diameterOfBinaryTreeUtil(root, dia);
    return dia;
}

TreeNode* makeTree(vector<int>& nums, int beg, int end) {
    if(beg > end) {
        return NULL;
    }
    int mid = beg + (end - beg) / 2;
    TreeNode* root = new TreeNode(nums[mid]);
    root->left = makeTree(nums, beg, mid - 1);
    root->right = makeTree(nums, mid + 1, end);
    return root;
}

TreeNode* sortedArrayToBST(vector<int>& nums) {
    return makeTree(nums, 0, nums.size() - 1);
}

void inorderTraversalUtil(TreeNode* root, vector<int>& inorder) {
    if(!root) {
        return;
    }
    inorderTraversalUtil(root->left, inorder);
    inorder.push_back(root->val);
    inorderTraversalUtil(root->right, inorder);
}

vector<int> inorderTraversal(TreeNode* root) {
    vector<int> inorder;
    inorderTraversalUtil(root, inorder);
    return inorder;
}

vector<int> mergeTwoBST(TreeNode* rootA, TreeNode* rootB) {
    vector<int> first = inorderTraversal(rootA);
    vector<int> second = inorderTraversal(rootB);
    vector<int> mergedArray;
    int i = 0, j = 0;
    while(i < first.size() and j < second.size()) {
        if(first[i] <= second[j]) {
            mergedArray.push_back(first[i++]);
        } else {
            mergedArray.push_back(second[j++]);
        }
    }
    while(i < first.size()) {
        mergedArray.push_back(first[i++]);
    }
    while(j < second.size()) {
        mergedArray.push_back(second[j++]);
    }
    return mergedArray;
}

int main() {
    TreeNode* rootA = new TreeNode(3);
    rootA->left = new TreeNode(1);
    rootA->right = new TreeNode(5);
    TreeNode* rootB = new TreeNode(4);
    rootB->left = new TreeNode(2);
    rootB->right = new TreeNode(6);
    for(auto it : mergeTwoBST(rootA, rootB)) {
        cout << it << ' ';
    }
    return 0;
}