#include<bits/stdc++.h>
using namespace std;

int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int n = gas.size();
    int total = 0, curr = 0, start = 0;
    for(int i = 0; i < n; i++) {
        int net = gas[i] - cost[i];
        total += net;
        curr += net;
        if(curr < 0) {
            curr = 0;
            start = i + 1;
        }
    }
    return total >= 0 ? start : -1;
}

vector<int> maxSlidingWindowBrute(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> res;
    for(int i = 0; i <= n - k; i++) {
        int winMax = INT_MIN;
        int j = i;
        while(j <= i + k - 1) {
            winMax = max(winMax, nums[j]);
            j++;
        }
        res.push_back(winMax);
    }
    return res;
}

vector<int> maxSlidingWindowOptimal(vector<int>& nums, int k) {
    int n = nums.size();
    deque<int> dq;
    vector<int> res;
    for(int i = 0; i < n; i++) {
        if(!dq.empty() and dq.front() <= i - k) {
            dq.pop_front();
        }
        while(!dq.empty() and nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
        if(i >= k - 1) {
            res.push_back(nums[dq.front()]);
        }
    }
    return res;
}

bool isValid(string s) {
    int n = s.length();
    stack<char> st;
    for(int i = 0; i < n; i++) {
        if(s[i] == '(') {
            st.push(s[i]);
        } else {
            if(st.empty()) {
                return false;
            }
            st.pop();
        }
    }
    return st.empty();
}

int longestValidParenthesesBrute(string s) {
    int n = s.length();
    int maxLen = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            if(isValid(s.substr(i, j - i + 1))) {
                maxLen = max(maxLen, j - i + 1);
            }
        }
    }
    return maxLen;
} 

int longestValidParenthesesBetter(string s) {
    int n = s.length();
    stack<int> st;
    st.push(-1);
    int maxLen = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == '(') {
            st.push(i);
        } else {
            st.pop();
            if(st.empty()) {
                st.push(i);
            } else {
                maxLen = max(maxLen, i - st.top());
            }
        }
    }
    return maxLen;
}

int longestValidParenthesesOptimal(string s) {
    int n = s.length();
    int left = 0, right = 0;
    int maxLen = 0;
    for(int i = 0; i < n; i++) {
        s[i] == '(' ? left++ : right++;
        if(right > left) {
            left = right = 0;
        } else if(right == left) {
            maxLen = max(maxLen, left + right);
        }
    }
    left = right = 0;
    for(int i = n - 1; i >= 0; i--) {
        s[i] == '(' ? left++ : right++;
        if(left > right) {
            left = right = 0;
        } else if(left == right) {
            maxLen = max(maxLen, left + right);
        }
    }
    return maxLen;
}

int main() {
    
    return 0;
}