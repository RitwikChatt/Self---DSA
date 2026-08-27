#include<bits/stdc++.h>
using namespace std;

int findPairsBrute(vector<int>& nums, int k) {
    int n = nums.size(), kDiffPairs = 0;

    set<vector<int>> st;
    
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            int diff = abs(nums[i] - nums[j]);
            vector<int> pair = {nums[i], nums[j]};
            sort(pair.begin(), pair.end());
            if(diff == k and st.find(pair) == st.end()) {
                kDiffPairs++;
                st.insert(pair);
            }
        }
    }

    return kDiffPairs;
}

int findPairsOptimal(vector<int>& nums, int k) {
    int n = nums.size();
    int l = 0, r = 1, count = 0;

    sort(nums.begin(), nums.end());

    while(r < n) {
        if(l == r) {
            r = l + 1;
            continue;
        }

        int diff = abs(nums[l] - nums[r]);

        if(diff == k) {
            count++;
            l++, r++;

            while(r < n and nums[r] == nums[r - 1]) {
                r++;
            }

        } else if(diff > k) {
            l++;
        } else {
            r++;
        }
    }
    
    return count;
}

int findMinDiff(vector<int>& a, vector<int>& b, vector<int>& c) {
    int n1 = a.size(), n2 = b.size(), n3 = c.size();
    int i = 0, j = 0, k = 0;

    int minDiff = INT_MAX;

    while(i < n1 and j < n2 and k < n3) {
        int maxi = max({a[i], b[j], c[k]}), mini = min({a[i], b[j], c[k]});
        minDiff = min(minDiff, maxi - mini);

        if(mini == a[i]) {
            i++;
        }

        if(mini == b[j]) {
            j++;
        }

        if(mini == c[k]) {
            k++;
        }

    }

    return minDiff;
}

int maxAreaOptimal(vector<int>& height) {
    int n = height.size();
    int l = 0, r = n - 1;
    int area = 0;

    while(l < r) {
        int width = r - l, hMin = min(height[l], height[r]);
        area = max(area, hMin * width);

        if(height[l] < height[r]) {
            l++;
        } else {
            r--;
        }
    }

    return area;
}

int maxAreaBrute(vector<int>& height) {
    int n = height.size(), area = INT_MIN;

    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            int width = j - i, hMin = min(height[i], height[j]);
            area = max(area, width * hMin);
        }
    }

    return area;
}

int triangleNumber(vector<int>& nums) {
    int n = nums.size(), count = 0;

    sort(nums.begin(), nums.end());

    for(int k = n - 1; k >= 2; k--) {
        int i = 0, j = k - 1;
        while(i < j) {
            if(nums[i] + nums[j] <= nums[k]) {
                i++;
            } else {
                count += (j - i);
                j--;
            }
        }
    }

    return count;
}

vector<int> findClosestElements(vector<int>& arr, int k, int x) {
    sort(arr.begin(), arr.end(), [&](const int& a, const int& b) {
        return abs(a - x) < abs(b - x) or abs(a - x) == abs(b - x) and a < b;
    });

    vector<int> ans(arr.begin(), arr.begin() + k);
    sort(ans.begin(), ans.end());

    return ans;
}

vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
    int n1 = nums1.size(), n2 = nums2.size();

    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;

    for(int i = 0; i < min(n1, k); i++) {
        pq.push({nums1[i] + nums2[0], i, 0});
    }

    vector<vector<int>> pairs;

    while(!pq.empty() and k--) {
        auto [sum, i, j] = pq.top();
        pq.pop();

        pairs.push_back({nums1[i], nums2[j]});

        if(j + 1 < n2) {
            pq.push({nums1[i] + nums2[j + 1], i, j + 1});
        }
    }

    return pairs;
}

int maxLength(vector<int>& nums) {
    int n = nums.size();
    unordered_map<int, int> prefixSumEndingFirstSeenMapping;
    int prefixSum = 0, maxLen = 0;

    prefixSumEndingFirstSeenMapping[prefixSum] = -1;

    for(int i = 0; i < n; i++) {
        prefixSum += nums[i];

        if(prefixSumEndingFirstSeenMapping.find(prefixSum) != prefixSumEndingFirstSeenMapping.end()) {
            maxLen = max(maxLen, i - prefixSumEndingFirstSeenMapping[prefixSum]);
        } else {
            prefixSumEndingFirstSeenMapping[prefixSum] = i;
        }
    }

    return maxLen;
}

int longestConsecutive(vector<int>& nums) {
    unordered_set<int> st{nums.begin(), nums.end()};

    int maxLen = 0;

    for(auto num : st) {
        if(st.find(num - 1) == st.end()) {
            int len = 1, start = num;

            while(st.find(start + 1) != st.end()) {
                len++;
                start++;
            }

            maxLen = max(maxLen, len);
        }
    }

    return maxLen;
}

int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> prefixSumFrequencyMapping;
    prefixSumFrequencyMapping[0] = 1;
    int prefixSum = 0, count = 0;

    for(auto num : nums) {
        prefixSum += num;
        count += prefixSumFrequencyMapping[prefixSum - k];
        prefixSumFrequencyMapping[prefixSum]++;
    }

    return count;
}

