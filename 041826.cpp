#include<bits/stdc++.h>
using namespace std;

int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    int n = grid.size();

    if(grid[0][0] == 1 or grid[n - 1][n - 1] == 1) {
        return -1;
    }

    queue<tuple<int, int, int>> q;
    q.push({0, 0, 1});
    grid[0][0] = 1;

    const vector<int> dx = {-1, -1, 0, 1, 1, 1, 0, -1};
    const vector<int> dy = {0, 1, 1, 1, 0, -1, -1, -1};

    while(!q.empty()) {
        auto [x, y, dist] = q.front();
        q.pop();

        if(x == n - 1 and y == n - 1) {
            return dist;
        }

        for(int i = 0; i < 8; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if(nx >= 0 and nx < n and ny >= 0 and ny < n and grid[nx][ny] == 0) {
                grid[nx][ny] = 1;
                q.push({nx, ny, dist + 1});
            }
        }
    }

    return -1;
}

void solve(vector<string>& board) {
    
}

int main() {
    vector<string> board = {
        "XXXX", 
        "XOOX", 
        "XXOX", 
        "XOXX"
    };

    solve(board);

    for(auto x : board) {
        for(auto y : x) {
            cout << y << ' ';
        }
        cout << endl;
    }
    return 0;
}