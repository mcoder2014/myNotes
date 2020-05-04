#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

using namespace std;

class TrieNode {

public:
    TrieNode():isEnd(false) {}
    unordered_map<char, shared_ptr<TrieNode>> childs;
    bool isEnd;
};

class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        root = make_shared<TrieNode>();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        shared_ptr<TrieNode> node = root;
        for(int i = 0; i < word.size(); i++) {
            if(node->childs.find(word[i]) != node->childs.end()) {
                node = node->childs[word[i]];
            } else {
                node->childs[word[i]] = make_shared<TrieNode>();
                node = node->childs[word[i]];
            }
        }
        if(word.size() > 0) {
            node->isEnd = true;
        }
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        shared_ptr<TrieNode> node = root;
        for(int i = 0; i < word.size(); i++) {
            if(node->childs.find(word[i]) != node->childs.end()) {
                node = node->childs[word[i]];
            } else {
                return false;
            }
        }
        return node->isEnd;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        shared_ptr<TrieNode> node = root;
        for(int i = 0; i < prefix.size(); i++) {
            if(node->childs.find(prefix[i]) != node->childs.end()) {
                node = node->childs[prefix[i]];
            } else {
                return false;
            }
        }
        return true;
    }
private:
    shared_ptr<TrieNode> root;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

int main()
{
    return 0;
}