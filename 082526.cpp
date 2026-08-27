#include<bits/stdc++.h>
using namespace std;

bool searchMatrix1(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();

    int i = 0, j = n - 1;

    while(i < m and j >= 0) {
        if(matrix[i][j] == target) {
            return true;
        } else if(matrix[i][j] > target) {
            j--;
        } else {
            i++;
        }
    }

    return false;
}

int findPeakElement(vector<int>& nums) {
    int low = 0, high = nums.size() - 1;

    while(low < high) {
        int mid = low + (high - low) / 2;

        if(nums[mid] < nums[mid + 1]) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    return low;
}

int singleNonDuplicate(vector<int>& nums) {
    int low = 0, high = nums.size() - 1;

    while(low < high) {
        int mid = low + (high - low) / 2;

        if(nums[mid] == nums[mid ^ 1]) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    return nums[high];
}

bool searchMatrix2(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();

    int low = 0, high = m * n - 1;

    while(low <= high) {
        int mid = low + (high - low ) / 2;

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

string smallestGoodBase(string n) {
    long long num = stoll(n);

    int maxM = log2(num);

    for(int m = maxM; m >= 1; m--) {
        long long low = 2, high = pow(num, 1.0 / m) + 1;

        while(low <= high) {
            long long k = low + (high - low) / 2;

            long long power = 1, sum = 1;

            bool overflow = false;

            for(int i = 1; i <= m; i++) {
                if(power > num / k) {
                    overflow = true;
                    break;
                }

                power *= k;

                if(sum > num - power) {
                    overflow = true;
                    break;
                }

                sum += power;
            }

            if(!overflow and sum == num) {
                return to_string(k);
            }

            if(overflow or sum > num) {
                high = k - 1;
            } else {
                low = k + 1;
            }
        }
    }

    return to_string(num - 1);
}

bool isPossible(vector<int>& position, int minDist, int totalBalls) {
    int lastOccupied = position[0], ballsPlaced = 1;

    for(int i = 1; i < position.size(); i++) {
        if(position[i] - lastOccupied >= minDist) {
            ballsPlaced++;
            lastOccupied = position[i];

            if(ballsPlaced == totalBalls) {
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

int main() {
    vector<int> position = {1,2,3,4,7};
    int m = 3;

    cout << maxDistance(position, m) << endl;
    return 0;
}