#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
    
}

int main() {
    vector<vector<int>> heights = {{1,2,2,3,5},{3,2,3,4,4},{2,4,5,3,1},{6,7,1,4,5},{5,1,1,2,4}};

    for(auto x : pacificAtlantic(heights)) {
        for(auto y : x) {
            cout << y << ' ';
        }
        cout << endl;
    }

    return 0;
}