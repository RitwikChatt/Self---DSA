#include<bits/stdc++.h>
using namespace std;

int maxArea(vector<int>& height) {
    int n = height.size();

    int left = 0, right = n - 1, area = INT_MIN;

    while(left <= right) {
        area = max(area, (right - left) * min(height[left], height[right]));

        if(height[left] <= height[right]) {
            left++;
        } else {
            right--;
        }
    }

    return area;
}

int minimumDifference(vector<int>& nums) {
    
}

int main() {
    vector<int> nums = {3,9,7,3};

    cout << minimumDifference(nums) << endl;
    return 0;
}