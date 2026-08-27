#include<bits/stdc++.h>
using namespace std;

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    map<int, vector<int>> adjList;
    vector<int> indegree(numCourses);

    for(auto edge : prerequisites) {
        adjList[edge[1]].push_back(edge[0]);
        indegree[edge[0]]++;
    }

    queue<int> q;

    for(int i = 0; i < numCourses; i++) {
        if(!indegree[i]) {
            q.push(i);
        }
    }

    int count = 0;

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        count++;

        for(auto neighbour : adjList[node]) {
            indegree[neighbour]--;
            if(!indegree[neighbour]) {
                q.push(neighbour);
            }
        }
    }

    return count == numCourses;
}

bool findOrderUtilDFS(int node, map<int, vector<int>>& adjList, vector<bool>& visited, 
    vector<bool>& pathVisited, stack<int>& st) {
        visited[node] = true;
        pathVisited[node] = true;

        for(int neighbour : adjList[node]) {
            if(!visited[neighbour]) {
                if(findOrderUtilDFS(neighbour, adjList, visited, pathVisited, st)) {
                    return true;
                };
            } else if(pathVisited[neighbour]) {
                return true;
            }
        }

        st.push(node);
        pathVisited[node] = false;
        
        return false;
}

vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    map<int, vector<int>> adjList;

    for(auto edge : prerequisites) {
        adjList[edge[1]].push_back(edge[0]);
    }

    vector<bool> visited(numCourses), pathVisited(numCourses);

    stack<int> st;

    for(int i = 0; i < numCourses; i++) {
        if(!visited[i]) {
            if(findOrderUtilDFS(i, adjList, visited, pathVisited, st)) {
                return {};
            }
        }
    }

    vector<int> toposort;

    while(!st.empty()) {
        toposort.push_back(st.top());
        st.pop();
    }

    return toposort;
}

vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
    int V = graph.size();

    map<int, vector<int>> adjList;
    vector<int> indegree(V);

    for(int i = 0; i < V; i++) {
        for(auto neighbour : graph[i]) {
            adjList[neighbour].push_back(i);
            indegree[i]++;
        }
    }

    queue<int> q;

    for(int i = 0; i < V; i++) {
        if(!indegree[i]) {
            q.push(i);
        }
    }

    vector<int> safenodes;

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        safenodes.push_back(node);

        for(auto neighbour : adjList[node]) {
            indegree[neighbour]--;
            if(!indegree[neighbour]) {
                q.push(neighbour);
            }
        }
    }

    sort(safenodes.begin(), safenodes.end());

    return safenodes;
}

string findOrder(vector<string> &words) {
    
}

int main() {
    vector<string> words = {
        "baa", "abcd", "abca", "cab", "cad"
    };

    cout << findOrder(words) << endl;

    return 0;
}