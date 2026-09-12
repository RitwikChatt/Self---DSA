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

void printBinaryTree(TreeNode* root) {
    if(!root) return;

    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()) {
        int sz = q.size();

        while(sz--) {
            auto node = q.front();
            q.pop();

            cout << node->val << ' ';

            if(node->left) q.push(node->left);

            if(node->right) q.push(node->right);
        }

        cout << endl;
    }
}

TreeNode* deleteNode(TreeNode* root, int key) {
    if(!root) {
        return root;
    }

    if(key < root->val) {
        root->left = deleteNode(root->left, key);
    } else if(key > root->val) {
        root->right = deleteNode(root->right, key);
    } else {
        if(!root->left) {
            return root->right;
        }

        if(!root->right) {
            return root->left;
        }

        TreeNode* successor = root->right;

        while(successor->left) {
            successor = successor->left;
        }

        root->val = successor->val;

        root->right = deleteNode(root->right, successor->val);
    }

    return root;
}

void pathSumHelper(TreeNode* root, int sum, int& paths, 
    unordered_map<int, int>& sumXFreqMapping, int targetSum) {
        if(!root) {
            return;
        }

        sum += root->val;

        paths += sumXFreqMapping[sum - targetSum];

        sumXFreqMapping[sum]++;

        pathSumHelper(root->left, sum, paths, sumXFreqMapping, targetSum);

        pathSumHelper(root->right, sum, paths, sumXFreqMapping, targetSum);

        sumXFreqMapping[sum]--;
}

int pathSum(TreeNode* root, int targetSum) {
    unordered_map<int, int> sumXFreqMapping;

    sumXFreqMapping[0] = 1;

    int paths = 0;

    pathSumHelper(root, 0, paths, sumXFreqMapping, targetSum);

    return paths;
}

void longestZigZagHelperMaxZigZag(TreeNode* root, int pathLen, string direction, int& maxZigZag) {
    if(!root) {
        return;
    }

    maxZigZag = max(maxZigZag, pathLen);

    if(direction == "RIGHT") {
        longestZigZagHelperMaxZigZag(root->right, pathLen + 1, "LEFT", maxZigZag);
    } else {
        longestZigZagHelperMaxZigZag(root->left, pathLen + 1, "RIGHT", maxZigZag);
    }
}

void longestZigZagHelperDFS(TreeNode* root, int& maxZigZag) {
    if(!root) {
        return;
    }

    longestZigZagHelperMaxZigZag(root, 1, "RIGHT", maxZigZag);
    longestZigZagHelperMaxZigZag(root, 1, "LEFT", maxZigZag);

    longestZigZagHelperDFS(root->left, maxZigZag);
    longestZigZagHelperDFS(root->right, maxZigZag);
}

int longestZigZagBrute(TreeNode* root) {
    int maxZigZag = 1;

    longestZigZagHelperDFS(root, maxZigZag);

    return maxZigZag - 1;
}

pair<int, int> longestZigZagHelper(TreeNode* root, int& maxLen) {
    if(!root) {
        return {0, 0};
    }

    auto leftChild = longestZigZagHelper(root->left, maxLen);
    auto rightChild = longestZigZagHelper(root->right, maxLen);

    int left = 0, right = 0;

    if(root->left) {
        left = 1 + leftChild.second;
    }

    if(root->right) {
        right = 1 + rightChild.first;
    }

    maxLen = max(maxLen, max(left, right));

    return {left, right};
}

int longestZigZag(TreeNode* root) {
    int maxLen = 0;

    longestZigZagHelper(root, maxLen);

    return maxLen;
}

vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
    
}

int main() {
    vector<string> words = {"aaaa","asas","able","ability","actt","actor","access"}, 
    puzzles = {"aboveyz","abrodyz","abslute","absoryz","actresz","gaswxyz"};

    for(auto x : findNumOfValidWords(words, puzzles)) {
        cout << x << ' ';
    }

    return 0;
}