#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
    
}

int main() {
    vector<vector<int>> points = {
        {3,3}, {5,-1}, {-2,4}
    };
    int k = 2;

    for(auto x : kClosest(points, k)) {
        for(auto y : x) {
            cout << y << ' ';
        }
        cout << endl;
    }
    return 0;
}