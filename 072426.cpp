#include<bits/stdc++.h>
using namespace std;

class DisjointSet {
    private:
    vector<int> parent, size;

    public:
    DisjointSet(int n) {
        this->parent.resize(n);
        for(int i = 0; i < n; i++) this->parent[i] = i;

        this->size.resize(n, 1);
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

    bool belongsToSameComponent(int u, int v) {
        return this->find(u) == this->find(v);
    }

};

int spanningTree(int V, vector<vector<int>>& edges, vector<pair<int, int>>& mst) {
    sort(edges.begin(), edges.end(), [](vector<int>& a, vector<int>& b) {
        return a[2] < b[2];
    });

    DisjointSet* ds = new DisjointSet(V);

    int mstWt = 0;

    for(auto edge : edges) {
        int u = edge[0], v = edge[1], wt = edge[2];

        if(!ds->belongsToSameComponent(u, v)) {
            mstWt += wt;
            mst.push_back({u, v});
            ds->unite(u, v);
        }
    }

    return mstWt;
}

int findCircleNum(vector<vector<int>>& isConnected) {
    int V = isConnected.size();

    DisjointSet* ds = new DisjointSet(V);

    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {
            if(isConnected[i][j]) {
                ds->unite(i, j);
            }
        }
    }

    int provinces = 0;

    for(int i = 0; i < V; i++) {
        if(ds->find(i) == i) {
            provinces++;
        }
    }

    return provinces;
}

void makeConnectedUtilDFS(int node, map<int, vector<int>>& adjList, vector<bool>& visited) {
    visited[node] = true;

    for(auto neighbour : adjList[node]) {
        if(!visited[neighbour]) {
            makeConnectedUtilDFS(neighbour, adjList, visited);
        }
    }
}

int makeConnected(int n, vector<vector<int>>& connections) {
    int cables = connections.size();

    if(cables < n - 1) {
        return -1;
    }

    map<int, vector<int>> adjList;

    for(auto connection : connections) {
        int u = connection[0], v = connection[1];
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    int clusters = 0;

    vector<bool> visited(n);

    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            clusters++;
            makeConnectedUtilDFS(i, adjList, visited);
        }
    }

    return clusters - 1;
}

vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    map<string, int> emailIDToNodeMapping;

    int id = 0;

    for(auto account : accounts) {
        for(int i = 1; i < account.size(); i++) {
            if(emailIDToNodeMapping.find(account[i]) == emailIDToNodeMapping.end()) {
                emailIDToNodeMapping[account[i]] = id++;
            }
        }
    }

    map<int, string> nodeToEmailIDMapping;

    for(auto [emailID, node] : emailIDToNodeMapping) {
        nodeToEmailIDMapping[node] = emailID;
    }

    map<int, string> nodeToNameMapping;

    for(auto account : accounts) {
        nodeToNameMapping[emailIDToNodeMapping[account[1]]] = account[0];
    }

    int V = emailIDToNodeMapping.size();

    DisjointSet* ds = new DisjointSet(V);

    for(auto account : accounts) {
        for(int i = 2; i < account.size(); i++) {
            ds->unite(emailIDToNodeMapping[account[1]], emailIDToNodeMapping[account[i]]);
        }
    }

    map<int, vector<int>> groups;

    for(int i = 0; i < V; i++) {
        groups[ds->find(i)].push_back(i);
    }

    vector<vector<string>> mergedAccounts;

    for(auto group : groups) {
        vector<string> account = {nodeToNameMapping[group.first]};
        for(auto node : group.second) {
            account.push_back(nodeToEmailIDMapping[node]);
        }
        sort(account.begin() + 1, account.end());
        mergedAccounts.push_back(account);
    }

    return mergedAccounts;
}

vector<int> numOfIslands(int n, int m, vector<vector<int>>& operators) {
    
}

int main() {
    int n = 4, m = 5;
    vector<vector<int>> operators = {{1, 1}, {0, 1}, {3, 3}, {3, 4}};

    for(auto it : numOfIslands(n, m, operators)) {
        cout << it << ' ';
    }

    return 0;
}