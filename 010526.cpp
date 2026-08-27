#include<bits/stdc++.h>
using namespace std;

int mySqrt(int x) {
    int low = 1, high = x;
    int ans = 0;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        long long sq = 1LL * mid * mid;
        if(sq <= x) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

int main() {
    cout << mySqrt(8) << endl;
    return 0;
}