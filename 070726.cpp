#include<bits/stdc++.h>
using namespace std;

bool isBipartiteUtilBFS(int start, vector<vector<int>>& graph, vector<int>& color) {
    queue<int> q;
    q.push(start);
    color[start] = 0;

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        for(int neighbour : graph[node]) {
            if(color[neighbour] == -1) {
                color[neighbour] = 1 - color[node];
                q.push(neighbour);
            } else if(color[neighbour] == color[node]) {
                return false;
            }
        }
    }

    return true;
}

bool isBipartite(vector<vector<int>>& graph) {
    int V = graph.size();

    vector<int> color(V, -1);

    for(int i = 0; i < V; i++) {
        if(color[i] == -1) {
            if(!isBipartiteUtilBFS(i, graph, color)) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    vector<vector<int>> graph = {
        {1,2,3}, 
        {0,2}, 
        {0,1,3}, 
        {0,2}
    };

    isBipartite(graph) ? cout << "true" : cout << "false";

    return 0;
}