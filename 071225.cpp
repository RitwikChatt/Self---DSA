#include<bits/stdc++.h>
using namespace std;

int maxChunksToSorted(vector<int>& arr) {
    int n = arr.size();
    int leftMax = INT_MIN;
    vector<int> rightMin(n, INT_MAX);
    int chunks = 0;
    for(int i = n - 2;i >= 0;i--) {
        rightMin[i] = min(rightMin[i + 1], arr[i + 1]);
    }
    for(int i = 0;i < n;i++) {
        leftMax = max(leftMax, arr[i]);
        if(leftMax <= rightMin[i]) {
            chunks++;
        }
    }
    return chunks;
}

int solve1(vector<vector<int>>& input) {
    int n = input.size(), m = input[0].size();
    int ans = 0;
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < m;j++) {
            if(input[i][j]) {
                ans++;
                int flag = true;
                for(int row = 0;row < n;row++) {
                    if(row == i) {
                        continue;
                    }
                    if(input[row][j]) {
                        ans--;
                        flag = false;
                        break;
                    }
                }
                if(flag) {
                    for(int col = 0;col < m;col++) {
                        if(col == j) {
                            continue;
                        }
                        if(input[i][col]) {
                            ans--;
                            break;
                        }
                    }
                }
            }
        }
    }
    return ans;
}

bool solve2(vector<vector<int>>& input, int target) {
    int n = input.size(), m = input[0].size();
    int low = 0, high = n * m - 1;
    while(low <= high) {
        int mid = high - (high - low) / 2;
        int row = mid / m, col = mid % m;
        if(input[row][col] == target) {
            return true;
        } else if(input[row][col] > target) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return false;
}

vector<vector<int>> transpose(vector<vector<int>>& matrix) {
    int n = matrix.size(), m = matrix[0].size();
    for(int i = 0;i < n - 1;i++) {
        for(int j = 1;j < m;j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
    return matrix;
}

int submatrixSum(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size(), ans = 0;
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < m;j++) {
            ans += mat[i][j] * (i + 1) * (j + 1) * (n - i) * (m - j);
        }
    }
    return ans;
}

int main() {
    vector<vector<int>> mat = {{1, 2, 3}, 
                               {4, 5, 6}, 
                               {7, 8, 9}};
    int ans = submatrixSum(mat);
    cout << ans << endl;
    return 0;
}