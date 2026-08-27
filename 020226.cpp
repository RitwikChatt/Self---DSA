#include<bits/stdc++.h>
using namespace std;

int nthUglyNumber(int n) {
    vector<int> ugly(n);
    ugly[0] = 1;
    int i2 = 0, i3 = 0, i5 = 0;
    for(int i = 1; i < n; i++) {
        ugly[i] = min(2 * ugly[i2], min(3 * ugly[i3], 5 * ugly[i5]));
        if(ugly[i] == 2 * ugly[i2]) {
            i2++;
        }
        if(ugly[i] == 3 * ugly[i3]) {
            i3++;
        }
        if(ugly[i] == 5 * ugly[i5]) {
            i5++;
        }
    }
    return ugly[n - 1];
}

int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    int sum = 0, cnt = 0;
    freq[sum]++;
    for(auto it : nums) {
        sum += it;
        cnt += freq[sum - k];
        freq[sum]++;
    }
    return cnt;
}

vector<int> twoSum(vector<int>& numbers, int target) {
    int n = numbers.size();
    int l = 0, r = n - 1;
    while(l < r) {
        if(numbers[l] + numbers[r] == target) {
            return {l + 1, r + 1};
        } else if(numbers[l] + numbers[r] < target) {
            l++;
        } else {
            r--;
        }
    }
    return {-1, -1};
}

int findPairs(vector<int>& nums, int k) {
    
}

int main() {
    vector<int> nums = {3,1,4,1,5};
    int k = 2;
    cout << findPairs(nums, k) << endl;
    return 0;
}