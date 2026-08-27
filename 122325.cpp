#include<bits/stdc++.h>
using namespace std;

int distributeCandies(vector<int>& candyType) {
    int n = candyType.size();
    unordered_set<int> distinctCandyTypes;
    for(auto candy : candyType) {
        distinctCandyTypes.insert(candy);
    }
    int distinctCandies = distinctCandyTypes.size();
    return min(distinctCandies, n / 2);
}

vector<int> findClosestElements(vector<int>& arr, int k, int x) {
    int minDistIdx = 0, n = arr.size();
    for(int i = 1;i < n;i++) {
        if(abs(arr[i] - x) < abs(arr[minDistIdx] - x)) {
            minDistIdx = i;
        }
    }
    int left = minDistIdx, right = minDistIdx;
    while(left >= 0 and right < n and right - left + 1 < k) {
        if(abs(arr[left] - x) <= abs(arr[right] - x)) {
            left--;
        } else {
            right++;
        }
    }

    while(right < n and right + 1 < k) {
        right++;
    }

    while(left >= 0 and n - left < k) {
        left--;
    }

    return vector<int>(arr.begin() + left, arr.begin() + right + 1);
}

string smallestGoodBase(string n) {
    
}

int main() {

    return 0;
}