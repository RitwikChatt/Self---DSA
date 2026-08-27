#include<bits/stdc++.h>
using namespace std;

int singleNumber(vector<int>& nums) {
    int ans = 0;
    for(int i = 0;i < 32;i++) {
        int setbits = 0;
        for(auto it : nums) {
            if(it & (1 << i)) {
                setbits++;
            }
        }
        int mask = (setbits % 3) << i;
        ans |= mask;
    }
    return ans;
}

int binaryToInt(string num) {
    int res = 0, mult = 1;
    for(int i = num.length() - 1;i >= 0;i--) {
        res += (num[i] - '0') * mult;
        mult *= 2;
    }
    return res;
}

int firstSetBitFromLeft(int n) {
    int lastSetBit;
    for(int i = 0;i < 32;i++) {
        if(n & (1 << i)) {
            lastSetBit = i + 1;
        }
    }
    return 32 - lastSetBit + 1;
}

int firstSetBitFromRight(int n) {
    int firstSetBit;
    for(int i = 0;i < 32;i++) {
        if(n & (1 << i)) {
            return i + 1;
        }
    }
    return -1;
}

int reverseBits(int n) {
    int ans = 0;
    for(int i = 0;i < 32;i++) {
        if(n & (1 << i)) {
            int new_pos = 32 - i - 1;
            ans |= (1 << new_pos);
        }
    }
    return ans;
}

uint32_t solve(string n) {
    uint32_t ans = 0;
    for(int i = n.length() - 1;i >= 0;i--) {
        ans <<= 1;
        if(n[i] == '1') {
            ans |= 1;
        }
    }
    return ans;
}

bool hasAlternatingBits(int n) {
    
}

int main() {
    int n = 5;
    hasAlternatingBits(n) ? cout << "yes" << endl : cout << "no" << endl; 
    return 0;
}