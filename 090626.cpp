#include<bits/stdc++.h>
using namespace std;

bool canComplete(int k, vector<int>& tasks, vector<int>& workers, int pills, int strength) {
    int n = tasks.size(), m = workers.size();

    multiset<int> ms;

    for(int i = n - k; i < n; i++) {
        ms.insert(workers[i]);
    }

    for(int i = k - 1; i >= 0; i--) {
        auto it = ms.lower_bound(tasks[i]);

        if(it != ms.end()) {
            ms.erase(it);
        } else {
            if(!pills) {
                return false;
            }

            it = ms.lower_bound(tasks[i] - strength);

            if(it == ms.end()) {
                return false;
            }

            ms.erase(it);
            pills--;
        }
    }

    return true;
}

int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
    int n = tasks.size(), m = workers.size();

    sort(tasks.begin(), tasks.end());
    sort(workers.begin(), workers.end());

    int low = 0, high = n, ans;

    while(low <= high) {
        int mid = low + (high - low) / 2;

        if(canComplete(mid, tasks, workers, pills, strength)) {
            ans = mid; 
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return ans;
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

void printLL(ListNode* head) {
    ListNode* ptr = head;

    while(ptr) {
        cout << ptr->val << ' ';
        ptr = ptr->next;
    }
}

ListNode* deleteMiddle(ListNode* head) {
    if(!head->next) {
        return NULL;
    }

    ListNode *slow = head, *fast = head, *prev;

    while(fast and fast->next) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    prev->next = slow->next;
    slow->next = NULL;
    delete(slow);

    return head;
}

ListNode* reverseLL(ListNode* head) {
    ListNode *curr = head, *next = head, *prev = NULL;

    while(curr) {
        next = next->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}

ListNode* reverseBetween(ListNode* head, int left, int right) {
    ListNode* l = head;

    while(l->val != left) {
        l = l->next;
    }

    ListNode* r = head;

    while(r->val != right) {
        r = r->next;
    }

    ListNode* prev = r;
    r = r->next;

    prev->next = NULL;

    ListNode *prevprev, *ptr = head;
    
    while(ptr != l) {
        prevprev = ptr;
        ptr = ptr->next;
    }

    prevprev->next = reverseLL(l);

    ptr = head;

    while(ptr->next) {
        ptr = ptr->next;
    }

    ptr->next = r;

    return head;
}

int main() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    int left = 2, right = 4;

    printLL(reverseBetween(head, left, right));
    return 0;
}