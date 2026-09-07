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

void printLL(ListNode* head) {
    ListNode* ptr = head;

    while(ptr) {
        cout << ptr->val << ' ';
        ptr = ptr->next;
    }

    cout << endl;
}

pair<ListNode*, ListNode*> reverseLL(ListNode* head) {
    ListNode *curr = head, *prev = NULL, *next = head;

    while(curr) {
        next = next->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return {prev, head};
}

ListNode* reverseBetween(ListNode* head, int left, int right) {
    int count = 1;

    ListNode *ptr = head, *prev = NULL, *l = head, *r, *next;

    while(ptr) {
        if(count == left - 1) {
            prev = ptr;
            l = ptr->next;
        } else if(count == right) {
            r = ptr;
            next = ptr->next;
        }
        count++;
        ptr = ptr->next;
    }

    if(prev) {
        prev->next = NULL;
    }

    r->next = NULL;

    auto [newhead, newTail] = reverseLL(l);

    if(prev) {
        prev->next = newhead;
    } else {
        head = newhead;
    }

    if(newTail) {
        newTail->next = next;
    }

    return head;
}

class LRUCache {
private:
    int capacity;
    list<pair<int, int>> cache;
    unordered_map<int, list<pair<int, int>>::iterator> keyToListIteratorMapping;

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        if(this->keyToListIteratorMapping.find(key) == this->keyToListIteratorMapping.end()) {
            return -1;
        }

        auto it = keyToListIteratorMapping[key];

        this->cache.splice(this->cache.begin(), this->cache, it);

        return it->second;
    }
    
    void put(int key, int value) {
        if(this->keyToListIteratorMapping.find(key) != this->keyToListIteratorMapping.end()) {
            auto it = keyToListIteratorMapping[key];

            it->second = value;

            this->cache.splice(this->cache.begin(), this->cache, it);

            return;
        }

        if(this->cache.size() == this->capacity) {
            int lruKey = this->cache.back().first;

            this->cache.pop_back();

            this->keyToListIteratorMapping.erase(lruKey);
        }

        this->cache.push_front({key, value});
        this->keyToListIteratorMapping[key] = this->cache.begin();
    }
};

int minFlips(int a, int b, int c) {
    int flips = 0;

    while(a or b or c) {
        int bitA = a & 1, bitB = b & 1, bitC = c & 1;

        if(bitC) {
            if(!bitA and !bitB) {
                flips++;
            }
        } else {
            if(bitA) {
                flips++;
            }

            if(bitB) {
                flips++;
            }
        }

        a >>= 1, b >>= 1, c >>= 1;
    }

    return flips;
}

string addBinary(string a, string b) {
    string result;

    int i = a.length() - 1, j = b.length() - 1, carry = 0;

    while(i >= 0 or j >= 0 or carry) {
        int sum = carry;

        if(i >= 0) {
            sum += a[i--] - '0';
        }

        if(j >= 0) {
            sum += b[j--] - '0';
        }

        result.push_back((sum % 2) + '0');
        carry = sum / 2;
    }

    reverse(result.begin(), result.end());

    return result;
}

int countGoodNumbers(long long n) {
    
}

int main() {
    cout << countGoodNumbers(50) << endl;

    return 0;
}