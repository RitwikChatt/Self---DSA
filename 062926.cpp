#include<bits/stdc++.h>
using namespace std;

int minimumEffortPath(vector<vector<int>>& heights) {
    int m = heights.size(), n = heights[0].size();

    priority_queue<
        tuple<int, int, int>, 
        vector<tuple<int, int, int>>, 
        greater<tuple<int, int, int>>
        > pq;

    vector<vector<int>> dist(m, vector<int>(n, INT_MAX));

    pq.push({0, 0, 0});
    dist[0][0] = 0;

    vector<int> dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};

    while(!pq.empty()) {
        auto [effort, x, y] = pq.top();
        pq.pop();

        if(x == m - 1 and y == n - 1) {
            return effort;
        }

        if(effort > dist[x][y]) {
            continue;
        }

        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if(nx >= 0 and nx < m and ny >= 0 and ny < n) {
                int newEffort = max(effort, abs(heights[x][y] - heights[nx][ny]));
                if(newEffort < dist[nx][ny]) {
                    dist[nx][ny] = newEffort;
                    pq.push({newEffort, nx, ny});
                }
            }
        }
    }

    return 0;
}

void findItineraryUtil(string airport, 
    map<string, priority_queue<string, vector<string>, greater<string>>>& adjList, 
    vector<string>& itinerary) {

        auto& neighbours = adjList[airport];

        while(!neighbours.empty()) {
            auto city = neighbours.top();
            neighbours.pop();

            findItineraryUtil(city, adjList, itinerary);

        }

        itinerary.push_back(airport);
}

vector<string> findItinerary(vector<vector<string>>& tickets) {
    map<string, priority_queue<string, vector<string>, greater<string>>> adjList;

    for(auto ticket : tickets) {
        adjList[ticket[0]].push(ticket[1]);
    }

    vector<string> itinerary;

    findItineraryUtil("JFK", adjList, itinerary);

    reverse(itinerary.begin(), itinerary.end());

    return itinerary;
}

int shortestPathLength(vector<vector<int>>& graph) {

}

int main() {
    vector<vector<int>> graph = {
        {1}, {0,2,4}, {1,3,4}, {2}, {1,2}
    };

    cout << shortestPathLength(graph) << endl;
    return 0;
}