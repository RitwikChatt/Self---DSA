#include<bits/stdc++.h>
using namespace std;

int minSideJumps(vector<int>& obstacles) {
    int n = obstacles.size();

    //dp[i][j] -> Minimum side jumps required to reach lane i at position j

    vector<vector<int>> dp(3, vector<int>(n));

    dp[0][0] = 1, dp[1][0] = 0, dp[2][0] = 1;

    for(int j = 1; j < n; j++) {
        for(int i = 0; i < 3; i++) {
            if(obstacles[j] == i + 1) {
                dp[i][j] = INT_MAX;
                continue;
            }

            dp[i][j] = dp[i][j - 1];
        }

        for(int i = 0; i < 3; i++) {
            if(dp[i][j] == INT_MAX and obstacles[j] == i + 1) {
                continue;
            }

            for(int k = 0; k < 3; k++) {
                if(k == i) {
                    continue;
                }

                if(dp[k][j] != INT_MAX) {
                    dp[i][j] = min(dp[i][j], 1 + dp[k][j]);
                }
            }
        }
    }

    return min({dp[0][n - 1], dp[1][n - 1], dp[2][n - 1]});
}

class FenwickTree {
    private:
    int size;
    vector<int> fen;

    public:
    FenwickTree(int n) {
        this->size = n + 1;
        this->fen.resize(size);
    }

    void update(int i, int add) {
        i++;

        while(i < this->size) {
            this->fen[i] += add;
            i += (i & (-i));
        }
    }

    int sum(int i) {
        int s = 0;

        i++;

        while(i) {
            s += this->fen[i];
            i -= (i & (-i));
        }

        return s;
    }
    
    int rangeSum(int l, int r) {
        return this->sum(r) - this->sum(l - 1);
    }

    int find(int k) {
        int curr = 0, prevSum = 0;

        for(int i = log2(this->size); i >= 0; i--) {
            int next = curr + (1 << i);
            if(next < this->size and this->fen[next] + prevSum < k) {
                curr = next;
                prevSum += this->fen[curr];
            }
        }

        return curr;
    }
};

class DisjointSet {
    private:
    vector<int> parent, size;

    public:
    DisjointSet(int n) {
        this->size.resize(n, 1);
        this->parent.resize(n);

        for(int i = 0; i < n; i++) this->parent[i] = i;
    }

    int find(int node) {
        if(node == this->parent[node]) {
            return node;
        }

        return this->parent[node] = this->find(this->parent[node]);
    }

    void unite(int u, int v) {
        u = this->find(u);
        v = this->find(v);

        if(this->size[u] < this->size[v]) {
            swap(u, v);
        }

        this->size[u] += this->size[v];
        this->parent[v] = u;
    }
};

class SegmentTree {
    private:
    vector<int> seg;

    public:
    SegmentTree(int n) {
        this->seg.resize(4 * n);
    }

    void build(int index, int low, int high, vector<int>& nums) {
        if(low == high) {
            this->seg[index] = nums[low];
            return;
        }

        int mid = low + (high - low) / 2;

        this->build(2 * index + 1, low, mid, nums);
        this->build(2 * index + 2, mid + 1, high, nums);

        this->seg[index] = max(this->seg[2 * index + 1], this->seg[2 * index + 2]);
    }

    int query(int index, int low, int high, int l, int r) {
        if(low >= l and high <= r) {
            return this->seg[index];
        }

        if(high < l or low > r) {
            return INT_MIN;
        }

        int mid = low + (high - low) / 2;

        return max(this->query(2 * index + 1, low, mid, l, r), this->query(2 * index + 2, mid + 1, high, l, r));
    }
};

int main() {
    
    return 0;
}