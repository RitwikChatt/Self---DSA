#include<bits/stdc++.h>
using namespace std;

class TreeNode {
    public:
    int val;
    TreeNode *left, *right;

    TreeNode(int data) {
        this->val = data;
        this->left = NULL;
        this->right = NULL;
    }

};

void printPreOrderTraversal(TreeNode* root) {
    if(!root) {
        return;
    }
    cout << root->val << ' ';
    printPreOrderTraversal(root->left);
    printPreOrderTraversal(root->right);
}

void printInOrderTraversal(TreeNode* root) {
    if(!root) {
        return;
    }
    printInOrderTraversal(root->left);
    cout << root->val << ' ';
    printInOrderTraversal(root->right);
}

void printPostOrderTraversal(TreeNode* root) {
    if(!root) {
        return;
    }
    printPostOrderTraversal(root->left);
    printPostOrderTraversal(root->right);
    cout << root->val << ' ';
}

void printLevelOrderTraversal(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        int sz = q.size();
        for(int i = 0; i < sz; i++) {
            cout << q.front()->val << ' ';
            if(q.front()->left) {
                q.push(q.front()->left);
            }
            if(q.front()->right) {
                q.push(q.front()->right);
            }
            q.pop();
        }
    }
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

void preorderTraversalUtil(TreeNode* root, vector<int>& preorder) {
    if(!root) {
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

int main() {
    TreeNode* root = new TreeNode(11);
    root->left = new TreeNode(5);
    root->left->left = new TreeNode(7);
    root->left->left->left = new TreeNode(65);
    root->left->left->right = new TreeNode(3);
    root->left->right = new TreeNode(9);
    root->right = new TreeNode(6);
    root->right->right = new TreeNode(10);
    root->right->right->left = new TreeNode(11);
    for(int data : preorderTraversal(root)) {
        cout << data << ' ';
    }
    return 0;
}