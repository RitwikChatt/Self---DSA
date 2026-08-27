#include<bits/stdc++.h>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    int n = nums.size();

    map<int, int> elementXIndexMapping;

    for(int i = 0; i < n; i++) {
        elementXIndexMapping[nums[i]] = i;
    }

    for(int i = 0; i < n; i++) {
        if(elementXIndexMapping.count(target - nums[i]) and i != elementXIndexMapping[target - nums[i]]) {
            return {i, elementXIndexMapping[target - nums[i]]};
        }
    }

    return {-1, -1};
}

int maxProfit(vector<int>& prices) {
    int n = prices.size();

    int minSoFar = prices[0], maxPro = INT_MIN;

    for(int i = 1; i < n; i++) {
        maxPro = max(maxPro, prices[i] - minSoFar);
        minSoFar = min(minSoFar, prices[i]);
    }

    return maxPro < 0 ? 0 : maxPro;
}

vector<int> spiralOrder(vector<vector<int>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();

    int top = 0, bottom = m - 1, left = 0, right = n - 1;

    vector<int> order;

    while(top <= bottom and left <= right) {
        for(int j = left; j <= right; j++) order.push_back(matrix[top][j]);
        top++;

        for(int i = top; i <= bottom; i++) order.push_back(matrix[i][right]);
        right--;

        if(top <= bottom) {
            for(int j = right; j >= left; j--) order.push_back(matrix[bottom][j]);
            bottom--;
        }

        if(left <= right) {
            for(int i = bottom; i >= top; i--) order.push_back(matrix[i][left]);
            left++;
        }
    }

    return order;
}

vector<vector<int>> construct2DArray(vector<int>& original, int m, int n) {
    int totalElements = original.size();

    vector<vector<int>> resultant;

    if(m * n != totalElements) {
        return resultant;
    }

    resultant.resize(m, vector<int>(n));

    for(int i = 0; i < totalElements; i++) {
        int row = i / n, col = i % n;

        resultant[row][col] = original[i];
    }

    return resultant;
}

bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();

    int low = 0, high = m * n - 1;

    while(low <= high) {
        int mid = low + (high - low) / 2;

        int row = mid / n, col = mid % n;

        if(matrix[row][col] == target) {
            return true;
        } else if(matrix[row][col] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return false;
}

int maxJump(vector<int>& stones) {
    int n = stones.size();

    int maxi = INT_MIN;

    for(int i = 0; i + 2 < n; i++) {
        maxi = max(maxi, stones[i + 2] - stones[i]);
    }

    return maxi;
}

int candy(vector<int>& ratings) {
    int n = ratings.size();

    vector<int> candies(n, 1);

    for(int i = 1; i < n; i++) {
        if(ratings[i] > ratings[i - 1]) {
            candies[i] = candies[i - 1] + 1;
        }
    }

    for(int i = n - 2; i >= 0; i--) {
        if(ratings[i] > ratings[i + 1]) {
            candies[i] = max(candies[i], candies[i + 1] + 1);
        }
    }

    int totalCandies = 0;

    for(auto c : candies) {
        totalCandies += c;
    }

    return totalCandies;
}

int main() {
    vector<int> ratings = {1,2,2};

    cout << candy(ratings) << endl;

    return 0;
}