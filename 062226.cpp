#include<bits/stdc++.h>
using namespace std;

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    map<int, vector<int>> adjList;

    for(auto edge : prerequisites) {
        adjList[edge[1]].push_back(edge[0]);
    }

    vector<int> indegree(numCourses);

    for(auto neighbours : adjList) {
        for(auto neighbour : neighbours.second) {
            indegree[neighbour]++;
        }
    }

    queue<int> q;

    for(int node = 0; node < numCourses; node++) {
        if(!indegree[node]) {
            q.push(node);
        }
    }

    int processed = 0;

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        processed++;

        for(int neighbour : adjList[node]) {
            indegree[neighbour]--;
            if(!indegree[neighbour]) {
                q.push(neighbour);
            }
        }
    }

    return processed == numCourses;
}

vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    map<int, vector<int>> adjacencyList;

    for(auto edge : prerequisites) {
        adjacencyList[edge[1]].push_back(edge[0]);
    }

    vector<int> indegree(numCourses);

    for(auto neighbours : adjacencyList) {
        for(auto neighbour : neighbours.second) {
            indegree[neighbour]++;
        }
    }

    queue<int> q;

    for(int node = 0; node < numCourses; node++) {
        if(!indegree[node]) {
            q.push(node);
        }
    }

    int processsed = 0;
    vector<int> order;

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        processsed++;
        order.push_back(node);

        for(auto neighbour : adjacencyList[node]) {
            indegree[neighbour]--;
            if(!indegree[neighbour]) {
                q.push(neighbour);
            }
        }
    }

    return processsed == numCourses ? order : vector<int>{};
}

class DSU {
    private:
    vector<int> parent, rank;

    int find(int node) {
        if(this->parent[node] == node) {
            return node;
        }

        return this->parent[node] = find(this->parent[node]);
    }

    public:
    DSU() {
        this->parent.resize(1001);
        this->rank.resize(1001, 1);

        for(int i = 1; i <= 1000; i++) {
            this->parent[i] = i;
        }
    }

    void unite(int u, int v) {
        u = this->find(u);
        v = this->find(v);

        if(u == v) {
            return;
        } 

        if(this->rank[u] < this->rank[v]) {
            swap(u, v);
        }

        this->parent[v] = u;
        this->rank[u] += this->rank[v];
    }

    bool isSameComponent(int u, int v) {
        return this->find(u) == this->find(v);
    }
};

vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    DSU* dsu = new DSU();

    for(auto edge : edges) {
        if(dsu->isSameComponent(edge[0], edge[1])) {
            return edge;
        } else {
            dsu->unite(edge[0], edge[1]);
        }
    }

    return vector<int>{};
}

int main() {
    
    return 0;
}