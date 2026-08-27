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

void inorderTraversal(TreeNode* root) {
    if(!root) {
        return;
    }
    inorderTraversal(root->left);
    cout << root->val << ' ';
    inorderTraversal(root->right);
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(!root or root == p or root == q) {
        return root;
    }
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    if(left and right) {
        return root;
    }
    return left ? left : right;
}

TreeNode* lowestCommonAncestorBST(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(!root) {
        return root;
    }

    if(p->val < root->val and q->val < root->val) {
        return lowestCommonAncestorBST(root->left, p, q);
    } else if(p->val > root->val and q->val > root->val) {
        return lowestCommonAncestorBST(root->right, p, q);
    }

    return root;
}

int rangeSumBSTBrute(TreeNode* root, int low, int high) {
    int rangeSum = 0;
    function<void(TreeNode*)> inorderTraversal = [&](TreeNode* root) {
        if(!root) {
            return;
        }
        inorderTraversal(root->left);
        if(root->val >= low and root->val <= high) {
            rangeSum += root->val;
        }
        inorderTraversal(root->right);
    };
    inorderTraversal(root);
    return rangeSum;
}

int rangeSumBSTOptimal(TreeNode* root, int low, int high) {
    if(!root) {
        return 0;
    }

    if(low <= root->val and root->val <= high) {
        return root->val + rangeSumBSTOptimal(root->left, low, high) 
        + rangeSumBSTOptimal(root->right, low, high);
    } else if(root->val < low) {
        return rangeSumBSTOptimal(root->right, low, high);
    }

    return rangeSumBSTOptimal(root->left, low, high);
}

TreeNode* trimBST(TreeNode* root, int low, int high) {
    if(!root) {
        return root;
    }

    if(low <= root->val and root->val <= high) {

        root->left = trimBST(root->left, low, high);
        root->right = trimBST(root->right, low, high);

    } else if(root->val < low) {

        return trimBST(root->right, low, high);

    } else if(high < root->val) {

        return trimBST(root->left, low, high);

    }
    
    return root;
}

TreeNode* searchBST(TreeNode* root, int val) {
    if(!root) {
        return root;
    }

    if(val < root->val) {
        return searchBST(root->left, val);
    } else if(val > root->val) {
        return searchBST(root->right, val);
    }

    return root;
}

vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    
}

int main() {
    vector<vector<int>> people = {{7,0},{4,4},{7,1},{5,0},{6,1},{5,2}};
    for(auto x : reconstructQueue(people)) {
        for(auto y : x) {
            cout << y << ' ';
        }
        cout << endl;
    }
    return 0;
}