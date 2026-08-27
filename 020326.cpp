#include<bits/stdc++.h>
using namespace std;

bool isUgly(int n) {
    if(n == 0) {
        return false;
    }
    while(n % 2 == 0) {
        n /= 2;
    }
    while(n % 3 == 0) {
        n /= 3;
    }
    while(n % 5 == 0) {
        n /= 5;
    }
    return n == 1;
}

int nthUglyNumber(int n, int a, int b, int c) {
    
}

int main() {
    int n = 4, a = 2, b = 3, c = 4;
    cout << nthUglyNumber(n, a, b, c) << endl;
    return 0;
}