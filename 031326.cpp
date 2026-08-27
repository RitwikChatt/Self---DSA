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

void preorderTraversal(TreeNode* root) {
    if(!root) {
        return;
    }
    cout << root->val << ' ';
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void inorderTraversal(TreeNode* root) {
    if(!root) {
        return;
    }
    inorderTraversal(root->left);
    cout << root->val << ' ';
    inorderTraversal(root->right);
}

void postorderTraversal(TreeNode* root) {
    if(!root) {
        return;
    }
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout << root->val << ' ';
}

TreeNode* build(const vector<int>& postorder, const vector<int>& inorder, int posS, int posE, int inS, int inE, 
    unordered_map<int, int>& inorderElementsIndexMapping) {
        if(posS > posE or inS > inE) {
            return NULL;
        }
        TreeNode* root = new TreeNode(postorder[posE]);
        int rI = inorderElementsIndexMapping[root->val];
        root->left = build(postorder, inorder, posS, posS + rI - inS - 1, inS, rI - 1, inorderElementsIndexMapping);
        root->right = build(postorder, inorder, posS + rI - inS, posE - 1, rI + 1, inE, inorderElementsIndexMapping);
        return root;
}

TreeNode* buildTree(const vector<int>& inorder, const vector<int>& postorder) {
    int n = inorder.size();
    unordered_map<int, int> inorderElementsIndexMapping;
    for(int i = 0; i < n; i++) {
        inorderElementsIndexMapping[inorder[i]] = i;
    }
    return build(postorder, inorder, 0, n - 1, 0, n - 1, inorderElementsIndexMapping);
}

TreeNode* build(const vector<int>& preorder, const vector<int>& inorder, int preS, int preE, int inS, int inE, 
    unordered_map<int, int>& dataIndexMapping) {
        if(preS > preE or inS > inE) {
            return NULL;
        }
        TreeNode* root = new TreeNode(preorder[preS]);
        int rI = dataIndexMapping[root->val];
        root->left = build(preorder, inorder, preS + 1, preS + rI - inS, inS, rI - 1, dataIndexMapping);
        root->right = build(preorder, inorder, preS + rI - inS + 1, preE, rI + 1, inE, dataIndexMapping);
        return root;
}

TreeNode* buildTree(const vector<int>& preorder, const vector<int>& inorder) {
    int n = inorder.size();
    unordered_map<int, int> dataIndexMapping;
    for(int i = 0; i < n; i++) {
        dataIndexMapping[inorder[i]] = i;
    }
    return build(preorder, inorder, 0, n - 1, 0, n - 1, dataIndexMapping);
}

void preorderTraversalUtil(TreeNode* root, vector<int>& preorder) {
    if(!root) {
        preorder.push_back(INT_MIN);
        return;
    }
    preorder.push_back(root->val);
    preorderTraversalUtil(root->left, preorder);
    preorderTraversalUtil(root->right, preorder);
}

vector<int> preorderTraversal(TreeNode* root) {
    vector<int> preorder;
    preorderTraversalUtil(root, preorder);
    return preorder;
}

bool isSameTree(TreeNode* p, TreeNode* q) {
    vector<int> inorderP, inorderQ;
    inorderP = preorderTraversal(p);
    inorderQ = preorderTraversal(q);
    return inorderP == inorderQ;
}

bool hasPathSum(TreeNode* root, int targetSum) {
    if(!root) {
        return false;
    }
    if(!root->left and !root->right and targetSum == root->val) {
        return true;
    }
    return hasPathSum(root->left, targetSum - root->val) or hasPathSum(root->right, targetSum - root->val);
}

TreeNode* invertTree(TreeNode* root) {
    if(!root) {
        return root;
    }
    TreeNode* lst = invertTree(root->left);
    TreeNode* rst = invertTree(root->right);
    root->left = rst;
    root->right = lst;
    return root;
}

void sumOfLeftLeavesUtil(TreeNode* root, int& sum) {
    if(!root) {
        return;
    }
    TreeNode* leftChild = root->left;
    if(leftChild and !leftChild->left and !leftChild->right) {
        sum += leftChild->val;
    }
    sumOfLeftLeavesUtil(root->left, sum);
    sumOfLeftLeavesUtil(root->right, sum);
}

int sumOfLeftLeaves(TreeNode* root) {
    int sum = 0;
    sumOfLeftLeavesUtil(root, sum);
    return sum;
}

TreeNode* sortedArrayToBSTUtil(const vector<int>& nums, int start, int end) {
    if(start > end) {
        return NULL;
    }
    int mid = start + (end - start) / 2;
    TreeNode* root = new TreeNode(nums[mid]);
    root->left = sortedArrayToBSTUtil(nums, start, mid - 1);
    root->right = sortedArrayToBSTUtil(nums, mid + 1, end);
    return root;
}

TreeNode* sortedArrayToBST(const vector<int>& nums) {
    int n = nums.size();
    return sortedArrayToBSTUtil(nums, 0, n - 1);
}

int kthSmallest(TreeNode* root, int k) {
    int ans;
    function<void(TreeNode*)> inorderTraversal = [&](TreeNode* root) {
        if(!root) {
            return;
        }
        inorderTraversal(root->left);
        if(!--k) {
            ans = root->val;
            return;
        }
        inorderTraversal(root->right);
    };
    inorderTraversal(root);
    return ans;
}

vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {

    function<void(TreeNode*, vector<int>&)> inorderTraversalUtil = [&](TreeNode* root, vector<int>& inorder) {
        if(!root) {
            return;
        }
        inorderTraversalUtil(root->left, inorder);
        inorder.push_back(root->val);
        inorderTraversalUtil(root->right, inorder);
    };

    function<vector<int>(TreeNode*)> inorderTraversal = [&](TreeNode* root) {
        vector<int> inorder;
        inorderTraversalUtil(root, inorder);
        return inorder;
    };

    vector<int> inorderA, inorderB;
    inorderA = inorderTraversal(root1);
    inorderB = inorderTraversal(root2);

    function<vector<int>(vector<int>&, vector<int>&)> merge = [&](vector<int>& a, vector<int>& b) {
        int n = a.size(), m = b.size();
        int i = 0, j = 0;
        vector<int> merged;

        while(i < n and j < m) {
            if(a[i] <= b[j]) {
                merged.push_back(a[i++]);
            } else {
                merged.push_back(b[j++]);
            }
        }

        while(i < n) {
            merged.push_back(a[i++]);
        }

        while(j < m) {
            merged.push_back(b[j++]);
        }

        return merged;
    };

    return merge(inorderA, inorderB);
}

int main() {

    return 0;
}