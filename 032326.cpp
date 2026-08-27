#include<bits/stdc++.h>
using namespace std;

int countSubstringsBrute(string s, string t) {
    int sLen = s.length(), tLen = t.length();

    unordered_map<string, int> substringFrequencyMapping;

    for(int i = 0; i < tLen; i++) {
        for(int j = i; j < tLen; j++) {
            string sub = t.substr(i, j - i + 1);
            substringFrequencyMapping[sub]++;
        }
    }

    int count = 0;
    
    for(int i = 0; i < sLen; i++) {
        for(int j = i; j < sLen; j++) {
            string sub = s.substr(i, j - i + 1);
            for(int k = 0; k < sub.length(); k++) {
                string subCopy = sub;
                for(char ch = 'a'; ch <= 'z'; ch++) {
                    subCopy[k] = ch;
                    if(subCopy == sub) {
                        continue;
                    }
                    count += substringFrequencyMapping[subCopy];
                }
            }
        }
    }

    return count;

}

int countSubstrings(string s, string t) {
    int n = s.length(), m = t.length();
    int count = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {

            int mismatch = 0;

            for(int k = 0; i + k < n and j + k < m; k++) {

                if(s[i + k] != t[j + k]) {
                    mismatch++;
                }

                if(mismatch == 1) {
                    count++;
                } else if(mismatch > 1) {
                    break;
                }

            }
        }
    }

    return count;
}

int findMaximumXORBrute(vector<int>& nums) {
    int n = nums.size(), maxi = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            maxi = max(maxi, nums[i] ^ nums[j]);
        }
    }
    return maxi;
}

class Solution {
    private:

    class Trie {
        private:

        class TrieNode {
            private:

            TrieNode* children[2];

            public:

            TrieNode() {
                this->children[0] = this->children[1] = NULL;
            }

            bool containsBit(int bit) {
                return this->children[bit] != NULL;
            }

            void addBit(int bit, TrieNode* address) {
                this->children[bit] = address;
            }

            TrieNode* moveTo(int bit) {
                return this->children[bit];
            }

        };

        TrieNode* root;

        public:

        Trie() {
            this->root = new TrieNode();
        }

        void addNum(int num) {
            TrieNode* node = this->root;

            for(int i = 31; i >= 0; i--) {
                int bit = (num >> i) & 1;

                if(!node->containsBit(bit)) {
                    node->addBit(bit, new TrieNode());
                }

                node = node->moveTo(bit);

            }
        }

        int getMaxXOR(int num) {
            int maxi = 0;
            TrieNode* node = this->root;

            for(int i = 31; i >= 0; i--) {
                int bit = (num >> i) & 1;
                int opposite = !bit;

                if(node->containsBit(opposite)) {
                    maxi |= (1 << i);
                    node = node->moveTo(opposite);
                } else {
                    node = node->moveTo(bit);
                }

            }

            return maxi;

        }

    };

    public:
    int findMaximumXOR(vector<int>& nums) {
        Trie* t = new Trie();

        for(auto num : nums) {
            t->addNum(num);
        }

        int ans = 0;

        for(auto num : nums) {
            ans = max(ans, t->getMaxXOR(num));
        }

        return ans;

    }
};

int main() {
    
    return 0;
}