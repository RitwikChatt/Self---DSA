#include<bits/stdc++.h>
using namespace std;

long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
    int n = nums1.size();

    vector<pair<long long, long long>> pairs(n);

    for(int i = 0; i < n; i++) {
        pairs[i] = {nums2[i], nums1[i]};
    }

    sort(pairs.begin(), pairs.end(), greater<pair<long long, long long>>());

    long long sum = 0, mini = LONG_LONG_MAX;

    priority_queue<long long, vector<long long>, greater<long long>> minHeap;

    for(int i = 0; i < k; i++) {
        sum += pairs[i].second;
        mini = min(mini, pairs[i].first);
        minHeap.push(pairs[i].second);
    }

    long long score = sum * mini;

    for(int i = k; i < n; i++) {
        sum -= minHeap.top();
        sum += pairs[i].second;

        minHeap.pop();
        minHeap.push(pairs[i].second);

        score = max(score, pairs[i].first * sum);
    }

    return score;
}

long long totalCost(vector<int>& costs, int k, int candidates) {
    int n = costs.size();

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> start, end;

    int left = 0, right = n - 1;

    while(left < candidates) {
        start.push({costs[left], left});
        left++;
    }

    while((right >= n - candidates) and (left <= right)) {
        end.push({costs[right], right});
        right--;
    }

    long long total = 0;

    while(k--) {
        if(!start.empty() and (end.empty() or start.top().first <= end.top().first)) {
            total += start.top().first;
            start.pop();

            if(left <= right) {
                start.push({costs[left], left});
                left++;
            }

        } else {
            total += end.top().first;
            end.pop();

            if(left <= right) {
                end.push({costs[right], right});
                right--;
            }
        }
    }

    return total;
}

int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    map<int, vector<pair<int, int>>> adjList;
    
    for(int i = 0; i < times.size(); i++) {
        int u = times[i][0], v = times[i][1], wt = times[i][2];

        adjList[u].push_back({v, wt});
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(n + 1, INT_MAX);

    pq.push({0, k});
    dist[k] = 0;

    while(!pq.empty()) {
        auto [d, node] = pq.top();
        pq.pop();

        if(d > dist[node]) {
            continue;
        }

        for(auto &[neighbour, wt] : adjList[node]) {
            if(d + wt < dist[neighbour]) {
                dist[neighbour] = d + wt;
                pq.push({dist[neighbour], neighbour});
            }
        }
    }

    int maxDist = *max_element(dist.begin() + 1, dist.end());

    return maxDist == INT_MAX ? -1 : maxDist;
}

int maxStarSum(vector<int>& vals, vector<vector<int>>& edges, int k) {
    
}

int main() {
    vector<int> vals = {1,2,3,4,10,-10,-20};
    vector<vector<int>> edges = {{0,1},{1,2},{1,3},{3,4},{3,5},{3,6}};
    int k = 2;

    cout << maxStarSum(vals, edges, k) << endl;
    return 0;
}