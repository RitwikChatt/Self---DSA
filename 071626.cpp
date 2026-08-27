#include<bits/stdc++.h>
using namespace std;

int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    map<int, vector<pair<int, int>>> adjList;

    for(auto flight : flights) {
        adjList[flight[0]].push_back({flight[1], flight[2]});
    }

    queue<tuple<int, int, int>> q;
    vector<int> dist(n, INT_MAX);

    q.push({src, 0, 0});
    dist[src] = 0;

    while(!q.empty()) {
        auto [node, cost, flights_used] = q.front();
        q.pop();

        if(flights_used > k) {
            continue;
        }

        for(auto &[neighbour, wt] : adjList[node]) {
            if(cost + wt < dist[neighbour]) {
                dist[neighbour] = cost + wt;
                q.push({neighbour, dist[neighbour], flights_used + 1});
            }
        }
    }

    return dist[dst] == INT_MAX ? -1 : dist[dst];
}

int minSteps(vector<int>& arr, int start, int end) {
    int mod = 1000;

    queue<pair<int, int>> q;
    vector<int> dist(mod, INT_MAX);

    q.push({start, 0});
    dist[start] = 0;

    while(!q.empty()) {
        auto [value, steps] = q.front();
        q.pop();

        for(auto it : arr) {
            int newValue = (it * value) % mod;
            if(steps + 1 < dist[newValue]) {
                dist[newValue] = steps + 1;
                q.push({newValue, dist[newValue]});
            }
        }
    }

    return dist[end] == INT_MAX ? -1 : dist[end];
}

int countPaths(int n, vector<vector<int>>& roads) {
    map<int, vector<pair<int, int>>> adjList;

    for(auto road : roads) {
        int u = road[0], v = road[1], time = road[2];
        adjList[u].push_back({v, time});
        adjList[v].push_back({u, time});
    }

    int mod = 1e9 + 7;

    
}

int main() {
    int n = 7;

    vector<vector<int>> roads = {
        {0,6,7},
        {0,1,2},
        {1,2,3},
        {1,3,3},
        {6,3,3},
        {3,5,1},
        {6,5,1},
        {2,5,1},
        {0,4,5},
        {4,6,2}
    };

    cout << countPaths(n, roads) << endl;

    return 0;
}