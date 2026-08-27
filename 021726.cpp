#include<bits/stdc++.h>
using namespace std;

unordered_map<char, int> open = {{'(', 0}, {'{', 1}, {'[', 2}};
unordered_map<char, int> closed = {{')', 0}, {'}', 1}, {']', 2}};

bool isValid(string s) {
    stack<char> stk;
    for(char c : s) {
        if(open.find(c) != open.end()) {
            stk.push(c);
        } else {
            if(stk.empty()) {
                return false;
            }
            if(open[stk.top()] != closed[c]) {
                return false;
            }
            stk.pop();
        }
    }
    return stk.empty();    
}

vector<int> computeNGE(vector<int>& nums) {
    int n = nums.size();
    vector<int> nge(n, INT_MAX);
    stack<int> st;
    for(int i = n - 1; i >= 0; i--) {
        while(!st.empty() and st.top() <= nums[i]) {
            st.pop();
        }
        if(!st.empty()) {
            nge[i] = st.top();
        }
        st.push(nums[i]);
    }
    return nge;
}

int largestRectangleAreaBrute(vector<int>& heights) {
    int n = heights.size();
    int largestArea = INT_MIN;
    for(int i = 0; i < n; i++) {
        int left = 0, right = 0;
        int j = i - 1;
        while(j >= 0 and heights[j] >= heights[i]) {
            left++, j--;
        }
        j = i + 1;
        while(j < n and heights[j] >= heights[i]) {
            right++, j++;
        }
        largestArea = max(largestArea, heights[i] * (left + right + 1));
    }
    return largestArea;
}

vector<int> computeNSE(vector<int>& nums) {
    int n = nums.size();
    vector<int> nse(n, n);
    stack<int> st;
    for(int i = n - 1; i >= 0; i--) {
        while(!st.empty() and nums[st.top()] >= nums[i]) {
            st.pop();
        }
        if(!st.empty()) {
            nse[i] = st.top();
        }
        st.push(i);
    }
    return nse;
}

vector<int> computePSE(vector<int>& nums) {
    int n = nums.size();
    vector<int> pse(n, -1);
    stack<int> st;
    for(int i = 0; i < n; i++) {
        while(!st.empty() and nums[st.top()] >= nums[i]) {
            st.pop();
        }
        if(!st.empty()) {
            pse[i] = st.top();
        }
        st.push(i);
    }
    return pse;
}

int largestRectangleAreaOptimal(vector<int>& heights) {
    int n = heights.size();
    vector<int> nse, pse;
    nse = computeNSE(heights);
    pse = computePSE(heights);
    int largestArea = INT_MIN;
    for(int i = 0; i < n; i++) {
        largestArea = max(largestArea, heights[i] * (nse[i] - pse[i] - 1));
    }
    return largestArea;
}

int main() {
    vector<int> heights = {2,4};
    cout << largestRectangleAreaOptimal(heights) << endl;
    return 0;
}