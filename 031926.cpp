#include<bits/stdc++.h>
using namespace std;

// class Trie {

//     public:

//     class TrieNode {

//         public:

//         TrieNode* links[26];
//         bool flag = false;

//         bool containsChar(char ch) {
//             return this->links[ch - 'a'] != NULL;
//         }

//         void addCharacter(char ch) {
//             this->links[ch - 'a'] = new TrieNode();
//         }

//         TrieNode* move(char ch) {
//             return this->links[ch - 'a'];
//         }

//         void setFlag() {
//             this->flag = true;
//         }

//         bool isFlagTrue() {
//             return this->flag;
//         }

//     };

//     TrieNode* root;

//     Trie() {
//         root = new TrieNode();
//     }

//     void insertWord(string s) {
//         TrieNode* node = this->root;

//         for(char ch : s) {
//             if(!node->containsChar(ch)) {
//                 node->addCharacter(ch);
//             }
//             node = node->move(ch);
//         }

//         node->setFlag();

//     }

//     bool searchWord(string s) {
//         TrieNode* node = this->root;

//         for(char ch : s) {
//             if(!node->containsChar(ch)) {
//                 return false;
//             }
//             node = node->move(ch);
//         }

//         return node->isFlagTrue();

//     }

//     bool searchPrefix(string s) {
//         TrieNode* node = this->root;
        
//         for(char ch : s) {
//             if(!node->containsChar(ch)) {
//                 return false;
//             }
//             node = node->move(ch);
//         }

//         return true;

//     }
// };

class Trie {
public:

    class TrieNode {
        public:

        TrieNode* links[26];
        bool flag = false;

        bool containCharacter(char ch) {
            return this->links[ch - 'a'] != NULL;
        }

        void addCharacter(char ch) {
            this->links[ch - 'a'] = new TrieNode();
        }

        TrieNode* move(char ch) {
            return this->links[ch - 'a'];
        }

        void setFlag() {
            this->flag = true;
        }

        bool isFlagSet() {
            return this->flag;
        }

    };

    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* node = this->root;

        for(char ch : word) {
            if(!node->containCharacter(ch)) {
                node->addCharacter(ch);
            }
            node = node->move(ch);
        }

        node->setFlag();

    }
    
    bool search(string word) {
        TrieNode* node = this->root;

        for(char ch : word) {
            if(!node->containCharacter(ch)) {
                return false;
            }
            node = node->move(ch);
        }

        return node->isFlagSet();

    }
    
    bool startsWith(string prefix) {
        TrieNode* node = this->root;

        for(char ch : prefix) {
            if(!node->containCharacter(ch)) {
                return false;
            }
            node = node->move(ch);
        }

        return true;

    }

};

int main() {
    return 0;
}