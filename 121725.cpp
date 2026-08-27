#include<bits/stdc++.h>
using namespace std;

bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
    int x1  = rec1[0], y1 = rec1[1], x2 = rec1[2], y2 = rec1[3];
    int x3  = rec2[0], y3 = rec2[1], x4 = rec2[2], y4 = rec2[3];
    if(x3 >= x2 or x4 <= x1 or y4 <= y1 or y3 >= y2) {
        return false;
    } 
    return true;
}

string alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

string convertToTitle(int columnNumber) {
    string ans = "";
    while(columnNumber) {
        columnNumber--;
        int idx = columnNumber % 26;
        ans += alphabets[idx];
        columnNumber /= 26;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int countSetBits(int n) {
    int count = 0;
    while(n) {
        if(n & 1) {
            count++;
        }
        n >>= 1;
    }
    return count;
}

int singleNumber(vector<int>& nums) {
    
}

int main() {
    vector<int> nums = {0,1,0,1,0,1,99};
    int ans = singleNumber(nums);
    cout << ans << endl;
    return 0;
}