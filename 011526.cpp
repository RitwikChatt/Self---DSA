#include<bits/stdc++.h>
using namespace std;

vector<int> grayCode(int n) {
    vector<int> res;
    int sz = (1 << n);
    for(int i = 0; i < sz; i++) {
        res.push_back(i ^ (i >> 1));
    }
    return res;
}

int main() {
    
    return 0;
}