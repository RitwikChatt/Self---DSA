#include<bits/stdc++.h>
using namespace std;

long long countUglyNumbersLesserEqual(long long x, long long a, 
                            long long b, long long c) {
    return x / a + x / b + x / c 
         - x / lcm(a, b) - x / lcm(b, c) - x / lcm(a, c)
         + x / lcm(a, lcm(b, c));
}

int nthUglyNumber(int n, int a, int b, int c) {
    long long low = 1, high = 2e18, ans;
    while(low <= high) {
        long long mid = low + (high - low) / 2;
        if(countUglyNumbersLesserEqual(mid, a, b, c) >= n) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return ans;
}

int findPairsOptimal(vector<int>& nums, int k) {
    int n = nums.size(), count = 0;
    sort(nums.begin(), nums.end());
    int l = 0, r = 1;
    while(r < n) {
        if(l == r) {
            r = l + 1;
            continue;
        }
        int diff = abs(nums[l] - nums[r]);
        if(diff < k) {
            r++;
        } else if(diff > k) {
            l++;
        } else {
            count++;
            l++, r++;
            while(r < n and nums[r] == nums[r - 1]) {
                r++;
            }
        }
    }
    return count;
}

int findPairsBrute(vector<int>& nums, int k) {
    int n = nums.size(), count = 0;
    sort(nums.begin(), nums.end());
    for(int i = 0; i < n - 1; i++) {
        if(i > 0 and nums[i] == nums[i - 1]) {
            continue;
        }
        for(int j = i + 1; j < n; j++) {
            if(j > i + 1 and nums[j] == nums[j - 1]) {
                continue;
            }
            if(abs(nums[i] - nums[j]) == k) {
                count++;
            }
        }
    }
    return count;
}

int solve(vector<int> input1, vector<int> input2, vector<int> input3) {
    int n1 = input1.size(), n2 = input2.size(), n3 = input3.size();
    int i = 0, j = 0, k = 0;
    int val = INT_MAX, curr_min = INT_MAX, curr_max = INT_MIN;
    while(i < n1 and j < n2 and k < n3) {
        curr_max = max(input1[i], max(input2[j], input3[k]));
        curr_min = min(input1[i], min(input2[j], input3[k]));
        val = min(val, curr_max - curr_min);
        if(curr_min == input1[i]) {
            i++;
        }
        if(curr_min == input2[j]) {
            j++;
        }
        if(curr_min == input3[k]) {
            k++;
        }
    }
    return val;
}

int maxArea(vector<int>& height) {
    
}

int main() {
    vector<int> height = {1,8,6,2,5,4,8,3,7};
    cout << maxArea(height) << endl;
    return 0;
}