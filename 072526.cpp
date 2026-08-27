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

vector<int> numOfIslands(int n, int m, vector<vector<int>>& operators) {
    vector<vector<bool>> visited(n, vector<bool>(m));

    DisjointSet* ds = new DisjointSet(n * m);

    int islands = 0;

    vector<int> ans;

    for(auto op : operators) {
        int r = op[0], c = op[1];

        if(visited[r][c]) {
            ans.push_back(islands);
            continue;
        }

        visited[r][c] = true;
        islands++;

        vector<int> dr = {-1, 0, 1, 0}, dc = {0, 1, 0, -1};

        for(int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if(nr >= 0 and nr < n and nc >= 0 and nc < m and visited[nr][nc]) {
                if(ds->find(r * m + c) != ds->find(nr * m + nc)) {
                    islands--;
                    ds->unite(r * m + c, nr * m + nc);
                }
            }
        }

        ans.push_back(islands);
    }

    return ans;
}

int largestIsland(vector<vector<int>>& grid) {
    int n = grid.size();

    DisjointSet* ds = new DisjointSet(n * n);

    vector<int> dr = {-1, 0, 1, 0}, dc = {0, 1, 0, -1};

    int maxArea = INT_MIN;

    for(int r = 0; r < n; r++) {
        for(int c = 0; c < n; c++) {
            if(!grid[r][c]) {
                continue;
            }

            for(int i = 0; i < 4; i++) {
                int nr = r + dr[i], nc = c + dc[i];

                if(nr >= 0 and nr < n and nc >= 0 and nc < n and grid[nr][nc]) {
                    ds->unite(r * n + c, nr * n + nc);
                }
            }

            maxArea = max(maxArea, ds->getSize(ds->find(r * n + c)));
        }
    }

    for(int r = 0; r < n; r++) {
        for(int c = 0; c < n; c++) {
            if(grid[r][c]) {
                continue;
            }

            int area = 1;

            unordered_set<int> components;

            for(int i = 0; i < 4; i++) {
                int nr = r + dr[i], nc = c + dc[i];

                if(nr >= 0 and nr < n and nc >= 0 and nc < n and grid[nr][nc]) {
                    components.insert(ds->find(n * nr + nc));
                }
            }

            for(auto component : components) {
                area += ds->getSize(component);
            }

            maxArea = max(maxArea, area);
        }
    }

    return maxArea;
}

int removeStones(vector<vector<int>>& stones) {
    
}

int main() {
    vector<vector<int>> stones = {
        {0, 0}, 
        {0, 1}, 
        {1, 0}, 
        {1, 2}, 
        {2, 1}, 
        {2, 2}
    };

    cout << removeStones(stones) << endl;
    return 0;
}