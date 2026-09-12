#include<bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

long long countGoodNumbersHelperFastExponentiation(long long a, long long n) {
    long long result = 1;

    while(n) {
        if(n % 2) {
            result = (result * a) % MOD;
        }

        a = (a * a) % MOD;
        n /= 2;
    }

    return result;
}

int countGoodNumbers(long long n) {
    long long pow5 = countGoodNumbersHelperFastExponentiation(5, n / 2), 
        pow4 = countGoodNumbersHelperFastExponentiation(4, n / 2);

    int resultant = (pow5 * pow4) % MOD;

    return n % 2 ? (5 * resultant) % MOD : resultant;
}

double myPow(double x, int n) {
    double result = 1;

    long long n_ = n;
    n_ = abs(n_);

    while(n_) {
        if(n_ & 1) {
            result *= x;
        }

        x *= x;
        n_ /= 2;
    }

    return n < 0 ? 1 / result : result;
}

int rangeBitwiseAnd(int left, int right) {
    int shift = 0;

    while(left != right) {
        left >>= 1;
        right >>= 1;
        shift++;
    }

    return left << shift;
}

int hammingWeight(int n) {
    int setbits = 0;

    while(n) {
        setbits += n & 1;
        n >>= 1;
    }

    return setbits;
}

int maxPoints(vector<vector<int>>& points) {
    int n = points.size(), ans = 0;

    for(int i = 0; i < n; i++) {
        unordered_map<double, int> slopeXFrequencyMapping;
        for(int j = 0; j < n; j++) {
            if(i == j) {
                continue;
            }

            int x1 = points[i][0], y1 = points[i][1];
            int x2 = points[j][0], y2 = points[j][1];

            double slope = DBL_MAX;

            if(x2 != x1) {
                slope = double(y2 - y1) / double(x2 - x1);
            }

            slopeXFrequencyMapping[slope]++;
        }

        for(auto it : slopeXFrequencyMapping) {
            ans = max(ans, it.second);
        }
    }

    return ans + 1;
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
            auto node = q.front();
            q.pop();

            level.push_back(node->val);

            if(node->left) {
                q.push(node->left);
            }

            if(node->right) {
                q.push(node->right);
            }
        }

        levels.push_back(level);
    }

    return levels;
}

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);

    
    return 0;
}