#include<bits/stdc++.h>
using namespace std;

int minimumNumberOfPlatforms(vector<int>& arr, vector<int>& dep) {
    sort(arr.begin(), arr.end());
    sort(dep.begin(), dep.end());

    int platforms = 1, maxPlatforms = 1;
    int i = 1, j = 0;

    int n = arr.size();

    while(i < n) {

        if(arr[i] <= dep[j]) {
            platforms++, i++;
        } else {
            platforms--, j++;
        }

        maxPlatforms = max(maxPlatforms, platforms);
    }

    return maxPlatforms;
}

int largestSumAfterKNegations(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<>> pq;

    for(int num : nums) {
        pq.push(num);
    }

    while(k--) {
        int topEle = pq.top();
        pq.pop();

        topEle *= -1;

        pq.push(topEle);
    }

    int sum = 0;

    while(!pq.empty()) {
        sum += pq.top();
        pq.pop();
    }

    return sum;
}

int miceToHole(vector<int>& mices, vector<int>& holes) {
    sort(mices.begin(), mices.end());
    sort(holes.begin(), holes.end());

    int n = mices.size();
    int minTime = 0;

    for(int i = 0; i < n; i++) {
        minTime = max(minTime, abs(holes[i] - mices[i]));
    }

    return minTime;
}

int maximumProduct(vector<int>& nums) {
    int n = nums.size();

    sort(nums.begin(), nums.end());

    return max(nums[n - 3] * nums[n - 2] * nums[n - 1], nums[0] * nums[1] * nums[n - 1]);
}

int bulbSwitchBrute(int n) {
    vector<string> bulbState(n + 1, "OFF");

    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j += i) {
            bulbState[j] = (bulbState[j] == "OFF") ? "ON" : "OFF";
        }
    }

    int bulbsSwitchedON = 0;

    for(string state : bulbState) {
        bulbsSwitchedON += (state == "ON");
    }

    return bulbsSwitchedON;
}

int bulbSwitchBetter(int n) {
    vector<string> bulbState(n + 1, "OFF");

    for(int i = 1; i <= n; i++) {
        int num = i, squareRoot = sqrt(num);
        bulbState[i] = (squareRoot * squareRoot == num) ? "ON" : "OFF";
    }

    int bulbsSwitchedON = 0;

    for(string state : bulbState) {
        bulbsSwitchedON += (state == "ON");
    }

    return bulbsSwitchedON;
}

int bulbSwitchBest(int n) {
    int bulbsSwitchedON = 0;

    for(int i = 1; i <= n; i++) {
        int bulb = i, squareRoot = sqrt(bulb);
        bulbsSwitchedON += (squareRoot * squareRoot == bulb);
    }

    return bulbsSwitchedON;
}

int bulbSwitchOptimal(int n) {
    return sqrt(n);
}

int minPartitions(string n) {
    int maxi = 0;

    for(auto it : n) {
        maxi = max(maxi, it - '0');
    }

    return maxi;
}

vector<vector<int>> groupThePeople(vector<int>& groupSizes) {
    int n = groupSizes.size();

    vector<pair<int, int>> personIDGroupSizeMapping;

    for(int i = 0; i < n; i++) {
        personIDGroupSizeMapping.push_back({groupSizes[i], i});
    }

    sort(personIDGroupSizeMapping.begin(), personIDGroupSizeMapping.end(), 
    [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.first < b.first or a.first == b.first and a.second < b.second;
    });

    int i = 0; 
    vector<vector<int>> groups;

    while(i < n) {
        vector<int> group;
        int limit = i + personIDGroupSizeMapping[i].first;

        while(i < limit) {
            group.push_back(personIDGroupSizeMapping[i].second);
            i++;
        }

        groups.push_back(group);
    }

    return groups;
}

int balancedStringSplit(string s) {
    int countL = 0, countR = 0;
    int maxSubstrings = 0;

    for(auto ch : s) {
        ch == 'L' ? countL++ : countR++;
        if(countL == countR) {
            maxSubstrings++;
            countL = countR = 0;
        }
    }

    return maxSubstrings;
}

int minMovesToSeat(vector<int>& seats, vector<int>& students) {
    int n = seats.size();

    sort(seats.begin(), seats.end());
    sort(students.begin(), students.end());

    int minMoves = 0;

    for(int i = 0; i < n; i++) {
        minMoves += abs(students[i] - seats[i]);
    }

    return minMoves;
}

int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
    int n = grid.size();

    vector<int> rowMax(n, INT_MIN), colMax(n, INT_MIN);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            rowMax[i] = max(rowMax[i], grid[i][j]);
            colMax[j] = max(colMax[j], grid[i][j]);
        }
    }

    int total = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            total += min(rowMax[i], colMax[j]) - grid[i][j];
        }
    } 

    return total;
}

class TreeNode {
    public:
    int val;
    TreeNode *left, *right;

    TreeNode(int val) {
        this->val = val;
        this->left = this->right = NULL;
    }

};

void inorderTraversalUtil(TreeNode* root, vector<int>& inorder) {
    if(!root) {
        return;
    }

    inorderTraversalUtil(root->left, inorder);
    inorder.push_back(root->val);
    inorderTraversalUtil(root->right, inorder);

}

vector<int> inorderTraversal(TreeNode* root) {
    vector<int> inorder;
    inorderTraversalUtil(root, inorder);
    return inorder;
}

TreeNode* makeBSTFromInorderTraversal(vector<int>& inorder, int left, int right) {
    if(left > right) {
        return NULL;
    }

    int mid = left + (right - left) / 2;

    TreeNode* root = new TreeNode(inorder[mid]);

    root->left = makeBSTFromInorderTraversal(inorder, left, mid - 1);
    root->right = makeBSTFromInorderTraversal(inorder, mid + 1, right);

    return root;
}

TreeNode* balanceBST(TreeNode* root) {
    vector<int> inorder = inorderTraversal(root);
    int n = inorder.size();
    return makeBSTFromInorderTraversal(inorder, 0, n - 1);
}

int minimumSum(int num) {
    vector<int> digits;

    while(num) {
        digits.push_back(num % 10);
        num /= 10;
    }

    sort(digits.begin(), digits.end());

    return (10 * digits[0] + digits[2]) + (10 * digits[1] + digits[3]);
}

int main() {
    cout << minimumSum(2932) << endl;
    return 0;
}