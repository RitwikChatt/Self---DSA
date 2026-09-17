#include<bits/stdc++.h>
using namespace std;

int maxStarSum(vector<int>& vals, vector<vector<int>>& edges, int k) {
    int n = vals.size();

    map<int, vector<int>> adjList;

    for(auto edge : edges) {
        int u = edge[0], v = edge[1];

        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    int starSum = INT_MIN;

    for(int node = 0; node < n; node++) {
        priority_queue<int, vector<int>, greater<int>> minHeap;

        for(auto neighbour : adjList[node]) {
            if(vals[neighbour] < 0) {
                continue;
            }

            minHeap.push(vals[neighbour]);

            if(minHeap.size() > k) {
                minHeap.pop();
            }
        }

        int sum = vals[node];

        while(!minHeap.empty()) {
            sum += minHeap.top();
            minHeap.pop();
        }

        starSum = max(starSum, sum);
    }

    return starSum;
}

int main() {
    vector<int> vals = {1,2,3,4,10,-10,-20};
    vector<vector<int>> edges = {{0,1},{1,2},{1,3},{3,4},{3,5},{3,6}};
    int k = 2;

    cout << maxStarSum(vals, edges, k) << endl;
    return 0;
}