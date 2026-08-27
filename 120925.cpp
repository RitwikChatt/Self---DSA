#include<bits/stdc++.h>
using namespace std;

vector<int> runningSum(vector<int>& nums) {
    int n = nums.size();
    vector<int> prefix(n);
    for(int i = 0;i < n;i++) {
        prefix[i] = nums[i];
        if(i - 1 >= 0) {
            prefix[i] += prefix[i - 1];
        }
    }
    return prefix;
}

int numSpecial(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size();
    vector<int> onesInRow(n), onesInCol(m);
    for(int i = 0; i < n;i++) {
        for(int j = 0;j < m;j++) {
            onesInRow[i] += mat[i][j];
            onesInCol[j] += mat[i][j];
        }
    }
    int specialPositions = 0;
    for(int i = 0; i < n;i++) {
        for(int j = 0;j < m;j++) {
            if(mat[i][j] and onesInRow[i] == 1 and onesInCol[j] == 1) {
                specialPositions++;
            }
        }
    }
    return specialPositions;
}

vector<vector<int>> transpose(vector<vector<int>>& matrix) {
    int n = matrix.size(), m = matrix[0].size();
    vector<vector<int>> transposedMatrix;
    for(int j = 0;j < m;j++) {
        vector<int> temp;
        for(int i = 0;i < n;i++) {
            temp.push_back(matrix[i][j]);
        }
        transposedMatrix.push_back(temp);
    }
    return transposedMatrix;
}

vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
    int m = mat.size(), n = mat[0].size();
    vector<vector<int>> reshapedMatrix(r, vector<int>(c));
    if(m * n != r * c) {
        return mat;
    }
    for(int i = 0;i < r * c;i++) {
        reshapedMatrix[i / c][i % c] = mat[i / n][i % n];
    } 
    return reshapedMatrix;
}

int main() {
    
    return 0;
}