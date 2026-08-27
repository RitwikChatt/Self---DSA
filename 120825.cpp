#include<bits/stdc++.h>
using namespace std;

int countNegatives(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    int row = 0, col = m - 1;
    int negatives = 0;
    while(row < n and col >= 0) {
        if(grid[row][col] < 0) {
            negatives += (n - row);
            col--;
        } else {
            row++;
        }
    }
    return negatives;
}

int main() {
    vector<vector<int>> grid = {{4,3,2,-1}, 
                                {3,2,1,-1}, 
                                {1,1,-1,-2}, 
                                {-1,-1,-2,-3}};
    int negatives = countNegatives(grid);
    cout << negatives << endl;
    return 0;
}