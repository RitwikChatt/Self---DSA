#include<bits/stdc++.h>
using namespace std;

int maxPoints(vector<vector<int>>& points) {
    int n = points.size();
    int maxi = 0;
    for(int i = 0; i < n; i++) {
        map<double, int> slopeFrequencyMapping;
        for(int j = 0; j < n; j++) {
            if(i == j) {
                continue;
            }
            int x1 = points[i][0], y1 = points[i][1];
            int x2 = points[j][0], y2 = points[j][1];
            double slope;
            if(x2 != x1) {
                slope = double(y2 - y1) / double(x2 - x1);
            } else {
                slope = DBL_MAX;
            }
            slopeFrequencyMapping[slope]++;   
        }
        for(auto it : slopeFrequencyMapping) {
            maxi = max(maxi, it.second);
        }
    }
    return maxi + 1;
}

set<string> operators = {"+", "-", "*", "/"};

int evalRPN(vector<string>& tokens) {
    int n = tokens.size();
    stack<int> st;
    for(string it : tokens) {
        if(operators.find(it) == operators.end()) {
            st.push(stoi(it));
        } else {
            int ele2 = st.top();
            st.pop();
            int ele1 = st.top();
            st.pop();
            if(it == "+") {
                st.push(ele1 + ele2);
            } else if(it == "-") {
                st.push(ele1 - ele2);
            } else if(it == "*") {
                st.push(ele1 * ele2);
            } else {
                if(ele1) {
                    st.push(ele1 / ele2);
                } else {
                    st.push(0);
                }
            }
        }
    }
    return st.top();
}

vector<int> dailyTemperaturesBrute(vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> ans(n);
    for(int i = 0; i < n - 1; i++) {
        int j = i + 1;
        while(j < n and temperatures[j] <= temperatures[i]) {
            j++;
        }
        if(j < n) {
            ans[i] = j - i;
        }
    } 
    return ans;
}

vector<int> computeNGE(vector<int>& nums) {
    int n = nums.size();
    vector<int> nge(n, n);
    stack<int> st;
    for(int i = n - 1; i >= 0; i--) {
        while(!st.empty() and nums[st.top()] <= nums[i]) {
            st.pop();
        }
        if(!st.empty()) {
            nge[i] = st.top();
        }
        st.push(i);
    }
    return nge;
}

vector<int> dailyTemperaturesOptimal(vector<int>& temperatures) {
    int n = temperatures.size();
    stack<int> st;
    vector<int> nge, ans(n);
    nge = computeNGE(temperatures);
    for(int i = 0; i < n; i++) {
        if(nge[i] < n) {
            ans[i] = nge[i] - i;
        }
    }
    return ans;
}

int main() {
    
    return 0;
}