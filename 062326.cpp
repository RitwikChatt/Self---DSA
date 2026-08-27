#include<bits/stdc++.h>
using namespace std;

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

vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    map<string, int> emailToIDMapping;
    int id = 0;

    for(auto account : accounts) {
        for(int i = 1; i < account.size(); i++) {
            if(emailToIDMapping.find(account[i]) == emailToIDMapping.end()) {
                emailToIDMapping[account[i]] = id++;
            }
        }
    }

    int numOfNodes = emailToIDMapping.size();

    DSU* dsu = new DSU(numOfNodes);

    for(auto account : accounts) {
        for(int i = 2; i < account.size(); i++) {
            dsu->unite(emailToIDMapping[account[1]], emailToIDMapping[account[i]]);
        }
    }

    map<int, string> IDToNameMapping;

    for(auto account : accounts) {
        if(IDToNameMapping.find(emailToIDMapping[account[1]]) == IDToNameMapping.end()) {
            IDToNameMapping[emailToIDMapping[account[1]]] = account[0];
        }
    }

    map<int, vector<string>> groups;

    for(auto it : emailToIDMapping) {
        string email = it.first;
        int id = it.second;

        int root = dsu->find(id);

        groups[root].push_back(email);
    }

    vector<vector<string>> ans;

    for(auto group : groups) {
        vector<string> emails = group.second;
        sort(emails.begin(), emails.end());

        vector<string> account;
        account.push_back(IDToNameMapping[group.first]);
        
        for(auto email : emails) {
            account.push_back(email);
        }

        ans.push_back(account);

    }

    return ans;
}

int main() {
    vector<vector<string>> accounts = {
        {"John","johnsmith@mail.com","john_newyork@mail.com"}, 
        {"John","johnsmith@mail.com","john00@mail.com"}, 
        {"Mary","mary@mail.com"}, 
        {"John","johnnybravo@mail.com"}
    };

    for(auto x : accountsMerge(accounts)) {
        for(auto y : x) {
            cout << y << ' ';
        }
        cout << endl;
    }
    return 0;
}