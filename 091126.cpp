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

void levelOrderTraversal(TreeNode* root) {
    if(!root) {
        return;
    }

    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()) {
        int sz = q.size();

        for(int i = 0; i < sz; i++) {
            auto node = q.front();
            q.pop();

            cout << node->val << ' ';

            if(node->left) {
                q.push(node->left);
            }

            if(node->right) {
                q.push(node->right);
            }
        }

        cout << endl;
    }
}

class Codec {
private:
    void serializeHelper(TreeNode* root, string& s) {
        if(!root) {
            s += "#,";
            return;
        }

        s += to_string(root->val) + ',';

        this->serializeHelper(root->left, s);
        this->serializeHelper(root->right, s);
    }

    TreeNode* deserializeHelper(stringstream& ss) {
        string val;
        getline(ss, val, ',');

        if(val == "#") {
            return NULL;
        }

        TreeNode* root = new TreeNode(stoi(val));
        root->left = this->deserializeHelper(ss);
        root->right = this->deserializeHelper(ss);        

        return root;
    } 

public:
    string serialize(TreeNode* root) {
        string s = "";
        this->serializeHelper(root, s);
        return s;
    }

    TreeNode* deserialize(string data) {
        stringstream ss(data);
        return this->deserializeHelper(ss);
    }
};

int maxLevelSum(TreeNode* root) {
    int maxSum = INT_MIN, smallestLevel = INT_MIN, currentLevel = 1;

    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()) {
        int sz = q.size();

        int levelSum = 0;

        while(sz--) {
            auto node = q.front();
            q.pop();

            levelSum += node->val;

            if(node->left) {
                q.push(node->left);
            }

            if(node->right) {
                q.push(node->right);
            }
        }

        if(levelSum > maxSum) {
            maxSum = levelSum;
            smallestLevel = currentLevel;
        }

        currentLevel++;
    }

    return smallestLevel;
}

TreeNode* deleteNode(TreeNode* root, int key) {
    
}

int main() {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);
    root->right = new TreeNode(6);
    root->right->right = new TreeNode(7);

    int key = 3;

    levelOrderTraversal(deleteNode(root, key));
    return 0;
}