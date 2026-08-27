#include<bits/stdc++.h>
using namespace std;

class DisjointSet {
    private:
    unordered_map<int, int> parent, size;

    public:
    DisjointSet(vector<int>& nodeIDS) {
        for(auto nodeID : nodeIDS) {
            this->parent[nodeID] = nodeID;
            this->size[nodeID] = 1;
        }
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

        if(u == v) {
            return;
        }

        if(this->size[u] < this->size[v]) {
            swap(u, v);   
        }

        this->parent[v] = u;
        this->size[u] += this->size[v];
    }

    int getSize(int node) {
        return this->size[node];
    }

};

int removeStones(vector<vector<int>>& stones) {
    int maxR = INT_MIN, maxC = INT_MIN;

    for(int i = 0; i < stones.size(); i++) {
        maxR = max(maxR, stones[i][0]);
        maxC = max(maxC, stones[i][1]);
    }

    int m = maxR + 1, n = maxC + 1;

    vector<int> nodeIDS;

    for(auto stone : stones) {
        nodeIDS.push_back(n * stone[0] + stone[1]);
    }

    DisjointSet* ds = new DisjointSet(nodeIDS);

    for(int i = 0; i < stones.size(); i++) {
        for(int j = i - 1; j >= 0; j--) {
            if(stones[i][0] == stones[j][0] or stones[i][1] == stones[j][1]) {
                ds->unite(n * stones[j][0] + stones[j][1], n * stones[i][0] + stones[i][1]);
            }
        }

        for(int j = i + 1; j < stones.size(); j++) {
            if(stones[i][0] == stones[j][0] or stones[i][1] == stones[j][1]) {
                ds->unite(n * stones[j][0] + stones[j][1], n * stones[i][0] + stones[i][1]);
            }
        }
    }

    int maxStonesRemoved = 0;

    for(auto nodeID : nodeIDS) {
        if(nodeID == ds->find(nodeID)) {
            maxStonesRemoved += ds->getSize(nodeID) - 1;
        }
    }

    return maxStonesRemoved;
}

int main() {
    vector<vector<int>> stones = {
        {0, 1}, {1, 0}, {1, 1}
    };

    cout << removeStones(stones) << endl;

    return 0;
}