#include<bits/stdc++.h>
using namespace std;

class Graph {
    private:
    int numOfNodes;
    map<int, vector<int>> adjList;

    void dfsUtil(int node, vector<bool>& vis) {
        vis[node] = true;
        cout << node << ' ';

        for(auto nbr : this->adjList[node]) {
            if(!vis[nbr]) {
                dfsUtil(nbr, vis);
            }
        }
    }

    public:
    Graph(int numOfNodes) {
        this->numOfNodes = numOfNodes;
    }

    void addEdge(int a, int b) {
        this->adjList[a].push_back(b);
        this->adjList[b].push_back(a);
    }

    void dfs(int root) {
        vector<bool> vis(this->numOfNodes, false);
        dfsUtil(root, vis);
    }

    void bfs(int root) {
        vector<bool> visited(this->numOfNodes, false);

        queue<int> q;

        q.push(root);
        visited[root] = true;

        while(!q.empty()) {
            int node = q.front();
            q.pop();

            cout << node << ' ';

            for(auto nbr : this->adjList[node]) {
                if(!visited[nbr]) {
                    visited[nbr] = true;
                    q.push(nbr);
                }
            }
        }
    }

};

vector<int> dijkstra(int v, int src, map<int, vector<pair<int, int>>>& adj) {
    vector<int> dist(v, INT_MAX);

    priority_queue<pair<int, int>, 
        vector<pair<int, int>>, 
        greater<pair<int, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while(!pq.empty()) {
        auto [d, node] = pq.top();
        pq.pop();

        if(d > dist[node]) {
            continue;
        }

        for(auto &[neighbour, wt] : adj[node]) {
            if(dist[node] + wt < dist[neighbour]) {
                dist[neighbour] = dist[node] + wt;
                pq.push({dist[neighbour], neighbour});
            }
        }
    }

    return dist;
}

int main() {
    map<int, vector<pair<int, int>>> adj;
    adj[0].push_back({1, 1});
    adj[0].push_back({4, 1});
    adj[1].push_back({0, 1});
    adj[1].push_back({2, 4});
    adj[1].push_back({3, 2});
    adj[1].push_back({4, 3});
    adj[2].push_back({1, 4});
    adj[3].push_back({1, 2});
    adj[3].push_back({4, 7});
    adj[4].push_back({1, 3});
    adj[4].push_back({3, 7});
    adj[4].push_back({0, 1});

    for(auto it : dijkstra(5, 0, adj)) { 
        cout << it << ' ';
    }

    return 0;
}