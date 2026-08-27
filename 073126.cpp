#include<bits/stdc++.h>
using namespace std;

int minimumJumps(vector<int>& forbidden, int a, int b, int x) {
    unordered_set<int> forbiddenPositions(forbidden.begin(), forbidden.end());

    int limit = max(*max_element(forbidden.begin(), forbidden.end()), x) + a + b;

    vector<vector<bool>> visited(limit + 1, vector<bool>(2));

    queue<tuple<int, bool, int>> q;

    q.push({0, true, 0});
    visited[0][1] = true;

    while(!q.empty()) {
        auto [pos, wasBack, jumps] = q.front();
        q.pop();

        if(pos == x) {
            return jumps;
        }

        int newPos = pos + a;

        if(newPos <= limit and !visited[newPos][0] and !forbiddenPositions.count(newPos)) {
            visited[newPos][0] = true;
            q.push({newPos, false, jumps + 1});
        }

        newPos = pos - b;

        if(!wasBack and newPos >= 0 and !visited[newPos][1] and !forbiddenPositions.count(newPos)) {
            visited[newPos][1] = true;
            q.push({newPos, true, jumps + 1});
        }
    }

    return -1;
}

class DisjointSet {
    private:
    vector<int> parent, size;

    public:
    DisjointSet(int n) {
        this->parent.resize(n + 1);
        for(int i = 0; i <= n; i++) this->parent[i] = i;

        this->size.resize(n + 1, 1);
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
};

int minimumCost(int n, vector<vector<int>>& connections) {
    sort(connections.begin(), connections.end(), [](vector<int>& a, vector<int>& b) {
        return a[2] < b[2];
    });

    DisjointSet* ds = new DisjointSet(n);

    int cost = 0, edgesUsed = 0;

    for(auto connection : connections) {
        int u = connection[0], v = connection[1], wt = connection[2];
        
        if(ds->find(u) != ds->find(v)) {
            ds->unite(u, v);
            cost += wt;
            edgesUsed++;
        }

        if(edgesUsed == n - 1) {
            break;
        }
    }

    return edgesUsed == n - 1 ? cost : -1;
}

vector<int> dr = {-1, 0, 1, 0}, dc = {0, 1, 0, -1};

int uniquePathsIIIUtilDFS(int r, int c, vector<vector<int>>& grid, vector<vector<bool>>& visited, int remaining) {
    if(r < 0 or r >= grid.size() or c < 0 or c >= grid[0].size() or visited[r][c] or grid[r][c] == -1) {
        return 0;
    }

    remaining--;

    if(grid[r][c] == 2) {
        return remaining == 0;
    }

    visited[r][c] = true;

    int paths = 0;

    for(int i = 0; i < 4; i++) {
        int nr = r + dr[i], nc = c + dc[i];
        paths += uniquePathsIIIUtilDFS(nr, nc, grid, visited, remaining);
    }

    visited[r][c] = false;
    return paths;
}

int uniquePathsIII(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();

    vector<vector<bool>> visited(m, vector<bool>(n));

    int remaining = 0, startRow, startCol;

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(grid[i][j] == 1) {
                startRow = i, startCol = j;
            }

            if(grid[i][j] != -1) {
                remaining++;
            }
        }
    }

    return uniquePathsIIIUtilDFS(startRow, startCol, grid, visited, remaining);
}

bool possibleBipartitionUtilDFS(int node, int c, map<int, vector<int>>& adjList, vector<int>& color) {
    color[node] = c;

    for(auto neighbour : adjList[node]) {
        if(color[neighbour] == -1) {
            if(!possibleBipartitionUtilDFS(neighbour, 1 - c, adjList, color)) {
                return false;
            }
        } else if(color[neighbour] == c) {
            return false;
        }
    }

    return true;
}

bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
    map<int, vector<int>> adjList;

    for(auto dislike : dislikes) {
        int u = dislike[0], v = dislike[1];
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    vector<int> color(n + 1, -1);

    for(int i = 1; i <= n; i++) {
        if(color[i] == -1) {
            if(!possibleBipartitionUtilDFS(i, 0, adjList, color)) {
                return false;
            }
        }
    }

    return true;
}

int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
    
}

int main() {
    vector<vector<int>> graph = {{1,1,0},{1,1,0},{0,0,1}};
    vector<int> initial = {0,1};

    cout << minMalwareSpread(graph, initial) << endl;

    return 0;
}