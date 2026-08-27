#include<bits/stdc++.h>
using namespace std;

vector<int> buildArray(vector<int>& nums) {
    vector<int> ans;
    for(int i = 0;i < nums.size();i++) {
        ans.push_back(nums[nums[i]]);
    }
    return ans;
}

int minimumOperations(vector<int>& nums) {
    int minOps = 0;
    for(int i = 0;i < nums.size();i++) {
        minOps += min(nums[i] % 3, 3 - nums[i] % 3);
    }
    return minOps;
}

vector<int> recoverOrder(vector<int>& order, vector<int>& friends) {
    vector<int> ans;
    set<int> st;
    for(auto it : friends) {
        st.insert(it);
    }
    for(auto it : order) {
        if(st.find(it) != st.end()) {
            ans.push_back(it);
        }
    }
    return ans;
}

vector<int> getConcatenation(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(2*n);
    for(int i = 0;i < 2*n;i++) {
        ans[i] = nums[i % n];
    }
    return ans;
}

map<string, int> lookup = {{"X++", 1}, {"++X", 2}, {"X--", 3}, {"--X", 4}};

int finalValueAfterOperations(vector<string>& operations) {
    int ans = 0;
    for(auto it : operations) {
        if(lookup[it] == 1 or lookup[it] == 2) {
            ans += 1;
        } else {
            ans -= 1;
        }
    }
    return ans;
}

vector<int> findWordsContaining(vector<string>& words, char x) {
    int n = words.size();
    vector<int> ans;
    for(int i = 0;i < n;i++) {
        for(auto it : words[i]) {
            if(it == x) {
                ans.push_back(i);
                break;
            } 
        }
    }
    return ans;
}

vector<int> minOperationsBrute(string boxes) {
    int n = boxes.length();
    vector<int> pos;
    for(int i = 0;i < n;i++) {
        if(boxes[i] == '1') {
            pos.push_back(i);
        }
    }
    vector<int> ans(n);
    for(int i = 0;i < n;i++) {
        for(auto it : pos) {
            ans[i] += abs(it - i);
        }
    }
    return ans;
}

vector<int> minOperationsBetter(string boxes) {
    int n = boxes.length();
    vector<int> left(n), right(n), ans(n);
    for(int i = 0;i < n;i++) {
        if(boxes[i] == '1') {
            ans[0] += i;
        }
    }
    for(int i = 0;i < n - 1;i++) {
        left[i + 1] = left[i];
        if(boxes[i] == '1') {
            left[i + 1] += 1;
        }
    }
    if(boxes[n - 1] == '1') {
        right[n - 1] = 1;
    }
    for(int i = n - 2;i >= 0;i--) {
        right[i] = right[i + 1];
        if(boxes[i] == '1') {
            right[i] += 1;
        }
    }
    for(int i = 1;i < n;i++) {
        ans[i] = ans[i - 1] - right[i] + left[i];
    }
    return ans;
}

vector<int> minOperationsOptimal(string boxes) {
    int n = boxes.length();
    vector<int> ans(n);
    int l = 0, r = 0;
    for(int i = 0;i < n;i++) {
        if(boxes[i] == '1') {
            r++;
            ans[0] += i;
        }
    }
    for(int i = 1;i < n;i++) {
        l += boxes[i - 1] - '0';
        r -= boxes[i - 1] - '0';
        ans[i] = ans[i - 1] - r + l;
    }
    return ans;
}

void subsets(int idx, vector<int>& ds, vector<int>& nums, int n, int& ans) {
    if(idx == n) {
        int xorr = 0;
        for(auto it : ds) {
            xorr ^= it;
        }
        ans += xorr;
        return;
    }
    ds.push_back(nums[idx]);
    subsets(idx + 1, ds, nums, n, ans);
    ds.pop_back();
    subsets(idx + 1, ds, nums, n, ans);
}

int subsetXORSum(vector<int>& nums) {
    int n = nums.size();
    int ans = 0;
    vector<int> ds;
    subsets(0, ds, nums, n, ans);
    return ans;
}

vector<int> getSneakyNumbers(vector<int>& nums) {
    
}

int main() {
    vector<int> nums = {0,1,1,0};
    vector<int> ans = getSneakyNumbers(nums);
    for(auto it : ans) {
        cout << it << ' ';
    }
    return 0;
}