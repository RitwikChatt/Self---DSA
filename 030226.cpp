#include<bits/stdc++.h>
using namespace std;

int firstUniqChar(string s) {
    int n = s.length();
    vector<int> characterFrequencyMapping(26);
    for(char ch : s) {
        characterFrequencyMapping[ch - 'a']++;
    }
    for(int i = 0; i < n; i++) {
        if(characterFrequencyMapping[s[i] - 'a'] == 1) {
            return i;
        }
    }
    return -1;
}

int largestPerimeter(vector<int>& nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    for(int i = n - 1; i >= 2; i--) {
        int a = nums[i - 2], b = nums[i - 1], c = nums[i];
        if(a + b > c) {
            return (a + b + c);
        }
    }
    return 0;
}

bool canArrange(vector<int>& arr, int k) {
    unordered_map<int, int> remainderFrequencyMapping;
    for(int num : arr) {
        remainderFrequencyMapping[((num % k) + k) % k]++;
    }
    if(remainderFrequencyMapping[0] % 2) {
        return false;
    }
    for(int r = 1; r <= k / 2; r++) {
        if(r == k - r) {
            if(remainderFrequencyMapping[r] % 2) {
                return false;
            }
        } else {
            if(remainderFrequencyMapping[r] != remainderFrequencyMapping[k - r]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    
    return 0;
}