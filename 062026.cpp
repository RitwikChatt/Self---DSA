#include<bits/stdc++.h>
using namespace std;

class Graph {
    private:
    int nodes;
    vector<vector<int>> adjMat;

    public:
    Graph(int nodes) {
        this->nodes = nodes;

        this->adjMat.resize(this->nodes, vector<int>(this->nodes, INT_MAX));

        for(int i = 0; i < this->nodes; i++) {
            this->adjMat[i][i] = 0;
        }
    }

    void addEdge(int a, int b, int wt) {
        this->adjMat[a][b] = wt;   
    }

    void printAdjMat() {
        for(auto x : this->adjMat) {
            for(auto y : x) {
                cout << y << ' ';
            }
            cout << endl;
        }
    }

    vector<vector<int>> floydWarshall() {
        //dp[i][j] -> Shortest distance between i and j

        vector<vector<int>> dp = this->adjMat;

        for(int k = 0; k < this->nodes; k++) {
            for(int i = 0; i < this->nodes; i++) {
                for(int j = 0; j < this->nodes; j++) {
                    if(dp[i][k] == INT_MAX or dp[k][j] == INT_MAX) {
                        continue;
                    }
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
                }
            }
        }

        return dp;
    }

};

int main() {
    Graph* g = new Graph(6);

    g->addEdge(0, 3, 2);
    g->addEdge(0, 1, 3);
    g->addEdge(5, 0, 4);
    g->addEdge(3, 1, 1);
    g->addEdge(1, 5, 7);
    g->addEdge(2, 3, 3);
    g->addEdge(1, 2, 6);
    g->addEdge(2, 4, 1);
    g->addEdge(5, 4, 2);

    vector<vector<int>> dp = g->floydWarshall();

    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            cout << "The shortest distance between " << i << " and " << j << " is " << dp[i][j] << endl;
        }
    }

    return 0;
}