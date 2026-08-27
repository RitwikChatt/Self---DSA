#include<bits/stdc++.h>
using namespace std;

// class Graph {
//     private:
//     vector<vector<int>> adjMat;
//     int numOfNodes;

//     public:
//     Graph(int numOfNodes) {
//         this->numOfNodes = numOfNodes;
//         this->adjMat.resize(this->numOfNodes);

//         for(int i = 0; i < this->numOfNodes; i++) {
//             this->adjMat[i].resize(this->numOfNodes, 0);
//         }
//     }

//     void addEdge(int a, int b) {
//         this->adjMat[a][b] = this->adjMat[b][a] = 1;
//     }

//     void printAdjMat() {
//         for(auto x : this->adjMat) {
//             for(auto y : x) {
//                 cout << y << ' ';
//             }
//             cout << endl;
//         }
//     }
// };

class Graph {
    private:
    unordered_map<int, vector<int>> adjList;
    int numOfNodes;

    public:
    Graph(int numOfNodes) {
        this->numOfNodes = numOfNodes;
        this->adjList.clear();
    }

    void addEdge(int a, int b) {
        this->adjList[a].push_back(b);
        this->adjList[b].push_back(a);
    }

    void printAdjList() {
        for(auto x : this->adjList) {
            for(auto y : x.second) {
                cout << y << ' ';
            }
            cout << endl;
        }
    }
};

int main() {
    Graph* g = new Graph(6);

    g->addEdge(0, 1);
    g->addEdge(0, 2);
    g->addEdge(0, 3);
    g->addEdge(3, 7);
    g->addEdge(1, 2);
    g->addEdge(2, 3);
    g->addEdge(2, 6);
    g->addEdge(2, 4);
    g->addEdge(2, 5);
    g->addEdge(4, 5);

    g->printAdjList();

    return 0;
}