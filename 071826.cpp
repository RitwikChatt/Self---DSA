#include<bits/stdc++.h>
using namespace std;

string rearrangeString(string s, char x, char y) {
    unordered_map<char, int> freq;

    for(auto ch : s) {
        freq[ch]++;
    }

    string ans = "";

    while(freq[y]) {
        ans += y;
        freq[y]--;
    }

    freq.erase(y);

    while(freq[x]) {
        ans += x;
        freq[x]--;
    }

    freq.erase(x);

    for(auto it : freq) {
        while(freq[it.first]) {
            ans += it.first;
            freq[it.first]--;
        }
    }

    return ans;
}

int countPaths(int n, vector<vector<int>>& roads) {
    int mod = 1e9 + 7;

    map<int, vector<pair<int, int>>> adjList;

    for(auto road : roads) {
        int u = road[0], v = road[1], wt = road[2];
        adjList[u].push_back({v, wt});
        adjList[v].push_back({u, wt});
    }

    priority_queue<
    pair<long long, int>, 
    vector<pair<long long, int>>, 
    greater<pair<long long, int>>
    > pq;

    vector<long long> dist(n, LONG_LONG_MAX), ways(n);

    pq.push({0, 0});
    dist[0] = 0;
    ways[0] = 1;

    while(!pq.empty()) {
        auto [d, node] = pq.top();
        pq.pop();

        for(auto &[neighbour, wt] : adjList[node]) {
            if(1LL*d + wt < dist[neighbour]) {
                dist[neighbour] =  d + wt;
                pq.push({dist[neighbour], neighbour});
                ways[neighbour] = ways[node];
            } else if(d + wt == dist[neighbour]) {
                ways[neighbour] = (ways[neighbour] + ways[node]) % mod;
            }
        }
    }

    return ways[n - 1];
}

int main() {
    int n = 7;
    vector<vector<int>> roads = {{0,6,7},{0,1,2},{1,2,3},{1,3,3},{6,3,3},{3,5,1},{6,5,1},{2,5,1},{0,4,5},{4,6,2}};

    cout << countPaths(n, roads) << endl; 

    return 0;
}