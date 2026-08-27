#include<bits/stdc++.h>
using namespace std;

const vector<int> dx = {-1, 0, 1, 0};
const vector<int> dy = {0, 1, 0, -1};

void dfs(int x, int y, vector<vector<bool>>& isVisited, vector<vector<char>>& grid) {
    int m = grid.size(), n = grid[0].size();

    if(x < 0 or x >= m or y < 0 or y >= n or isVisited[x][y] or grid[x][y] == '0') {
        return;
    }

    isVisited[x][y] = true;

    for(int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        dfs(nx, ny, isVisited, grid);
    }

}

void bfs(int row, int col, vector<vector<bool>>& isVisited, vector<vector<char>>& grid) {
    int m = grid.size(), n = grid[0].size();

    queue<pair<int, int>> q;
    isVisited[row][col] = true;
    q.push({row, col});

    while(!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];

            if(nx >= 0 and nx < m and ny >= 0 and ny < n and !isVisited[nx][ny] and grid[nx][ny] == '1') {
                isVisited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
}

int numIslands(vector<vector<char>>& grid) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<bool>> isVisited(m, vector<bool>(n, false));

    int islands = 0;

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(grid[i][j] == '1' and !isVisited[i][j]) {
                islands++;
                dfs(i, j, isVisited, grid);
            }
        }
    } 

    return islands;
}

void floodFillUtilBfs(vector<vector<int>>& image, int sr, int sc, int color, int originalColor) {
    int m = image.size(), n = image[0].size();

    queue<pair<int, int>> q;
    image[sr][sc] = color;
    q.push({sr, sc});

    while(!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if(nx >= 0 and nx < m and ny >= 0 and ny < n and image[nx][ny] != color 
                and image[nx][ny] == originalColor) {

                image[nx][ny] = color;
                q.push({nx, ny});

            }
        }
    }
}

vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
    int originalColor = image[sr][sc];
    floodFillUtilBfs(image, sr, sc, color, originalColor);
    return image;
}

int orangesRotting(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();

    queue<pair<int, int>> rottenOranges;
    int freshOranges = 0;

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(grid[i][j] == 2) {
                rottenOranges.push({i, j});
            } else if(grid[i][j] == 1) {
                freshOranges++;
            }
        }
    }

    int timeElapsed = 0;

    while(!rottenOranges.empty() and freshOranges) {
        int sz = rottenOranges.size();

        while(sz--) {
            auto [x, y] = rottenOranges.front();
            rottenOranges.pop();

            for(int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if(nx >= 0 and nx < m and ny >= 0 and ny < n and grid[nx][ny] == 1) {
                    grid[nx][ny] = 2;
                    freshOranges--;
                    rottenOranges.push({nx, ny});
                }
            }
        }
        timeElapsed++;
    }

    return freshOranges ? -1 : timeElapsed;
}

bool detectCycleBFS(int src, map<int, vector<int>>& adjList, vector<bool>& isVisited) {
    queue<pair<int, int>> q;
    q.push({src, -1});
    isVisited[src] = true;

    while(!q.empty()) {
        auto [node, parent] = q.front();
        q.pop();

        for(auto neighbour : adjList[node]) {
            if(!isVisited[neighbour]) {
                isVisited[neighbour] = true;
                q.push({neighbour, node});
            } else if(neighbour != parent) {
                return true;
            }
        }
    }

    return false;   
}

bool detectCycleDFS(int node, int parent, map<int, vector<int>>& adjList, vector<bool>& isVisited) {
    isVisited[node] = true;

    for(auto neighbour : adjList[node]) {
        if(!isVisited[neighbour]) {
            if(detectCycleDFS(neighbour, node, adjList, isVisited)) {
                return true;
            }
        } else if(neighbour != parent) {
            return true;
        }
    }

    return false;
}

bool hasCycle(map<int, vector<int>>& adjList) {
    int V = adjList.size();

    vector<bool> isVisited(V, false);

    for(int node = 0; node < V; node++) {
        if(!isVisited[node]) {
            if(detectCycleDFS(node, -1, adjList, isVisited)) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    map<int, vector<int>> adjList;
    adjList[0] = {1, 4};
    adjList[1] = {0, 2};
    adjList[2] = {1, 3};
    adjList[3] = {2, 5};
    adjList[4] = {0, 5, 6};
    adjList[5] = {3, 4};
    adjList[6] = {4};

    hasCycle(adjList) ? cout << "yes" : cout << "no";

    return 0;
}