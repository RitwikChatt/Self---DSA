#include<bits/stdc++.h>
using namespace std;

bool isBipartiteUtilDFS(int node, vector<vector<int>>& graph, vector<int>& color) {
    for(int neighbour : graph[node]) {
        if(color[neighbour] == -1) {
            color[neighbour] = 1 - color[node];
            if(!isBipartiteUtilDFS(neighbour, graph, color)) {
                return false;
            }
        } else if(color[neighbour] == color[node]) {
            return false;
        }
    }
    return true;
}

bool isBipartite(vector<vector<int>>& graph) {
    int V = graph.size();

    vector<int> color(V, -1);

    for(int i = 0; i < V; i++) {
        if(color[i] == -1) {
            color[i] = 0;
            if(!isBipartiteUtilDFS(i, graph, color)) {
                return false;
            }
        }
    }

    return true;
}

bool isCyclicUtilDFS(int node, map<int, vector<int>>& adjList, vector<bool>& isVisited, vector<bool>& isPathVisited) {
    isVisited[node] = true;
    isPathVisited[node] = true;

    for(int neighbour : adjList[node]) {
        if(!isVisited[neighbour]) {
            if(isCyclicUtilDFS(neighbour, adjList, isVisited, isPathVisited)) {
                return true;
            }
        } else if(isPathVisited[neighbour]) {
            return true;
        }
    }

    isPathVisited[node] = false;
    return false;
}

// bool isCyclic(int V, vector<vector<int>> &edges) {
//     map<int, vector<int>> adjList;

//     for(auto edge : edges) {
//         adjList[edge[0]].push_back(edge[1]);
//     }

//     vector<bool> isVisited(V), isPathVisited(V);

//     for(int i = 0; i < V; i++) {
//         if(!isVisited[i]) {
//             if(isCyclicUtilDFS(i, adjList, isVisited, isPathVisited)) {
//                 return true;
//             }
//         }
//     }

//     return false;
// }

void topologicalSortDFSUtil(int node, map<int, vector<int>>& adjList, vector<bool>& isVisited, stack<int>& st) {
    isVisited[node] = true;

    for(int neighbour : adjList[node]) {
        if(!isVisited[neighbour]) {
            topologicalSortDFSUtil(neighbour, adjList, isVisited, st);
        }
    }

    st.push(node);
}

vector<int> topologicalSortDFS(int V, map<int, vector<int>>& adjList) {
    vector<bool> isVisited(V);
    stack<int> st;

    for(int i = 0; i < V; i++) {
        if(!isVisited[i]) {
            topologicalSortDFSUtil(i, adjList, isVisited, st);
        }
    }

    vector<int> ordering;

    while(!st.empty()) {
        ordering.push_back(st.top());
        st.pop();
    }

    return ordering;
}

vector<int> topoSort(int V, vector<vector<int>>& edges) {
    vector<int> ordering, indegree(V);

    map<int, vector<int>> adjList;

    for(auto edge : edges) {
        adjList[edge[0]].push_back(edge[1]);
        indegree[edge[1]]++;
    }

    queue<int> q;
    
    for(int i = 0; i < V; i++) {
        if(!indegree[i]) {
            q.push(i);
        }
    }

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        ordering.push_back(node);

        for(int neighbour : adjList[node]) {
            indegree[neighbour]--;
            if(!indegree[neighbour]) {
                q.push(neighbour);
            }
        }
    }

    return ordering;
}

bool isCyclic(int V, vector<vector<int>> &edges) {
    map<int, vector<int>> adjList;

    vector<int> indegree(V), toposort;

    for(auto edge : edges) {
        adjList[edge[0]].push_back(edge[1]);
        indegree[edge[1]]++;
    }

    queue<int> q;

    for(int i = 0; i < V; i++) {
        if(!indegree[i]) {
            q.push(i);
        }
    }

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        toposort.push_back(node);

        for(int neighbour : adjList[node]) {
            indegree[neighbour]--;
            if(!indegree[neighbour]) {
                q.push(neighbour);
            }
        }
    }

    return toposort.size() != V;
}

int main() {
    
    return 0;
}