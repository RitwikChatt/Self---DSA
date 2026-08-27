#include<bits/stdc++.h>
using namespace std;

int shortestPathLength(vector<vector<int>>& graph) {
    int n = graph.size();

    vector<vector<bool>> visited(n, vector<bool>(1 << n, false));

    queue<pair<int, int>> q;

    for(int i = 0; i < n; i++) {
        int mask = 1 << i;
        q.push({i, mask});
        visited[i][mask] = true;
    }

    int steps = 0;

    while(!q.empty()) {
        int sz = q.size();

        while(sz--) {
            auto [node, mask] = q.front();
            q.pop();

            if(mask == (1 << n) - 1) {
                return steps;
            }

            for(auto neighbour : graph[node]) {
                int newMask = mask | (1 << neighbour);
                if(!visited[neighbour][newMask]) {
                    visited[neighbour][newMask] = true;
                    q.push({neighbour, newMask});
                }
            }
        }
        steps++;
    }

    return -1;
}

vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
    
}

int main() {
    int n = 4;
    vector<vector<int>> connections = {
        {0, 1}, {1, 2}, {2, 0}, {1, 3}
    };

    for(auto x : criticalConnections(n, connections)) {
        for(auto y : x) {
            cout << y << ' ';
        }
        cout << endl;
    }

    return 0;
}