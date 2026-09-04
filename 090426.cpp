#include<bits/stdc++.h>
using namespace std;

int minimumDifference(vector<int>& nums) {
    int n = nums.size() / 2, total = accumulate(nums.begin(), nums.end(), 0);

    vector<vector<int>> leftSums(n + 1), rightSums(n + 1);

    for(int mask = 0; mask < (1 << n); mask++) {
        int leftSum = 0, rightSum = 0, count = 0;

        for(int i = 0; i < n; i++) {
            if(mask & (1 << i)) {
                count++;
                leftSum += nums[i];
                rightSum += nums[i + n];
            }
        }

        leftSums[count].push_back(leftSum);
        rightSums[count].push_back(rightSum);
    }

    for(int i = 0; i <= n; i++) {
        sort(rightSums[i].begin(), rightSums[i].end());
    }

    int answer = INT_MAX;

    for(int leftCount = 0; leftCount <= n; leftCount++) {
        int rightCount = n - leftCount;

        for(int leftSum : leftSums[leftCount]) {
            int target = total / 2 - leftSum;

            auto &sums = rightSums[rightCount];

            auto it = lower_bound(sums.begin(), sums.end(), target);

            if(it != sums.end()) {
                int subsetSum = leftSum + *it;

                answer = min(answer, abs(total - 2 * subsetSum));
            }

            if(it != sums.begin()) {
                --it;

                int subsetSum = leftSum + *it;

                answer = min(answer, abs(total - 2 * subsetSum));
            }
        }
    }

    return answer;
}

vector<int> computeSuffixMax(vector<int>& arr) {
    int n = arr.size();

    vector<int> suffixMax(n);

    for(int i = n - 2; i >= 0; i--) {
        suffixMax[i] = max(suffixMax[i + 1], arr[i + 1]);
    }

    return suffixMax;
}

vector<int> computePrefixMax(vector<int>& arr) {
    int n = arr.size();

    vector<int> prefixMax(n);

    for(int i = 1; i < n; i++) {
        prefixMax[i] = max(prefixMax[i - 1], arr[i - 1]);
    }

    return prefixMax;
}

int trap(vector<int>& height) {
    int n = height.size();

    vector<int> suffixMax = computeSuffixMax(height), prefixMax = computePrefixMax(height);

    int totalWaterTrapped = 0;

    for(int i = 0; i < n; i++) {
        totalWaterTrapped += max(0, min(suffixMax[i], prefixMax[i]) - height[i]);
    }

    return totalWaterTrapped;
}

int longestAwesome(string s) {
    
}

int main() {
    cout << longestAwesome("3242415") << endl;
    return 0;
}