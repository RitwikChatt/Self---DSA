#include<bits/stdc++.h>
using namespace std;

const vector<int> dx = {-1, 0, 1, 0};
const vector<int> dy = {0, 1, 0, -1};

vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    int m = mat.size(), n = mat[0].size();

    vector<vector<int>> dist(m, vector<int>(n));
    vector<vector<bool>> isVisited(m, vector<bool>(n));

    queue<tuple<int, int, int>> q;

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(!mat[i][j]) {
                q.push({i, j, 0});
                isVisited[i][j] = true;
            }
        }
    }

    while(!q.empty()) {
        auto [x, y, steps] = q.front();
        q.pop();

        dist[x][y] = steps;

        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if(nx >= 0 and nx < m and ny >= 0 and ny < n and !isVisited[nx][ny]) {
                isVisited[nx][ny] = true;
                q.push({nx, ny, steps + 1});
            } 
        }
    }

    return dist;
}

void solveUtilDFS(int x, int y, vector<vector<char>>& board) {
    int m = board.size(), n = board[0].size();

    if(x < 0 or x >= m or y < 0 or y >= n or board[x][y] == '#' or board[x][y] == 'X') {
        return;
    }

    board[x][y] = '#';

    for(int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        solveUtilDFS(nx, ny, board);
    }
}

void solve(vector<vector<char>>& board) {
    int m = board.size(), n = board[0].size();

    for(int j = 0; j < n; j++) {
        if(board[0][j] == 'O') {
            solveUtilDFS(0, j, board);
        }
        if(board[m - 1][j] == 'O') {
            solveUtilDFS(m - 1, j, board);
        }
    }

    for(int i = 1; i < m - 1; i++) {
        if(board[i][0] == 'O') {
            solveUtilDFS(i, 0, board);
        }
        if(board[i][n - 1] == 'O') {
            solveUtilDFS(i, n - 1, board);
        }
    }

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(board[i][j] == '#') {
                board[i][j] = 'O';
            } else if(board[i][j] == 'O') {
                board[i][j] = 'X';
            }
        }
    }
}

void numEnclavesUtilDFS(int x, int y, vector<vector<int>>& grid, vector<vector<bool>>& isVisited) {
    int m = grid.size(), n = grid[0].size();

    if(x < 0 or x >= m or y < 0 or y >= n or isVisited[x][y] or !grid[x][y]) {
        return;
    }

    isVisited[x][y] = true;

    for(int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        numEnclavesUtilDFS(nx, ny, grid, isVisited);
    }

}

int numEnclaves(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();

    vector<vector<bool>> isVisited(m, vector<bool>(n));

    for(int j = 0; j < n; j++) {
        if(grid[0][j] and !isVisited[0][j]) {
            numEnclavesUtilDFS(0, j, grid, isVisited);
        }
        if(grid[m - 1][j] and !isVisited[m - 1][j]) {
            numEnclavesUtilDFS(m - 1, j, grid, isVisited);
        }
    }

    for(int i = 1; i < m - 1; i++) {
        if(grid[i][0] and !isVisited[i][0]) {
            numEnclavesUtilDFS(i, 0, grid, isVisited);
        }
        if(grid[i][n - 1] and !isVisited[i][n - 1]) {
            numEnclavesUtilDFS(i, n - 1, grid, isVisited);
        }
    }

    int totalLandCells = 0, boundaryLandCells = 0;

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(grid[i][j]) {
                totalLandCells++;
            }
            if(isVisited[i][j]) {
                boundaryLandCells++;
            }
        }
    }

    return totalLandCells - boundaryLandCells;
}

void countDistinctIslandsUtilDFS(int x, int y, int x0, int y0, vector<vector<char>>& grid, 
    vector<vector<bool>>& isVisited, vector<pair<int, int>>& coordinates) {

        int m = grid.size(), n = grid[0].size();

        if(x < 0 or x >= m or y < 0 or y >= n or grid[x][y] == 'W' or isVisited[x][y]) {
            return;
        }

        isVisited[x][y] = true;
        coordinates.push_back({x - x0, y - y0});

        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            countDistinctIslandsUtilDFS(nx, ny, x0, y0, grid, isVisited, coordinates);
        }
}

int countDistinctIslands(vector<vector<char>>& grid) {
    int m = grid.size(), n = grid[0].size();

    vector<vector<bool>> isVisited(m, vector<bool>(n));

    set<vector<pair<int, int>>> uniqueIslands;

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(grid[i][j] == 'L' and !isVisited[i][j]) {
                vector<pair<int, int>> coordinates;
                countDistinctIslandsUtilDFS(i, j, i, j, grid, isVisited, coordinates);
                uniqueIslands.insert(coordinates);
            }
        }
    }

    return uniqueIslands.size();
}

int main() {
    vector<vector<char>> grid = {
        {'L', 'L', 'W', 'L', 'L'}, 
        {'L', 'W', 'W', 'W', 'W'}, 
        {'W', 'W', 'L', 'W', 'L'}, 
        {'L', 'W', 'W', 'L', 'L'}
    };

    cout << countDistinctIslands(grid) << endl;

    return 0;
}