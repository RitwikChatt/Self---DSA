#include<bits/stdc++.h>
using namespace std;

vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
    vector<int> dist(V, 1e8);
    dist[src] = 0;

    for(int i = 0; i < V - 1; i++) {
        for(auto edge : edges) {
            int u = edge[0], v = edge[1], wt = edge[2];
            if(dist[u] != 1e8 and dist[u] + wt < dist[v]) {
                dist[v] = dist[u] + wt;
            }
        }
    }

    for(auto edge : edges) {
        int u = edge[0], v = edge[1], wt = edge[2];
        if(dist[u] != 1e8 and dist[u] + wt < dist[v]) {
            return {-1};
        }
    }

    return dist;
}

void floydWarshall(vector<vector<int>> &dist) {
    int n = dist.size();
        
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(dist[i][k] != 1e8 and dist[k][j] != 1e8) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

int findTheCityBrute(int n, vector<vector<int>>& edges, int distanceThreshold) {
    vector<vector<int>> adjMat(n, vector<int>(n, INT_MAX));

    for(int i = 0; i < n; i++) {
        adjMat[i][i] = 0;
    }

    for(auto edge : edges) {
        int u = edge[0], v = edge[1], wt = edge[2];
        adjMat[u][v] = wt;
        adjMat[v][u] = wt;
    }

    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(adjMat[i][k] != INT_MAX and adjMat[k][j] != INT_MAX) {
                    adjMat[i][j] = min(adjMat[i][j], adjMat[i][k] + adjMat[k][j]);
                }
            }
        }
    }

    int city, neighbours = INT_MAX;

    for(int i = 0; i < n; i++) {
        int nbr = 0;
        for(int j = 0; j < n; j++) {
            if(i != j and adjMat[i][j] <= distanceThreshold) {
                nbr++;
            }
        }
        if(nbr <= neighbours) {
            neighbours = nbr;
            city = i;
        }
    }

    return city;
}

int findTheCityOptimal(int n, vector<vector<int>>& edges, int distanceThreshold) {
    map<int, vector<pair<int, int>>> adjList;

    for(auto edge : edges) {
        int u = edge[0], v = edge[1], wt = edge[2];
        adjList[u].push_back({v, wt});
        adjList[v].push_back({u, wt});
    }

    int city, neighbours = INT_MAX;

    for(int src = 0; src < n; src++) {

        priority_queue<
        pair<int, int>, 
        vector<pair<int, int>>, 
        greater<pair<int, int>>
        > pq;

        vector<int> dist(n, INT_MAX);

        pq.push({0, src});
        dist[src] = 0;

        while(!pq.empty()) {
            auto [d, node] = pq.top();
            pq.pop();

            for(auto &[neighbour, wt] : adjList[node]) {
                if(d + wt < dist[neighbour]) {
                    dist[neighbour] = d + wt;
                    pq.push({dist[neighbour], neighbour});
                }
            }
        }

        int nbr = 0;

        for(int i = 0; i < n; i++) {
            if(i != src and dist[i] <= distanceThreshold) {
                nbr++;
            }
        }

        if(nbr <= neighbours) {
            neighbours = nbr;
            city = src;
        }
    }

    return city;
}

int main() {
    

    return 0;
}