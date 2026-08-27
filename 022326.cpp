#include<bits/stdc++.h>
using namespace std;

class ListNode {
    public:
    int data;
    ListNode* next;

    ListNode(int data) {
        this->data = data;
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
        cout << node->data << ' ';
        node = node->next;
    }
    cout << endl;
}

ListNode* deleteGivenNode(ListNode* head, int n) {
    ListNode *toBeDeleted = head, *prev = NULL;
    if(n == 1) {
        head = head->next;
    }
    int cnt = 1;
    while(cnt < n) {
        prev = toBeDeleted;
        toBeDeleted = toBeDeleted->next;
        cnt++;
    }
    if(prev) {
        prev->next = toBeDeleted->next;
    }
    toBeDeleted->next = NULL;
    delete(toBeDeleted);
    return head;
}

ListNode* reverseList(ListNode* head) {
    ListNode *prev = NULL, *curr = head, *next = head;
    while(next) {
        next = next->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

bool isPalindrome(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while(fast->next and fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    slow->next = reverseList(slow->next);
    ListNode *ptr1 = head, *ptr2 = slow->next;
    while(ptr2) {
        if(ptr1->data != ptr2->data) {
            return false;
        }
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    return true;
}

ListNode* removeElements(ListNode* head, int val) {
    ListNode* dummyNode = new ListNode(-1);
    dummyNode->next = head;
    ListNode *prev = dummyNode, *curr = head;
    while(curr) {
        if(curr->data == val) {
            ListNode* toBeDeleted = curr;
            prev->next = curr->next;
            curr = curr->next;
            toBeDeleted->next = NULL;
            delete(toBeDeleted);
        } else {
            curr = curr->next;
            prev = prev->next;
        }
    }
    ListNode* toBeDeleted = dummyNode;
    head = dummyNode->next;
    dummyNode->next = NULL;
    delete(dummyNode);
    return head;
}

int getDecimalValue(ListNode* head) {
    int ans = 0;
    ListNode* node = head;
    while(node) {
        ans <<= 1;
        ans |= node->data;
        node = node->next;
    }
    return ans;
}

ListNode* reverseBetween(ListNode* head, int left, int right) {
    ListNode *leftPtr = head, *rightPtr = head;
    int leftBKP = left;
    while(left-- > 2) {
        leftPtr = leftPtr->next;
    }
    while(right-- > 1) {
        rightPtr = rightPtr->next;
    }
    ListNode* leftOverPart = rightPtr->next;
    rightPtr->next = NULL;
    if(leftBKP == 1) {
        head = reverseList(head);
    } else {
        leftPtr->next = reverseList(leftPtr->next);
    }
    ListNode* last = head;
    while(last->next) {
        last = last->next;
    }
    last->next = leftOverPart;
    return head;
}

ListNode* mergeTwoSortedLists(ListNode* head1, ListNode* head2) {
    ListNode* dummyNode = new ListNode(-1);
    ListNode *ptr = dummyNode, *ptr1 = head1, *ptr2 = head2;
    while(ptr1 and ptr2) {
        if(ptr1->data < ptr2->data) {
            ptr->next = ptr1;
            ptr = ptr->next;
            ptr1 = ptr1->next;
        } else {
            ptr->next = ptr2;
            ptr = ptr->next;
            ptr2 = ptr2->next;
        }
    }
    if(ptr1) {
        ptr->next = ptr1;
    }
    if(ptr2) {
        ptr->next = ptr2;
    }
    ListNode* head = dummyNode->next;
    dummyNode->next = NULL;
    delete(dummyNode);
    return head;
}

ListNode* sortList(ListNode* head) {
    if(!head or !head->next) {
        return head;
    }
    ListNode *slow = head, *fast = head;
    while(fast->next and fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode* rightHalf = sortList(slow->next);
    slow->next = NULL;
    ListNode* leftHalf = sortList(head);
    return mergeTwoSortedLists(leftHalf, rightHalf);
}

int noOfNodesInLinkedList(ListNode* head) {
    ListNode* node = head;
    int nodes = 0;
    while(node) {
        nodes++;
        node = node->next;
    }
    return nodes;
}

ListNode* reverseKGroup(ListNode* head, int k) {
    if(k > noOfNodesInLinkedList(head)) {
        return head;
    }
    ListNode* ptr = head;
    int count = 1;
    while(count < k) {
        ptr = ptr->next;
        count++;
    }
    ListNode* leftOver = ptr->next;
    ptr->next = NULL;
    head = reverseList(head);
    ListNode* last = head;
    while(last->next) {
        last = last->next;
    }
    last->next = reverseKGroup(leftOver, k);
    return head;
}

ListNode* deleteDuplicatesBrute(ListNode* head) {
    unordered_set<int> st;
    ListNode *prev = NULL, *curr = head;
    while(curr) {
        if(st.find(curr->data) != st.end()) {
            ListNode* toBeDeleted = curr;
            prev->next = curr->next;
            curr = curr->next;
            toBeDeleted->next = NULL;
            delete(toBeDeleted);
        } else {
            st.insert(curr->data);
            prev = curr;
            curr = curr->next;
        }
    }
    return head;
}

ListNode* deleteDuplicatesOptimal(ListNode* head) {
    ListNode* node = head;
    while(node->next) {
        if(node->data == node->next->data) {
            ListNode* toBeDeleted = node->next;
            node->next = node->next->next;
            toBeDeleted->next = NULL;
            delete(toBeDeleted);
        } else {
            node = node->next;
        }
    }
    return head;
}

ListNode* swapPairs(ListNode* head) {
    if(!head or !head->next) {
        return head;
    }
    ListNode* leftOverPart = head->next->next;
    head->next->next = NULL;
    head = reverseList(head);
    head->next->next = swapPairs(leftOverPart);
    return head;
}

int main() {
    
    return 0;
}