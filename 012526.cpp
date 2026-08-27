#include<bits/stdc++.h>
using namespace std;

void sortColors(vector<int>& nums) {
    int n = nums.size();
    int i = 0, j = 0, k = n - 1;
    while(i <= k) {
        if(nums[i] == 0) {
            swap(nums[i], nums[j]);
            i++, j++;
        } else if(nums[i] == 1) {
            i++;
        } else {
            swap(nums[i], nums[k]);
            k--;
        }
    }
}

vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
    sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[0] * a[0] + a[1] * a[1] < b[0] * b[0] + b[1] * b[1];
    });
    return {points.begin(), points.begin() + k};
}

vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
    vector<vector<int>> res;
    sort(arr.begin(), arr.end());
    int minAbsDist = INT_MAX;
    for(int i = 0;i < arr.size() - 1; i++) {
        minAbsDist = min(minAbsDist, arr[i + 1] - arr[i]);
    }
    for(int i = 0; i < arr.size() - 1; i++) {
        if(arr[i + 1] - arr[i] == minAbsDist) {
            res.push_back({arr[i], arr[i + 1]});
        }
    }
    return res;
}

vector<int> sortArrayByParity(vector<int>& nums) {
    int n = nums.size();
    int i = 0, j = 0;
    while(i < n) {
        if((nums[i] & 1) == 0) {
            swap(nums[i], nums[j]);
            j++;
        }
        i++;
    }
    return nums;
}

int maxChunksToSorted(vector<int>& arr) {
    int maxi = INT_MIN, chunks = 0;
    for(int i = 0; i < arr.size(); i++) {
        maxi = max(maxi, arr[i]);
        if(i == maxi) {
            chunks++;
        }
    }
    return chunks;
}

int main() {
    
    return 0;
}