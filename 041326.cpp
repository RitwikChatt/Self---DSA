#include<bits/stdc++.h>
using namespace std;

class Graph {
    private:
    map<int, vector<int>> adjList;
    int numOfNodes;

    void dfsUtil(int node, vector<bool>& isVisited) {
        isVisited[node] = true;
        cout << node << ' ';

        for(auto neighbour : this->adjList[node]) {
            if(!isVisited[neighbour]) {
                dfsUtil(neighbour, isVisited);
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

    void dfs() {
        vector<bool> isVisited(this->numOfNodes);
        dfsUtil(0, isVisited);
    }

    void bfs() {
        vector<bool> isVisited(this->numOfNodes);
        queue<int> q;

        q.push(0);
        isVisited[0] = true;

        while(!q.empty()) {
            int node = q.front();
            q.pop();

            cout << node << ' ';

            for(auto neighbour : this->adjList[node]) {
                if(!isVisited[neighbour]) {
                    isVisited[neighbour] = true;
                    q.push(neighbour);
                }
            }
        }
    }
};

vector<pair<int, int>> dirs = {
    {-1, 0}, 
    {0, 1}, 
    {1, 0}, 
    {0, -1}
};

void dfs(vector<vector<char>>& grid, int i, int j) {
    if(i < 0 or i >= grid.size() or j < 0 or j >= grid[0].size() or grid[i][j] == '0') {
        return;
    }

    grid[i][j] = '0';

    for(auto dir : dirs) {
        dfs(grid, i + dir.first, j + dir.second);
    }
}

void bfs(vector<string>& grid, int i, int j) {
    int n = grid.size(), m = grid[0].size();

    queue<pair<int, int>> q;
    q.push({i, j});

    grid[i][j] = '0';

    while(!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for(auto dir : dirs) {
            int nx = x + dir.first, ny = y + dir.second;

            if(nx >= 0 and nx < n and ny >= 0 and ny < m and grid[nx][ny] == '1') {
                grid[nx][ny] = '0';
                q.push({nx, ny});
            }
        }
    }
}

int numIslands(vector<string>& grid) {
    int n = grid.size(), m = grid[0].size();
    int count = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[i][j] == '1') {
                count++;
                bfs(grid, i, j);
            }
        }
    }

    return count;
}

int orangesRotting(vector<vector<int>>& grid) {
    
}

int main() {    
    vector<vector<int>> grid = {
        {2,1,1}, 
        {1,1,0}, 
        {0,1,1}
    };

    cout << orangesRotting(grid) << endl;
    return 0;
}