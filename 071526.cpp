#include<bits/stdc++.h>
using namespace std;

vector<vector<string>> findSequences(vector<string> &words, string &s, string &e) {
    unordered_set<string> st(words.begin(), words.end());
    queue<vector<string>> q;

    q.push({s});
    st.erase(s);

    vector<vector<string>> sequences;

    while(!q.empty()) {
        int sz = q.size();

        vector<string> wordsUsedOnLevel;

        while(sz--) {
            auto sequence = q.front();
            q.pop();

            string word = sequence.back();

            if(word == e) {
                sequences.push_back(sequence);
            }

            for(int i = 0; i < word.length(); i++) {
                char orig = word[i];
                for(char ch = 'a'; ch <= 'z'; ch++) {
                    word[i] = ch;
                    if(st.find(word) != st.end()) {
                        sequence.push_back(word);
                        wordsUsedOnLevel.push_back(word);
                        q.push(sequence);
                        sequence.pop_back();
                    }
                }
                word[i] = orig;
            }
        }

        for(auto usedWord : wordsUsedOnLevel) {
            st.erase(usedWord);
        }
    }

    return sequences;
}

vector<int> shortestPath(int V, vector<vector<int>> &edges, int src, int dest) {
    map<int, vector<pair<int, int>>> adjList;

    for(auto edge : edges) {
        adjList[edge[0]].push_back({edge[1], edge[2]});
        adjList[edge[1]].push_back({edge[0], edge[2]});
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    vector<int> dist(V + 1, INT_MAX);

    pq.push({0, dest});
    dist[dest] = 0;

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

    if(dist[dest] == INT_MAX) {
        return {-1};
    }

    vector<int> path;

    int node = src;
    
    path.push_back(node);

    while(node != dest) {
        int nextNode = INT_MAX;

        for(auto &[neighbour, wt] : adjList[node]) {
            if(dist[node] == dist[neighbour] + wt) {
                nextNode = min(nextNode, neighbour);
            }
        }

        path.push_back(nextNode);
        node = nextNode;
    }

    return path;
}

const vector<int> dr = {-1, 0, 1, 0, -1, 1, 1, -1};
const vector<int> dc = {0, 1, 0, -1, 1, 1, -1, -1};

int shortestPath(vector<vector<int>> &mat, vector<int> &src, vector<int> &dest) {
    int m = mat.size(), n = mat[0].size();

    if(!mat[dest[0]][dest[1]]) {
        return -1;
    }

    queue<tuple<int, int, int>> q;
    q.push({src[0], src[1], 0});
    mat[src[0]][src[1]] = -1;

    while(!q.empty()) {
        auto [r, c, steps] = q.front();
        q.pop();

        if(r == dest[0] and c == dest[1]) {
            return steps;
        }

        for(int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if(nr >= 0 and nr < m and nc >= 0 and nc < n and mat[nr][nc] == 1) {
                q.push({nr, nc, steps + 1});
                mat[nr][nc] = -1;
            }
        }
    }

    return -1;
}

int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    int n = grid.size();

    if(grid[0][0] or grid[n - 1][n - 1]) {
        return -1;
    }

    queue<tuple<int, int, int>> q;
    q.push({0, 0, 1});
    grid[0][0] = -1;

    while(!q.empty()) {
        auto [r, c, len] = q.front();
        q.pop();

        if(r == n - 1 and c == n - 1) {
            return len;
        }

        for(int i = 0; i < 8; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if(nr >= 0 and nr < n and nc >= 0 and nc < n and !grid[nr][nc]) {
                grid[nr][nc] = -1;
                q.push({nr, nc, len + 1});
            }
        }
    }

    return -1;
}

int minimumEffortPath(vector<vector<int>>& heights) {
    int rows = heights.size(), columns = heights[0].size();

    priority_queue<
    tuple<int, int, int>, 
    vector<tuple<int, int, int>>, 
    greater<tuple<int, int, int>>
    > pq;

    vector<vector<int>> effort(rows, vector<int>(columns, INT_MAX));

    pq.push({0, 0, 0});
    effort[0][0] = 0;

    while(!pq.empty()) {
        auto [eff, r, c] = pq.top();
        pq.pop();

        for(int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if(nr >= 0 and nr < rows and nc >= 0 and nc < columns and 
                max(effort[r][c], abs(heights[r][c] - heights[nr][nc])) < effort[nr][nc]) {
                    effort[nr][nc] = max(effort[r][c], abs(heights[r][c] - heights[nr][nc]));
                    pq.push({effort[nr][nc], nr, nc});
            }
        }
    }

    return effort[rows - 1][columns - 1];
}

int main() {

    return 0;
}