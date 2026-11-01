#include<bits/stdc++.h>
using namespace std;

bool canCrossHelper(int stone, int lastJump, vector<int>& stones, vector<vector<int>>& dp, unordered_map<int, int>& index) {
    if(stone == stones.size() - 1) {
        return dp[stone][lastJump] = true;
    }

    if(dp[stone][lastJump] != -1) return dp[stone][lastJump];

    for(int jump = -1; jump <= 1; jump++) {
        if(lastJump + jump == 0) {
            continue;
        }

        int nextPosition = stones[stone] + lastJump + jump;

        if(index.find(nextPosition) == index.end()) {
            continue;
        }

        int nextStone = index[nextPosition];

        if(canCrossHelper(nextStone, lastJump + jump, stones, dp, index)) {
            return dp[stone][lastJump] = true;
        }
    }

    return dp[stone][lastJump] = false;
}

bool canCross(vector<int>& stones) {
    int n = stones.size();

    if(stones[1] != stones[0] + 1) {
        return false;
    }

    unordered_map<int, int> index;

    for(int i = 0; i < n; i++) index[stones[i]] = i;

    vector<vector<int>> dp(n, vector<int>(n + 1, -1));

    return canCrossHelper(1, 1, stones, dp, index);
}

int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
    int reach = startFuel, i = 0, stops = 0;

    priority_queue<int> pq;

    while(reach < target) {
        while(i < stations.size() and stations[i][0] <= reach) {
            pq.push(stations[i][1]);
            i++;
        }

        if(pq.empty()) return -1;

        reach += pq.top();
        pq.pop();

        stops++;
    }

    return stops;
}

int profitableSchemes3DDP(int n, int minProfit, vector<int>& group, vector<int>& profit) {
    int m = group.size(), mod = 1e9 + 7;

    vector<vector<vector<int>>> dp(m + 1, vector<vector<int>>(n + 1, vector<int>(minProfit + 1)));

    dp[0][0][0] = 1;

    for(int i = 1; i <= m; i++) {
        for(int j = 0; j <= n; j++) {
            for(int k = 0; k <= minProfit; k++) {
                int skip = dp[i - 1][j][k], commit = 0;

                if(j - group[i - 1] >= 0) {
                    commit = dp[i - 1][j - group[i - 1]][max(0, k - profit[i - 1])];
                }

                dp[i][j][k] = (skip + commit) % mod;
            }
        }
    }

    int ans = 0;

    for(int j = 0; j <= n; j++) {
        ans = (ans + dp[m][j][minProfit]) % mod;
    }

    return ans;
}

int profitableSchemes2DDP(int n, int minProfit, vector<int>& group, vector<int>& profit) {
    int m = group.size(), mod = 1e9 + 7;

    vector<vector<int>> prev(n + 1, vector<int>(minProfit + 1));

    prev[0][0] = 1;

    for(int i = 1; i <= m; i++) {
        vector<vector<int>> curr(n + 1, vector<int>(minProfit + 1));

        for(int j = 0; j <= n; j++) {
            for(int k = 0; k <= minProfit; k++) {
                int skip = prev[j][k], commit = 0;

                if(j - group[i - 1] >= 0) {
                    commit = prev[j - group[i - 1]][max(0, k - profit[i - 1])];
                }

                curr[j][k] = (skip + commit) % mod;
            }
        }

        prev = curr;
    }

    int ans = 0;

    for(int j = 0; j <= n; j++) {
        ans = (ans + prev[j][minProfit]) % mod;
    }

    return ans;
}

int main() {
    int n = 10, minProfit = 5;
    vector<int> group = {2,3,5}, profit = {6,7,8};

    cout << profitableSchemes2DDP(n, minProfit, group, profit) << endl;
    return 0;
}