#include<bits/stdc++.h>
using namespace std;

string findOrder(vector<string> &words) {
    int n = words.size();

    unordered_set<char> uniqueCharacters;

    for(auto word : words) {
        for(auto ch : word) {
            uniqueCharacters.insert(ch);
        }
    }

    unordered_map<char, unordered_set<char>> adjList;

    for(int i = 0; i < n - 1; i++) {
        string s1 = words[i], s2 = words[i + 1];
        bool found = false;
        for(int j = 0; j < min(s1.length(), s2.length()); j++) {
            if(s1[j] != s2[j]) {
                adjList[s1[j]].insert(s2[j]);
                found = true;
                break;
            }
        }

        if(!found and s1.length() > s2.length()) {
            return "";
        }
    }

    unordered_map<char, int> indegree;

    for(auto x : adjList) {
        for(auto y : x.second) {
            indegree[y]++;
        }
    }

    for(auto ch : uniqueCharacters) {
        if(indegree.find(ch) == indegree.end()) {
            indegree[ch] = 0;
        }
    }

    queue<char> q;

    for(auto ch : uniqueCharacters) {
        if(!indegree[ch]) {
            q.push(ch);
        }
    }

    string toposort = "";

    while(!q.empty()) {
        auto node = q.front();
        q.pop();

        toposort += node;

        for(auto neighbour : adjList[node]) {
            indegree[neighbour]--;
            if(!indegree[neighbour]) {
                q.push(neighbour);
            }
        }
    }

    return toposort.length() == uniqueCharacters.size() ? toposort : "";
}

vector<int> shortestPath(int V, int E, vector<vector<int>>& edges) {
    map<int, vector<pair<int, int>>> adjList;

    for(auto edge : edges) {
        int u = edge[0], v = edge[1], wt = edge[2];
        adjList[u].push_back({v, wt});
    }

    priority_queue<
    pair<int, int>, 
    vector<pair<int, int>>, 
    greater<pair<int, int>>
    > pq;

    vector<int> dist(V, INT_MAX);

    pq.push({0, 0});
    dist[0] = 0;

    while(!pq.empty()) {
        auto [d, node] = pq.top();
        pq.pop();

        if(dist[node] < d) {
            continue;
        }

        for(auto &[neighbour, wt] : adjList[node]) {
            if(dist[node] + wt < dist[neighbour]) {
                dist[neighbour] = dist[node] + wt;
                pq.push({dist[neighbour], neighbour});
            }
        }
    }

    for(int i = 0; i < V; i++) {
        if(dist[i] == INT_MAX) {
            dist[i] = -1;
        }
    }

    return dist;
}

vector<int> shortestDist(int V, map<int, vector<int>>& adjList) {
    vector<int> dist(V, INT_MAX);
    queue<pair<int, int>> q;
    vector<bool> visited(V);

    q.push({0, 0});
    visited[0] = true;

    while(!q.empty()) {
        auto [node, d] = q.front();
        q.pop();

        dist[node] = d;

        for(auto neighbour : adjList[node]) {
            if(!visited[neighbour]) {
                visited[neighbour] = true;
                q.push({neighbour, d + 1});
            }
        }
    }
    
    for(int i = 0; i < V; i++) {
        if(dist[i] == INT_MAX) {
            dist[i] = -1;
        } 
    }

    return dist;
}

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> uniqueWords(wordList.begin(), wordList.end());

    queue<pair<string, int>> q;
    q.push({beginWord, 1});
    uniqueWords.erase(beginWord);

    while(!q.empty()) {
        auto [word, lt] = q.front();
        q.pop();

        if(word == endWord) {
            return lt;
        }

        for(int i = 0; i < word.length(); i++) {
            string s = word;
            for(char ch = 'a'; ch <= 'z'; ch++) {
                s[i] = ch;
                if(uniqueWords.find(s) != uniqueWords.end()) {
                    q.push({s, lt + 1});
                    uniqueWords.erase(s);
                }
            }
        }
    }

    return 0;
}

vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
    
}

int main() {
    string beginWord = "hit" , endWord = "cog";
    vector<string> wordList = {"hot","dot","dog","lot","log","cog"};

    for(auto x : findLadders(beginWord, endWord, wordList)) {
        for(auto y : x) {
            cout << y << ' ';
        }
        cout << endl;
    }

    return 0;
}