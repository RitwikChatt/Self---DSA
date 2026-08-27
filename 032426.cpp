#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> kSmallestPairsBrute(vector<int>& nums1, vector<int>& nums2, int k) {
    vector<vector<int>> pairs;

    for(int i = 0; i < nums1.size(); i++) {
        for(int j = 0; j < nums2.size(); j++) {
            pairs.push_back({nums1[i], nums2[j]});
        }
    }

    sort(pairs.begin(), pairs.end(), [](vector<int>& a, vector<int>& b) {
        return a[0] + a[1] < b[0] + b[1];
    });

    return {pairs.begin(), pairs.begin() + k};
    
}

vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
    int n = nums1.size(), m = nums2.size();
    vector<vector<int>> pairs;
    
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;

    for(int i = 0; i < n and pq.size() <= k; i++) {
        pq.push({nums1[i] + nums2[0], i, 0});
    }

    while(k-- and !pq.empty()) {
        auto [sum, i, j] = pq.top();
        pq.pop();

        pairs.push_back({nums1[i], nums2[j]});

        if(j + 1 < m) {
            pq.push({nums1[i] + nums2[j + 1], i, j + 1});
        }
    }

    return pairs;

}

class ListNode {
    public:
    int val;
    ListNode* next;

    ListNode(int val) {
        this->val = val;
        this->next = NULL;
    }

};

ListNode* createLL(const vector<int>& nums) {
    ListNode* head = new ListNode(nums[0]);
    ListNode* node = head;

    for(int i = 1; i < nums.size(); i++) {
        node->next = new ListNode(nums[i]);
        node = node->next;
    }

    return head;

}

void printLL(ListNode* head) {
    ListNode* node = head;

    while(node) {
        cout << node->val << ' ';
        node = node->next;
    }

    cout << endl;

}

ListNode* mergeKLists(vector<ListNode*>& lists) {
    ListNode* dummyNode = new ListNode(-1);
    ListNode* node = dummyNode;

    struct comp {
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val;
        }
    };

    priority_queue<ListNode*, vector<ListNode*>, comp> pq;

    for(ListNode* head : lists) {
        if(head) {
            pq.push(head);
        }
    }

    while(!pq.empty()) {
        ListNode* topNode = pq.top();
        pq.pop();

        if(topNode->next) {
            pq.push(topNode->next);
        }

        node->next = topNode;
        node = node->next;
    }

    ListNode* head = dummyNode->next;
    delete(dummyNode);

    return head;
}

int largestSumAfterKNegationsBrute(vector<int>& nums, int k) {
    while(k--) {
        sort(nums.begin(), nums.end());
        nums[0] *= -1;
    }

    int ans = 0;

    for(int num : nums) {
        ans += num;
    }

    return ans;
}

int largestSumAfterKNegationsBetter(vector<int>& nums, int k) {
    int n = nums.size();

    while(k--) {
        int min = INT_MAX, minIdx;
        for(int i = 0; i < n; i++) {
            if(nums[i] < min) {
                min = nums[i];
                minIdx = i;
            }
        }
        nums[minIdx] *= -1;
    }

    int ans = 0;

    for(int num : nums) {
        ans += num;
    }

    return ans;
}

int largestSumAfterKNegationsOptimal(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<>> pq;

    for(auto num : nums) {
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

vector<vector<int>> kClosestBrute(vector<vector<int>>& points, int k) {
    sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[0] * a[0] + a[1] * a[1] < b[0] * b[0] + b[1] * b[1];
    });

    return {points.begin(), points.begin() + k};
}

vector<vector<int>> kClosestOptimal(vector<vector<int>>& points, int k) {
    int n = points.size();

    struct comp {
        bool operator()(vector<int>& a, vector<int>& b) {
            return a[0] * a[0] + a[1] * a[1] < b[0] * b[0] + b[1] * b[1];
        }
    };

    priority_queue<vector<int>, vector<vector<int>>, comp> pq;

    for(int i = 0; i < k; i++) {
        pq.push(points[i]);
    }

    for(int i = k; i < n; i++) {
        vector<int> topPoint = pq.top();
        if(points[i][0] * points[i][0] + points[i][1] * points[i][1] < 
            topPoint[0] * topPoint[0] + topPoint[1] * topPoint[1]) {
            pq.pop();
            pq.push(points[i]);
        }
    }

    vector<vector<int>> closestPoints;

    while(!pq.empty()) {
        closestPoints.push_back(pq.top());
        pq.pop();
    }

    return closestPoints;

}

int kthSmallestBrute(vector<vector<int>>& mat, int k) {
    int n = mat.size();
    vector<int> possibleSums;

    function<void(int, int)> generateAllSums = [&](int index, int sum) {
        if(index == n) {
            possibleSums.push_back(sum);
            return;
        }

        for(int num : mat[index]) {
            generateAllSums(index + 1, sum + num);
        }

    };

    generateAllSums(0, 0);
    
    sort(possibleSums.begin(), possibleSums.end());
    
    return possibleSums[k - 1];
}

int kthSmallestOptimal(vector<vector<int>>& mat, int k) {
    int n = mat.size();
    vector<int> smallestSums = mat[0];

    auto findKSmallestSums = [](vector<int>& a, vector<int>& b, int k) -> vector<int> {
        int n = a.size(), m = b.size();
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;

        for(int i = 0; i < min(n, k); i++) {
            pq.push({a[i] + b[0], i, 0});
        }

        vector<int> kSmallestSums;

        while(k-- and !pq.empty()) {
            auto [sum, i, j] = pq.top();
            pq.pop();

            kSmallestSums.push_back(sum);

            if(j + 1 < m) {
                pq.push({a[i] + b[j + 1], i, j + 1});
            }
        }

        return kSmallestSums;

    };

    for(int i = 1; i < n; i++) {
        smallestSums = findKSmallestSums(smallestSums, mat[i], k);
    }

    return smallestSums[k - 1];

}

int lastStoneWeight(vector<int>& stones) {
    priority_queue<int> pq;

    for(int stone : stones) {
        pq.push(stone);
    }

    while(pq.size() > 1) {
        int y = pq.top();
        pq.pop();
        int x = pq.top();
        pq.pop();

        int diff = y - x;

        if(diff) {
            pq.push(diff);
        }

    }

    return pq.empty() ? 0 : pq.top();

}

int main() {
    
    return 0;
}