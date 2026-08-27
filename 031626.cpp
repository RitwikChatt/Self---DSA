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

vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    vector<vector<int>> ans;
    sort(people.begin(), people.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[0] > b[0] or a[0] == b[0] and a[1] < b[1];
    });
    for(auto &p : people) {
        ans.insert(ans.begin() + p[1], p);
    }
    return ans;
}

vector<int> rightSideView(TreeNode* root) {
    vector<int> view;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        int sz = q.size();
        for(int i = 0; i < sz; i++) {
            TreeNode* frontNode = q.front();
            q.pop();
            if(!i) {
                view.push_back(frontNode->val);
            }
            if(frontNode->right) {
                q.push(frontNode->right);
            }
            if(frontNode->left) {
                q.push(frontNode->left);
            }
        }
    }
    return view;
}

int findBottomLeftValue(TreeNode* root) {

    function<int(TreeNode*)> height = [&](TreeNode* root) {
        if(!root) {
            return 0;
        }
        int lh = height(root->left);
        int rh = height(root->right);
        return 1 + max(lh, rh);
    };

    int levels = height(root);

    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()) {
        int sz = q.size();
        for(int i = 0; i < sz; i++) {
            TreeNode* frontNode = q.front();
            q.pop();
            if(levels == 1 and !i) {
                return frontNode->val;
            }
            if(frontNode->left) {
                q.push(frontNode->left);
            }
            if(frontNode->right) {
                q.push(frontNode->right);
            }
        }
        levels--;
    }

    return -1;
}

void inorderTraversal(TreeNode* root) {
    if(!root) {
        return;
    }
    inorderTraversal(root->left);
    cout << root->val << ' ';
    inorderTraversal(root->right);
}

TreeNode* pruneTree(TreeNode* root) {
    if(!root) {
        return root;
    }

    root->left = pruneTree(root->left);
    root->right = pruneTree(root->right);

    if(!root->left and !root->right and !root->val) {
        return NULL;
    }

    return root;
}

int maxLevelSum(TreeNode* root) {
    int level = 1, maxLevel = INT_MIN, maxSum = INT_MIN;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        int sz = q.size(), sum = 0;
        for(int i = 0; i < sz; i++) {
            TreeNode* frontNode = q.front();
            q.pop();
            sum += frontNode->val;
            if(frontNode->left) {
                q.push(frontNode->left);
            }
            if(frontNode->right) {
                q.push(frontNode->right);
            }
        }
        if(sum > maxSum) {
            maxSum = sum;
            maxLevel = level;
        }
        level++;
    }
    return maxLevel;
}

vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {

}

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);
    root->right = new TreeNode(1);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    for(auto it : distanceK(root, root->left, 2)) {
        cout << it << ' ';
    }
    return 0;
}