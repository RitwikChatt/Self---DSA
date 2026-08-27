#include<bits/stdc++.h>
using namespace std;

int getSum(int a, int b) {
    while(b) {
        int carry = (a & b) << 1;
        a ^= b;
        b = carry;
    }
    return a;
}

bool isPossibleForKokoToEatAllBananasInGivenHoursWithGivenSpeed(vector<int>& piles, int h, int eatingSpeed) {
    long long hoursTaken = 0;
    for(int pile : piles) {
        hoursTaken += ceil((double)pile / (double)eatingSpeed);
    }
    return hoursTaken <= h;
} 

int minEatingSpeed(vector<int>& piles, int h) {
    int minSpeed = 1, maxSpeed = piles[max_element(piles.begin(), piles.end()) - piles.begin()];
    int minEatingSpeed;
    while(minSpeed <= maxSpeed) {
        int speed = minSpeed + (maxSpeed - minSpeed) / 2;
        if(isPossibleForKokoToEatAllBananasInGivenHoursWithGivenSpeed(piles, h, speed)) {
            minEatingSpeed = speed;
            maxSpeed = speed - 1;
        } else {
            minSpeed = speed + 1;
        }
    }
    return minEatingSpeed;
}

map<char, string> digitToLetterMapping = {
                  {'2', "abc"}, {'3', "def"}, 
    {'4', "ghi"}, {'5', "jkl"}, {'6', "mno"}, 
    {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}
};

vector<string> allPossibleLetterCombinations;

void letterCombinationsUtil(int idx, string s, string digits) {
    if(idx == digits.size()) {
        allPossibleLetterCombinations.push_back(s);
        return;
    }
    for(char ch : digitToLetterMapping[digits[idx]]) {
        s += ch;
        letterCombinationsUtil(idx + 1, s, digits);
        s.pop_back();
    }
}

vector<string> letterCombinations(string digits) {
    string s = "";
    letterCombinationsUtil(0, s, digits);
    return allPossibleLetterCombinations;
}

int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
    int n = boxTypes.size();
    sort(boxTypes.begin(), boxTypes.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[1] > b[1] or 
            (a[1] == b[1] and a[0] > b[0]);
    });
    int totalUnits = 0;
    for(int i = 0; i < n and truckSize > 0; i++) {
        int boxesToTake = min(boxTypes[i][0], truckSize);
        totalUnits += boxesToTake * boxTypes[i][1];
        truckSize -= boxesToTake;
    }
    return totalUnits;
}

int maxProfitAssignmentBrute(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
    int n = difficulty.size(), m = worker.size(), totalProfit = 0;
    for(int j = 0; j < m; j++) {
        int maxProfit = 0;
        for(int i = 0; i < n; i++) {
            if(difficulty[i] <= worker[j]) {
                maxProfit = max(maxProfit, profit[i]);
            }
        }
        totalProfit += maxProfit;
    }
    return totalProfit;
}

int maxProfitAssignmentOptimal(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
    int n = difficulty.size(), m = worker.size();
    vector<vector<int>> difficultyXProfitXMaxProfitTillNow(n);

    for(int i = 0; i < n; i++) {
        difficultyXProfitXMaxProfitTillNow[i] = {difficulty[i], profit[i], INT_MIN};
    }

    sort(difficultyXProfitXMaxProfitTillNow.begin(), difficultyXProfitXMaxProfitTillNow.end(), 
        [](vector<int>& a, vector<int>& b) {
            return a[0] < b[0] or 
            (a[0] == b[0] and a[1] < b[1]);
        }
    );

    for(int i = 0; i < n; i++) {
        difficultyXProfitXMaxProfitTillNow[i][2] = difficultyXProfitXMaxProfitTillNow[i][1];
        if(i > 0) {
            difficultyXProfitXMaxProfitTillNow[i][2] = max(difficultyXProfitXMaxProfitTillNow[i][2], 
                difficultyXProfitXMaxProfitTillNow[i - 1][2]);
        }
    }

    int totalProfit = 0;

    for(int j = 0; j < m; j++) {
        int low = 0, high = n - 1, idx = -1;
        while(low <= high) {
            int mid = low + (high - low) / 2;
            if(difficultyXProfitXMaxProfitTillNow[mid][0] <= worker[j]) {
                idx = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        if(idx >= 0 and idx < n) {
            totalProfit += difficultyXProfitXMaxProfitTillNow[idx][2];
        }
    }

    return totalProfit;
}

int main() {
    vector<int> difficulty = {85,47,57}, profit = {24,66,99}, worker = {40,25,25};
    cout << maxProfitAssignmentOptimal(difficulty, profit, worker) << endl;
    return 0;
}