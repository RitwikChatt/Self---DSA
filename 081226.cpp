#include<bits/stdc++.h>
using namespace std;

const vector<int> dr = {-1, 0, 1, 0}, dc = {0, 1, 0, -1};

void pacificAtlanticUtilDFS(int r, int c, vector<vector<bool>>& visited, vector<vector<int>>& heights) {
    visited[r][c] = true;

    for(int i = 0; i < 4; i++) {
        int nr = r + dr[i], nc = c + dc[i];

        if(nr >= 0 and nr < heights.size() and nc >= 0 and nc < heights[0].size() and 
            !visited[nr][nc] and heights[nr][nc] >= heights[r][c]) {
                pacificAtlanticUtilDFS(nr, nc, visited, heights);
            }
    }
}

void pacificAtlanticUtilBFS(int r0, int c0, vector<vector<bool>>& visited, vector<vector<int>>& heights) {
    queue<pair<int, int>> q;
    
    q.push({r0, c0});
    visited[r0][c0] = true;

    while(!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for(int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];

            if(nr >= 0 and nr < heights.size() and nc >= 0 and nc < heights[0].size() 
                and !visited[nr][nc] and heights[nr][nc] >= heights[r][c]) {
                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
        }
    }
}

vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
    int m = heights.size(), n = heights[0].size();

    vector<vector<bool>> pacific(m, vector<bool>(n)), atlantic(m, vector<bool>(n));

    for(int j = 0; j < n; j++) {
        if(!pacific[0][j]) {
            pacificAtlanticUtilBFS(0, j, pacific, heights);
        }

        if(!atlantic[m - 1][j]) {
            pacificAtlanticUtilBFS(m - 1, j, atlantic, heights);
        }
    }

    for(int i = 0; i < m; i++) {
        if(!pacific[i][0]) {
            pacificAtlanticUtilBFS(i, 0, pacific, heights);
        }

        if(!atlantic[i][n - 1]) {
            pacificAtlanticUtilBFS(i, n - 1, atlantic, heights);
        }
    }

    vector<vector<int>> coordinates;

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(pacific[i][j] and atlantic[i][j]) {
                coordinates.push_back({i, j});
            }
        }
    }

    return coordinates;
}

int main() {
    vector<vector<int>> heights = {
        {1,2,2,3,5}, 
        {3,2,3,4,4}, 
        {2,4,5,3,1}, 
        {6,7,1,4,5}, 
        {5,1,1,2,4}
    };

    for(auto x : pacificAtlantic(heights)) {
        for(auto y : x) {
            cout << y << ' ';
        }
        cout << endl;
    }
    return 0;
}