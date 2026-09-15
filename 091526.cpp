#include<bits/stdc++.h>
using namespace std;

int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
    int n = capital.size();

    vector<pair<int, int>> capitalToProfitMapping(n);

    for(int i = 0; i < n; i++) {
        capitalToProfitMapping[i] = {capital[i], profits[i]};
    }

    sort(capitalToProfitMapping.begin(), capitalToProfitMapping.end());

    priority_queue<int, vector<int>> pq;

    int i = 0, maximumCapital = 0;

    while(k--) {
        while(i < n and capitalToProfitMapping[i].first <= w) {
            pq.push(capitalToProfitMapping[i++].second);
        }

        if(!pq.empty()) {
            w += pq.top();
            pq.pop();
        }
    }

    return w;
}

class MedianFinder {
private:
    priority_queue<int, vector<int>> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;

public:
    MedianFinder() {}
    
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
        return this->maxHeap.size() == this->minHeap.size() ? (this->maxHeap.top() + this->minHeap.top()) / 2.0 : this->maxHeap.top();
    }
};

long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
    
}

int main() {
    vector<int> nums1 = {1,3,3,2}, nums2 = {2,1,3,4};
    int k = 3;

    cout << maxScore(nums1, nums2, k) << endl;
    return 0;
}