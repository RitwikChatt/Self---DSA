#include<bits/stdc++.h>
using namespace std;

class ListNode {
    public:
    int val;
    ListNode* next;
    ListNode(int val) {
        this->val = val;
        this->next = NULL;
    }
};

ListNode* createLinkedListFromArray(const vector<int>& nums) {
    ListNode* head = new ListNode(nums[0]);
    ListNode* node = head;
    for(int i = 1; i < nums.size(); i++) {
        node->next = new ListNode(nums[i]);
        node = node->next;
    }
    return head;
}

void printLinkedList(ListNode* head) {
    ListNode* node = head;
    while(node) {
        cout << node->val << ' ';
        node = node->next;
    }
}

ListNode* deleteDuplicates(ListNode* head) {
    ListNode* dummyNode = new ListNode(-1);
    dummyNode->next = head;
    ListNode* prev = dummyNode, *curr = head, *next = head;
    while(curr) {
        while(curr->next and curr->val == curr->next->val) {
            curr = curr->next;
        }
        next = curr->next;
        if(prev->next != curr) {
            ListNode* temp = prev->next;
            curr->next = NULL;
            curr = NULL;
            prev->next = next;
            while(temp) {
                ListNode* toBeDeleted = temp;
                temp = temp->next;
                toBeDeleted->next = NULL;
                delete(toBeDeleted);
            }
        }
        if(curr) {
            prev = curr;
        }
        curr = next;
    }
    head = dummyNode->next;
    dummyNode->next = NULL;
    delete(dummyNode);
    return head;
}

ListNode* partition(ListNode* head, int x) {
    ListNode *leftPart = new ListNode(-1), *rightPart = new ListNode(-1);
    ListNode *leftPtr = leftPart, *rightPtr = rightPart, *ptr = head;
    while(ptr) {
        if(ptr->val < x) {
            leftPtr->next = ptr;
            leftPtr = leftPtr->next;
        } else {
            rightPtr->next = ptr;
            rightPtr = rightPtr->next;
        }
        ptr = ptr->next;
    }
    rightPtr->next = NULL;
    leftPtr->next = rightPart->next;
    rightPart->next = NULL;
    delete(rightPart);
    head = leftPart->next;
    leftPart->next = NULL;
    delete(leftPart);
    return head;
}

vector<int> computeNSEDeprecated(vector<int>& nums) {
    int n = nums.size();
    vector<int> nse(n, 0);
    stack<int> st;
    for(int i = n - 1; i >= 0; i--) {
        while(!st.empty() and st.top() > nums[i]) {
            st.pop();
        }
        if(!st.empty()) {
            nse[i] = st.top();
        }
        st.push(nums[i]);
    }
    return nse;
}

vector<int> finalPrices(vector<int>& prices) {
    int n = prices.size();
    vector<int> nse = computeNSEDeprecated(prices);
    for(int i = 0; i < n; i++) {
        prices[i] -= nse[i];
    }
    return prices;
}

bool find132patternBrute(vector<int>& nums) {
    int n = nums.size();
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            for(int k = j + 1; k < n; k++) {
                if(nums[i] < nums[k] and nums[k] < nums[j]) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    vector<int> nums = {3,1,4,2};
    find132patternBrute(nums) ? cout << "true" : cout << "false";
    return 0;
}