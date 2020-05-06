#include <string>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <deque>

using namespace std;
class TrieNode {

public:
    TrieNode():isEnd(false) {}
    unordered_map<char, shared_ptr<TrieNode>> childs;
    bool isEnd;
};


class WordDictionary {
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        root = make_shared<TrieNode>();
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
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
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        if(word.size() == 0) {
            return false;
        }

        deque<shared_ptr<TrieNode>> nodeList;
        nodeList.push_back(root);
        nodeList.push_back(nullptr);

        shared_ptr<TrieNode> node;
        for(int i = 0; i < word.size(); i++) {
            while(nodeList.size() >0) {
                node = nodeList[0];
                nodeList.pop_front();

                if(node == nullptr && nodeList.size() == 0) {
                    return false;
                } else if (node == nullptr && i != word.size() - 1) {
                    nodeList.push_back(nullptr);
                    break;
                } else if(node == nullptr) {
                    break;
                }

                if(word[i] == '.') {
                    for(auto& item:node->childs) {
                        nodeList.push_back(item.second);
                    }
                } else if (node->childs.find(word[i]) != node->childs.end()) {
                    nodeList.push_back(node->childs[word[i]]);
                }
            }
        }
        
        for(shared_ptr<TrieNode> node:nodeList) {
            if(node != nullptr && node->isEnd) {
                return true;
            }
        }
        return false;
    }

private:
    shared_ptr<TrieNode> root;
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */

int main()
{
    WordDictionary wordDictionary;
    wordDictionary.addWord("bad");
    wordDictionary.addWord("pad");
    wordDictionary.addWord("mad");

    auto search = [&](string str) {
        cout << str << " " << wordDictionary.search(str) << endl;
    };


    search("bad");
    search("dad");
    search("");
    search("..d");

    return 0;
}