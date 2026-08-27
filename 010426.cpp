#include<bits/stdc++.h>
using namespace std;

void pi(int n) {
    if(!n) {
        return;
    }
    pi(n - 1);
    cout << n << endl;
}

void pd(int n) {
    if(!n) {
        return;
    }
    cout << n << endl;
    pd(n - 1);
}

void pdi(int n) {
    if(!n) {
        return;
    }
    cout << n << endl;
    pdi(n - 1);
    cout << n << endl;
}

int fact(int n) {
    return !n ? 1 : n * fact(n - 1);
}

int mult(int a, int b) {
    if(b > a) {
        return mult(b, a);
    }
    if(!b) {
        return 0;
    }
    return a + mult(a, b - 1);
}

int power(int a, int b) {
    return !b ? 1 : a * power(a, b - 1);
}

int powerLog(int a, int b) {
    if(!b) {
        return 1;
    }
    int hp = powerLog(a, b / 2);
    int ans = hp * hp;
    return b % 2 ? ans * a : ans;
}

void printPermutations(vector<int>& arr, unordered_set<int>& st) {
    if(st.size() == arr.size()) {
        for(auto it : st) {
            cout << it << ' ';
        }
        cout << endl;
        return;
    }
    for(auto it : arr) {
        if(st.find(it) == st.end()) {
            st.insert(it);
            printPermutations(arr, st);
            st.erase(it);
        }
    }
}

    vector<vector<int>> permutations;

    void permuteHelper(vector<int>& vec, vector<int>& nums) {
        if (vec.size() == nums.size()) {
            permutations.push_back(vec);
            return;
        }
        for (auto it : nums) {
            if (find(vec.begin(), vec.end(), it) == vec.end()) {
                vec.push_back(it);
                permuteHelper(vec, nums);
                vec.pop_back();
            }
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> vec;
        permuteHelper(vec, nums);
        return permutations;
    }

void permuteUniqueHelper(vector<int>& vec, vector<bool>& isVisited, vector<int>& nums) {
    if(vec.size() == nums.size()) {
        permutations.push_back(vec);
        return;
    }
    for(int i = 0; i < nums.size();i++) {
        if(isVisited[i] or i > 0 and nums[i] == nums[i - 1] and !isVisited[i - 1]) {
            continue;
        }
        isVisited[i] = true;
        vec.push_back(nums[i]);
        permuteUniqueHelper(vec, isVisited, nums);
        vec.pop_back();
        isVisited[i] = false;
    }
}

vector<vector<int>> permuteUnique(vector<int>& nums) {
    vector<int> vec;
    vector<bool> isVisited(nums.size());
    sort(nums.begin(), nums.end());
    permuteUniqueHelper(vec, isVisited, nums);
    return permutations;
}

int main() {
    vector<int> nums = {1,1,2};
    vector<vector<int>> ans = permuteUnique(nums);
    for(auto x : ans) {
        for(auto y : x) {
            cout << y << ' ';
        }
        cout << endl;
    }
    return 0;
}