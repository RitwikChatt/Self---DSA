#include<bits/stdc++.h>
using namespace std;

int firstOccurence(vector<int>& nums, int target) {
    int n = nums.size();
    int low = 0, high = n - 1;
    int pos = -1;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(nums[mid] == target) {
            pos = mid;
            high = mid - 1;
        } else if(nums[mid] > target) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return pos;
}

int lastOccurence(vector<int>& nums, int target) {
    int n = nums.size();
    int low = 0, high = n - 1;
    int pos = -1;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(nums[mid] == target) {
            pos = mid;
            low = mid + 1;
        } else if(nums[mid] > target) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return pos;
}
 
int singleNonDuplicate(vector<int>& nums) {
    int n = nums.size();
    int low = 0, high = n - 1;
    while(low <= high) { 
        int mid = low + (high - low) / 2;
        if(mid != n - 1 and nums[mid] == nums[mid ^ 1]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return nums[low];
}

bool hasAlternatingBits(int n) {
    int actualLastBit = n & 1;
    int expectedLastBit = n & 1;
    while(n and actualLastBit == expectedLastBit) {
        n >>= 1;
        actualLastBit = n & 1;
        expectedLastBit ^= 1;
        if(actualLastBit != expectedLastBit) {
            return false;
        }
    }
    return true;
}

vector<int> evenOddBit(int n) {
    vector<int> evenOdd(2);
    int idx = 0;
    while(n) {
        if(n & 1) {
            evenOdd[idx % 2]++;
        }
        idx++;
        n >>= 1;
    }
    return evenOdd;
}

vector<int> countBits(int n) {
    vector<int> dp(n + 1);
    for(int i = 1;i <= n;i++) {
        dp[i] = dp[i & (i - 1)] + 1;
    }
    return dp;
}

vector<int> searchRange(vector<int>& nums, int target) {
    vector<int> ans = {-1, -1};
    int n = nums.size();
    int low = 0, high = n - 1;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(target == nums[mid]) {
            ans[0] = mid;
            high = mid - 1;
        } else if(target > nums[mid]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    low = 0, high = n - 1;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(target == nums[mid]) {
            ans[1] = mid;
            low = mid + 1;
        } else if(target > nums[mid]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

int search(vector<int>& nums, int target) {
    int n = nums.size();
    int low = 0, high = n - 1;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(nums[mid] == target) {
            return mid;
        }
        if(nums[low] <= nums[mid]) {
            if(nums[low] <= target and target <= nums[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        } else {
            if(nums[mid] <= target and target <= nums[high]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }
    return -1;
}

int findPeakElement(vector<int>& nums) {
    int n = nums.size();
    if(n == 1) {
        return 0;
    }
    if(nums[0] > nums[1]) {
        return 0;
    }
    if(nums[n - 2] < nums[n - 1]) {
        return n - 1;
    }
    int low = 1, high = n - 2;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(nums[mid - 1] < nums[mid] and nums[mid] > nums[mid + 1]) {
            return mid;
        } else if(nums[mid - 1] < nums[mid] and nums[mid] < nums[mid + 1]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int divide(int dividend, int divisor) {
    if(dividend == INT_MIN and divisor == -1) {
        return INT_MAX;
    }
    long long quotient = 0;
    long long dividendABS = llabs(dividend);
    long long divisorABS = llabs(divisor);
    while (dividendABS >= divisorABS) {
        long long multiple = 1;
        long long temp = divisorABS;
        while ((temp << 1) <= dividendABS) {
            temp <<= 1;
            multiple <<= 1;
        }
        quotient += multiple;
        dividendABS -= temp;
    }
    if ((dividend < 0) ^ (divisor < 0)) {
        quotient = -quotient;
    }
    return quotient;
}

int findSmallestInRotatedSortedArray(vector<int>& nums) {
    int n = nums.size();
    int low = 0, high = n - 1;
    while(low < high) {
        int mid = low + (high - low) / 2;
        if(nums[mid] <= nums[high]) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return low = high;
}

int findHighestInRotatedSortedArray(vector<int>& nums) {
    int n = nums.size();
    int pivot = findSmallestInRotatedSortedArray(nums);
    return (pivot >= 1) ? (pivot - 1) : (n - 1);
}

int searchBetter(vector<int>& nums, int target) {
    int n = nums.size(), low, high;
    int pivot = findSmallestInRotatedSortedArray(nums);
    if(nums[pivot] <= target and target <= nums[n - 1]) {
        low = pivot, high = n - 1;
    } else {
        low = 0, high = pivot - 1;
    }
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(target == nums[mid]) {
            return mid;
        } else if(target > nums[mid]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

bool isPossible(vector<int>& position, int minDistance, int m) {
    int ballsPlaced = 1;
    int lastPosOccupied = position[0];
    int n = position.size();
    for(int i = 1;i < n;i++) {
        if(position[i] - lastPosOccupied >= minDistance) {
            ballsPlaced++;
            lastPosOccupied = position[i];
            if(ballsPlaced == m) {
                return true;
            }
        }
    }
    return false;
}

int maxDistance(vector<int>& position, int m) {
    int n = position.size();
    sort(position.begin(), position.end());
    int low = 1, high = position[n - 1] - position[0];
    int ans;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(isPossible(position, mid, m)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

int totalHammingDistanceBrute(vector<int>& nums) {
    int n = nums.size();
    int totalHammingDistance = 0;
    for(int i = 0;i < n;i++) {
        for(int j = i + 1;j < n;j++) {
            int a = nums[i], b = nums[j];
            while(a or b) {
                int aLastBit = a & 1, bLastBit = b & 1;
                if(aLastBit != bLastBit) {
                    totalHammingDistance++;
                }
                a >>= 1, b >>= 1;
            }
        }
    }
    return totalHammingDistance;
}

int totalHammingDistanceOptimal(vector<int>& nums) {
    int n = nums.size();
    int totalHammingDistance = 0;
    for(int i = 0;i < 32;i++) {
        int count = 0;
        for(int j = 0;j < n;j++) {
            if(nums[j] & (1 << i)) {
                count++;
            }
        }
        totalHammingDistance += count * (n - count);
    }
    return totalHammingDistance;
}

bool isPossibleToShipWithinDDays(vector<int>& weights, int maxCapacity, int days) {
    int load = 0, daysTaken = 1;
    for(auto it : weights) {
        load += it;
        if(load > maxCapacity) {
            daysTaken++;
            load = it;
        }
    }
    return daysTaken <= days;
}

int shipWithinDays(vector<int>& weights, int days) {
    int maxWeight = weights[max_element(weights.begin(), weights.end()) - weights.begin()];
    int minCapacity = maxWeight;
    int maxCapacity = 0;
    for(auto it : weights) {
        maxCapacity += it;
    }
    int low = minCapacity, high = maxCapacity;
    int ans;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(isPossibleToShipWithinDDays(weights, mid, days)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return ans;
}

int maxAreaBrute(vector<int>& height) {
    int n = height.size();
    int maxArea = INT_MIN;
    for(int i = 0;i < n;i++) {
        for(int j = i + 1;j < n;j++) {
            maxArea = max(maxArea, min(height[i], height[j]) * (j - i));
        }
    }
    return maxArea;
}

int maxAreaOptimal(vector<int>& height) {
    int n = height.size();
    int maxArea = INT_MIN;
    int l = 0, r = n - 1;
    while(l < r) {
        maxArea = max(maxArea, min(height[l], height[r]) * (r - l));
        if(height[l] < height[r]) {
            l++;
        } else {
            r--;
        }
    }
    return maxArea;
}

vector<int> findClosestElements(vector<int>& arr, int k, int x) {
    vector<pair<int, int>> vec;
    for(auto it : arr) {
        vec.push_back({abs(it - x), it});
    }
    sort(vec.begin(), vec.end(), [](pair<int, int>& a, pair<int, int>& b) {
        return a.first < b.first or (a.first == b.first and a.second < b.second);
    });
    vector<int> ans;
    for(int i = 0;i < k;i++) {
        ans.push_back(vec[i].second);
    }
    sort(ans.begin(), ans.end());
    return ans;
}

int main() {
    vector<int> arr = {1,2,3,4,5};
    int k = 4, x = 3;
    vector<int> ans = findClosestElements(arr, k, x);
    for(auto it : ans) {
        cout << it << ' ';
    }
    return 0;
}