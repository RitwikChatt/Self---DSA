#include<bits/stdc++.h>
using namespace std;

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

    int getComponentSize(int node) {
        return this->size[this->find(node)];
    }

};

int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
    int V = graph.size();

    DisjointSet* ds = new DisjointSet(V);

    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {
            if(graph[i][j]) {
                ds->unite(i, j);
            }
        }
    }

    unordered_set<int> infectedComponents;

    for(auto infectedNode : initial) {
        infectedComponents.insert(ds->find(infectedNode));
    }

    int mInitial = 0;

    for(auto infectedComponent : infectedComponents) {
        mInitial += ds->getComponentSize(infectedComponent);
    }

    sort(initial.begin(), initial.end());

    int nodeToBeRemoved = initial[0], mFinal = mInitial;

    for(int i = 0; i < initial.size(); i++) {
        int infectedNode = initial[i];
        bool anotherNodeBelongingToSameComponentAsInfectedNodePresent = false;

        for(int j = i - 1; j >= 0; j--) {
            if(ds->find(infectedNode) == ds->find(initial[j])) {
                anotherNodeBelongingToSameComponentAsInfectedNodePresent = true;
                break;
            }
        }

        if(!anotherNodeBelongingToSameComponentAsInfectedNodePresent) {
            for(int j = i + 1; j < initial.size(); j++) {
                if(ds->find(infectedNode) == ds->find(initial[j])) {
                    anotherNodeBelongingToSameComponentAsInfectedNodePresent = true;
                    break;
                }
            }
        }

        int spread;

        if(!anotherNodeBelongingToSameComponentAsInfectedNodePresent) {
            spread = mInitial - ds->getComponentSize(infectedNode);
            if(spread < mFinal) {
                mFinal = spread;
                nodeToBeRemoved = infectedNode;
            }
        }

    }

    return nodeToBeRemoved;
}

int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
    map<int, vector<pair<int, int>>> adjList;

    for(auto edge : edges) {
        int u = edge[0], v = edge[1], wt = edge[2] + 1;
        adjList[u].push_back({v, wt});
        adjList[v].push_back({u, wt});
    }

    priority_queue<
    pair<int, int>, 
    vector<pair<int, int>>, 
    greater<pair<int, int>>
    > pq;
    
    vector<int> dist(n, INT_MAX);

    pq.push({0, 0});
    dist[0] = 0;

    while(!pq.empty()) {
        auto [d, node] = pq.top();
        pq.pop();

        for(auto &[neighbour, wt] : adjList[node]) {
            if(d + wt < dist[neighbour]) {
                dist[neighbour] = d + wt;
                pq.push({dist[neighbour], neighbour});
            }
        }
    }

    int count = 0;

    for(int i = 0; i < n; i++) {
        if(dist[i] <= maxMoves) {
            count++;
        }
    }

    for(auto edge : edges) {
        int u = edge[0], v = edge[1], cnt = edge[2];

        int fromU = min(cnt, max(0, maxMoves - dist[u]));
        int fromV = min(cnt, max(0, maxMoves - dist[v]));
        
        count += min(cnt, fromU + fromV);
    }

    return count;
}

int shortestPathAllKeys(vector<string>& grid) {
    int m = grid.size(), n = grid[0].size();

    vector<vector<vector<bool>>> visited(m, vector<vector<bool>>(n, vector<bool>(64)));

    queue<tuple<int, int, int, int>> q;

    int totalKeys = 0, startRow, startCol;

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(grid[i][j] == '@') {
                startRow = i, startCol = j;
            }

            if(grid[i][j] >= 'a' and grid[i][j] <= 'f') {
                totalKeys++;
            }
        }
    }

    visited[startRow][startCol][0] = true;
    q.push({startRow, startCol, 0, 0});

    vector<int> dr = {-1, 0, 1, 0}, dc = {0, 1, 0, -1};

    while(!q.empty()) {
        auto [r, c, mask, moves] = q.front();
        q.pop();

        int keysAcquired = 0;

        for(int i = 0; i < 6; i++) {
            if(mask & (1 << i)) {
                keysAcquired++;
            }
        }

        if(keysAcquired  == totalKeys) {
            return moves;
        }

        for(int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if(nr >= 0 and nr < m and nc >= 0 and nc < n and grid[nr][nc] != '#') {

                if(grid[nr][nc] >= 'a' and grid[nr][nc] <= 'f') {

                    int newMask = mask | (1 << (grid[nr][nc] - 'a'));

                    if(!visited[nr][nc][newMask]) {

                        visited[nr][nc][newMask] = true;
                        q.push({nr, nc, newMask, moves + 1});

                    }

                } else if(grid[nr][nc] >= 'A' and grid[nr][nc] <= 'F' 
                    and (mask & (1 << (grid[nr][nc] - 'A'))) and !visited[nr][nc][mask]) {

                    visited[nr][nc][mask] = true;
                    q.push({nr, nc, mask, moves + 1});

                } else if((grid[nr][nc] == '.' or grid[nr][nc] == '@') and !visited[nr][nc][mask]) {

                    visited[nr][nc][mask] = true;
                    q.push({nr, nc, mask, moves + 1});

                }
            }
        }
    }

    return -1;
}

int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
    
}

int main() {
    vector<vector<int>> routes = {{1,2,7}, {3,6,7}};
    int source = 1, target = 6;
    
    cout << numBusesToDestination(routes, source, target) << endl;

    return 0;
}