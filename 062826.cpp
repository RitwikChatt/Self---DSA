#include<bits/stdc++.h>
using namespace std;

int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    map<int, vector<pair<int, int>>> adjList;

    vector<int> dist(n + 1, INT_MAX);

    for(auto edge : times) {
        adjList[edge[0]].push_back({edge[1], edge[2]});
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push({0, k});
    dist[k] = 0;

    while(!pq.empty()) {
        auto [d, node] = pq.top();
        pq.pop();

        if(d > dist[node]) {
            continue;
        }

        for(auto &[neighbour, wt] : adjList[node]) {
            if(dist[node] + wt < dist[neighbour]) {
                dist[neighbour] = dist[node] + wt;
                pq.push({dist[neighbour], neighbour});
            }
        }
    }

    int maxVal = INT_MIN;

    for(int i = 1; i <= n; i++) {
        if(i == k) {
            continue;
        }
        maxVal = max(maxVal, dist[i]);
    }

    return maxVal == INT_MAX ? -1 : maxVal;
}

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> dict(wordList.begin(), wordList.end());

    if(dict.find(endWord) == dict.end()) {
        return 0;
    }

    queue<string> q;
    q.push(beginWord);

    int steps = 1;

    while(!q.empty()) {
        int sz = q.size();

        while(sz--) {
            string word = q.front();
            q.pop();

            if(word == endWord) {
                return steps;
            }

            for(int i = 0; i < word.length(); i++) {
                char original = word[i];

                for(char ch = 'a'; ch <= 'z'; ch++) {
                    word[i] = ch;

                    if(dict.find(word) != dict.end()) {
                        q.push(word);
                        dict.erase(word);
                    }
                }

                word[i] = original;
            }
        }
        steps++;
    }
    return 0;
}

class DSU {
    private:
    vector<int> parent, rank;

    public:
    DSU(int n) {
        this->parent.resize(n);
        this->rank.resize(n, 1);

        for(int i = 0; i < n; i++) {
            this->parent[i] = i;
        }
    }

    int find(int node) {
        if(this->parent[node] == node) {
            return node;
        }

        return this->parent[node] = this->find(this->parent[node]);
    }

    void unite(int u, int v) {
        u = this->find(u);
        v = this->find(v);

        if(u == v) {
            return;
        }

        if(this->rank[u] < this->rank[v]) {
            swap(u, v);
        }

        this->parent[v] = u;
        this->rank[u] += this->rank[v];
    }

};

int minCostConnectPoints(vector<vector<int>>& points) {
    int n = points.size();

    vector<tuple<int, int, int>> edges;

    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            edges.push_back({abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]), i, j});
        }
    }

    sort(edges.begin(), edges.end());

    DSU* dsu = new DSU(n);

    int minCost = 0, edgesUsed = 0;

    for(auto edge : edges) {
        auto [cost, u, v] = edge;

        if(dsu->find(u) != dsu->find(v)) {
            dsu->unite(u, v);
            minCost += cost;
            edgesUsed++;

            if(edgesUsed == n - 1) {
                break;
            }
        }

    }

    return minCost;
}

bool dfs(int node, int currColor, vector<vector<int>>& graph, vector<int>& color) {
    color[node] = currColor;

    for(int neighbour : graph[node]) {
        if(color[neighbour] == -1) {
            if(!dfs(neighbour, 1 - currColor, graph, color)) {
                return false;
            }
        } else if(color[neighbour] == currColor) {
            return false;
        }
    }

    return true;
}

bool isBipartite(vector<vector<int>>& graph) {
    int n = graph.size();

    vector<int> color(n, -1);

    for(int root = 0; root < n; root++) {
        if(color[root] == -1) {
            if(!dfs(root, 0, graph, color)) {
                return false;
            }
        }
    }

    return true;
}

int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    map<int, vector<pair<int, int>>> adjList;

    for(auto flight : flights) {
        adjList[flight[0]].push_back({flight[1], flight[2]});
    }

    queue<tuple<int, int, int>> q;
    q.push({src, 0, 0});

    vector<int> dist(n, INT_MAX);
    dist[src] = 0;

    while(!q.empty()) {
        auto [node, cost, stops] = q.front();
        q.pop();

        if(stops > k) {
            continue;
        }

        for(auto [neighbour, wt] : adjList[node]) {
            if(cost + wt < dist[neighbour]) {
                dist[neighbour] = cost + wt;
                q.push({neighbour, dist[neighbour], stops + 1});
            }
        }
    }

    if(dist[dst] == INT_MAX) {
        return -1;
    }

    return dist[dst];
}

int main() {
    vector<vector<int>> flights = {
        {0,1,100}, {1,2,100}, {2,0,100}, {1,3,600}, {2,3,200}
    };

    int n = 4, src = 0, dst = 3, k = 1;

    cout << findCheapestPrice(n, flights, src, dst, k) << endl;

    return 0;
}