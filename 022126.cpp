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

void printLinkedList(ListNode* head) {
    ListNode* node = head;
    while(node) {
        cout << node->val << ' ';
        node = node->next;
    }
}

ListNode* createLinkedList(const vector<int>& nums) {
    int n = nums.size();
    ListNode* head = new ListNode(nums[0]);
    ListNode* node = head;
    for(int i = 1; i < n; i++) {
        node->next = new ListNode(nums[i]);
        node = node->next;
    }
    return head;
}

void addValuesToLinkedList(ListNode* head, vector<int>& nums) {
    ListNode* node = head;
    while(node->next) {
        node = node->next;
    }
    for(int i = 0; i < nums.size(); i++) {
        node->next = new ListNode(nums[i]);
        node = node->next;
    }
}

ListNode* middleNode(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while(fast and fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode* ptr1 = list1;
    ListNode* ptr2 = list2;
    ListNode* dummyNode = new ListNode(-1);
    ListNode* node = dummyNode;
    while(ptr1 and ptr2) {
        if(ptr1->val <= ptr2->val) {
            node->next = ptr1;
            node = node->next;
            ptr1 = ptr1->next;
        } else {
            node->next = ptr2;
            node = node->next;
            ptr2 = ptr2->next;
        }
    }
    if(ptr1) {
        node->next = ptr1;
    }
    if(ptr2) {
        node->next = ptr2;
    }
    ListNode* head = dummyNode->next;
    dummyNode->next = NULL;
    delete(dummyNode);
    return head;
}

ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode* slow = head;
    ListNode* fast = head;
    while(n--) {
        fast = fast->next;
    }
    if(!fast) {
        ListNode* temp = head;
        head = head->next;
        temp->next = NULL;
        delete(temp);
        return head;
    }
    while(fast->next) {
        slow = slow->next;
        fast = fast->next;
    }
    ListNode* temp = slow->next;
    slow->next = slow->next->next;
    temp->next = NULL;
    delete(temp);
    return head;
}

int main() {
    return 0;
}