#include<bits/stdc++.h>
using namespace std;

vector<pair<int, int>> merge(vector<pair<int, int>>& a, vector<pair<int, int>>& b, 
    vector<int>& numberOfSmallerElementsToTheRight) {
    int n = a.size(), m = b.size();
    int i = 0, j = 0, k = 0;
    vector<pair<int, int>> mergedVector(n + m);
    int elementsThatMovedFromRight = 0;
    while(i < n and j < m) {
        if(a[i] <= b[j]) {
            numberOfSmallerElementsToTheRight[a[i].second] += elementsThatMovedFromRight;
            mergedVector[k++] = a[i++];
        } else {
            elementsThatMovedFromRight++;
            mergedVector[k++] = b[j++];
        }
    }
    while(i < n) {
        numberOfSmallerElementsToTheRight[a[i].second] += elementsThatMovedFromRight;
        mergedVector[k++] = a[i++];
    }
    while(j < m) {
        mergedVector[k++] = b[j++];
    }
    return mergedVector;
}

vector<pair<int, int>> mergeSort(vector<pair<int, int>>& elementsAndIndices, 
    int start, int end, vector<int>& numberOfSmallerElementsToTheRight) {
        if(start == end) {
            return vector<pair<int, int>>{elementsAndIndices[start]};
        }
        int mid = start + (end -  start) / 2;
        vector<pair<int, int>> leftHalf = mergeSort(elementsAndIndices, start, mid, 
            numberOfSmallerElementsToTheRight);
        vector<pair<int, int>> rightHalf = mergeSort(elementsAndIndices, mid + 1, 
            end, numberOfSmallerElementsToTheRight);
        return merge(leftHalf, rightHalf, numberOfSmallerElementsToTheRight);
}

vector<int> countSmaller(vector<int>& nums) {
    int n = nums.size();
    vector<int> numberOfSmallerElementsToTheRight(n);
    vector<pair<int, int>> elementsAndIndices(n);
    for(int i = 0; i < n; i++) {
        elementsAndIndices[i] = {nums[i], i};
    }
    mergeSort(elementsAndIndices, 0, n - 1, numberOfSmallerElementsToTheRight);
    return numberOfSmallerElementsToTheRight;
}

vector<vector<int>> possiblePermutations;

void permuteUtil(int idx, vector<int>& permutation, vector<int>& nums) {
    if(idx == nums.size()) {
        possiblePermutations.push_back(permutation);
        return;
    }
    for(auto it : nums) {
        if(find(permutation.begin(), permutation.end(), it) == permutation.end()) {
            permutation.push_back(it);
            permuteUtil(idx + 1, permutation, nums);
            permutation.pop_back();
        }
    }
}

vector<vector<int>> permute(vector<int>& nums) {
    vector<int> permutations;
    permuteUtil(0, permutations, nums);
    return possiblePermutations;
}

vector<vector<int>> allSubsets;

void subsetsUtil(int idx, vector<int>& subset, vector<int>& nums) {
    if(idx == nums.size()) {
        allSubsets.push_back(subset);
        return;
    }
    subset.push_back(nums[idx]);
    subsetsUtil(idx + 1, subset, nums);
    subset.pop_back();
    subsetsUtil(idx + 1, subset, nums);
}

vector<vector<int>> subsets(vector<int>& nums) {
    vector<int> subset;
    subsetsUtil(0, subset, nums);
    return allSubsets;
}

vector<vector<int>> uniquePermutations;

void permuteUniqueUtil(int idx, vector<int>& permutation, 
    vector<bool>& isVisited, int n, vector<int>& nums) {
        if(idx == n) {
            uniquePermutations.push_back(permutation);
            return;
        }
        for(int i = 0; i < n; i++) {
            if(i > 0 and nums[i] == nums[i - 1] and !isVisited[i - 1] or isVisited[i]) {
                continue;
            }
            permutation.push_back(nums[i]);
            isVisited[i] = true;
            permuteUniqueUtil(idx + 1, permutation, isVisited, n, nums);
            isVisited[i] = false;
            permutation.pop_back();
        }
}

vector<vector<int>> permuteUnique(vector<int>& nums) {
    int n = nums.size();
    vector<int> permutation;
    vector<bool> isVisited(n);
    sort(nums.begin(), nums.end());
    permuteUniqueUtil(0, permutation, isVisited, n, nums);
    return uniquePermutations;
}

bool predictTheWinnerUtil(int start, int end, vector<int>& nums, int turn, vector<int>& playerScore) {
    if(start > end) {
        return playerScore[0] >= playerScore[1];
    }
    playerScore[turn] += nums[start];
    if(predictTheWinnerUtil(start + 1, end, nums, turn ^ 1, playerScore)) {
        return true;
    };
    playerScore[turn] -= nums[start];
    playerScore[turn] += nums[end];
    if(predictTheWinnerUtil(start, end - 1, nums, turn ^ 1, playerScore)) {
        return true;
    };
    playerScore[turn] -= nums[end];
    return false;
}

bool predictTheWinner(vector<int>& nums) {
    vector<int> playerScore(2);
    return predictTheWinnerUtil(0, nums.size() - 1, nums, 0, playerScore);
}

int main() {
    vector<int> nums = {1,5,233,7};
    predictTheWinner(nums) ? cout << "true" : cout << "false";
    return 0;
}