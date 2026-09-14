#include<bits/stdc++.h>
using namespace std;

class TrieNode {
    public:
    TrieNode* links[26];
    bool flag = false;
};

void suggestedProductsHelperDFS(TrieNode* node, string str, vector<string>& productsSuggested) {
    if(productsSuggested.size() == 3) {
        return;
    }

    if(node->flag) {
        productsSuggested.push_back(str);
    }

    for(int i = 0; i < 26; i++) {
        if(node->links[i]) {
            str += i + 'a';
            suggestedProductsHelperDFS(node->links[i], str, productsSuggested);
            str.pop_back();
        }
    }
}

vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
    TrieNode* root = new TrieNode();

    for(auto product : products) {
        TrieNode* node = root;

        for(auto ch : product) {
            if(!node->links[ch - 'a']) {
                node->links[ch - 'a'] = new TrieNode();
            }
            node = node->links[ch - 'a'];
        }

        node->flag = true;
    }

    TrieNode* node = root;
    bool pathBroken = false;

    vector<vector<string>> allProductsSuggested;

    for(int i = 0; i < searchWord.length(); i++) {
        string str = searchWord.substr(0, i + 1);
        vector<string> productsSuggested;

        if(!pathBroken && node->links[searchWord[i] - 'a']) {
            node = node->links[searchWord[i] - 'a'];
            suggestedProductsHelperDFS(node, str, productsSuggested);
        } else {
            pathBroken = true;
        }

        allProductsSuggested.push_back(productsSuggested);
    }

    return allProductsSuggested;
}

class Trie {
private:
class TrieNode {
    public:
    TrieNode* links[26];
    bool flag = false;
};

TrieNode* root;

public:
    Trie() {
        this->root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* node = this->root;

        for(auto ch : word) {
            if(!node->links[ch - 'a']) {
                node->links[ch - 'a'] = new TrieNode();
            }
            node = node->links[ch - 'a'];
        }

        node->flag = true;
    }
    
    bool search(string word) {
        TrieNode* node = this->root;

        for(auto ch : word) {
            if(!node->links[ch - 'a']) {
                return false;
            }
            node = node->links[ch - 'a'];
        }

        return node->flag;
    }
    
    bool startsWith(string prefix) {
        TrieNode* node = this->root;

        for(auto ch : prefix) {
            if(!node->links[ch - 'a']) {
                return false;
            }
            node = node->links[ch - 'a'];
        }

        return true;
    }
};

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

void levelOrderTraveral(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()) {
        int sz = q.size();

        while(sz--) {
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
    int maximalSum = INT_MIN, smallestLevel = INT_MAX;

    queue<TreeNode*> q;
    q.push(root);

    int level = 1;

    while(!q.empty()) {
        int sz = q.size(), levelSum = 0;

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

        if(levelSum > maximalSum) {
            maximalSum = levelSum;
            smallestLevel = level;
        }

        level++;
    }

    return smallestLevel;
}

void pathSumHelperDFS(TreeNode* root, int targetSum, vector<int>& path, vector<vector<int>>& paths) {
    if(!root) {
        return;
    }

    path.push_back(root->val);
    targetSum -= root->val;

    if(!root->left and !root->right) {
        if(!targetSum) {
            paths.push_back(path);
        }
    } else {
        pathSumHelperDFS(root->left, targetSum, path, paths);
        pathSumHelperDFS(root->right, targetSum, path, paths);
    }

    path.pop_back();
}

vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
    vector<int> path;
    vector<vector<int>> paths;

    pathSumHelperDFS(root, targetSum, path, paths);

    return paths;
}

void populateAdjList(TreeNode* root, unordered_map<int, vector<int>>& adjList) {
    if(!root) {
        return;
    }

    if(root->left) {
        adjList[root->val].push_back(root->left->val);
        adjList[root->left->val].push_back(root->val);
        populateAdjList(root->left, adjList);
    }

    if(root->right) {
        adjList[root->val].push_back(root->right->val);
        adjList[root->right->val].push_back(root->val);
        populateAdjList(root->right, adjList);
    }
}

vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
    unordered_map<int, vector<int>> adjList;
    populateAdjList(root, adjList);

    vector<bool> visited(adjList.size() + 1);
    queue<int> q;

    int level = 0;

    visited[target->val] = true;
    q.push(target->val);

    vector<int> nodesDistK;

    while(!q.empty()) {
        int sz = q.size();

        while(sz--) {
            auto node = q.front();
            q.pop();

            if(level == k) {
                nodesDistK.push_back(node);
            }

            for(auto neighbour : adjList[node]) {
                if(!visited[neighbour]) {
                    visited[neighbour] = true;
                    q.push(neighbour);
                }
            }
        }

        level++;
    }

    return nodesDistK;
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

    TreeNode* target = root->left;

    int k = 2;

    for(auto it : distanceK(root, target, k)) {
        cout << it << ' ';
    }

    return 0;
}