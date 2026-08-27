#include<bits/stdc++.h>
using namespace std;

class DSU {
    private:
    vector<int> parent, size;

    public:
    DSU(int n) {
        this->size.resize(n + 1, 1);
        this->parent.resize(n + 1);

        for(int i = 1; i <= n; i++) this->parent[i] = i;
    }

    int find(int u) {
        if(u == this->parent[u]) {
            return u;
        }

        return this->parent[u] = this->find(this->parent[u]);
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

};

pair<int, vector<pair<int, int>>> spanningTree(int V, vector<vector<int>>& edges) {
    map<int, vector<pair<int, int>>> adjList;

    for(auto edge : edges) {
        int u = edge[0], v = edge[1], wt = edge[2];
        adjList[u].push_back({v, wt});
        adjList[v].push_back({u, wt});
    }

    priority_queue<
    tuple<int, int, int>,
    vector<tuple<int, int, int>>, 
    greater<tuple<int, int, int>>
    > pq;

    vector<bool> visited(V);

    pq.push({0, 0, -1});
    
    int sum = 0;
    vector<pair<int, int>> mst;

    while(!pq.empty()) {
        auto [cost, node, parent] = pq.top();
        pq.pop();

        if(visited[node]) {
            continue;
        }

        visited[node] = true;

        if(parent != -1) {
            mst.push_back({parent, node});
        }

        sum += cost;

        for(auto &[neighbour, wt] : adjList[node]) {
            if(!visited[neighbour]) {
                pq.push({wt, neighbour, node});
            }
        }
    }

    return {sum, mst};
}

int main() {

    return 0;
}