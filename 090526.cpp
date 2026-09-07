#include<bits/stdc++.h>
using namespace std;

int longestAwesome(string s) {
    int mask = 0, maxLen = INT_MIN;

    vector<int> first(1024, -2);
    first[mask] = -1;

    for(int i = 0; i < s.length(); i++) {
        int digit = s[i] - '0';

        mask ^= (1 << digit);

        if(first[mask] != -2) {
            maxLen = max(maxLen, i - first[mask]);
        }

        for(int d = 0; d < 10; d++) {
            int candidate = mask ^ (1 << d);

            if(first[candidate] != -2) {
                maxLen = max(maxLen, i - first[candidate]);
            }
        }

        if(first[mask] == -2) {
            first[mask] = i;
        }
    }

    return maxLen;
}

struct Node {
    int data;
    Node* left;
    Node* right;
    Node *random;
};

Node* cloneTree(Node* root) {
    if(!root) {
        return root;
    }

    unordered_map<Node*, Node*> originalXCloneMapping;

    queue<Node*> q;
    q.push(root);

    while(!q.empty()) {
        auto node = q.front();
        q.pop();

        originalXCloneMapping[node] = new Node();
        originalXCloneMapping[node]->data = node->data;

        if(node->left) {
            q.push(node->left);
        }

        if(node->right) {
            q.push(node->right);
        }
    }

    q.push(root);

    while(!q.empty()) {
        auto node = q.front();
        q.pop();

        Node* clone = originalXCloneMapping[node];

        clone->left = node->left ? originalXCloneMapping[node->left] : NULL;
        clone->right = node->right ? originalXCloneMapping[node->right] : NULL;
        clone->random = node->random ? originalXCloneMapping[node->random] : NULL;

        if(node->left) {
            q.push(node->left);
        }

        if(node->right) {
            q.push(node->right);
        }
    }

    return originalXCloneMapping[root];
}

bool hasTripletSumBetter(vector<int> &arr, int target) {
    int n = arr.size();

    sort(arr.begin(), arr.end());

    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            int low = j + 1, high = n - 1;

            while(low <= high) {
                int mid = low + (high - low) / 2;

                if(arr[mid] == target - arr[i] - arr[j]) {
                    return true;
                } else if(arr[mid] > target - arr[i] - arr[j]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
        }
    }

    return false;
}

bool hasTripletSumOptimal(vector<int> &arr, int target) {
    int n = arr.size();

    sort(arr.begin(), arr.end());

    for(int i = 0; i < n - 2; i++) {
        int j = i + 1, k = n - 1;

        while(j < k) {
            if(arr[j] + arr[k] == target - arr[i]) {
                return true;
            } else if(arr[j] + arr[k] < target - arr[i]) {
                j++;
            } else {
                k--;
            }
        }
    }

    return false;
}

void printCommonElements(vector<vector<int>>& mat) {
    int m = mat.size(), n = mat[0].size();

    unordered_map<int, int> freq;

    for(int j = 0; j < n; j++) {
        freq[mat[0][j]] = 1;
    }

    for(int i = 1; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(freq[mat[i][j]] == i) {
                freq[mat[i][j]]++;
            }

            if(freq[mat[i][j]] == m) {
                cout << mat[i][j] << ' ';
            }
        }
    }
}

bool isValid(string s) {
    unordered_set<char> openingBraces = {'(', '[', '{'};

    unordered_map<char, char> closingToOpeningBraceMapping = {
        {')', '('}, {']', '['}, {'}', '{'}
    };

    int n = s.length();

    stack<char> st;

    for(int i = 0; i < n; i++) {
        if(openingBraces.count(s[i])) {
            st.push(s[i]);
        } else {
            if (st.empty() or st.top() != closingToOpeningBraceMapping[s[i]]) {
                return false;
            }
            st.pop();
        }
    }

    return true;
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

void printLL(ListNode* root) {
    ListNode* node = root;

    while(node) {
        cout << node->val << ' ';
        node = node->next;
    }

    cout << endl;
}

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode* dummyNode = new ListNode(-1);

    ListNode *ptr1 = list1, *ptr2 = list2, *ptr = dummyNode;

    while(ptr1 and ptr2) {
        if(ptr1->val <= ptr2->val) {
            ptr->next = ptr1;
            ptr1 = ptr1->next;
        } else {
            ptr->next = ptr2;
            ptr2 = ptr2->next;
        }
        ptr = ptr->next;
    }

    if(ptr1) {
        ptr->next = ptr1;
    }

    if(ptr2) {
        ptr->next = ptr2;
    }

    ListNode* root = dummyNode->next;
    dummyNode->next = NULL;
    delete(dummyNode);

    return root;
}

ListNode* middleNode(ListNode* head) {
    ListNode *slow = head, *fast = head;

    while(fast and fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

ListNode* mergeKLists(vector<ListNode*>& lists) {
    priority_queue<
    pair<int, ListNode*>, 
    vector<pair<int, ListNode*>>,
    greater<pair<int, ListNode*>>
    > pq;

    for(auto list : lists) {
        if(list) {
            pq.push({list->val, list});
        }
    }

    ListNode* dummyNode = new ListNode(-1);
    ListNode* ptr = dummyNode;

    while(!pq.empty()) {
        auto node = pq.top().second;
        pq.pop();

        ptr->next = node;
        ptr = ptr->next;

        if(node->next) {
            pq.push({node->next->val, node->next});
        }
    }

    ListNode* newHead = dummyNode->next;
    dummyNode->next = NULL;
    delete(dummyNode);

    return newHead;
}

int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
    
}

int main() {
    vector<int> tasks = {3,2,1}, workers = {0,3,3};
    int pills = 1, strength = 1;

    cout << maxTaskAssign(tasks, workers, pills, strength) << endl;
    return 0;
}