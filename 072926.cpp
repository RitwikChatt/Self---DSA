#include<bits/stdc++.h>
using namespace std;

class Solution {
    private:
    void dfs(int node, map<int, vector<int>>& adjList, vector<bool>& visited, stack<int>& st) {
        visited[node] = true;

        for(auto neighbour : adjList[node]) {
            if(!visited[neighbour]) {
                dfs(neighbour, adjList, visited, st);
            }
        }

        st.push(node);
    }

    void dfs(int node, map<int, vector<int>>& adjList, vector<bool>& visited, vector<int>& scc) {
        visited[node] = true;
        scc.push_back(node);

        for(auto neighbour : adjList[node]) {
            if(!visited[neighbour]) {
                dfs(neighbour, adjList, visited, scc);
            }
        }
    }

    public:
    vector<vector<int>> kosaraju(int V, vector<vector<int>> &edges) {
        map<int, vector<int>> adjList;

        for(auto edge : edges) {
            int u = edge[0], v = edge[1];
            adjList[u].push_back(v);
        }

        vector<bool> visited(V);
        stack<int> st;

        for(int i = 0; i < V; i++) {
            if(!visited[i]) {
                dfs(i, adjList, visited, st);
            }
        }

        map<int, vector<int>> adjListRev;

        for(int v = 0; v < V; v++) {
            for(auto u : adjList[v]) {
                adjListRev[u].push_back(v);
            }
        }

        fill(visited.begin(), visited.end(), false);

        vector<vector<int>> sccs;

        while(!st.empty()) {
            auto node = st.top();
            st.pop();

            if(!visited[node]) {
                vector<int> scc;
                dfs(node, adjListRev, visited, scc);
                sccs.push_back(scc);
            }
        }

        return sccs;
    }
};

int timer = 1;

void criticalConnectionsUtilDFS(int node, int parent, map<int, vector<int>>& adjList, 
    vector<int>& tin, vector<int>& low, vector<bool>& visited, vector<vector<int>>& bridges) {
        visited[node] = true;
        tin[node] = low[node] = timer++;

        for(auto neighbour : adjList[node]) {
            if(neighbour == parent) {
                continue;
            }

            if(!visited[neighbour]) {
                criticalConnectionsUtilDFS(neighbour, node, adjList, tin, low, visited, bridges);
                low[node] = min(low[node], low[neighbour]);
                if(low[neighbour] > tin[node]) {
                    bridges.push_back({node, neighbour});
                }
            } else {
                low[node] = min(low[node], tin[neighbour]);
            }
        }
}

vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
    map<int, vector<int>> adjList;

    for(auto connection : connections) {
        int u = connection[0], v = connection[1];
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    vector<int> tin(n, -1), low(n, -1);
    vector<bool> visited(n);

    vector<vector<int>> bridges;

    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            criticalConnectionsUtilDFS(i, -1, adjList, tin, low, visited, bridges);
        }
    }

    return bridges;
}

void articulationPointsUtilDFS(int node, int parent, map<int, vector<int>>& adjList, 
    vector<int>& tin, vector<int>& low, vector<bool>& visited, vector<bool>& isArticulation) {
        visited[node] = true;
        tin[node] = low[node] = timer++;

        int children = 0;

        for(auto neighbour : adjList[node]) {
            if(neighbour == parent) {
                continue;
            }

            if(!visited[neighbour]) {
                articulationPointsUtilDFS(neighbour, node, adjList, tin, low, visited, isArticulation);
                low[node] = min(low[node], low[neighbour]);

                if(parent != -1 and low[neighbour] >= tin[node]) {
                    isArticulation[node] = true;
                }

                children++;
            } else {
                low[node] = min(low[node], tin[neighbour]);
            }
        }

        if(parent == -1 and children > 1) {
            isArticulation[node] = true;
        }
}

vector<int> articulationPoints(int V, vector<vector<int>>& edges) {
    map<int, vector<int>> adjList;

    for(auto edge : edges) {
        int u = edge[0], v = edge[1];
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    vector<int> tin(V), low(V);
    vector<bool> visited(V), isArticulation(V);

    for(int i = 0; i < V; i++) {
        if(!visited[i]) {
            articulationPointsUtilDFS(i, -1, adjList, tin, low, visited, isArticulation);
        }
    }

    vector<int> articulationPoints;

    for(int i = 0; i < V; i++) {
        if(isArticulation[i]) {
            articulationPoints.push_back(i);
        }
    }

    return articulationPoints.empty() ? vector<int>{-1} : articulationPoints;
}

void allPathsSourceTargetUtilDFS(int node, vector<vector<int>>& graph, 
    vector<int>& path, vector<vector<int>>& paths, int V) {
        if(node == V - 1) {
            paths.push_back(path);
            return;
        }

        for(auto neighbour : graph[node]) {
            path.push_back(neighbour);
            allPathsSourceTargetUtilDFS(neighbour, graph, path, paths, V);
            path.pop_back();
        }

}

vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
    int V = graph.size();

    vector<int> path;
    vector<vector<int>> paths;

    path.push_back(0);

    allPathsSourceTargetUtilDFS(0, graph, path, paths, V);

    return paths;
}

class DisjointSet {
    private:
    vector<int> parent, size;

    public:
    DisjointSet(int n) {
        this->parent.resize(n);
        for(int i = 0; i < n; i++) {
            this->parent[i] = i;
        }

        this->size.resize(n, 1);
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

const vector<int> dr = {-1, 0, 1, 0}, dc = {0, 1, 0, -1};

int maxAreaOfIsland(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();

    DisjointSet* ds = new DisjointSet(m * n);

    int maxArea = INT_MIN;

    bool allZero = true;

    for(int row = 0; row < m; row++) {
        for(int col = 0; col < n; col++) {
            if(!grid[row][col]) {
                continue;
            }

            allZero = false;

            int r = row, c = col;

            for(int i = 0; i < 4; i++) {
                int nr = r + dr[i], nc = c + dc[i];

                if(nr >= 0 and nr < m and nc >= 0 and nc < n and grid[nr][nc]) {
                    ds->unite(n * r + c, n * nr + nc);
                }
            }
        }
    }

    for(int i = 0; i < m * n; i++) {
        maxArea = max(maxArea, ds->getSize(ds->find(i)));
    }

    return !allZero ? maxArea : 0;
}

void canVisitAllRoomsUtilDFS(int node, vector<vector<int>>& adjList, vector<bool>& visited) {
    visited[node] = true;

    for(auto neighbour : adjList[node]) {
        if(!visited[neighbour]) {
            canVisitAllRoomsUtilDFS(neighbour, adjList, visited);
        }
    }
}

bool canVisitAllRooms(vector<vector<int>>& rooms) {
    int V = rooms.size();

    vector<bool> visited(V);

    canVisitAllRoomsUtilDFS(0, rooms, visited);

    for(int i = 0; i < V; i++) {
        if(!visited[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    vector<vector<int>> rooms = {{1,3},{3,0,1},{2},{0}};

    canVisitAllRooms(rooms) ? cout << "true" : cout << "false";

    return 0;
}