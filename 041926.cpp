#include<bits/stdc++.h>
using namespace std;

const vector<int> dx = {-1, 0, 1, 0};
const vector<int> dy = {0, 1, 0, -1};

void dfs(int i, int j, int m, int n, vector<string>& board) {
    if(i < 0 or i >= m or j < 0 or j >= n or board[i][j] != 'O') {
        return;
    }

    board[i][j] = '#';

    for(int k = 0; k < 4; k++) {
        dfs(i + dx[k], j + dy[k], m, n, board);
    }
}

void solve(vector<string>& board) {
    int m = board.size(), n = board[0].size();

    for(int i = 0; i < m; i++) {
        if(board[i][0] == 'O') {
            dfs(i, 0, m, n, board);
        }
        if(board[i][n - 1] == 'O') {
            dfs(i, n - 1, m, n, board);
        }
    }

    for(int j = 0; j < n; j++) {
        if(board[0][j] == 'O') {
            dfs(0, j, m, n, board);
        }
        if(board[m - 1][j] == 'O') {
            dfs(m - 1, j, m, n, board);
        }
    }

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(board[i][j] == 'O') {
                board[i][j] = 'X';
            } else if(board[i][j] == '#') {
                board[i][j] = 'O';
            }
        }
    }
}

string getMinimumMultipleOfBinaryDigit(int n) {
    vector<bool> visited(n);
    queue<pair<string, int>> q;

    q.push({"1", 1 % n});
    visited[1 % n] = true;

    while(!q.empty()) {
        auto [num, rem] = q.front();
        q.pop();

        if(!rem) {
            return num;
        }

        int rem0 = (rem * 10) % n;
        if(!visited[rem0]) {
            visited[rem0] = true;
            q.push({num + '0', rem0});
        }

        int rem1 = (rem * 10 + 1) % n;
        if(!visited[rem1]) {
            visited[rem1] = true;
            q.push({num + '1', rem1});
        }
    }

    return "";
}

int minCost(int n) {
    
}

int main() {
    cout << minCost(4) << endl;
    return 0;
}