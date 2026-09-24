#include<bits/stdc++.h>
using namespace std;

class FenwickTree {
    private:
    int size;
    vector<int> fen;

    public:
    FenwickTree(int size) {
        this->size = size + 1;
        this->fen.resize(this->size);
    }

    void update(int i, int add) {
        i++;

        while(i < this->size) {
            this->fen[i] += add;
            i += i & (-i);
        }
    }

    int sum(int i) {
        i++;

        int s = 0;

        while(i) {
            s += this->fen[i];
            i -= i & (-i);
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

class SegmentTree {
    private:
    vector<int> seg;
    vector<int> lazy;

    public:
    SegmentTree(int n) {
        this->seg.resize(4 * n);
        this->lazy.resize(4 * n);
    }

    void build(int index, int low, int high, vector<int>& arr) {
        if(low == high) {
            this->seg[index] = arr[low];
            return;
        }

        int mid = low + (high - low) / 2;

        this->build(2 * index + 1, low, mid, arr);
        this->build(2 * index + 2, mid + 1, high, arr);

        this->seg[index] = this->seg[2 * index + 1] + this->seg[2 * index + 2];
    }

    int query(int index, int low, int high, int l, int r) {
        if(low >= l and high <= r) {
            return this->seg[index];
        }

        if(high < l or low > r) {
            return 0;
        }

        int mid = low + (high - low) / 2;

        return this->query(2 * index + 1, low, mid, l, r) + this->query(2 * index + 2, mid + 1, high, l, r);
    }

    void pointUpdate(int index, int low, int high, int node, int val) {
        if(low == high) {
            this->seg[index] += val;
            return;
        }

        int mid = low + (high - low) / 2;

        if(node >= low and node <= mid) this->pointUpdate(2 * index + 1, low, mid, node, val);
        else this->pointUpdate(2 * index + 2, mid + 1, high, node, val);

        this->seg[index] = this->seg[2 * index + 1] + this->seg[2 * index + 2];
    }

    void rangeUpdate(int index, int low, int high, int l, int r, int val) {
        if(this->lazy[index]) {
            this->seg[index] += (high - low + 1) * this->lazy[index];
            
            if(low != high) {
                this->lazy[2 * index + 1] += this->lazy[index];
                this->lazy[2 * index + 2] += this->lazy[index];
            }

            this->lazy[index] = 0;
        }

        if(r < low or l > high) return;

        if(low >= l and high <= r) {
            this->seg[index] += (high - low + 1) * val;

            if(low != high) {
                this->lazy[2 * index + 1] += val;
                this->lazy[2 * index + 2] += val;
            }

            return;
        }

        int mid = low + (high - low) / 2;

        this->rangeUpdate(2 * index + 1, low, mid, l, r, val);
        this->rangeUpdate(2 * index + 2, mid + 1, high, l, r, val);

        this->seg[index] = this->seg[2 * index + 1] + this->seg[2 * index + 2];
    }

    int querySumLazy(int index, int low, int high, int l, int r, int val) {
        if(this->lazy[index]) {
            this->seg[index] += (high - low + 1) * this->lazy[index];
            
            if(low != high) {
                this->lazy[2 * index + 1] += this->lazy[index];
                this->lazy[2 * index + 2] += this->lazy[index];
            }

            this->lazy[index] = 0;
        }

        if(r < low or l > high) return 0;

        if(low >= l and high <= r) {
            return this->seg[index];
        }

        int mid = low + (high - low) / 2;

        return querySumLazy(2 * index + 1, low, mid, l, r, val) + this->querySumLazy(2 * index + 2, mid + 1, high, l, r, val);
    }
};

long long countOperationsToEmptyArrayFenwickTree(vector<int>& nums) {
    int n = nums.size();

    vector<pair<int, int>> elementsIndexMapping;

    for(int i = 0; i < n; i++) {
        elementsIndexMapping.push_back({nums[i], i});
    }

    sort(elementsIndexMapping.begin(), elementsIndexMapping.end());

    FenwickTree* fenwickTree = new FenwickTree(n);

    for(int i = 0; i < n; i++) {
        fenwickTree->update(i, 1);
    }

    int curr = 0;

    long long ans = 0;

    for(auto& [val, index] : elementsIndexMapping) {
        if(index >= curr) {
            ans += fenwickTree->rangeSum(curr, index);
        } else {
            ans += fenwickTree->rangeSum(curr, n - 1);
            ans += fenwickTree->rangeSum(0, index);
        }

        fenwickTree->update(index, -1);

        curr = index + 1;

        if(curr == n) {
            curr = 0;
        }
    }

    return ans;
}

long long countOperationsToEmptyArray(vector<int>& nums) {
    int n = nums.size();

    vector<pair<int, int>> elementsIndexMapping;

    for(int i = 0; i < n; i++) {
        elementsIndexMapping.push_back({nums[i], i});
    }

    sort(elementsIndexMapping.begin(), elementsIndexMapping.end());

    SegmentTree* segmentTree = new SegmentTree(n);

    vector<int> alive(n, 1);

    segmentTree->build(0, 0, n - 1, alive);

    int curr = 0;

    long long ans = 0;

    for(auto& [val, index] : elementsIndexMapping) {
        if(index >= curr) {
            ans += segmentTree->query(0, 0, n - 1, curr, index);
        } else {
            ans += segmentTree->query(0, 0, n - 1, curr, n - 1);
            ans += segmentTree->query(0, 0, n - 1, 0, index);
        }

        segmentTree->pointUpdate(0, 0, n - 1, index, -1);

        curr = index + 1;

        if(curr == n) {
            curr = 0;
        }
    }

    return ans;
}

int main() {
    vector<int> nums = {3,4,-1};

    cout << countOperationsToEmptyArray(nums) << endl;
    return 0;
}