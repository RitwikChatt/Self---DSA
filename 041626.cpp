#include<bits/stdc++.h>
using namespace std;

const vector<int> dx = {-1, 0, 1, 0, -1, 1, 1, -1};
const vector<int> dy = {0, 1, 0, -1, 1, 1, -1, -1};

vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    int rows = mat.size(), cols = mat[0].size();

    queue<pair<int, int>> q;

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
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

            if(nx >= 0 and nx < rows and ny >= 0 and ny < cols and mat[nx][ny] == -1) {
                mat[nx][ny] = 1 + mat[x][y];
                q.push({nx, ny});
            }
        }
    }

    return mat;
}

int main() {
    
    return 0;
}