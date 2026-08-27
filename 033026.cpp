#include<bits/stdc++.h>
using namespace std;

class KthLargest {

private:
    priority_queue<int, vector<int>, greater<>> pq;
    int k;

public:
    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        int n = nums.size();
        
        for(int i = 0; i < min(n, k); i++) {
            this->pq.push(nums[i]);
        }

        for(int i = k; i < n; i++) {
            if(nums[i] > this->pq.top()) {
                this->pq.pop();
                this->pq.push(nums[i]);
            }
        }

    }
    
    int add(int val) {
        this->pq.push(val);

        if(this->pq.size() > this->k) {
            this->pq.pop();
        }

        return this->pq.top();

    }
};

vector<int> solve(vector<int> input1, vector<int> input2) {
    int n = input1.size();

    vector<pair<int, int>> intervals;

    for(int i = 0; i < n; i++) {
        intervals.push_back({input1[i], input2[i]});
    }

    sort(intervals.begin(), intervals.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second or a.second == b.second and a.first > b.first;
    });

    vector<int> activities = {0};

    for(int i = 1; i < n; i++) {
        if(intervals[i].first > intervals[activities.back()].second) {
            activities.push_back(i);
        }
    }

    return activities;
}

int minimumNumberOfPlatforms(vector<int>& arr, vector<int>& dep) {
    
}

int main() {
    vector<int> input1 = {10, 12, 20}, input2 = {20, 25, 30};
    for(auto it : solve(input1, input2)) {
        cout << it << ' ';
    }
    return 0;
}