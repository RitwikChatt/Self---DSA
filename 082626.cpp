#include<bits/stdc++.h>
using namespace std;

int sumOfPowerBruteForce(vector<int>& nums) {
    int n = nums.size();

    sort(nums.begin(), nums.end());

    long long ans = 0, mod = 1e9 + 7;

    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            long long power = 1;

            for(int k = 0; k < j - i - 1; k++) {
                power = (power * 2) % mod;
            }

            ans = (ans + 1LL * nums[j] * nums[j] % mod * nums[i] % mod * power % mod) % mod;
        }
    }

    return ans;
}

int sumOfPowerOptimal(vector<int>& nums) {
    int n = nums.size(), mod = 1e9 + 7;

    sort(nums.begin(), nums.end());

    long long ans = 0, sum = 0;

    for(int num : nums) {
        ans = (ans + 1LL * sum * num % mod * num % mod) % mod;
        ans = (ans + 1LL * num * num % mod * num % mod) % mod;

        sum = ((sum * 2) % mod + num) % mod;
    }

    return ans;
}

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