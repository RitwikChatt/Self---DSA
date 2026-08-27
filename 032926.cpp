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
}

int findKthLargest(vector<int>& nums, int k) {
    int n = nums.size();
    priority_queue<int, vector<int>, greater<>> pq;

    for(int i = 0; i < k; i++) {
        pq.push(nums[i]);
    }

    for(int i = k; i < n; i++) {
        if(pq.top() < nums[i]) {
            pq.pop();
            pq.push(nums[i]);
        }
    }

    return pq.top();
}

ListNode* mergeKLists(const vector<ListNode*>& lists) {
    struct comp {
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val;
        }
    };

    priority_queue<ListNode*, vector<ListNode*>, comp> pq;

    for(auto head : lists) {
        pq.push(head);
    }

    ListNode* dummyNode = new ListNode(-1);
    ListNode* node = dummyNode;

    while(!pq.empty()) {
        ListNode* frontNode = pq.top();
        pq.pop();

        if(frontNode->next) {
            pq.push(frontNode->next);
        }

        node->next = frontNode;
        node = node->next;
    }

    if(!dummyNode->next) {
        return NULL;
    }

    ListNode* head = dummyNode->next;
    delete(dummyNode);

    return head;

}

int largestSumAfterKNegations(const vector<int>& nums, int k) {
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

class MedianFinder {
    
private:
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<>> minHeap;

public:
    MedianFinder() {

    }
    
    void addNum(int num) {
        this->maxHeap.push(num);

        this->minHeap.push(this->maxHeap.top());
        this->maxHeap.pop();

        if(this->maxHeap.size() < this->minHeap.size()) {
            this->maxHeap.push(this->minHeap.top());
            this->minHeap.pop();
        }

    }
    
    double findMedian() {
        return this->maxHeap.size() == this->minHeap.size() ? 
        (this->maxHeap.top() + this->minHeap.top()) / 2.0 : (double)this->maxHeap.top();
    }
};

int main() {

    return 0;
}