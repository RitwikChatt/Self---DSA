#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
    priority_queue<
    tuple<int, int, int>, 
    vector<tuple<int, int, int>>
    > pq;

    for(int i = 0; i < k; i++) {
        int x = points[i][0], y = points[i][1], dist = x * x + y * y;
        pq.push({dist, x, y});
    }

    for(int i = k; i < points.size(); i++) {
        int x_ = points[i][0], y_ = points[i][1], dist_ = x_ * x_ + y_ * y_;
        
        auto [dist, x, y] = pq.top();
        
        if(dist_ < dist) {
            pq.pop();
            pq.push({dist_, x_, y_});
        }
    }

    vector<vector<int>> closestPoints;

    while(!pq.empty()) {
        auto [dist, x, y] = pq.top();
        pq.pop();

        closestPoints.push_back({x, y});
    }

    return closestPoints;
}

void sortColors(vector<int>& nums) {
    int n = nums.size();

    int low = 0, mid = 0, high = n - 1;

    while(mid <= high) {
        if(nums[mid] == 0) {
            swap(nums[low], nums[mid]);
            low++, mid++;
        } else if(nums[mid] == 1) {
            mid++;
        } else {
            swap(nums[mid], nums[high]);
            high--;
        }
    }
}

void wiggleSort(vector<int>& nums) {
    int n = nums.size();

    vector<int> sorted = nums;

    sort(sorted.begin(), sorted.end());

    int mid = (n - 1) / 2, high = n - 1;
    
    for(int i = 0; i < n; i++) {
        if(i % 2) {
            nums[i] = sorted[high--];
        } else {
            nums[i] = sorted[mid--];
        }
    }
}

vector<pair<int, int>> merge(vector<pair<int, int>>& a, vector<pair<int, int>>& b, vector<int>& counts) {
    vector<pair<int, int>> mergedArray;

    int i = 0, j = 0, m = a.size(), n = b.size();

    int count = 0;

    while(i < m and j < n) {
        if(a[i].first <= b[j].first) {
            counts[a[i].second] += count;
            mergedArray.push_back(a[i++]);
        } else {
            count++;
            mergedArray.push_back(b[j++]);
        }
    }

    while(i < m) {
        counts[a[i].second] += count;
        mergedArray.push_back(a[i++]);
    }

    while(j < n) {
        mergedArray.push_back(b[j++]);
    }

    return mergedArray;
}

vector<pair<int, int>> mergeSort(vector<pair<int, int>>& elementsAndIndices, vector<int>& counts, int start, int end) {
    if(start == end) {
        return vector<pair<int, int>>{elementsAndIndices[start]};
    }

    int mid = start + (end - start) / 2;

    vector<pair<int, int>> left = mergeSort(elementsAndIndices, counts, start, mid);
    vector<pair<int, int>> right = mergeSort(elementsAndIndices, counts, mid + 1, end);

    return merge(left, right, counts);
}

vector<int> countSmaller(vector<int>& nums) {
    int n = nums.size();

    vector<int> counts(n);

    vector<pair<int, int>> elementsAndIndices;

    for(int i = 0; i < n; i++) {
        elementsAndIndices.push_back({nums[i], i});
    }

    mergeSort(elementsAndIndices, counts, 0, n - 1);

    return counts;
}

vector<int> reversePairsUtilMerge(vector<int>& a, vector<int>& b) {
    int m = a.size(), n = b.size();

    int i = 0, j = 0;

    vector<int> mergedArray;

    while(i < m and j < n) {
        if(a[i] <= b[j]) {
            mergedArray.push_back(a[i++]);
        } else {
            mergedArray.push_back(b[j++]);
        }
    } 

    while(i < m) {
        mergedArray.push_back(a[i++]);
    }

    while(j < n) {
        mergedArray.push_back(b[j++]);
    }

    return mergedArray;
}

vector<int> reversePairsUtilMergeSort(vector<int>& nums, int start, int end, int& totalPairs) {
    if(start == end) {
        return vector<int>{nums[start]};
    }

    int mid = start + (end - start) / 2;

    vector<int> left = reversePairsUtilMergeSort(nums, start, mid, totalPairs);
    vector<int> right = reversePairsUtilMergeSort(nums, mid + 1, end, totalPairs);

    int i = 0, j = 0;

    while(i < mid - start + 1 and j < end - mid) {
        if(left[i] > 2 * right[j]) {
            totalPairs += mid - start - i + 1;
            j++;
        } else {
            i++;
        }
    }

    return reversePairsUtilMerge(left, right);
}

int reversePairs(vector<int>& nums) {
    int totalPairs = 0, n = nums.size();

    reversePairsUtilMergeSort(nums, 0, n - 1, totalPairs);

    return totalPairs;
}

void permuteUtil(int idx, vector<bool>& visited, vector<int>& permutation, vector<vector<int>>& permutations, vector<int>& nums) {
    if(idx == nums.size()) {
        permutations.push_back(permutation);
        return;
    }

    for(int i = 0; i < nums.size(); i++) {
        if(!visited[i]) {
            visited[i] = true;
            permutation.push_back(nums[i]);
            permuteUtil(idx + 1, visited, permutation, permutations, nums);
            visited[i] = false;
            permutation.pop_back();
        }
    }
}

