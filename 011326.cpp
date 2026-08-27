#include<bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;

bool judgePoint24Util(vector<double>& nums) {
    if(nums.size() == 1) {
        return fabs(nums[0] - 24.0) < EPS;
    }
    for(int i = 0; i < nums.size(); i++) {
        for(int j = 0; j < nums.size(); j++) {
            if(i == j) {
                continue;
            }
            vector<double> next;
            for(int k = 0; k < nums.size(); k++) {
                if(k != i and k != j) {
                    next.push_back(nums[k]);
                }
            }
            double a = nums[i], b = nums[j];
            vector<double> operations = {a + b, a - b, b - a, a * b};
            if(fabs(b) > EPS) {
                operations.push_back(a / b);
            }
            if(fabs(a) > EPS) {
                operations.push_back(b / a);
            }
            for(auto it : operations) {
                next.push_back(it);
                if(judgePoint24Util(next)) {
                    return true;
                }
                next.pop_back();
            }
        }
    }
    return false;
}

bool judgePoint24(vector<int>& cards) {
    vector<double> nums(cards.begin(), cards.end());
    return judgePoint24Util(nums);
}

vector<vector<int>> possibleCombinations;

void combineUtil(int idx, int lastUsed, vector<int>& ds, int n, int k) {
    if(idx == k) {
        possibleCombinations.push_back(ds);
        return;
    }
    for(int i = lastUsed + 1; i <= n; i++) {
        ds.push_back(i);
        combineUtil(idx + 1, i, ds, n, k);
        ds.pop_back();
    }
}

vector<vector<int>> combine(int n, int k) {
    vector<int> ds;
    combineUtil(0, 0, ds, n, k);
    return possibleCombinations;
}

vector<int> grayCode(int n) {
    
}

int main() {
    int n = 2;
    for(auto it : grayCode(n)) {
        cout << it << ' ';
    }
    return 0;
}