#include<bits/stdc++.h>
using namespace std;

bool isPossibleToPlace(char c, int row, int col, vector<string>& board) {
    for(int i = 0; i < 9; i++) {
        if(board[row][i] == c) {
            return false;
        } 
        if(board[i][col] == c) {
            return false;
        }
        if(board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c) {
            return false;
        }
    }
    return true;
}

bool sudokuSolver(vector<string>& board) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(board[i][j] == '.') {
                for(char c = '1'; c <= '9'; c++) {
                    if(isPossibleToPlace(c, i, j, board)) {
                        board[i][j] = c;
                        if(sudokuSolver(board)) {
                            return true;
                        }
                        board[i][j] = '.';
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void solveSudoku(vector<string>& board) {
    sudokuSolver(board);
}

bool isPossibleToPlaceQueenHere(int row, int col, int n, vector<string>& grid) {

    for(int i = row - 1, j = col - 1; i >= 0 and j >= 0; i--, j--) {
        if(grid[i][j] == 'Q') {
            return false;
        }
    }

    for(int j = col - 1; j >= 0; j--) {
        if(grid[row][j] == 'Q') {
            return false;
        }
    }

    for(int i = row + 1, j = col - 1; i < n and j >= 0; i++, j--) {
        if(grid[i][j] == 'Q') {
            return false;
        }
    }

    return true;

}

vector<vector<string>> allGrids;

void solveGrid(int col, vector<string>& grid, int n) {
    if(col == n) {
        allGrids.push_back(grid);
        return;
    }

    for(int row = 0; row < n; row++) {
        if(isPossibleToPlaceQueenHere(row, col, n, grid)) {
            grid[row][col] = 'Q';
            solveGrid(col + 1, grid, n);
            grid[row][col] = '.';
        }
    }
}

vector<vector<string>> solveNQueens(int n) {
    vector<string> grid(n, string(n, '.'));
    solveGrid(0, grid, n);
    return allGrids;
}

vector<int> dr = {1, 0, 0, -1};
vector<int> dc = {0, -1, 1, 0};
string dir = "DLRU";

void ratInAMaze(int row, int col, string path, int n, vector<vector<int>>& isVisited, vector<vector<int>>& maze) {
    if(row == n - 1 and col == n - 1) {
        cout << path << endl;
        return;
    }

    isVisited[row][col] = 1;

    for(int i = 0; i < 4; i++) {
        if(row + dr[i] < n and row + dr[i] >= 0 
            and col + dc[i] < n and col + dc[i] >= 0 
            and maze[row + dr[i]][col + dc[i]] == 1
            and !isVisited[row + dr[i]][col + dc[i]]) {

            ratInAMaze(row + dr[i], col + dc[i], path + dir[i], n, isVisited, maze);

        }
    }

    isVisited[row][col] = 0;
}

bool judgePoint24(vector<int>& cards) {
    
}

int main() {
    vector<int> cards = {4,1,8,7};
    judgePoint24(cards) ? cout << "true" : cout << "false";
    return 0;
}