vector<vector<int>> permute(vector<int>& nums) {
    int n = nums.size();

    vector<vector<int>> permutations;

    vector<bool> visited(n);

    vector<int> permutation;

    permuteUtil(0, visited, permutation, permutations, nums);

    return permutations;
}

void combinationSumUtil(int idx, int sum, vector<int>& combination, vector<vector<int>>& combinations, 
    vector<int>& candidates, int target) {
    if(sum == target) {
        combinations.push_back(combination);
        return;
    }

    if(sum > target) {
        return;
    }

    for(int i = idx; i < candidates.size(); i++) {
        combination.push_back(candidates[i]);
        combinationSumUtil(i, sum + candidates[i], combination, combinations, candidates, target);
        combination.pop_back();
    }
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    int n = candidates.size();

    vector<vector<int>> combinations;

    vector<int> combination;

    combinationSumUtil(0, 0, combination, combinations, candidates, target);

    return combinations;
}

vector<int> dr = {-1, 0, 1, 0}, dc = {0, 1, 0, -1};

bool existUtilDFS(int idx, int r, int c, vector<vector<bool>>& visited, 
    vector<vector<char>>& board, string word) {
    if(idx == word.length() - 1) {
        return true;
    }

    visited[r][c] = true;

    for(int i = 0; i < 4; i++) {
        int nr = r + dr[i], nc = c + dc[i];

        if(nr >= 0 and nr < board.size() and nc >= 0 and nc < board[0].size() 
            and !visited[nr][nc] and board[nr][nc] == word[idx + 1]) {
                if(existUtilDFS(idx + 1, nr, nc, visited, board, word)) {
                    return true;
                }
        }
    }

    visited[r][c] = false;
    return false;
}

bool exist(vector<vector<char>>& board, string word) {
    int m = board.size(), n = board[0].size();

    vector<vector<bool>> visited(m, vector<bool>(n));

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(board[i][j] == word[0]) {
                if(existUtilDFS(0, i, j, visited, board, word)) {
                    return true;
                }            
            }
        }
    }

    return false;
}

void combinationSum3Util(int idx, int last, int sum, vector<int>& combination, 
    vector<vector<int>>& combinations, int k, int n) {
    if(idx == k) {
        if(sum == n) {
            combinations.push_back(combination);
        }
        return;
    }

    if(sum > n) {
        return;
    }

    for(int i = last + 1; i <= 9; i++) {
        combination.push_back(i);
        combinationSum3Util(idx + 1, i, sum + i, combination, combinations, k, n);
        combination.pop_back();
    }
}

vector<vector<int>> combinationSum3(int k, int n) {
    vector<vector<int>> combinations;

    vector<int> combination;

    combinationSum3Util(0, 0, 0, combination, combinations, k, n);

    return combinations;
}

map<char, string> digitToLetterMapping = {
    {'2', "abc"}, {'3', "def"}, 
    {'4', "ghi"}, {'5', "jkl"}, {'6', "mno"}, 
    {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}
};

void letterCombinationUtil(int idx, string& combination, vector<string>& combinations, string digits) {
    if(idx == digits.length()) {
        combinations.push_back(combination);
        return;
    }

    for(auto ch : digitToLetterMapping[digits[idx]]) {
        combination.push_back(ch);
        letterCombinationUtil(idx + 1, combination, combinations, digits);
        combination.pop_back();
    }
}

vector<string> letterCombinations(string digits) {
    vector<string> combinations;
    
    string combination;

    letterCombinationUtil(0, combination, combinations, digits);

    return combinations;
}

char parseAnd(vector<char>& tf) {
    int ans = 1;

    for(int i = 0; i < tf.size(); i++) {
        int term = tf[i] == 'f' ? 0 : 1;
        ans &= term;
    }

    return ans ? 't' : 'f';
}

char parseOr(vector<char>& tf) {
    int ans = 0;

    for(int i = 0; i < tf.size(); i++) {
        int term = tf[i] == 'f' ? 0 : 1;
        ans |= term;
    }

    return ans ? 't' : 'f';
}

char parseNot(vector<char>& tf) {
    return tf[0] == 'f' ? 't' : 'f';
}

bool parseBoolExpr(string expression) {
    stack<char> st;

    unordered_set<char> important = {')', 't', 'f'}, 
    operators = {'&', '|', '!'};

    for(int i = expression.length() - 1; i >= 0; i--) {
        if(important.count(expression[i])) {

            st.push(expression[i]);

        } else if(operators.count(expression[i])) {

            vector<char> tf;

            while(st.top() != ')') {
                tf.push_back(st.top());
                st.pop();
            }

            st.pop();

            if(expression[i] == '&') {
                st.push(parseAnd(tf));
            } else if(expression[i] == '|') {
                st.push(parseOr(tf));
            } else {
                st.push(parseNot(tf));
            }

        }
    }

    return st.top() == 't' ? true : false;
}

int maxNiceDivisors(int primeFactors) {
    
}

int main() {
    cout << maxNiceDivisors(8) << endl;
    return 0;
}