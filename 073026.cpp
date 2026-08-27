#include<bits/stdc++.h>
using namespace std;

int minimumSemester(int n, vector<vector<int>>& relations) {
    map<int, vector<int>> adjList;
    vector<int> indegree(n + 1);

    for(auto relation : relations) {
        int u = relation[0], v = relation[1];
        adjList[u].push_back(v);
        indegree[v]++;
    }

    queue<int> q;

    for(int i = 1; i <= n; i++) {
        if(!indegree[i]) {
            q.push(i);
        }
    }

    vector<int> toposort;
    int steps = 0;

    while(!q.empty()) {
        int sz = q.size();

        while(sz--) {
            auto node = q.front();
            q.pop();

            toposort.push_back(node);

            for(auto neighbour : adjList[node]) {
                indegree[neighbour]--;
                if(!indegree[neighbour]) {
                    q.push(neighbour);
                }
            }
        }

        steps++;
    }

    return toposort.size() == n ? steps : -1;
} 

class DisjointSet {
    private:
    vector<int> parent, size;

    public:
    DisjointSet(int n) {
        this->parent.resize(n + 1);
        for(int i = 0; i <= n; i++) this->parent[i] = i;

        this->size.resize(n + 1, 1);
    }

    int find(int node) {
        if(node == this->parent[node]) {
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

        if(this->size[u] < this->size[v]) {
            swap(u, v);
        }

        this->parent[v] = u;
        this->size[u] += this->size[v];
    }

};

vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
    int V = edges.size();

    vector<int> parent(V + 1), candidate1, candidate2;

    for(auto edge : edges) {
        int u = edge[0], v = edge[1];

        if(!parent[v]) {
            parent[v] = u;
        } else {
            candidate1 = {parent[v], v};
            candidate2 = edge;
        }
    }

    DisjointSet* ds = new DisjointSet(V);

    for(auto edge : edges) {
        if(edge == candidate2) {
            continue;
        }

        int u = edge[0], v = edge[1];

        if(ds->find(u) != ds->find(v)) {
            ds->unite(u, v);
        } else {
            if(candidate1.empty()) {
                return edge;
            }

            return candidate1;
        }
    }

    return candidate2;
}

bool isTreeUtilDFS(int node, int parent, map<int, vector<int>>& adjList, vector<bool>& visited) {
    visited[node] = true;

    for(auto neighbour : adjList[node]) {
        if(!visited[neighbour]) {
            if(isTreeUtilDFS(neighbour, node, adjList, visited)) {
                return true;
            }
        } else if(neighbour != parent) {
            return true;
        }
    }

    return false;
}

int isTree(int n, int m, vector<vector<int>> &edges) {
    map<int, vector<int>> adjList;

    for(auto edge : edges) {
        int u = edge[0], v = edge[1];\
        
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    vector<bool> visited(n);

    if(isTreeUtilDFS(0, -1, adjList, visited)) {
        return 0;
    }

    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            return 0;
        }
    }

    return 1;
}

bool equationsPossible(vector<string>& equations) {
    DisjointSet* ds = new DisjointSet(26);

    for(auto equation : equations) {
        int u = equation[0] - 'a', v = equation[3] - 'a';
        char sign = equation[1];

        if(sign == '=') {
            ds->unite(u, v);
        }
    }

    for(auto equation : equations) {
        int u = equation[0] - 'a', v = equation[3] - 'a';
        char sign = equation[1];

        if(sign == '!' and ds->find(u) == ds->find(v)) {
            return false;
        }
    }

    return true;
}

string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
    int V = s.length();

    DisjointSet* ds = new DisjointSet(V);

    for(auto pair : pairs) {
        int u = pair[0], v = pair[1];
        ds->unite(u, v);
    }

    unordered_map<int, vector<int>> groups;

    for(int i = 0; i < V; i++) {
        groups[ds->find(i)].push_back(i);
    }

    string ans = s;

    for(auto group : groups) {
        auto indices = group.second;

        vector<char> characters;

        for(auto index : indices) {
            characters.push_back(s[index]);
        }

        sort(characters.begin(), characters.end());

        for(int i = 0; i < indices.size(); i++) {
            ans[indices[i]] = characters[i];
        }
    }

    return ans;
}

double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
    map<int, vector<pair<int, double>>> adjList;

    for(int i = 0; i < edges.size(); i++) {
        int u = edges[i][0], v = edges[i][1];
        double wt = succProb[i];

        adjList[u].push_back({v, wt});
        adjList[v].push_back({u, wt});
    }

    priority_queue<
    pair<double, int>,
    vector<pair<double, int>>
    > pq;

    vector<double> probability(n, 0.0);

    pq.push({1.0, start_node});
    probability[start_node] = 1.0;

    while(!pq.empty()) {
        auto [p, node] = pq.top();
        pq.pop();

        for(auto [neighbour, wt] : adjList[node]) {
            if(p * wt > probability[neighbour] ) {
                probability[neighbour] = p * wt;
                pq.push({probability[neighbour], neighbour});
            }
        }
    }

    return probability[end_node];
}

int openLock(vector<string>& deadends, string target) {
    unordered_set<string> st(deadends.begin(), deadends.end());

    queue<pair<string, int>> q;

    if(st.find("0000") != st.end()) {
        return -1;
    }

    st.insert("0000");
    q.push({"0000", 0});

    while(!q.empty()) {
        auto [node, steps] = q.front();
        q.pop();

        if(node == target) {
            return steps;
        }

        for(int i = 0; i < 4; i++) {
            char orig = node[i];
            
            node[i] = (orig - '0' + 1) % 10 + '0';

            if(st.find(node) == st.end()) {
                st.insert(node);
                q.push({node, steps + 1});
            }

            node[i] = (orig - '0' + 9) % 10 + '0';

            if(st.find(node) == st.end()) {
                st.insert(node);
                q.push({node, steps + 1});
            }

            node[i] = orig;
        }
    }

    return -1;
}

int minMutation(string startGene, string endGene, vector<string>& bank) {
    unordered_set<string> st(bank.begin(), bank.end());

    if(!st.count(endGene)) {
        return -1;
    }

    queue<pair<string, int>> q;

    st.erase(startGene);
    q.push({startGene, 0});

    while(!q.empty()) {
        auto [gene, mutations] = q.front();
        q.pop();

        if(gene == endGene) {
            return mutations;
        }

        for(int i = 0; i < 8; i++) {
            char orig = gene[i];

            for(auto ch : {'A', 'C', 'G', 'T'}) {
                gene[i] = ch;
                if(st.count(gene)) {
                    st.erase(gene);
                    q.push({gene, mutations + 1});
                }
            } 

            gene[i] = orig;
        }
    }

    return -1;
}

int main() {
    return 0;
}