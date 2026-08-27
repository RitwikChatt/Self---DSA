#include<bits/stdc++.h>
using namespace std;

class WordDictionary {
public:

    class TrieNode {

        public:

        TrieNode* children[26];
        bool isEnd;

        TrieNode() {
            for(int i = 0; i < 26; i++) {
                this->children[i] = NULL;
            }

            this->isEnd = false;
        }

        bool containsLetter(char letter) {
            return this->children[letter - 'a'] != NULL;
        }

        void addLetter(char letter, TrieNode* address) {
            this->children[letter - 'a'] = address;
        }

        TrieNode* moveTo(char letter) {
            return this->children[letter - 'a'];
        }

        void markWordEnd() {
            this->isEnd = true;
        }

        bool isWordEndingHere() {
            return this->isEnd;
        }

    };
    
    TrieNode* root;

    WordDictionary() {
        root = new TrieNode();
    }
    
    void addWord(string word) {
        TrieNode* node = root;

        for(char letter : word) {
            if(!node->containsLetter(letter)) {
                node->addLetter(letter, new TrieNode());
            }
            node = node->moveTo(letter);
        }

        node->markWordEnd();

    }

    bool searchUtil(int index, string& word, TrieNode* node) {
        if(index == word.length()) {
            return node->isWordEndingHere();
        }

        char letter = word[index];

        if(letter != '.') {
            if(!node->containsLetter(letter)) {
                return false;
            }
            return searchUtil(index + 1, word, node->moveTo(letter));
        }

        for(int i = 0; i < 26; i++) {
            char letter = 'a' + i;
            if(node->containsLetter(letter)) {
                if(searchUtil(index + 1, word, node->moveTo(letter))) {
                    return true;
                }
            }
        }

        return false;

    }
    
    bool search(string word) {
        return searchUtil(0, word, this->root);
    }
};

// class WordFilter {
// private:
//     vector<string> words;
    
// public:
//     WordFilter(vector<string>& words) {
//         this->words = words;
//     }
    
//     int f(string pref, string suff) {
//         int n = words.size(), prefLen = pref.length(), suffLen = suff.length();

//         for(int i = n - 1; i >= 0; i--) {
//             string word = words[i];
//             int len = word.length();
            
//             if(prefLen > len or suffLen > len) {
//                 continue;
//             }

//             if(word.substr(0, prefLen) == pref and word.substr(len - suffLen) == suff) {
//                 return i;
//             }

//         }

//         return -1;

//     }
// };

// class WordFilter {

// private:
//     unordered_map<string, int> prefixPlusSuffixVSIndexMapping;

// public:
//     WordFilter(vector<string>& words) {
//         int n = words.size();

//         for(int i = 0; i < n; i++) {
//             string word = words[i];
//             int wordLen = word.length();

//             for(int j = 0; j <= wordLen; j++) {
//                 string prefix = word.substr(0, j);

//                 for(int k = 0; k <= wordLen; k++) {
//                     string suffix = word.substr(wordLen - k);

//                     this->prefixPlusSuffixVSIndexMapping[prefix + '#' + suffix] = i;

//                 }

//             }

//         }

//     }
    
//     int f(string pref, string suff) {

//         if(this->prefixPlusSuffixVSIndexMapping.find(pref + '#' + suff) != this->prefixPlusSuffixVSIndexMapping.end()) {
//             return prefixPlusSuffixVSIndexMapping[pref + '#' + suff];
//         }

//         return -1;

//     }
// };

class WordFilter {

private:

    class Trie {

        private:

        class TrieNode {

            private:

            TrieNode* links[27];
            bool isEnd;
            int index;

            public:

            TrieNode() {

                for(int i = 0; i < 27; i++) {
                    this->links[i] = NULL;
                }

                this->isEnd = false;
                this->index = -1;

            }

            bool containsCharacter(char ch) {
                return ch == '#' ? this->links[26] != NULL : this->links[ch - 'a'] != NULL;
            }

            void addCharacter(char ch, TrieNode* address) {
                ch == '#' ? this->links[26] = address : this->links[ch - 'a'] = address;
            }

            TrieNode* moveTo(char ch) {
                return ch == '#' ? this->links[26] : this->links[ch - 'a'];
            }

            void markWordEnd() {
                this->isEnd = true;
            }

            bool isWordEndingHere() {
                return this->isEnd;
            }

            void setIndex(int index) {
                this->index = index;
            }

            int getIndex() {
                return this->index;
            }

        };

        TrieNode* root;

        public:

        Trie() {
            root = new TrieNode();
        }

        void addWord(string word, int index) {
            TrieNode* node = this->root;

            for(char ch : word) {

                if(!node->containsCharacter(ch)) {
                    TrieNode* newNode = new TrieNode();
                    newNode->setIndex(index);
                    node->addCharacter(ch, newNode);
                }

                node = node->moveTo(ch);
                node->setIndex(index);

            }

            node->markWordEnd();

        }

        int searchPrefix(string word) {
            TrieNode* node = this->root;

            for(char ch : word) {
                if(!node->containsCharacter(ch)) {
                    return -1;
                }
                node = node->moveTo(ch);
            }

            return node->getIndex();

        }

    };

    Trie* t;

public:
    WordFilter(vector<string>& words) {
        this->t = new Trie();

        int n = words.size();

        for(int i = 0; i < n; i++) {
            string word = words[i];
            int wordLen = word.length();

            for(int j = 1; j <= wordLen; j++) {
                string suffix = word.substr(wordLen - j);

                this->t->addWord(suffix + '#' + word, i);

            }

        }

    }
    
    int f(string pref, string suff) {

        return this->t->searchPrefix(suff + '#' + pref);
    
    }   

};

int main() {
    
    return 0;
}