#include<bits/stdc++.h>
using namespace std;

class Graph {
    private:
    map<int, vector<int>> adjList;
    int numOfNodes;

    public:
    Graph(int numOfNodes) {
        this->numOfNodes = numOfNodes;
        this->adjList.clear();
    }

    void addEdge(int a, int b) {
        this->adjList[a].push_back(b);
        this->adjList[b].push_back(a);
    }

    void printAdjList() {
        for(auto x : this->adjList) {
            for(auto y : x.second) {
                cout << y << ' ';
            }
            cout << endl;
        }
    }
};

const vector<pair<int, int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void bfs(vector<string>& grid, int i, int j, int n, int m) {
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

void dfs(vector<string>& grid, int i, int j, int n, int m) {
    if(i < 0 or i >= n or j < 0 or j >= m or grid[i][j] == '0') {
        return;
    }

    grid[i][j] = '0';

    for(auto dir : dirs) {
        dfs(grid, i + dir.first, j + dir.second, n, m);
    }

}

int numIslands(vector<string>& grid) {
    int n = grid.size(), m = grid[0].size();
    int count = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[i][j] == '1') {
                count++;
                bfs(grid, i, j, n, m);
            }
        }
    }

    return count;
}

int orangesRotting(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    
    int freshOranges = 0;
    queue<pair<int, int>> rottenOranges;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[i][j] == 2) {
                rottenOranges.push({i, j});
            } else if(grid[i][j] == 1) {
                freshOranges++;
            }
        }
    }

    int timeElapsed = 0;

    while(!rottenOranges.empty() and freshOranges > 0) {
        int sz = rottenOranges.size();

        for(int i = 0; i < sz; i++) {
            auto [x, y] = rottenOranges.front();
            rottenOranges.pop();

            for(auto dir : dirs) {
                int nx = x + dir.first, ny = y + dir.second;

                if(nx >= 0 and nx < n and ny >= 0 and ny < m and grid[nx][ny] == 1) {
                    grid[nx][ny] = 2;
                    rottenOranges.push({nx, ny});
                    freshOranges--;
                }
            }
        }

        timeElapsed++;
    }

    return freshOranges == 0 ? timeElapsed : -1;
}

vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    
}

int main() {
    vector<vector<int>> mat = {
        {0,0,0}, 
        {0,1,0}, 
        {1,1,1}
    };

    for(auto x : updateMatrix(mat)) {
        for(auto y : x) {
            cout << y << ' ';
        }
        cout << endl;
    }

    return 0;
}