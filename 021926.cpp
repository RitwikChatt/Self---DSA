#include<bits/stdc++.h>
using namespace std;

bool check(string s) {
    stack<char> st;
    for(char c : s) {
        bool operatorFound = true;
        if(c == ')') {
            operatorFound = false;
            while(!st.empty() and st.top() != '(') {
                if(st.top() == '+' or st.top() == '-' or 
                    st.top() == '*' or st.top() == '/') {
                        operatorFound = true;
                    }
                st.pop();
            }
            if(!st.empty() and st.top() == '(') {
                st.pop();
            }
        }
        if(!operatorFound) {
            return true;
        }
        if(c != ')') {
            st.push(c);
        }
    } 
    return false;
}

int largestRectangleAreaBrute(vector<int>& heights) {
    int n = heights.size();
    int largestArea = INT_MIN;
    for(int i = 0; i < n; i++) {
        int pse = i, nse = i;
        while(pse >= 0 and heights[pse] >= heights[i]) {
            pse--;
        }
        while(nse < n and heights[nse] >= heights[i]) {
            nse++;
        }
        largestArea = max(largestArea, heights[i] * (nse - pse - 1));
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
    int largestArea = INT_MIN;
    vector<int> pse, nse;
    pse = computePSE(heights);
    nse = computeNSE(heights);
    for(int i = 0; i < n; i++) {
        largestArea = max(largestArea, heights[i] * (nse[i] - pse[i] - 1));
    }
    return largestArea;
}

string removeDuplicateLetters(string s) {
    int n = s.length();
    stack<char> st;
    vector<int> lastOccurence(26);
    vector<bool> isVisited(26);
    for(int i = 0; i < n; i++) {
        lastOccurence[s[i] - 'a'] = i;
    }
    for(int i = 0; i < n; i++) {
        if(isVisited[s[i] - 'a']) {
            continue;
        }
        while(!st.empty() and st.top() > s[i] and lastOccurence[st.top() - 'a'] > i) {
            isVisited[st.top() - 'a'] = false;
            st.pop();
        }
        st.push(s[i]);
        isVisited[s[i] - 'a'] = true;
    }
    string res = "";
    while(!st.empty()) {
        res += st.top();
        st.pop();
    }
    reverse(res.begin(), res.end());
    return res;
}

int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    
}

int main() {
    vector<int> gas = {1,2,3,4,5}, cost = {3,4,5,1,2};
    cout << canCompleteCircuit(gas, cost) << endl;
    return 0;
}