#include<bits/stdc++.h>
using namespace std;

int diagonalSum(vector<vector<int>>& mat) {
    int order = mat.size();
    int sum = 0;
    for(int i = 0;i < order;i++) {
        sum += mat[i][i] + mat[i][order - i - 1];
    }
    if(order & 1) {
        return sum - mat[order / 2][order / 2];
    }
    return sum;
}

int solve1(vector<int>& input, int k) {
    int n = input.size();
    int goodElements = 0;
    for(int i = 0;i < n;i++) {
        goodElements += (input[i] <= k);
    }
    int badElements = 0;
    for(int i = 0;i < goodElements;i++) {
        badElements += (input[i] > k);
    }
    int mini = INT_MAX;
    int start = 0;
    while(start + goodElements - 1 < n) {
        mini = min(mini, badElements);
        badElements -= (input[start] > k);
        if(start + goodElements < n) {
            badElements += (input[start + goodElements] > k);
        }
        start++;
    }
    return mini;
}

vector<int> sortfun(vector<int>& input) {
    int n = input.size();
    queue<int> pos, neg;
    for(auto it : input) {
        if(it >= 0) {
            pos.push(it);
        } else {
            neg.push(it);
        }
    }
    vector<int> res;
    while(!pos.empty() and !neg.empty()) {
        res.push_back(pos.front());
        pos.pop();
        res.push_back(neg.front());
        neg.pop();
    }
    while(!pos.empty()) {
        res.push_back(pos.front());
        pos.pop();
    }
    while(!neg.empty()) {
        res.push_back(neg.front());
        neg.pop();
    }
    return res;
}

int findGCD(vector<int>& nums) {
    int smallest = INT_MAX, largest = INT_MIN;
    for(auto it : nums) {
        smallest = min(smallest, it);
        largest = max(largest, it);
    }
    return __gcd(smallest, largest);
}

bool isSelfDividing(int num) {
    int temp = num;
    while(temp) {
        int lastDigit = temp % 10;
        if(lastDigit == 0 or num % lastDigit != 0) {
            return false;
        }
        temp /= 10;
    }
    return true;
}

vector<int> selfDividingNumbers(int left, int right) {
    vector<int> ans;
    for(int i = left;i <= right;i++) {
        if(isSelfDividing(i)) {
            ans.push_back(i);
        }
    }
    return ans;
}

int numIdenticalPairsBrute(vector<int>& nums) {
    int n = nums.size(), cnt = 0;
    for(int i = 0;i < n;i++) {
        for(int j = i + 1;j < n;j++) {
            if(nums[i] == nums[j]) {
                cnt++;
            }
        }
    }
    return cnt;
}

int numIdenticalPairsOptimal(vector<int>& nums) {
    int n = nums.size();
    map<int, int> freqTable;
    for(auto it : nums) {
        freqTable[it]++;
    }
    int identicalPairs = 0;
    for(auto it : freqTable) {
        identicalPairs += it.second * (it.second - 1) / 2;
    }
    return identicalPairs;
}

    bool leapYear(int year) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
            return true;
        return false;
    }

    string dayOfTheWeek(int day, int month, int year) {
        vector<string> daY = {"Sunday",   "Monday", "Tuesday", "Wednesday",
                              "Thursday", "Friday", "Saturday"};
        vector<int> daysOfMonth = {0,  31, 28, 31, 30, 31, 30,
                                   31, 31, 30, 31, 30, 31};
        if (leapYear(year)) {
            daysOfMonth[2] = 29; // Feb has 29 days if it is a leap year
        }
        int daysOfYear = 4; // 31st December 1970 is Thursday, so intialize as 4

        // Add the days of the previous years
        for (int i = 1971; i < year; i++) {
            if (leapYear(i)) {
                daysOfYear += 366;
            } else {
                daysOfYear += 365;
            }
        }
        // Add the days of the previous months
        for (int i = 1; i < month; i++) {
            daysOfYear += daysOfMonth[i];
        }
        daysOfYear += day;          // Add the current day
        return daY[daysOfYear % 7]; // Modulo divide by 7 to find odd days
    }

int subtractProductAndSum(int n) {
    int sum = 0, prod = 1;
    while(n) {
        int lastDigit = n % 10;
        sum += lastDigit;
        prod *= lastDigit;
        n /= 10;
    }
    return prod - sum;
}

int numberOfMatches(int n) {
    int matches = 0;
    while(n != 1) {
        matches += n / 2;
        n -= n / 2;
    }
    return matches;
}

int findMaxConsecutiveOnes(vector<int>& nums) {
    int n = nums.size();
    int maxConsecutive = INT_MIN;
    int ones = 0;
    for(int i = 0;i < n;i++) {
        nums[i] ? ones++ : ones = 0;
        maxConsecutive = max(maxConsecutive, ones);
    }
    return maxConsecutive;
}

bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
    
}

int main() {
    vector<int> rec1 = {0,0,2,2}, rec2 = {1,1,3,3};
    isRectangleOverlap ? cout << "True" : cout << "False";
    return 0;
}