bool isAnagram(string s, string t) {
    unordered_map<char, int> characterFrequencyMapping;

    for(auto ch : s) {
        characterFrequencyMapping[ch]++;
    }

    for(char ch : t) {
        if(characterFrequencyMapping.find(ch) == characterFrequencyMapping.end()) {
            return false;
        }

        characterFrequencyMapping[ch]--;

        if(!characterFrequencyMapping[ch]) {
            characterFrequencyMapping.erase(ch);
        }
    }

    return characterFrequencyMapping.empty();
}

bool isRowValid(int i, int j, vector<string>& board) {
    for(int col = 0; col < 9; col++) {
        if(col == j) {
            continue;
        }
        if(board[i][col] == board[i][j]) {
            return false;
        }
    }
    return true;
}

bool isColumnValid(int i, int j, vector<string>& board) {
    for(int row = 0; row < 9; row++) {
        if(row == i) {
            continue;
        }
        if(board[row][j] == board[i][j]) {
            return false;
        }
    }
    return true;
}

bool isBoxValid(int i, int j, vector<string>& board) {
    for(int k = 0; k < 9; k++) {
        int row = 3 * (i / 3) + (k / 3), col = 3 * (j / 3) +(k % 3);

        if(row == i and col == j) {
            continue;
        }

        if(board[row][col] == board[i][j]) {
            return false;
        }
    }
    return true;
}

bool isValidSudoku(vector<string>& board) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(board[i][j] != '.') {
                if(!isRowValid(i, j, board) or !isColumnValid(i, j, board) or !isBoxValid(i, j, board)) {
                    return false;
                }
            }
        }
    }
    return true;
}

int lengthOfLongestSubstring(string s) {
    int n = s.length(), l = 0, maxLen = 0;
    unordered_set<char> st;

    for(int r = 0; r < n; r++) {
        while(st.find(s[r]) != st.end()) {
            st.erase(s[l]);
            l++;
        }

        st.insert(s[r]);
        maxLen = max(maxLen, r - l + 1);

    }

    return maxLen;
}

const set<string> OPERATORS = {"+", "-", "*", "/"};

int evalRPN(vector<string>& tokens) {
    stack<int> st;

    for(auto token : tokens) {
        if(!OPERATORS.count(token)) {
            st.push(stoi(token));
        } else {
            int second = st.top();
            st.pop();
            int first = st.top();
            st.pop();

            if(token == "+") {
                st.push(first + second);
            } else if(token == "-") {
                st.push(first - second);
            } else if(token == "*") {
                st.push(first * second);
            } else {
                st.push(first / second);
            }
        }
    }

    return st.top();
}

vector<int> computeNGE(vector<int>& nums) {
    int n = nums.size();
    vector<int> nge(n);

    for(int i = 0; i < n; i++) {
        nge[i] = i;
    }

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

vector<int> dailyTemperatures(vector<int>& temperatures) {
    int n = temperatures.size();

    vector<int> nge = computeNGE(temperatures);

    for(int i = 0; i < n; i++) {
        nge[i] -= i;
    }

    return nge;
}

void setZeroes(vector<vector<int>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();

    int firstRowZero = false, firstColZero = false;

    for(int j = 0; j < n; j++) {
        if(!matrix[0][j]) {
            firstRowZero = true;
            break;
        }
    }

    for(int i = 0; i < m; i++) {
        if(!matrix[i][0]) {
            firstColZero = true;
            break;
        }
    }

    for(int i = 1; i < m; i++) {
        for(int j = 1; j < n; j++) {
            if(!matrix[i][j]) {
                matrix[i][0] = 0, matrix[0][j] = 0;
            }
        }
    }

    for(int i = 1; i < m; i++) {
        for(int j = 1; j < n; j++) {
            if(!matrix[i][0] or !matrix[0][j]) {
                matrix[i][j] = 0;
            }
        }
    }

    if(firstRowZero) {
        for(int j = 0; j < n; j++) {
            matrix[0][j] = 0;
        }
    }

    if(firstColZero) {
        for(int i = 0; i < m; i++) {
            matrix[i][0] = 0;
        }
    }
}

int largestRectangleAreaBrute(vector<int>& heights) {
    int n = heights.size(), maxArea = 0;

    for(int i = 0; i < n; i++) {
        int l = i - 1, left = 0;

        while(l >= 0 and heights[l] >= heights[i]) {
            left++, l--;
        }

        int r = i + 1, right = 0;

        while(r < n and heights[r] >= heights[i]) {
            right++, r++;
        }

        maxArea = max(maxArea, heights[i] * (left + right + 1));
    }

    return maxArea;
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

    vector<int> nse = computeNSE(heights), pse = computePSE(heights);

    int maxArea = 0;

    for(int i = 0; i < n; i++) {
        maxArea = max(maxArea, heights[i] * (nse[i] - pse[i] - 1));
    }

    return maxArea;
}

string removeDuplicateLetters(string s) {
    
}

int main() {
    cout << removeDuplicateLetters("cbacdcbc") << endl;
    return 0;
}