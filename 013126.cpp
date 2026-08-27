#include<bits/stdc++.h>
using namespace std;

int hIndexOptimal(vector<int>& citations) {
    int n = citations.size();
    int low = 0, high = n;
    int h;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        int noOfPapersWithGreaterEqualMidCitations = 0;
        for(auto it : citations) {
            if(it >= mid) {
                noOfPapersWithGreaterEqualMidCitations++;
            }
        }
        if(noOfPapersWithGreaterEqualMidCitations >= mid) {
            h = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    } 
    return h;
}

int hIndexBrute(vector<int>& citations) {
    int n = citations.size();
    for(int h = n; h >= 0; h--) {
        int noOfPapersWithGreaterEqualHCitations = 0;
        for(auto it : citations) {
            if(it >= h) {
                noOfPapersWithGreaterEqualHCitations++;
            }
        }
        if(noOfPapersWithGreaterEqualHCitations >= h) {
            return h;
        }
    }
    return -1;
}

int main() {
    vector<int> citations = {3,0,6,1,5};
    cout << hIndexBrute(citations) << endl;
    return 0;
}