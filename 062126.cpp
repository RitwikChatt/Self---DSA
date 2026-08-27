#include<bits/stdc++.h>
using namespace std;

class DSU {
    private:
    vector<int> parent, rank;

    public:
    DSU(int n) {
        this->parent.resize(n);
        this->rank.resize(n, 1);

        for(int i = 0; i < n; i++) {
            this->parent[i] = i;
        }
    }

    int find(int node) {
        if(this->parent[node] == node) {
            return node;
        }

        return this->parent[node] = find(this->parent[node]);
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

vector<int> dijkstra(int V, int src, map<int, vector<pair<int, int>>>& adjList) {
    vector<int> dist(V, INT_MAX);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while(!pq.empty()) {
        auto [d, node] = pq.top();
        pq.pop();

        if(d > dist[node]) {
            continue;
        }

        for(auto& [neighbour, wt] : adjList[node]) {
            if(dist[node] + wt < dist[neighbour]) {
                dist[neighbour] = dist[node] + wt;
                pq.push({dist[neighbour], neighbour});
            }
        }
    }

    return dist;
}

class Graph {
    private:
    int numOfNodes;
    vector<vector<int>> adjMat;

    public:
    Graph(int numOfNodes) {
        this->numOfNodes = numOfNodes;

        this->adjMat.resize(this->numOfNodes, vector<int>(this->numOfNodes, INT_MAX));

        for(int i = 0; i < this->numOfNodes; i++) {
            this->adjMat[i][i] = 0;
        }
    }

    void addEdge(int u, int v, int wt) {
        this->adjMat[u][v] = wt;
    }

    vector<vector<int>> floydWarshall() {
        vector<vector<int>> dist = this->adjMat;

        for(int k = 0; k < this->numOfNodes; k++) {
            for(int i = 0; i < this->numOfNodes; i++) {
                for(int j = 0; j < this->numOfNodes; j++) {
                    if(dist[i][k] == INT_MAX or dist[k][j] == INT_MAX) {
                        continue;
                    }

                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        return dist;
    }
};

const vector<int> dx = {-1, 0, 1, 0};
const vector<int> dy = {0, 1, 0, -1};

void bfs(vector<string>& grid, int i, int j) {
    int m = grid.size(), n = grid[0].size();

    queue<pair<int, int>> q;
    q.push({i, j});
    grid[i][j] = '0';

    while(!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];

            if(nx >= 0 and nx < m and ny >= 0 and ny < n and grid[nx][ny] == '1') {
                grid[nx][ny] = '0';
                q.push({nx, ny});
            }
        }
    }
}

void dfs(vector<string>& grid, int x, int y) {
    int m = grid.size(), n = grid[0].size();

    if(x < 0 or x >= m or y < 0 or y >= n or grid[x][y] == '0') {
        return;
    }

    grid[x][y] = '0';

    for(int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        dfs(grid, nx, ny);
    }
}

int numIslands(vector<string>& grid) {
    int m = grid.size(), n = grid[0].size();
    int islands = 0;

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(grid[i][j] == '1') {
                islands++;
                dfs(grid, i, j);
            }
        }
    }

    return islands;
}

int orangesRotting(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();

    int freshOranges = 0;
    queue<pair<int, int>> rottenOranges;

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(grid[i][j] == 1) {
                freshOranges++;
            } else if(grid[i][j] == 2) {
                rottenOranges.push({i, j});
            }
        }
    }

    int elapsedTime = 0;

    while(!rottenOranges.empty() and freshOranges) {
        int sz = rottenOranges.size();

        for(int i = 0; i < sz; i++) {
            auto [x, y] = rottenOranges.front();
            rottenOranges.pop();

            for(int j = 0; j < 4; j++) {
                int nx = x + dx[j], ny = y + dy[j];

                if(nx >= 0 and nx < m and ny >= 0 and ny < n and grid[nx][ny] == 1) {
                    grid[nx][ny] = 2;
                    rottenOranges.push({nx, ny});
                    freshOranges--;
                }
            }
        }

        elapsedTime++;
    }

    return freshOranges ? -1 : elapsedTime;
}

int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();

    const vector<int> dx = {-1, -1, 0, 1, 1, 1, 0, -1};
    const vector<int> dy = {0, 1, 1, 1, 0, -1, -1, -1};

    if(grid[0][0] == 1 or grid[m - 1][n - 1] == 1) {
        return -1;
    }

    queue<tuple<int, int, int>> q;
    q.push({0, 0, 1});
    grid[0][0] = 1;

    while(!q.empty()) {
        auto [x, y, dist] = q.front();
        q.pop();

        if(x == m - 1 and y == n - 1) {
            return dist;
        }

        for(int i = 0; i < 8; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if(nx >= 0 and nx < m and ny >= 0 and ny < n and !grid[nx][ny]) {
                grid[nx][ny] = 1;
                q.push({nx, ny, dist + 1});
            }
        }
    }

    return -1;
}

vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    int m = mat.size(), n = mat[0].size();

    queue<pair<int, int>> q;

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(!mat[i][j]) {
                q.push({i, j});
            } else {
                mat[i][j] = -1;
            }
        }
    }

    while(!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if(nx >= 0 and nx < m and ny >= 0 and ny < n and mat[nx][ny] == -1) {
                q.push({nx, ny});
                mat[nx][ny] = 1 + mat[x][y];
            }
        }
    }

    return mat;
}

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    
}

int main() {
    int numCourses = 2;
    vector<vector<int>> prerequisites = {
        {1,0}, 
        {0,1}
    };

    canFinish(numCourses, prerequisites) ? cout << "true" << endl : cout << "false" << endl;
    return 0;
}