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
        int s = 0;

        i++;

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

    public:
    SegmentTree(int n) {
        this->seg.resize(4 * n);
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
        } else {
            int mid = (low + high) >> 1;

            if(node >= low and node <= mid) this->pointUpdate(2 * index + 1, low, mid, node, val);
            else this->pointUpdate(2 * index + 2, mid + 1, high, node, val);

            this->seg[index] = this->seg[2 * index + 1] + this->seg[2 * index + 2];
        }
    }
};

int main() {
    vector<int> arr = {2, 3, 1, 4, 2, 5, 2, 3, 1, 5};

    int n = arr.size();

    SegmentTree* segmentTree = new SegmentTree(n);

    segmentTree->build(0, 0, n - 1, arr);

    cout << segmentTree->query(0, 0, n - 1, 3, 7) << endl;

    segmentTree->pointUpdate(0, 0, n - 1, 3, 5);

    cout << segmentTree->query(0, 0, n - 1, 3, 7) << endl;
    return 0;
}