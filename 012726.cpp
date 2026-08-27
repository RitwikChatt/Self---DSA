#include<bits/stdc++.h>
using namespace std;

int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int> pq;
    for(auto it : nums) {
        pq.push(it);
    }
    while(k-- > 1) {
        pq.pop();
    }
    return pq.top();
}

int rp = 0;

vector<int> merge(vector<int>& a, vector<int>& b) {
    int n = a.size(), m = b.size();
    int i = 0, j = 0, k = 0;
    vector<int> mergedArray(n + m);
    while(i < n and j < m) {
        if(a[i] <= b[j]) {
            mergedArray[k++] = a[i++];
        } else {
            mergedArray[k++] = b[j++];
        }
    }
    while(i < n) {
        mergedArray[k++] = a[i++];
    } 
    while(j < m) {
        mergedArray[k++] = b[j++];
    }
    return mergedArray;
}

vector<int> mergeSort(vector<int>& nums, int start, int end) {
    if(start == end) {
        return vector<int>{nums[start]};
    }
    int mid = start + (end - start) / 2;
    vector<int> leftHalf = mergeSort(nums, start, mid);
    vector<int> rightHalf = mergeSort(nums, mid + 1, end);
    int i = 0, j = 0;
    while(i < mid - start + 1 and j < end - mid) {
        if(leftHalf[i] > 2 * (long long)rightHalf[j]) {
            rp += mid - start + 1 - i;
            j++;
        } else {
            i++;
        }
    }
    return merge(leftHalf, rightHalf);
}

int reversePairs(vector<int>& nums) {
    vector<int> numsSorted = mergeSort(nums, 0, nums.size() - 1);
    return rp;
}

vector<int> countSmallerOptimal(vector<int>& nums) {
    
}

vector<int> countSmallerBrute(vector<int>& nums) {
    int n = nums.size();
    vector<int> res(n);
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(nums[j] < nums[i]) {
                res[i]++;
            }
        }
    }
    return res;
}

int main() {
    vector<int> nums = {5,2,6,1};
    vector<int> res = countSmallerOptimal(nums);
    for(auto it : res) {
        cout << it << ' ';
    }
    return 0;
}